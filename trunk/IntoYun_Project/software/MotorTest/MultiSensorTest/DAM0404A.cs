using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ControlPoxy;
using System.Threading;

namespace MultiSensorTest
{
    public partial class DAM0404A : UserControl
    {
        private bool b_jdq1 = false;
        private bool b_jdq2 = false;
        private bool b_jdq3 = false;
        private bool b_jdq4 = false;

        private bool b_ReadAddressOK = false;
        private bool b_SerialEable = false;

        private byte address;
        private string sysCondigIni = System.Environment.CurrentDirectory + "\\SysConfig.ini";
        private Thread dataHandler;

        private String ComPort = "COM1";
        private string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置

        private ConfigIni st_ConfigIni = new ConfigIni();
        private Serial_Proxy st_Serial_Proxy = new Serial_Proxy();
        private CRC_Proxy st_CRC_Proxy = new CRC_Proxy();
        private Util_Proxy st_Util_Proxy = new Util_Proxy();

        #region system init
        public DAM0404A()
        {
            InitializeComponent();
        }

        public void DAM0404A_Stop()
        {
            if (b_SerialEable)
            {
                st_Serial_Proxy.SerialPort_Stop();
                dataHandler.Abort();
            }
        }

        private void DAM0404A_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            Serial_ConfigInit();
            SerialPort_IniInit();
            b_ReadAddressOK = false;
            Button_Ctrl(b_ReadAddressOK);

            radioButton_ascll.Checked = true;
            radioButton_RecvAscll.Checked = true;
            groupBox_Receive.Enabled = false;
            groupBox_Send.Enabled = false;
            checkBox_Status.Checked = true;

            textBox_SendInterVal.Text = "1000";
            textBox_jdqAddress.Text = "1";
            textBox_channel.Text = "1";
            radioButton_off.Checked = true;

        }

        private void Button_Ctrl( bool b_res )
        {
            if (b_res)
            {
                button_jdq1.Enabled = true;
                button_jdq2.Enabled = true;
                button_jdq3.Enabled = true;
                button_jdq4.Enabled = true;

                button_Send.Enabled = true;
                radioButton_hex.Enabled = true;
                radioButton_ascll.Enabled = true;

                button_self.Enabled = true;

                groupBox_controlMode.Enabled = true;

            }
            else
            {
                button_jdq1.Enabled = false;
                button_jdq2.Enabled = false;
                button_jdq3.Enabled = false;
                button_jdq4.Enabled = false;

                button_Send.Enabled = false;
                radioButton_hex.Enabled = false;
                radioButton_ascll.Enabled = false;
                button_self.Enabled = false;

                groupBox_controlMode.Enabled = false; 
            }
        }
        #endregion

        #region 串口控制

        private void Serial_ConfigInit()
        {
            int baudIndex = 0;
            string[] port = System.IO.Ports.SerialPort.GetPortNames();//搜索PC可用的串口号 

            if (port != null)
            {
                comboBox_ComPort.Items.Clear();
                foreach (string cName in port)
                {
                    comboBox_ComPort.Items.Add(cName);
                    if (cName == ComPort)
                    {
                        comboBox_ComPort.SelectedIndex = baudIndex;
                    }
                    baudIndex++;
                }
            }

            //波特率
            comboBox_Baud.Items.Clear();
            foreach (string cName in StringBaud)
            {
                comboBox_Baud.Items.Add(cName);
            }
            comboBox_Baud.SelectedIndex = 0;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Serial_ConfigInit();
        }

        private void Monitor_String( byte []buff, int len )
        {
            if (len > 0)
            {
                byte[] buffExt = new byte[st_Serial_Proxy.DataLength];
                Array.Copy(st_Serial_Proxy.RtBuff, 0, buffExt, 0, st_Serial_Proxy.DataLength);
                string s = System.Text.Encoding.ASCII.GetString(buffExt);
                string str = "Recv:" + s + "\r\n";
                Montior_printString(str );
            }
        }

        private void Montior_printString( string str )
        {
            textBox_receive.AppendText(str);
        }

        private void DataCommandHander()
        {
            bool res = false;
            while (true)
            {
                if (st_Serial_Proxy.b_SerialReceiveReady)
                {
                    st_Serial_Proxy.b_SerialReceiveReady = false;
                    if (st_Serial_Proxy.DataLength > 0)
                    {
                        res = ReceiveMode_forMontior(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                        if ( res == false )
                        {
                            //for light 
                            res = LightCmd_Parser(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                            if( res )
                            {
                                st_Serial_Proxy.DataLength = 0;
                            }

                            res = jdq_ReceiveBoolParer(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                            if (res)
                            {
                                Monitor_Display(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, true);    /* 数据监控 */
                                st_Serial_Proxy.DataLength = 0;
                            }

                            //for jdq control 
                            res = jdq_ReceiveParer(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                            if (res)
                            {
                                Monitor_Display(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, true);    /* 数据监控 */
                                st_Serial_Proxy.DataLength = 0;
                            }

                            //Presence sensor: ID
                            res = Presence_IDParser(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                            if (res)
                            {
                                byte[] buff = new byte[st_Serial_Proxy.DataLength];
                                Array.Copy(st_Serial_Proxy.RtBuff, 0, buff, 0, st_Serial_Proxy.DataLength);
                                string str = System.Text.Encoding.ASCII.GetString(buff) + "\r\n";
                                Moitor_String(str, true );
                                st_Serial_Proxy.DataLength = 0;
                            }

                            //Presence sensor: value
                            res = Presence_ReadValue(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                            if (res)
                            {
                                byte[] buff = new byte[st_Serial_Proxy.DataLength];
                                Array.Copy(st_Serial_Proxy.RtBuff, 0, buff, 0, st_Serial_Proxy.DataLength);
                                string str = System.Text.Encoding.ASCII.GetString(buff) + "\r\n";
                                Moitor_String(str, true);

                                st_Serial_Proxy.DataLength = 0;
                            }
                        }

                        st_Serial_Proxy.DataLength = 0;
                    }
                }
            }
        }

        private void button_Enable_Click(object sender, EventArgs e)
        {
            bool res = false;
            st_Serial_Proxy.Baud = int.Parse(comboBox_Baud.Text);    //设置Baud
            st_Serial_Proxy.Comport = comboBox_ComPort.Text;         //获取端口号
            st_Serial_Proxy.Parity = System.IO.Ports.Parity.None;
            st_Serial_Proxy.TimeOut = 100;

            if (b_SerialEable == false)
            {
                res =  st_Serial_Proxy.SerialPort_Start();
                if (res)
                {
                    button_Enable.Text = "关闭串口";
                    b_SerialEable = true;
                    comboBox_Baud.Enabled = false;
                    comboBox_ComPort.Enabled = false;
                    dataHandler = new Thread(DataCommandHander);
                    dataHandler.Start();
                }
            }
            else
            {
                button_Enable.Text = "打开串口";
                b_SerialEable = false;
                comboBox_Baud.Enabled = true;
                comboBox_ComPort.Enabled = true;
                st_Serial_Proxy.SerialPort_Stop();
                dataHandler.Abort();
            }

            Button_Ctrl( b_SerialEable );
            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Sensor_Serial", "Baud", st_Serial_Proxy.Baud.ToString());
            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Sensor_Serial", "Port", st_Serial_Proxy.Comport);
        }

        private void button_ClearBuff_Click(object sender, EventArgs e)
        {
            textBox_Send.Clear();
        }

        private void button_ClearReciveBuff_Click(object sender, EventArgs e)
        {
            textBox_receive.Clear();
        }
        private void Monitor_Printf(byte[] data, int length)
        {
            if (length > 0)
            {
                string s = "";
                for (int i = 0; i < length; i++)
                {
                    s += data[i].ToString("X2");
                    s += " ";
                }
                Montior_printString(s);
            }
        }

        private void SerialPort_IniInit()
        {
            try
            {
                st_Serial_Proxy.Baud = Convert.ToInt32(st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Sensor_Serial", "Baud"));
                st_Serial_Proxy.Comport = st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Sensor_Serial", "Port");

                comboBox_ComPort.Text = st_Serial_Proxy.Comport;
                comboBox_Baud.Text = st_Serial_Proxy.Baud.ToString();
            }
            catch
            {
            }
        }

        private void Monitor_Display(byte[] buff, int lenght, bool type)
        {
            string LogdateTextstring = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss fff");
            string str = "\r\n【 " + LogdateTextstring + " 】";

            Montior_printString(str);
            if (type)
                Montior_printString(" Recv:" + "\r\n");
            else
                Montior_printString(" Send:" + "\r\n");

            Monitor_Printf(buff, lenght);
            Montior_printString("\r\n");
        }

        private void Moitor_String(string str, bool type)
        {
            string LogdateTextstring = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss fff");

            string strTmp = "\r\n【 " + LogdateTextstring + " 】";

            Montior_printString(strTmp);
            if (type)
                Montior_printString(" Recv:" + "\r\n");
            else
                Montior_printString(" Send:" + "\r\n");

            Montior_printString(str + "\r\n");
        }

        #endregion

        #region jdq button control

        private void jdq_Ctrl( byte channel, byte status )
        {
            byte[] Cmd = new byte[] { 0x0F, 0x05, 0, 0, 0xFF, 0, 0x8D, 0x14 };
            int crc;

            Cmd[0] = address;
            Cmd[3] = channel;
            Cmd[4] = status;
            crc = st_CRC_Proxy.CRC16(Cmd, 6);
            Cmd[6] = (byte)crc;
            Cmd[7] = (byte)(crc >> 8);

            st_Serial_Proxy.SerialSend(Cmd, Cmd.Length);
            Monitor_Display(Cmd, Cmd.Length, false);
    }

        private void jdq_Ctrl(byte address, byte channel, byte status)
        {
            byte[] Cmd = new byte[] { 0x0F, 0x05, 0, 0, 0xFF, 0, 0x8D, 0x14 };
            int crc;

            Cmd[0] = address;
            Cmd[3] = channel;
            Cmd[4] = status;
            crc = st_CRC_Proxy.CRC16(Cmd, 6);
            Cmd[6] = (byte)crc;
            Cmd[7] = (byte)(crc >> 8);
            st_Serial_Proxy.SerialSend(Cmd, Cmd.Length);
            Monitor_Display(Cmd, Cmd.Length, false);
        }

        private void jdq_readBoolValueResponse()
        {
            byte[] Cmd = new byte[] { 0x0F, 0x02, 0x01, 0, 0xFF, 0 };
            byte address = 0;
            byte boolValue = 0;
            int crc;

            if (textBox_ReadAddress.Text != "")
            {
                address = (byte)(int.Parse(textBox_ReadAddress.Text));
            }
            Cmd[0] = address;

            if (textBox_jdqbool.Text != "")
            {
                boolValue = (byte)(int.Parse(textBox_jdqbool.Text));
            }
            Cmd[3] = boolValue;

            crc = st_CRC_Proxy.CRC16(Cmd, 4);
            Cmd[4] = (byte)crc;
            Cmd[5] = (byte)(crc >> 8);
            st_Serial_Proxy.SerialSend(Cmd, Cmd.Length);
            Monitor_Display(Cmd, Cmd.Length, false);
        }


        private void button_ReadAddress_Click(object sender, EventArgs e)
        {
            byte[] Cmd = new byte[] { 0xfe, 0x04, 0x03, 0xe8, 0, 0x01, 0x55, 0xEA };
            int crc = st_CRC_Proxy.CRC16(Cmd, 6);

            Cmd[6] = (byte)crc;
            Cmd[7] = (byte)(crc >> 8);
            st_Serial_Proxy.SerialSend(Cmd, Cmd.Length);
            Monitor_Display(Cmd, Cmd.Length, false);
            System.Threading.Thread.Sleep(500);
            int calCrc = st_CRC_Proxy.CRC16(st_Serial_Proxy.RtBuff, 6);
            int RecCrc = (int)(st_Serial_Proxy.RtBuff[7] << 8 | st_Serial_Proxy.RtBuff[6]);
            if( calCrc == RecCrc )
            {
                address = st_Serial_Proxy.RtBuff[4];
                textBox_Address.Text = st_Serial_Proxy.RtBuff[4].ToString();
                b_ReadAddressOK = true;
                Button_Ctrl(b_ReadAddressOK);
            }
        }

        private void button_jdq1_Click(object sender, EventArgs e)
        {
            byte addres = 0xff;

            button_jdq1.Enabled = false;
            if (b_jdq1)
            {
                addres = 0;
            }

            jdq_Ctrl(0, addres);
            button_jdq1.Enabled = true;
        }

        private void button_jdq2_Click(object sender, EventArgs e)
        {
            byte addres = 0xff;

            button_jdq2.Enabled = false;
            if (b_jdq2)
            {
                addres = 0;
            }
            jdq_Ctrl(1, addres);
            button_jdq2.Enabled = true;
        }

        private void button_jdq3_Click(object sender, EventArgs e)
        {
            byte addres = 0xff;

            button_jdq3.Enabled = false;
            if (b_jdq3)
            {
                addres = 0;
            }
            jdq_Ctrl(2, addres);
            button_jdq3.Enabled = true;
        }

        private void button_jdq4_Click(object sender, EventArgs e)
        {
            byte addres = 0xff;

            button_jdq4.Enabled = false;
            if (b_jdq4)
            {
                addres = 0;
            }
            jdq_Ctrl(3, addres);
            button_jdq4.Enabled = true;
        }

        private bool jdq_ReceiveParer(byte[] buff, int length)
        {
            if (length >= 6)
            {
                int calCrc = st_CRC_Proxy.CRC16(buff, 6);
                int RecCrc = (int)(buff[7] << 8 | buff[6]);
                if (calCrc == RecCrc)
                {
                    st_Serial_Proxy.SerialSend(buff, 8);
                    Monitor_Display(buff, 8, false);
                    return true;
                }
            }

            return false;
        }

        private bool jdq_ReceiveBoolParer(byte[] buff, int length)
        {
            if (length >= 6)
            {
                int calCrc = st_CRC_Proxy.CRC16(buff, 6);
                int RecCrc = (int)(buff[7] << 8 | buff[6]);
                if (calCrc == RecCrc)
                {
                    if (buff[1] == 0x02)
                    {
                        jdq_readBoolValueResponse();
                        Monitor_Display(buff, 8, true);
                        return true;
                    }
                }
            }

            return false;
        }


        #endregion

        #region 灯控制
        private bool LightCmd_Parser(byte[] packet, int len)
        {
            if (len > 0)
            {
                if (packet[0] == 0x1a && packet[1] == 0 &&
                    packet[2] == 0 && (packet[4] > 0))
                {
                    LED_StatusFresh(packet[4], packet[5]);
                    Monitor_Display(packet, len, true);
                    return true;
                }
            }

            return false;
        }

        private void LED_StatusFresh(byte channel, byte status)
        {
            switch (channel)
            {
                case 1:
                    if (status == 0xff)
                    {
                        b_jdq1 = true;
                        this.pictureBox_jdq1.Image = global::MultiSensorTest.Properties.Resources.On;
                    }
                    else
                    {
                        b_jdq1 = false;
                        this.pictureBox_jdq1.Image = global::MultiSensorTest.Properties.Resources.Off;
                    }
                    break;
                case 2:
                    if (status == 0xff)
                    {
                        b_jdq2 = true;
                        this.pictureBox_jdq2.Image = global::MultiSensorTest.Properties.Resources.On;
                    }
                    else
                    {
                        b_jdq2 = false;
                        this.pictureBox_jdq2.Image = global::MultiSensorTest.Properties.Resources.Off;
                    }
                    break;
                case 3:
                    if (status == 0xff)
                    {
                        b_jdq3 = true;
                        this.pictureBox_jdq3.Image = global::MultiSensorTest.Properties.Resources.On;
                    }
                    else
                    {
                        b_jdq3 = false;
                        this.pictureBox_jdq3.Image = global::MultiSensorTest.Properties.Resources.Off;
                    }
                    break;
                case 4:
                    if (status == 0xff)
                    {
                        b_jdq4 = true;
                        this.pictureBox_jdq4.Image = global::MultiSensorTest.Properties.Resources.On;
                    }
                    else
                    {
                        b_jdq4 = false;
                        this.pictureBox_jdq4.Image = global::MultiSensorTest.Properties.Resources.Off;
                    }
                    break;
            }
        }

        #endregion

        #region 模拟人体检测sensor

        private bool Presence_IDParser( byte[] packet, int len)
        {
            string str = "ID=1E23DCA0\r\n";

            if (len > 0)
            {
                if (packet[0] == 'I' && packet[1] == 'D' &&
                    packet[2] == '=' && packet[3] == '?')
                {
                    byte[] ID = System.Text.Encoding.ASCII.GetBytes(str);
                    st_Serial_Proxy.SerialSend(ID, ID.Length);
                    Moitor_String(str, false);
                    return true;
                }
            }

            return false;
        }

        private bool Presence_ReadValue(byte[] packet, int len )
        {
            string str = "ID=1E23DCA0 ";

            if (len > 0)
            {
                if (packet[0] == 'I' && packet[1] == 'D' && packet[2] == '=' )
                {
                    for (int i = 0; i < len; i++)
                    {
                        if (packet[3 + i] == 'B' && packet[3 + i + 1] == 'T' && packet[3 + i + 2] == '=')
                        {
                            if(radioButton_off.Checked )
                            {
                                str += "BT=" + "0";
                            }
                            else
                            {
                                str += "BT=" + "1";
                            }
                            byte[] ID = System.Text.Encoding.ASCII.GetBytes(str);
                            st_Serial_Proxy.SerialSend(ID, ID.Length);
                            Moitor_String(str, false);
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        #endregion

        #region send command

        void Send_packet()
        {
            if (b_SerialEable)
            {
                byte[] data;
                string str = "";
                string strRead = textBox_Send.Text;
 
                if (strRead.Length > 0)
                {
                    //Remove space 
                    if (checkBox_RemoveSapce.Checked)
                    {
                       str = strRead.Replace(" ", "");
                    }
                    else
                    {
                        str = strRead;
                    }

                    if (radioButton_hex.Checked)   //ascll format
                    {
                        try
                        {
                            data = st_Util_Proxy.GetByteArray(str);
                        }
                        catch {
                            MessageBox.Show("请输入正确的hex数据：字符串范围（ 0~f） ");
                            return;
                        }
                    }
                    else    //BIN format
                    {
                        data = System.Text.Encoding.Default.GetBytes(str);
                    }

                    st_Serial_Proxy.SerialSend(data, data.Length);
                }
            }
        }

        private void button_Send_Click(object sender, EventArgs e)
        {
            Send_packet();
        }

        #endregion


        #region  montior Acttion

        private void checkBoxStatus_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_Status.Checked)
            {
                checkBox_Status.Text = "ON";
            }
            else
            {
                checkBox_Status.Text = "OFF";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox_jdqAddress.Text == "")
            {
                MessageBox.Show("请输入正确的地址");
                return;
            }

            if (textBox_channel.Text == "")
            {
                MessageBox.Show("请选择正确通道");
                return;
            }

            if (b_SerialEable)
            {
                byte status = 0;
                byte addres = (byte)int.Parse(textBox_jdqAddress.Text);
                byte channel = (byte)int.Parse(textBox_channel.Text);
                if (checkBox_Status.Checked)
                {
                    status = 0xff;
                }
                else
                {
                    status = 0;
                }

                jdq_Ctrl(channel, addres, status);
            }
        }

        private bool ReceiveMode_forMontior( byte []data, int len )
        {
            string str = "";

            if ( checkBox_Montior.Checked )
            {
                if(checkBox_feedTime.Checked )
                {
                    string dateTextstring = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss fff");
                    str += dateTextstring+ " ";
                }

                if (radioButton_Recvhex.Checked)  //hex 模式显示 
                {
                    for (int i = 0; i < len; i++)
                    {
                        str += data[i].ToString("X2");
                        str += " ";
                    }

                }
                else
                {
                    byte[] dathex = new byte[len];
                    Array.Copy(data, 0, dathex, 0, len);
                    str += System.Text.Encoding.ASCII.GetString(dathex);
                }

                if (checkBox_Autoline.Checked)
                {
                    str += "  \r\n";
                }

                Montior_printString(str);

                return true;
            }

            return false;
        }

        private void timerAct_Tick(object sender, EventArgs e)
        {
            Send_packet();
        }

        private void sendMode_Monitor()
        {

        }
        #endregion

        private void checkBox_Montior_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_Montior.Checked)
            {
                groupBox_Receive.Enabled = true;
                groupBox_Send.Enabled = true;
            }
            else
            {
                groupBox_Receive.Enabled = false;
                groupBox_Send.Enabled = false;
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_AutoSend.Checked)
            {
                if (textBox_SendInterVal.Text == "")
                {
                    timerAct.Interval = 100;
                }
                else
                {
                    timerAct.Interval = int.Parse(textBox_SendInterVal.Text);
                }
                timerAct.Start();
            }
            else {
                timerAct.Stop();
            }
        }

        private void richTextBox_MonitorReceive_TextChanged(object sender, EventArgs e)
        {
            textBox_receive.SelectionStart = textBox_receive.Text.Length; //Set the current caret position at the end
            textBox_receive.ScrollToCaret(); //Now scroll it automatically
        }

        private void DAM0404A_KeyDown(object sender, KeyEventArgs e)
        {
            string s = e.KeyValue.ToString();

            textBox_receive.AppendText("kEY DOWN "+s + "\r\n");
        }

        private void DAM0404A_KeyUp(object sender, KeyEventArgs e)
        {
            string s = e.KeyValue.ToString();

            textBox_receive.AppendText("kEY UP " + s + "\r\n");
        }

        private void DAM0404A_KeyPress(object sender, KeyPressEventArgs e)
        {
            string s = e.KeyChar.ToString();

            textBox_receive.AppendText("kEY PRESS " + s + "\r\n");
        }
    }
}

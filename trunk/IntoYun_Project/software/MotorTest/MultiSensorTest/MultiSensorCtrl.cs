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
    public partial class MultiSensorCtrl : UserControl
    {
        #region 变量定义区
        private byte presence_value;
        private int time_interval = 1000;
        private byte Modbusaddress;
        private byte step = 0xff;
        private bool b_ReadSensorValue = false;
        private bool b_PresenceSensorValue = false;
        private bool b_AllSensorValue = false;

        private short x, y;
        private string id = "";
        private string presenceResult = "";
        private bool b_SerialEable = false;
        private byte[] address = new byte[5];
        private string sysCondigIni = System.Environment.CurrentDirectory + "\\SysConfig.ini";
        private Thread dataHandler;

        private ConfigIni st_ConfigIni = new ConfigIni();
        private Serial_Proxy st_Serial_Proxy = new Serial_Proxy();
        private CRC_Proxy st_CRC_Proxy = new CRC_Proxy();
        private MCS_Protocol st_MCS_Protocol = new MCS_Protocol();
        private DeviceCtrl_Proxy st_DeviceCtrl_Proxy = new DeviceCtrl_Proxy();
        private Util_Proxy st_Util_Proxy = new Util_Proxy();

        private String ComPort = "COM1";
        private string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置
        #endregion

        #region System config
        public MultiSensorCtrl()
        {
            InitializeComponent();
        }

        public void MultiSensor_Stop()
        {
            if (b_SerialEable)
            {
                st_Serial_Proxy.SerialPort_Stop();
                dataHandler.Abort();
            }
        }

        private void MultiSensorCtrl_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            Serial_ConfigInit();
            SerialPort_IniInit();
            button_Contrl(b_SerialEable);

            timerSensor.Interval = time_interval;
            textBox_time.Text = time_interval.ToString();

            hScrollBar_yellow.Minimum = 0x25;
            hScrollBar_yellow.Maximum = 0xf0;

            hScrollBar_bright.Minimum = 0x25;
            hScrollBar_bright.Maximum = 0xf0;

            hScrollBar_bright.Value = 0x30;
            hScrollBar_yellow.Value = 0x30;
        }

        private void timeCtrl()
        {
            timerSensor.Interval = Convert.ToUInt16(textBox_time.Text);
            timerSensor.Start();
        }

        private void button_Contrl(bool b_ctrl)
        {
            if (b_ctrl)
            {
                button_PresenceSensor.Enabled = true;
                button_readPresenceData.Enabled = true;
                button_ReadAddr.Enabled = true;
                button_ReadValue.Enabled = true;
                button_modifyAddress.Enabled = true;
                button_ReadEnable.Enabled = true;
                textBox_time.Enabled = true;

                button_configAddress.Enabled = true;
                button_turnOnLight.Enabled = true;
                button_turnOff.Enabled = true;
                button_CheckStatus.Enabled = true;

                hScrollBar_yellow.Enabled = true;
                hScrollBar_bright.Enabled = true;
            }
            else
            {
                button_PresenceSensor.Enabled = false;
                button_readPresenceData.Enabled = false;
                button_ReadAddr.Enabled = false;
                button_ReadValue.Enabled = false;
                button_modifyAddress.Enabled = false;
                button_ReadEnable.Enabled = false;
                textBox_time.Enabled = false;

                button_configAddress.Enabled = false;
                button_turnOnLight.Enabled = false;
                button_turnOff.Enabled = false;
                button_CheckStatus.Enabled = false;

                hScrollBar_yellow.Enabled = false;
                hScrollBar_bright.Enabled = false;
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

        private void DataCommandHander()
        {
            while (true)
            {
                bool res = false;
                if (st_Serial_Proxy.b_SerialReceiveReady)
                {
                    st_Serial_Proxy.b_SerialReceiveReady = false;
                    if (st_Serial_Proxy.DataLength > 0)
                    {
                        Monitor_Display(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, true);    /* 数据监控 */
                        res = Presence_IDParser( st_Serial_Proxy.RtBuff );
                        if (res)
                        {
                            st_Serial_Proxy.DataLength = 0;
                        }

                        res = st_DeviceCtrl_Proxy.Presence_IDParser(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, out id, out presenceResult); /* 读取ID 和 结果 */
                        if (res)
                        {
                            textBox_PresenceID.Text = id;
                            textBox_PresenceRes.Text = presenceResult;
                            try
                            {
                                presence_value = Convert.ToByte(presenceResult);
                            }
                            catch { }
                        }

                        res = st_DeviceCtrl_Proxy.LightCtrl_AddressParser(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, address);
                        if (res)
                        {
                            st_Serial_Proxy.DataLength = 0;
                            textBox_Address.Text = st_Util_Proxy.ByteToString(address, 5);
                        }

                        res = st_DeviceCtrl_Proxy.InclinometerSenor_Parser(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, out x, out y);
                        if(res)
                        {
                            Modbusaddress = st_Serial_Proxy.RtBuff[0];
                            Printf_SensorValue();
                            textBox_ModbussAddress.Text = Modbusaddress.ToString();
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
                res = st_Serial_Proxy.SerialPort_Start();
                if( res )
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
                MultiSensor_Stop();
                button_Enable.Text = "打开串口";
                comboBox_Baud.Enabled = true;
                comboBox_ComPort.Enabled = true;
                b_SerialEable = false;
            }

            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Sensor_Serial", "Baud", st_Serial_Proxy.Baud.ToString());
            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Sensor_Serial", "Port", st_Serial_Proxy.Comport);

            button_Contrl(b_SerialEable);
        }

        private void button_ClearBuff_Click(object sender, EventArgs e)
        {
            richTextBox_Monitor.Clear();
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
                richTextBox_Monitor.AppendText(s + "\r\n");
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
            if (type)
                richTextBox_Monitor.AppendText("Recv:" + "\r\n");
            else
                richTextBox_Monitor.AppendText("Send:" + "\r\n");

            if (buff[0] == 'I' && buff[1] == 'D')
            {
                string str = System.Text.Encoding.ASCII.GetString(buff);
                richTextBox_Monitor.AppendText(str + "\r\n");
                return;
            }

            Monitor_Printf(buff, lenght);
        }

        private void Moitor_String(string str, bool type)
        {
            if (type)
                richTextBox_Monitor.AppendText("Recv:" + "\r\n");
            else
                richTextBox_Monitor.AppendText("Send:" + "\r\n");

            richTextBox_Monitor.AppendText(str + "\r\n");
        }
        #endregion

        #region 人体存在传感器
        private void button_PresenceSensor_Click(object sender, EventArgs e)
        {
            string id = "ID=?\r\n";
            byte[] byteArray = System.Text.Encoding.Default.GetBytes(id);

            st_Serial_Proxy.SerialSend(byteArray, byteArray.Length);
            Moitor_String(id, false);
        }

        private void button_ReadPresenceDataClick(object sender, EventArgs e)
        {
            if (b_PresenceSensorValue == false)
            {
                button_readPresenceData.Text = "读禁止";
                b_PresenceSensorValue = true;
                step = 2;
            }
            else
            {
                button_readPresenceData.Text = "读使能";
                b_PresenceSensorValue = false;
                step = 0xff;
            }
        }
        #endregion

        #region 倾角传感器
        private void button_ReadAddr_Click(object sender, EventArgs e)
        {
            byte[] CmdInit = new byte[] { 0, 0x03, 0, 0x5D, 0, 0x02, 0x55, 0xEA };

            int crc = st_CRC_Proxy.CRC16(CmdInit, 6);

            CmdInit[6] = (byte)crc;
            CmdInit[7] = (byte)(crc >> 8);
            st_Serial_Proxy.SerialSend(CmdInit, CmdInit.Length);
            Monitor_Display(CmdInit, CmdInit.Length, false);
        }

        private void button_modifyAddress_Click(object sender, EventArgs e)
        {
            byte[] CmdInit = new byte[] { 0, 0x06, 0, 0x03, 0, 0, 0x55, 0xEA };

            if (textBox_ModbussAddress.Text.Length > 0)
            {
                CmdInit[0] = Modbusaddress;
                CmdInit[5] = Convert.ToByte(textBox_ModbussAddress.Text);
                int crc = st_CRC_Proxy.CRC16(CmdInit, 6);
                CmdInit[6] = (byte)crc;
                CmdInit[7] = (byte)(crc >> 8);

                st_Serial_Proxy.SerialSend(CmdInit, CmdInit.Length);
                Monitor_Display(CmdInit, CmdInit.Length, false);
            }
        }

        private void button_ReadValue_Click(object sender, EventArgs e)
        {
            if (textBox_ModbussAddress.Text.Length > 0)
            {
                if (b_ReadSensorValue == false)
                {
                    button_ReadValue.Text = "读禁止";
                    b_ReadSensorValue = true;
                    step = 0;
                }
                else
                {
                    button_ReadValue.Text = "读使能";
                    b_ReadSensorValue = false;
                    step = 0xff;
                }
            }
        }

        private void timerAct_Tick(object sender, EventArgs e)
        {
            if (b_ReadSensorValue && b_SerialEable ||
                b_PresenceSensorValue && b_SerialEable ||
                b_AllSensorValue && b_SerialEable)
            {
                ReadSensor_ValueAction();
            }
        }

        private void Printf_SensorValue()
        {
            textBox_Value_X.Text = (x * 0.01).ToString("f2");
            textBox_Value_Y.Text = (y * 0.01).ToString("f2");
        }

        private void button_ReadEnable_Click(object sender, EventArgs e)
        {
            if (b_AllSensorValue == false)
            {
                button_ReadEnable.Text = "读禁止";
                b_AllSensorValue = true;
                step = 0;
                timeCtrl();
            }
            else
            {
                button_ReadEnable.Text = "读使能";
                b_AllSensorValue = false;
                step = 0xff;
            }

            b_ReadSensorValue = false;
            b_PresenceSensorValue = false;

            button_Contrl(!b_AllSensorValue);
            button_ReadEnable.Enabled = true;
        }

        private void ReadSensor_ValueAction()
        {
            switch (step)
            {
                case 0:
                    byte[] CmdInit = new byte[] { 0xC0, 0x65, 0x03, 0x04, 0, 0, 0, 0, 0, 0, 0xC0 };
                    st_Serial_Proxy.SerialSend(CmdInit, CmdInit.Length);
                    Monitor_Display(CmdInit, CmdInit.Length, false);
                    step = 1;
                    break;
                case 1:
                    byte[] CmdInitExt = new byte[] { 0x02, 0x03, 0, 0x5D, 0, 0x02, 0x55, 0xEA };

                    CmdInitExt[0] = Modbusaddress;
                    int crc = st_CRC_Proxy.CRC16(CmdInitExt, 6);
                    CmdInitExt[6] = (byte)crc;
                    CmdInitExt[7] = (byte)(crc >> 8);

                    st_Serial_Proxy.SerialSend(CmdInitExt, CmdInitExt.Length);
                    Monitor_Display(CmdInitExt, CmdInitExt.Length, false);

                    if (b_ReadSensorValue)
                    {
                        return;
                    }

                    if ((textBox_PresenceID.Text == "") || (textBox_PresenceID.Text == null))
                    {
                        step = 2;
                    }
                    else
                    {
                        step = 3;
                    }
                    break;
                case 2:
                    string cmd = "ID=?\r\n";
                    byte[] byteArray = System.Text.Encoding.Default.GetBytes(cmd);

                    st_Serial_Proxy.SerialSend(byteArray, byteArray.Length);
                    Moitor_String(cmd, false);
                    step = 3;
                    break;
                case 3:
                    string cmdExt = "ID=" + textBox_PresenceID.Text + " BT=?\r\n";
                    byte[] byteArrayExt = System.Text.Encoding.ASCII.GetBytes(cmdExt);

                    st_Serial_Proxy.SerialSend(byteArrayExt, byteArrayExt.Length);
                    Moitor_String(cmdExt, false);

                    if (!b_PresenceSensorValue)
                        step = 4;
                    break;
                case 4:
                    Light_ControlAction();
                    step = 1;
                    break;
                default:
                    break;
            }
        }
        #endregion

        #region 灯控制
        private bool check_address()
        {
            if (textBox_Address.Text == "")
            {
                richTextBox_Monitor.AppendText("请重新给控制器上电，获取设备地址！" + "\r\n");
                return false;
            }

            return true;
        }

        private void SendLightCtrl_Cmd(byte[] cmd)
        {
            bool res = check_address();
            if (res)
            {
                st_Serial_Proxy.SerialSend(cmd, cmd.Length);
                Monitor_Display(cmd, cmd.Length, false);
            }
        }

        /// <summary>
        /// 查询灯控制状态
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_CheckStatus_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[] { 0, 0, 0, 0, 0, 0x86, 0x86, 0x86, 0x0f };

            Buffer.BlockCopy(address, 0, cmd, 0, 5);
            SendLightCtrl_Cmd(cmd);
        }


        /// <summary>
        /// 开灯
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_turnOnLight_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[] { 0, 0, 0, 0, 0,
                                     0x01, 0x86, 0x01,
                                     0x01, 0x86, 0x01,
                                     0x0f };

            Buffer.BlockCopy(address, 0, cmd, 0, 5);
            SendLightCtrl_Cmd(cmd);
        }


        /// <summary>
        /// 关灯
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_turnOff_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[] { 0, 0, 0, 0, 0,
                                      0, 0x86, 0x01,
                                      0, 0x86, 0x01,
                                      0x0f };

            Buffer.BlockCopy(address, 0, cmd, 0, 5);
            SendLightCtrl_Cmd(cmd);
        }


        /// <summary>
        /// 配置地址
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_configAddress_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[] { 0,0,0,0,0,
                                      0xf8,0xe7,0xd6,
                                      0,0,0,0,0};
            byte[] newAddress = new byte[5];

            newAddress = st_Util_Proxy.GetByteArray(textBox_Address.Text);
            Buffer.BlockCopy(address, 0, cmd, 0, 5);
            Buffer.BlockCopy(newAddress, 0, cmd, 8, 5);
            SendLightCtrl_Cmd(cmd);
        }


        /// <summary>
        /// 调黄光
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void hScrollBar_yellow_Scroll(object sender, ScrollEventArgs e)
        {
            byte[] cmd = new byte[] { 0, 0, 0, 0, 0,
                                      0xff, 0x86, 0x01,
                                      0xff, 0x86, 0x01,
                                      0x0f };

            cmd[6] = (byte)hScrollBar_yellow.Value;
            cmd[9] = (byte)hScrollBar_bright.Value;

            Buffer.BlockCopy(address, 0, cmd, 0, 5);
            SendLightCtrl_Cmd(cmd);
        }

        /// <summary>
        /// 调白光
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void hScrollBar_bright_Scroll(object sender, ScrollEventArgs e)
        {
            byte[] cmd = new byte[] { 0, 0, 0, 0, 0,
                                      0xff, 0x86, 0x01,
                                      0xff, 0x86, 0x01,
                                      0x0f };

            cmd[6] = (byte)hScrollBar_yellow.Value;
            cmd[9] = (byte)hScrollBar_bright.Value;

            Buffer.BlockCopy(address, 0, cmd, 0, 5);
            SendLightCtrl_Cmd(cmd);
        }

        private void turnOn_Light()
        {
            byte[] cmd = new byte[] { 0, 0, 0, 0, 0,
                                      0xff, 0x86, 0x01,
                                      0xff, 0x86, 0x01,
                                      0x0f };

            cmd[6] = (byte)hScrollBar_yellow.Value;
            cmd[9] = (byte)hScrollBar_bright.Value;

            Buffer.BlockCopy(address, 0, cmd, 0, 5);
            SendLightCtrl_Cmd(cmd);
        }

        private void turnOff_Light()
        {
            byte[] cmd = new byte[] { 0, 0, 0, 0, 0,
                                      0, 0x86, 0x01,
                                      0, 0x86, 0x01,
                                      0x0f };

            Buffer.BlockCopy(address, 0, cmd, 0, 5);
            SendLightCtrl_Cmd(cmd);
        }
        #endregion

        #region 人体检测和灯控制综合测试
        private void Light_ControlAction()
        {
            //Step 3: 根据状态控制灯
            if (presence_value == 1)
            {
                turnOn_Light();
            }
            else
            {
                turnOff_Light();
            }
        }
        #endregion

        #region 模拟人体检测sensor

        public bool Presence_IDParser(byte[] packet )
        {
            string str = "ID=1E23DCA0\r\n";

            if (packet[0] == 'I' && packet[1] == 'D'  &&
                packet[3] == '=' && packet[1] == '?')
            {
                byte[] ID = System.Text.Encoding.ASCII.GetBytes(str);
                st_Serial_Proxy.SerialSend(ID, ID.Length);
                Moitor_String(id, false);
                return true;
            }

            return false;
        }

        #endregion
    }
}

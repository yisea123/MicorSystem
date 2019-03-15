using ControlPoxy;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LightTest
{
    public partial class LightControl : Form
    {
        private bool b_buttonCtrl = false;
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

        public LightControl()
        {
            InitializeComponent();
        }

        private void LightControl_Load(object sender, EventArgs e)
        {
            dataHandler = new Thread(DataCommandHander);
            dataHandler.Start();
            Control.CheckForIllegalCrossThreadCalls = false;
            Serial_ConfigInit();
            SerialPort_IniInit();

            hScrollBar_yellow.Minimum = 0x25;
            hScrollBar_yellow.Maximum = 0xf0;

            hScrollBar_bright.Minimum = 0x25;
            hScrollBar_bright.Maximum = 0xf0;
        }

        private void LightControl_FormClosed(object sender, FormClosedEventArgs e)
        {
            st_Serial_Proxy.SerialPort_Stop();
            dataHandler.Abort();
            Application.Exit();
        }

        #region uart Control
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
                if (st_Serial_Proxy.b_SerialReceiveReady)
                {
                    st_Serial_Proxy.b_SerialReceiveReady = false;
                    bool res = st_DeviceCtrl_Proxy.LightCtrl_AddressParser(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength , address);
                    if (res)
                    {
                        textBox_Address.Text = st_Util_Proxy.ByteToString(address, 5);
                    }
                    Monitor_Display(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, true);
                    st_Serial_Proxy.DataLength = 0;
                }
            }
        }

        private void button_Enable_Click(object sender, EventArgs e)
        {
            st_Serial_Proxy.Baud = int.Parse(comboBox_Baud.Text);    //设置Baud
            st_Serial_Proxy.Comport = comboBox_ComPort.Text;         //获取端口号
            st_Serial_Proxy.Parity = System.IO.Ports.Parity.None;

            if (b_buttonCtrl == false)
            {
                button_Enable.Text = "关闭串口";
                b_buttonCtrl = true;
                st_Serial_Proxy.SerialPort_Start();
                comboBox_Baud.Enabled = false;
                comboBox_ComPort.Enabled = false;
            }
            else
            {
                button_Enable.Text = "打开串口";
                b_buttonCtrl = false;
                st_Serial_Proxy.SerialPort_Stop();
                comboBox_Baud.Enabled = true;
                comboBox_ComPort.Enabled = true;
            }

            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Serial", "Baud", st_Serial_Proxy.Baud.ToString());
            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Serial", "Port", st_Serial_Proxy.Comport);
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
                st_Serial_Proxy.Baud = Convert.ToInt32(st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Serial", "Baud"));
                st_Serial_Proxy.Comport = st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Serial", "Port");

                comboBox_ComPort.Text = st_Serial_Proxy.Comport;
                comboBox_Baud.Text = st_Serial_Proxy.Baud.ToString();
            }
            catch
            {
            }
        }

        private void Monitor_Display( byte [] buff , int lenght ,bool type )
        {
            if( type )
                richTextBox_Monitor.AppendText("Recv:" + "\r\n");
            else
                richTextBox_Monitor.AppendText("Send:" + "\r\n");

            Monitor_Printf(buff, lenght);
        }
        #endregion Control

        #region Light Control
        private bool check_address()
        {
            if (textBox_Address.Text == "")
            {
                richTextBox_Monitor.AppendText("请重新给控制器上电，获取设备地址！" + "\r\n");
                return false;
            }

            return true;
        }

        private void SendLightCtrl_Cmd(byte[] cmd )
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
            byte[] cmd = new byte[] { 0,0,0,0,0,0x86,0x86,0x86,0x0f};

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

        #endregion
    }
}

/* End of this file */

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

namespace BlueTooth
{
    public partial class MainWin : Form
    {
        private Thread dataHandler;
        private Boolean b_buttonCtrl = false;
        private ControlPoxy.Serial_Proxy st_Serial_Proxy = new ControlPoxy.Serial_Proxy();
        private ControlPoxy.CRC_Proxy st_CRC_Proxy = new ControlPoxy.CRC_Proxy();
        private ControlPoxy.MCS_Protocol st_MCS_Protocol = new ControlPoxy.MCS_Protocol();

        private String ComPort = "COM1";
        private string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置
        public MainWin()
        {
            InitializeComponent();
        }

        private void MainWin_Load(object sender, EventArgs e)
        {
            Serial_ConfigInit();
            dataHandler = new Thread(DataCommandHander);
            dataHandler.Start();
            Control.CheckForIllegalCrossThreadCalls = false;
        }

        private void MainWin_FormClosed(object sender, FormClosedEventArgs e)
        {
            dataHandler.Abort();
            st_Serial_Proxy.SerialPort_Stop();
            Application.Exit();
        }

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
            comboBox_Baud.SelectedIndex = 4;
        }

        private void DataCommandHander()
        {
            Boolean b_res = false;
            while (true)
            {
                if (st_Serial_Proxy.DataLength > 0)
                {
                    b_res = st_MCS_Protocol.MCS_ProtocolPaeser(st_Serial_Proxy.RtBuff);
                    if (b_res)
                    {
                        Mcs_ReceiveAndSendMonitor(st_MCS_Protocol, true);
                        CtrCmd_Action(st_MCS_Protocol);
                        Mcs_ReceiveAndSendMonitor(st_MCS_Protocol, false);
                    }
                    st_Serial_Proxy.DataLength = 0;
                }
            }
        }

        private void CtrCmd_Action(MCS_Protocol mcs)
        {
            int cmd = mcs.CMD & 0x00ff;
            byte CtrCmd = mcs.DataBuf[0];

            mcs.CMD = (UInt16)(cmd | 0x8000);
            switch (CtrCmd)
            {
                case 0:    //Up
                    break;
                case 1:    //Down
                    break;
                case 2:    //Stop
                    break;
                default:
                    return;
            }

            CtrCmd_McsBuiding(mcs);
        }

        private void CtrCmd_McsBuiding(MCS_Protocol mcs)
        {
            byte[] buff = new byte[128];
            int length = 0;

            length = mcs.MCS_Building(mcs.srcAddr, mcs.tarAddr, mcs.Frum, mcs.CMD, mcs.DataBuf, (byte)mcs.DataLen, buff);

            st_Serial_Proxy.SerialSend(buff, length);
        }

        private void Mcs_ReceiveAndSendMonitor(MCS_Protocol mcs, bool mode)
        {
            byte[] buff = new byte[128];
            int length = 0;

            if (mode == true)
                richTextBox_Monitor.AppendText("Recv:" + "\r\n");
            else
                richTextBox_Monitor.AppendText("Send:" + "\r\n");

            length = mcs.MCS_Building(mcs.srcAddr, mcs.tarAddr, mcs.Frum, mcs.CMD, mcs.DataBuf, (byte)mcs.DataLen, buff);
            Monitor_Display(buff, length);
        }

        private void Monitor_Display(byte[] data, int length)
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
        }

        private void button_ClearBuff_Click(object sender, EventArgs e)
        {
            richTextBox_Monitor.Clear();
        }

    }
}

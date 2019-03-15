using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MCS_Studio
{
    public partial class MainWindows : Form
    {
        DeviceConfig str_DeviceConfig = new DeviceConfig();
        private string sysCondigIni = System.Environment.CurrentDirectory + "\\SysConfig.ini";
        private ControlPoxy.ConfigIni st_ConfigIni = new ControlPoxy.ConfigIni();
        private ControlPoxy.Serial_Proxy st_Serial_Proxy = new ControlPoxy.Serial_Proxy();
        private ControlPoxy.Util_Proxy st_Util_Proxy = new ControlPoxy.Util_Proxy();

        private String ComPort = "COM1";
        private string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置
        private Boolean b_buttonCtrl = false;
        private Thread dataHandler;
        private byte[] RtBuff = new byte[1024 * 512];

        private int Pageindex = -1;
        /*********************************************************************
         ***            窗口信息传输
         ********************************************************************/
        #region Windows transfer function
        public struct COPYDATASTRUCT
        {
            public IntPtr dwData;
            public int cbData;
            [MarshalAs(UnmanagedType.LPStr)]
            public string lpData;
        }

        [DllImport("User32.dll", EntryPoint = "SendMessage")]
        private static extern int SendMessage(
            int hWnd,           // handle to destination window
            int Msg,            // message
            int wParam,         // first message parameter
            ref COPYDATASTRUCT lParam // second message parameter
        );
        [DllImport("User32.dll", EntryPoint = "FindWindow")]
        private static extern int FindWindow(string lpClassName, string lpWindowName);

        const int WM_COPYDATA = 0x004A;
        protected void sendComMessage(string buf, string targetWindow)              //copydata发送消息
        {
            int WINDOW_HANDLER = FindWindow(null, @targetWindow);
            if (WINDOW_HANDLER == 0)
            {

            }
            else
            {
                byte[] sarr = System.Text.Encoding.Default.GetBytes(buf);
                int len = sarr.Length;
                COPYDATASTRUCT cds;
                cds.dwData = (IntPtr)100;
                cds.lpData = buf;
                cds.cbData = len + 1;
                SendMessage(WINDOW_HANDLER, WM_COPYDATA, 0, ref cds);
            }
        }

        protected override void DefWndProc(ref System.Windows.Forms.Message m)      //copydata接收消息
        {
            switch (m.Msg)
            {
                case WM_COPYDATA:
                    COPYDATASTRUCT mystr = new COPYDATASTRUCT();
                    Type mytype = mystr.GetType();
                    mystr = (COPYDATASTRUCT)m.GetLParam(mytype);
                    Serial_SendProcess(mystr.lpData);
                    break;
                default:
                    base.DefWndProc(ref m);
                    break;
            }
        }
        #endregion

        /*********************************************************************
        ***            system function
        **********************************************************************/
        #region system handler
        public MainWindows()
        {
            InitializeComponent();
        }

        private void MainWindows_Load(object sender, EventArgs e)
        {
            panel_Config.Controls.Clear();
            panel_Config.Controls.Add(str_DeviceConfig);
            Serial_ConfigInit();
            button_Contrl(false);
            Control.CheckForIllegalCrossThreadCalls = false;
            
            //开启数据处理线程
            dataHandler = new Thread(DataCommandHander);
            dataHandler.Start();

            //系统变量初始化
            Pageindex = 0;
        }

        private void MainWindows_FormClosed(object sender, FormClosedEventArgs e)
        {
            dataHandler.Abort();
            st_Serial_Proxy.SerialPort_Stop();
            Application.Exit();
        }

        private void SystemSavedIniRefresh()
        {
            try
            {
                st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Serial", "Baud", st_Serial_Proxy.Baud.ToString());
                st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Serial", "Port", st_Serial_Proxy.Comport);
            }
            catch
            {

            }
        }

        private void SystemUIIniInit()
        {
            try
            {
                st_Serial_Proxy.Baud = Convert.ToInt32(st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Serial", "Baud"));
                st_Serial_Proxy.Comport = st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Serial", "Port");

                cmbox_ComPort.Text = st_Serial_Proxy.Comport;
                cbx_ComBaud.Text = st_Serial_Proxy.Baud.ToString();
            }
            catch
            {
            }
        }

        private void DataCommandHander()
        {
            while (true)
            {
                if (st_Serial_Proxy.b_SerialReceiveReady )
                {
                    DataCommandResponsed(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                    st_Serial_Proxy.DataLength = 0;
                    st_Serial_Proxy.b_SerialReceiveReady = false;
                }
            }
        }

        private void Serial_SendProcess( string str )
        {
            if (str.Length == 0)
                return;

            byte []databuff = st_Util_Proxy.GetByteArray(str);
            if (databuff.Length > 0)
            {
                st_Serial_Proxy.SerialSend(databuff, databuff.Length);
            }
        }

        private void Serial_ConfigInit()
        {
            int baudIndex = 0;
            string[] port = System.IO.Ports.SerialPort.GetPortNames();//搜索PC可用的串口号 

            if (port != null)
            {
                cmbox_ComPort.Items.Clear();
                foreach (string cName in port)
                {
                    cmbox_ComPort.Items.Add(cName);
                    if (cName == ComPort)
                    {
                        cmbox_ComPort.SelectedIndex = baudIndex;
                    }
                    baudIndex++;
                }
            }

            //波特率
            cbx_ComBaud.Items.Clear();
            foreach (string cName in StringBaud)
            {
                cbx_ComBaud.Items.Add(cName);
            }
            cbx_ComBaud.SelectedIndex = 0;

            SystemUIIniInit();
        }

        #endregion

        /*********************************************************************
        ***            user function
        **********************************************************************/
        #region user handler

        private void DataCommandResponsed(byte[] data, int length )
        {
            switch (Pageindex)
            {
                case 0:
                    str_DeviceConfig.DeviceConfig_dataHandler(data, length);
                    break;
                default:
                    return;
            }
        }

        private void button_Contrl(bool b_ctrl)
        {
            if (b_ctrl)
            {
                button_Device.Enabled = true;
                button_system.Enabled = true;

            }
            else
            {
                button_Device.Enabled = false;
                button_system.Enabled = false;
            }
        }

        private void Button_SerialCtrl_Click(object sender, EventArgs e)
        {
            st_Serial_Proxy.Baud = int.Parse(cbx_ComBaud.Text);    //设置Baud
            st_Serial_Proxy.Comport = cmbox_ComPort.Text;         //获取端口号
            st_Serial_Proxy.Parity = System.IO.Ports.Parity.None;
            st_Serial_Proxy.TimeOut = 300;

            if (b_buttonCtrl == false)
            {
                Button_SerialCtrl.Text = "关闭串口";
                b_buttonCtrl = true;
                st_Serial_Proxy.SerialPort_Start();
                cbx_ComBaud.Enabled = false;
                cmbox_ComPort.Enabled = false;
            }
            else
            {
                Button_SerialCtrl.Text = "打开串口";
                b_buttonCtrl = false;
                st_Serial_Proxy.SerialPort_Stop();
                cbx_ComBaud.Enabled = true;
                cmbox_ComPort.Enabled = true;
            }

            button_Contrl(b_buttonCtrl);

            SystemSavedIniRefresh();
        }

        private void button_system_Click(object sender, EventArgs e)
        {
            panel_Config.Controls.Clear();
            panel_Config.Controls.Add(str_DeviceConfig);
            Pageindex = 0;
        }

        private void button_Device_Click(object sender, EventArgs e)
        {

        }
        #endregion
    }
}


/* End of this file */
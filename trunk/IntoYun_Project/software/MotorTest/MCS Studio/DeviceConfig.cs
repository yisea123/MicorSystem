using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using ControlPoxy;

namespace MCS_Studio
{
    public partial class DeviceConfig : UserControl
    {
        private const int CONFIG_PROJECT_PARMERT = 0x0010;
        private const int CONFIG_READ_PARMERT = 0x4000;
        private const int CONFIG_WRITE_PARMERT = 0;

        private const int CONFIG_SUCESS = 0x8000;
        private const int CONFIG_ERROR = 0;
        private const int RETRY = 10;

        MCS_Protocol st_mcs = new MCS_Protocol();
        private Util_Proxy st_Util_Proxy = new Util_Proxy();
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
        protected void sendComMessage(string buf, string targetWindow)  //copydata发送消息
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

        private void DevFrorm_SendProcess(byte[] buff, int length)
        {
            string SenString = "";

            sendComMessage(SenString, "MCS Studio");
        }
        #endregion

        /**********************************************************************
        *** System function interface
        **********************************************************************/
        #region System function
        private void CtrCmd_McsBuidingAndSend(int type,  byte[] data)
        {
            MCS_Protocol st_mcsSend = new MCS_Protocol();
            byte[] buff = new byte[128];
            int length = 0;
            string SenString = "";

            st_mcsSend.srcAddr = 0;
            st_mcsSend.tarAddr = 0;
            st_mcsSend.Frum = 0;
            st_mcsSend.CMD = (ushort)(CONFIG_PROJECT_PARMERT|type);
            st_mcsSend.DataLen = (ushort)data.Length;
            st_mcsSend.DataBuf = data;

            length = st_mcsSend.MCS_Building(st_mcsSend.srcAddr, 
                                             st_mcsSend.tarAddr, 
                                             st_mcsSend.Frum, 
                                             st_mcsSend.CMD, 
                                             st_mcsSend.DataBuf, 
                                             (byte)st_mcsSend.DataLen, 
                                             buff);

            SenString = st_Util_Proxy.ByteToString(buff, length);
            sendComMessage(SenString, "MCS Studio");
        }

        private void DeviceConfig_Load(object sender, EventArgs e)
        {

        }

        public DeviceConfig()
        {
            InitializeComponent();
        }

        private  void SendString_Interface(int type, byte id, string str)
        {
            byte[] data = System.Text.Encoding.ASCII.GetBytes(str);
            byte[] dataPacket = new byte[data.Length + 1];

            dataPacket[0] = id;
            data.CopyTo(dataPacket, 1);
            CtrCmd_McsBuidingAndSend(type, dataPacket);
        }

        public void DeviceConfig_dataHandler(byte[] data, int length)
        {
            if (length > 0)
            {
                st_mcs.MCS_ProtocolPaeser(data);
            }
        }

        private string ReadInformation_Result( byte[] data )
        {
            byte retry = RETRY;

            while (retry > 0)
            {
                CtrCmd_McsBuidingAndSend(CONFIG_READ_PARMERT, data);
                System.Threading.Thread.Sleep(300);

                if (st_mcs.b_result)
                {
                    if (data[0] == st_mcs.DataBuf[0])
                    {
                        st_mcs.b_result = false;
                        byte[] Result = new byte[st_mcs.DataLen];
                        Buffer.BlockCopy(st_mcs.DataBuf, 1, Result, 0, st_mcs.DataLen - 1);
                        string str = Encoding.ASCII.GetString(Result);
                        return str;
                    }
                }
                retry--;
            }

            return null;
        }

        private void TextBox_Item_Clear( byte type)
        {
            switch (type)
            {
                case 0x01:
                    textBox_ProjectID.Text = "";
                    textBox_ProjectID.Clear();
                    break;
                case 0x02:
                    textBox_secret.Text = "";
                    textBox_secret.Clear();
                    break;
                case 0x03:
                    textBox_DeviceID.Text = "";
                    textBox_DeviceID.Clear();
                    break;
                case 0x04:
                    textBox_SSID.Text = "";
                    textBox_SSID.Clear();
                    break;
                case 0x05:
                    textBox_PWD.Text = "";
                    textBox_PWD.Clear();
                    break;
            }
        }

        #endregion
        /**********************************************************************
        *** User function interface
        **********************************************************************/
        #region User function
        private void button_readProjectID_Click(object sender, EventArgs e)
        {
            byte[] data= new byte[1];

            data[0] = 0x01;

            TextBox_Item_Clear(data[0]);
            string str = ReadInformation_Result( data );
            if(str != null)
               textBox_ProjectID.Text = str;
        }

        private void button_ConfigProjectID_Click(object sender, EventArgs e)
        {
            string str = textBox_ProjectID.Text;

            if (str.Length == 0)
                MessageBox.Show("请输入项目 ID......");

            SendString_Interface(CONFIG_WRITE_PARMERT, 0x01,str);
        }

        private void button_ReadSecret_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1];

            TextBox_Item_Clear(data[0]);
            data[0] = 0x02;
            string str = ReadInformation_Result(data);
            if (str != null)
                textBox_secret.Text = str;
        }

        private void button_configSecret_Click(object sender, EventArgs e)
        {
            string str = textBox_secret.Text;

            if (str.Length == 0)
                MessageBox.Show("请输入项目 secret......");

            SendString_Interface(CONFIG_WRITE_PARMERT,0x02, str);
        }

        private void button_ReadDeviceID_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1];

            data[0] = 0x03;
            TextBox_Item_Clear(data[0]);
            string str = ReadInformation_Result(data);
            if (str != null)
                textBox_DeviceID.Text = str;
        }

        private void button_configDeviceID_Click(object sender, EventArgs e)
        {
            string str = textBox_DeviceID.Text;

            if (str.Length == 0)
                MessageBox.Show("请输入设备标识......");

            SendString_Interface(CONFIG_WRITE_PARMERT,0x03, str);
        }

        private void button_read_SSID_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1];

            data[0] = 0x04;
            TextBox_Item_Clear(data[0]);
            string str = ReadInformation_Result(data);
            if (str != null)
                textBox_SSID.Text = str;
        }

        private void button_config_SSID_Click(object sender, EventArgs e)
        {
            string str = textBox_SSID.Text;

            if (str.Length == 0)
                MessageBox.Show("请输入wifi ssid......");

            SendString_Interface(CONFIG_WRITE_PARMERT,0x04, str);
        }

        private void button_read_PWD_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1];

            data[0] = 0x05;
            TextBox_Item_Clear(data[0]);
            string str = ReadInformation_Result(data);
            if (str != null)
                textBox_PWD.Text = str;
        }

        private void button_config_PWD_Click(object sender, EventArgs e)
        {
            string str = textBox_PWD.Text;

            if (str.Length == 0)
                MessageBox.Show("请输入wifi password......");

            SendString_Interface(CONFIG_WRITE_PARMERT,0x05, str);
        }

        #endregion
    }
}

/* End of this file */

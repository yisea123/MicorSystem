using ControlPoxy;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace McsCommandTest
{
    public partial class Form_McsCommand : Form
    {
        const byte LIVE_TYPE = 1;                 // 平台
        const byte CORRIDOR_TYPE = 2;             // 楼梯
        const byte LAZYBACK_TYPE = 3;             // 靠背
        const byte DESK_TYPE = 4;                 // 桌子
        const byte LED_TYPE = 5;                  // 灯
        const byte TV_TYPE = 6;                   //TV
        const byte STAIR_TYPE = 7;                //stair
        const byte KITCHEN_TYPE = 8;              //厨房
        const byte NULL_TYPE = 0xff;
        private const int RETRY = 3;

        private bool b_AutoTestEnable = false;
        private int timeOut = 0;
        private int CntOut = 0;

        private int CurrentState = -1;
        private int RunTimeCnt = 0;
        private int RunIntervalCnt = 0;

        private string sysCondigIni = System.Environment.CurrentDirectory + "\\SysConfig.ini";
        private Thread dataHandler;
        private Boolean b_buttonCtrl = false;
        private ControlPoxy.ConfigIni st_ConfigIni = new ControlPoxy.ConfigIni();
        private ControlPoxy.Serial_Proxy st_Serial_Proxy = new ControlPoxy.Serial_Proxy();
        private ControlPoxy.CRC_Proxy st_CRC_Proxy = new ControlPoxy.CRC_Proxy();
        private ControlPoxy.MCS_Protocol st_MCS_Protocol = new ControlPoxy.MCS_Protocol();
        private ModbusStruc st_ModbusStruc = new ModbusStruc();

        int receiveIndex = -1;
        private String ComPort = "COM1";
        private string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置
        private string[] deviceName = {"平台","电视","1号靠背", "2号靠背", "桌子", "楼梯", "厨房"};
        private byte[] deviceID     = {  7,    5,    3,       4,         6,      8,     1};
        private byte[] deviceType   = {  1,    6,    3,       3,         4,      2,     8};
        private Dictionary<string , StateObject> deviceDic = new Dictionary<string, StateObject>();

        public class StateObject
        {
            public string deviceName;  
            public byte deviceID; 
            public byte deviceType;
        }


        public Form_McsCommand()
        {
            InitializeComponent();
        }

        private void DeviceType_select()
        {
            string str = comboBox_deviceType.Text;

        }
        private void Form_McsCommand_Load(object sender, EventArgs e)
        {
            Serial_ConfigInit();
            DeviceType_ConfigInit();

            dataHandler = new Thread(DataCommandHander);
            dataHandler.Start();
            Control.CheckForIllegalCrossThreadCalls = false;

            button_Contrl( false);
            DeciceIDSavedIniInit();
        }

        private void Form_McsCommand_FormClosed(object sender, FormClosedEventArgs e)
        {
            st_Serial_Proxy.SerialPort_Stop();
            dataHandler.Abort();
            Application.Exit();
        }

        private void DeviceType_ConfigInit()
        {
            byte deviceTypeIndex = 0;

            if (deviceType != null)
            {
                comboBox_deviceType.Items.Clear();
                foreach (string cName in deviceName)
                {
                    comboBox_deviceType.Items.Add(cName);
                    deviceTypeIndex++;
                }
            }

            if(deviceTypeIndex > 0)
            {
                comboBox_deviceType.SelectedIndex = 0;
            }

            deviceDic.Clear();
            // add device to Dictionary
            for ( int i = 0; i < deviceID.Length; i++ )
            {
                StateObject state = new StateObject();
                state.deviceID = deviceID[i];
                state.deviceType = deviceType[i];
                state.deviceName = deviceName[i];
                deviceDic.Add(deviceName[i], state);
            }
        }

        private bool Send_CtrlCmd( byte dir )
        {
            bool res = false;
            string DeviceName = comboBox_deviceType.Text;
            string log = "deviceName:" + deviceDic[DeviceName].deviceName + ",  " +
                         "deviceType:" + deviceDic[DeviceName].deviceType + ",  " +
                         "deviceID:" + deviceDic[DeviceName].deviceID + ",  " +
                         "dir:" +dir.ToString();

            RunTimeCnt = 0;
            ShowMessage(log + "\r\n");
            Mcs_CommandCtrl(deviceDic[DeviceName].deviceType, deviceDic[DeviceName].deviceID, dir);
            res = SendCmdAndCheckResult(st_MCS_Protocol);
            if( res )
            {
                  CurrentState = dir;
            }
            return res;
        }

        private void comboBox_deviceType_SelectedIndexChanged(object sender, EventArgs e)
        {

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
            comboBox_Baud.SelectedIndex = 0;
        }

        private void button_Contrl(bool b_ctrl)
        {
            if (b_ctrl)
            {

                button_led1.Enabled = true;
                button_LED1_OFF.Enabled = true;


                button_LazyUp.Enabled = true;
                button_lazy_down.Enabled = true;
                button_StopLazyBack_1.Enabled = true;
            }
            else
            {
                button_led1.Enabled = false;
                button_LED1_OFF.Enabled = false;


                button_LazyUp.Enabled = false;
                button_lazy_down.Enabled = false;
                button_StopLazyBack_1.Enabled = false;
            }
        }

        private void DataCommandHander()
        {
            Boolean b_res = false;

            while (true)
            {
                if (st_Serial_Proxy.b_SerialReceiveReady)
                {
                    st_Serial_Proxy.b_SerialReceiveReady = false;
                    if (st_Serial_Proxy.DataLength > 0)
                    {
                        if (st_Serial_Proxy.RtBuff[0] == 0x5b)
                        {
                            b_res = st_MCS_Protocol.MCS_ProtocolPaeser(st_Serial_Proxy.RtBuff);
                            if (b_res)
                            {
                                Mcs_ReceiveAndSendMonitor(st_MCS_Protocol, true);
                                st_MCS_Protocol.b_result = true;
                            }
                        }
                        st_Serial_Proxy.DataLength = 0;
                    }
                }
            }
        }

        private void CtrCmd_McsBuiding(MCS_Protocol mcs)
        {
            byte[] buff = new byte[512];
            int length = 0;

            length = mcs.MCS_Building(mcs.srcAddr, mcs.tarAddr, mcs.Frum, mcs.CMD, mcs.DataBuf, (byte)mcs.DataLen, buff);

            st_Serial_Proxy.SerialSend(buff, length);

            richTextBox_Monitor.AppendText("Send" + "\r\n");
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
        private void Mcs_ReceiveAndSendMonitor(MCS_Protocol mcs, bool mode)
        {
            byte[] buff = new byte[512];
            int length = 0;

            if (mode == true)
                richTextBox_Monitor.AppendText("Recv:" + "\r\n");
            else
                richTextBox_Monitor.AppendText("Send:" + "\r\n");

            length = mcs.MCS_Building(mcs.srcAddr, mcs.tarAddr, mcs.Frum, mcs.CMD, mcs.DataBuf, (byte)mcs.DataLen, buff);
            Monitor_Display(buff, length);
        }
        private void button_Enable_Click(object sender, EventArgs e)
        {
            st_Serial_Proxy.Baud = int.Parse(comboBox_Baud.Text);    //设置Baud
            st_Serial_Proxy.Comport = comboBox_ComPort.Text;         //获取端口号
            st_Serial_Proxy.Parity = System.IO.Ports.Parity.None;
            st_Serial_Proxy.TimeOut = 500;

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

            button_Contrl(b_buttonCtrl);
        }

        private byte DataIDConvert( string sID)
        {
            byte byteID = 0;

            try {
                if (sID == "")
                {
                    MessageBox.Show("请输入数据ID!");
                }
                byteID = Convert.ToByte(sID);
            }
            catch { }

            return byteID;
        }

        private void Mcs_CommandCtrl( byte deviceType, byte DeviceID, byte CtrlRes)
        {
            st_MCS_Protocol.srcAddr = 0;
            st_MCS_Protocol.tarAddr = 0;
            st_MCS_Protocol.Frum = 0;
            st_MCS_Protocol.CMD = 0x0013;
            st_MCS_Protocol.DataLen = 3;
            st_MCS_Protocol.DataBuf[0] = deviceType;
            st_MCS_Protocol.DataBuf[1] = DeviceID;
            st_MCS_Protocol.DataBuf[2] = CtrlRes;
        }

        private void Mcs_CommandCtrl(byte deviceType, byte DeviceID, byte []CtrlRes)
        {
            st_MCS_Protocol.srcAddr = 0;
            st_MCS_Protocol.tarAddr = 0;
            st_MCS_Protocol.Frum = 0;
            st_MCS_Protocol.CMD = 0x0013;
            st_MCS_Protocol.DataLen = 5;
            st_MCS_Protocol.DataBuf[0] = deviceType;
            st_MCS_Protocol.DataBuf[1] = DeviceID;
            st_MCS_Protocol.DataBuf[2] = CtrlRes[0];
            st_MCS_Protocol.DataBuf[3] = CtrlRes[1];
            st_MCS_Protocol.DataBuf[4] = CtrlRes[2];
        }

        private void button_ClearBuff_Click(object sender, EventArgs e)
        {
            richTextBox_Monitor.Clear();
        }

        private void ShowMessage( string msg)
        {
            richTextBox_Monitor.AppendText(msg);
            DeciceIDSavedIniRefresh();
        }

        private bool SendCmdAndCheckResult(MCS_Protocol mcs)
        {
            byte retry = RETRY;

            while (retry > 0)
            {
                CtrCmd_McsBuiding(mcs);
                System.Threading.Thread.Sleep(500);
                if (mcs.b_result)
                {
                    mcs.b_result = false;
                    return true;
                }
                retry--;
            }

            return false;
        }

        #region LED_1
        private void button_LED1_ON_Click(object sender, EventArgs e)
        {
            byte DataID = DataIDConvert(textBox_led1.Text);
            byte[] res = { 0x01, 0x3f,0x3f};

            ShowMessage("LED-1: ON  \r\n");
            Mcs_CommandCtrl(LED_TYPE, DataID, res);
            SendCmdAndCheckResult(st_MCS_Protocol);
        }

        private void button_LED1_OFF_Click(object sender, EventArgs e)
        {
            byte DataID = DataIDConvert(textBox_led1.Text);
            byte[] res = { 0x00, 0x3f, 0x3f };

            ShowMessage("LED-1: OFF  \r\n");
            Mcs_CommandCtrl(LED_TYPE, DataID, res);
            SendCmdAndCheckResult(st_MCS_Protocol);
        }
        #endregion

        #region lazy_1
        private void button_LazyDown_Click(object sender, EventArgs e)
        {
            Send_CtrlCmd(0);
            RunIntervalCnt = 0;
        }

        private void button_LazyUp_Click(object sender, EventArgs e)
        {
            Send_CtrlCmd(1);
            RunIntervalCnt = 0;
        }

        private void button_StopLazyBack_1_Click(object sender, EventArgs e)
        {
            Send_CtrlCmd(2);
        }
        #endregion

        #region ini config
        private string DeviceIDSaveIni(bool type, string Devtype, string value)
        {
            string strValue = "";
            try
            {
                if (Devtype == null && value == null)
                    return strValue;

                if (type)
                    st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Device", Devtype, value);
                else
                {
                    value = st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Device", Devtype);
                    strValue = value;
                }
            }
            catch { }

            return strValue;
        }


        private void DeciceIDSavedIniRefresh()
        {
            try
            {

                st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Serial", "Baud", st_Serial_Proxy.Baud.ToString());
                st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Serial", "Port", st_Serial_Proxy.Comport);

                DeviceIDSaveIni(true, "LED_1", textBox_led1.Text);
            }
            catch
            {
            }
        }

        private void DeciceIDSavedIniInit()
        {
            try
            {
                st_Serial_Proxy.Baud  = Convert.ToInt32(st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Serial", "Baud"));
                st_Serial_Proxy.Comport = st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Serial", "Port");

                comboBox_ComPort.Text = st_Serial_Proxy.Comport;
                comboBox_Baud.Text = st_Serial_Proxy.Baud.ToString();

                textBox_led1.Text = DeviceIDSaveIni(false, "LED_1", textBox_led1.Text);

            }
            catch
            {
            }
        }

        private void button_BluetoothSend_Click(object sender, EventArgs e)
        {
            byte DataLen = DataIDConvert(textBox_DataLen.Text);
            if (DataLen > 45)
            {
                DataLen = 45;
            }

            ShowMessage("蓝牙数据包测试 \r\n");
            st_MCS_Protocol.srcAddr = 0;
            st_MCS_Protocol.tarAddr = 0;
            st_MCS_Protocol.Frum = 0;
            st_MCS_Protocol.CMD = 0x0013;
            st_MCS_Protocol.DataLen = DataLen;

            if (DataLen > 0)
            {
                for (int i = 0; i < DataLen; i++)
                {
                    st_MCS_Protocol.DataBuf[i] = (byte)(0x30 + i);
                }
            }
            CtrCmd_McsBuiding(st_MCS_Protocol);
        }
        #endregion

        #region FileDownload

        private void DownlaodFile_CheckCmd()
        {
            if (st_MCS_Protocol.CMD == 0x8013)
            {
                receiveIndex = st_MCS_Protocol.Frum;
            }
        }
        private void MakePacket_ByMcs(ushort DataLen, byte[] data, ushort frum)
        {
            st_MCS_Protocol.srcAddr = 0;
            st_MCS_Protocol.tarAddr = 0;
            st_MCS_Protocol.Frum = frum;
            st_MCS_Protocol.CMD = 0x0013;
            st_MCS_Protocol.DataLen = DataLen;

            if (DataLen > 0)
            {
                for (int i = 0; i < DataLen; i++)
                {
                    st_MCS_Protocol.DataBuf[i] = data[i];
                }
            }
            CtrCmd_McsBuiding(st_MCS_Protocol);
        }


        byte[] AppBt;
        int totalPacket = 0;
        const int fwSendLen = 128;

        private void AddFile_Click(object sender, EventArgs e)
        {
            try
            {
                OpenFileDialog openbinFile = new OpenFileDialog();
                openbinFile.Filter = "下载文件|*.bin;*.hex";
                if (openbinFile.ShowDialog() == DialogResult.OK)
                {
                    FileStream IniRead = new FileStream(openbinFile.FileName, FileMode.OpenOrCreate, FileAccess.Read);
                    filePath.Text = openbinFile.FileName;

                    if (IniRead.Length > 0)
                    {
                        AppBt = new byte[IniRead.Length];
                        IniRead.Read(AppBt, 0, AppBt.Length);      //读取app应用代码数据

                        totalPacket = AppBt.Length / fwSendLen;    //计算数据包总数
                        if (AppBt.Length % fwSendLen != 0)
                        {
                            totalPacket += 1;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        bool b_fwStart = false;
        Thread sub = null;
        ushort sendFrum = 0;

        private void button_Start_Click(object sender, EventArgs e)
        {
            progressBar_download.Maximum = totalPacket;
            progressBar_download.Value = 0;
            FwProcessBar.Text = "0%";
            b_fwStart = true;
            sendFrum = 0;

            sub = new Thread(sendUpDataThreading);
            sub.IsBackground = true;
            sub.Start();

            button_Start.Enabled = false;
            AddFile.Enabled = false;
            button1_Stop.Enabled = true;
        }

        private void button1_Stop_Click(object sender, EventArgs e)
        {
            button_Start.Enabled = true;
            AddFile.Enabled = true;
            button1_Stop.Enabled = false;
            FwProcessBar.Text = "0%";

            receiveIndex = -1;
            sendFrum = 0;
            b_fwStart = false;
            sub.Abort();
        }

        private void sendUpDataThreading()
        {
            byte[] data = new byte[fwSendLen];
            byte readLen;

            while (true)
            {
                if (!b_fwStart)
                    return;

                if ((AppBt.Length - sendFrum * fwSendLen) >= fwSendLen)
                {
                    readLen = fwSendLen;
                }
                else
                {
                    readLen = (byte)(AppBt.Length - sendFrum * fwSendLen);
                }

                if (readLen > 0)
                {
                    Buffer.BlockCopy(AppBt, sendFrum * fwSendLen, data, 0, readLen);
                    try
                    {
                        MakePacket_ByMcs(readLen, data, sendFrum);
                        System.Threading.Thread.Sleep(550);
                        DownlaodFile_CheckCmd();
                    }
                    catch
                    {

                    }


                    FwProcessBar.Text = (Convert.ToDouble(sendFrum) / Convert.ToDouble(progressBar_download.Maximum) * 100).ToString("0.0") + "%";
                    if (sendFrum == receiveIndex)
                    {
                        sendFrum++;
                    }
                    progressBar_download.Value = sendFrum;
                }

                //判断数据包是否发送完毕
                if (sendFrum == totalPacket)
                {
                    receiveIndex = -1;
                    FwProcessBar.Text = "100%";
                    sendFrum = 0;
                    b_fwStart = false;

                    button_Start.Enabled = true;
                    AddFile.Enabled = true;
                    button1_Stop.Enabled = false;
                    sub.Abort();
                    return;
                }
            }
        }
        #endregion

        private void checkBox_AutoTest_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_AutoTest.Checked)
            {
                timer1.Enabled = true;
                textBox_interval.Enabled = false;
                textBox_cmdCnt.Enabled = false;
                b_AutoTestEnable = true;
                comboBox_deviceType.Enabled = false;
            }
            else
            {
                timer1.Enabled = false;
                textBox_interval.Enabled = true;
                textBox_cmdCnt.Enabled = true;
                comboBox_deviceType.Enabled = true;
                b_AutoTestEnable = false;
            }
            timeOut = int.Parse(textBox_interval.Text);
            CntOut = int.Parse(textBox_cmdCnt.Text);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            bool res = false;

            if (b_AutoTestEnable)
            {
                if (CurrentState != -1)
                {
                    RunTimeCnt++;
                    if (RunTimeCnt > timeOut)
                    {
                        if (RunIntervalCnt > CntOut)
                        {
                            RunTimeCnt = 0;
                            RunIntervalCnt = 0;
                            CurrentState = -1;
                        }
                        else
                        {
                            RunIntervalCnt++;
                            ShowMessage(" level auto test: " + RunIntervalCnt.ToString() + "\r\n");
                            if (CurrentState == 0)
                            {
                                //Send up command
                                res = Send_CtrlCmd(1);
                                if (res)
                                {
                                    ShowMessage(" level up \r\n");
                                    RunTimeCnt = 0;
                                }
                            }
                            else if (CurrentState == 1)
                            {
                                //Send down command
                                res = Send_CtrlCmd(0);
                                if (res)
                                {
                                    ShowMessage(" level down \r\n");
                                    RunTimeCnt = 0; ;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/* End of this file */

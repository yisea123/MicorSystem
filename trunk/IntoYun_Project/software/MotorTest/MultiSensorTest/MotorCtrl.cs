using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using ControlPoxy;

namespace MultiSensorTest
{
    public partial class MotorCtrl : UserControl
    {
        #region parmater
        private ConfigIni st_ConfigIni = new ConfigIni();
        private MotorReadSpeed str_MotorRead = new MotorReadSpeed();
        private Serial_Proxy st_Serial_Proxy = new Serial_Proxy();
        private CRC_Proxy st_CRC_Proxy = new CRC_Proxy();

        private MotorStatus st_Motor1Status = new MotorStatus();
        private MotorStatus st_Motor2Status = new MotorStatus();
        private MotorStatus st_Motor3Status = new MotorStatus();
        private MotorStatus st_Motor4Status = new MotorStatus();

        private string sysCondigIni = System.Environment.CurrentDirectory + "\\SysConfig.ini";
        private string LogMotorSpeed1 = "";
        private string LogMotorSpeed2 = "";
        private string LogMotorSpeed3 = "";
        private string LogMotorSpeed4 = "";

        private Thread dataHandler;
        private int SendCmdInterval = 0;
        private int CtrStep = 0xff;
        private int readCmdCnt = 0;
        private int actCount = 0;
        private int actReadSpeedCount = 0;
        private int actCheckErrorCount = 0;
        private int ActionStatus = 0xff;

        private Boolean b_Threader = false;
        private Boolean b_buttonCtrl = false;
        private Boolean b_StopEnable = false;
        private Boolean b_ReadCmdEnable = false;

        private String ComPort = "COM1";
        private string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置

        private List<int> MotorRunLive = new List<int>();
        private List<int> MotorReadSpeedLive = new List<int>();
        #endregion

        public MotorCtrl()
        {
            InitializeComponent();
        }

        public void MotorCtrl_Stop()
        {
            if( b_Threader )
            {
                b_Threader = false;
                dataHandler.Abort();
                st_Serial_Proxy.SerialPort_Stop();
                Application.Exit();
            }
        }

        public void MotorCtrl_Start()
        {
            dataHandler = new Thread(DataCommandHander);
            dataHandler.Start();
            b_Threader = true;
        }

        private void MotorCtrl_Load(object sender, EventArgs e)
        {
            SerialPort_IniInit();

            button_Contrl(false);
            textBox_inteval.Text = "100";
            textBox_Cmd.Text = "10";
            textBox_Speed.Text = "150";
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);

            checkBox_AllMotor.Checked = true;
            checkBox_Motor_1.Checked = true;
            checkBox_Motor_2.Checked = true;
            checkBox_Motor_3.Checked = true;
            checkBox_Motor_4.Checked = true;

            checkBox_ReadAll.Checked = true;
            checkBox_ReadMotor1.Checked = true;
            checkBox_ReadMotor2.Checked = true;
            checkBox_ReadMotor3.Checked = true;
            checkBox_ReadMotor4.Checked = true;

            LogMotorSpeed1 = System.Environment.CurrentDirectory + "\\Motor_1.log";
            LogMotorSpeed2 = System.Environment.CurrentDirectory + "\\Motor_2.log";
            LogMotorSpeed3 = System.Environment.CurrentDirectory + "\\Motor_3.log";
            LogMotorSpeed4 = System.Environment.CurrentDirectory + "\\Motor_4.log";
            actCheckErrorCount = 0;
        }

        private void SerialPort_IniInit()
        {
            try
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

                Control.CheckForIllegalCrossThreadCalls = false;
                //波特率
                comboBox_Baud.Items.Clear();
                foreach (string cName in StringBaud)
                {
                    comboBox_Baud.Items.Add(cName);
                }
                comboBox_Baud.SelectedIndex = 4;

                st_Serial_Proxy.Baud = Convert.ToInt32(st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Motor_Serial", "Baud"));
                st_Serial_Proxy.Comport = st_ConfigIni.GetProjectInfor2Ini(sysCondigIni, "Motor_Serial", "Port");

                comboBox_ComPort.Text = st_Serial_Proxy.Comport;
                comboBox_Baud.Text = st_Serial_Proxy.Baud.ToString();
            }
            catch
            {
            }
        }

        private void timeCtrl()
        {
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
            timerAct.Interval = Convert.ToUInt16(textBox_inteval.Text);
            timerAct.Enabled = true;
            timerAct.Start();
        }

        private void button_Enable_Click(object sender, EventArgs e)
        {
            bool res = false;
            st_Serial_Proxy.Baud = int.Parse(comboBox_Baud.Text);    //设置Baud
            st_Serial_Proxy.Comport = comboBox_ComPort.Text;         //获取端口号
            st_Serial_Proxy.Parity = System.IO.Ports.Parity.Even;    //偶校验
            st_Serial_Proxy.TimeOut = 100;

            if (b_buttonCtrl == false)
            {
                res = st_Serial_Proxy.SerialPort_Start();
                if(res)
                {
                    button_Enable.Text = "关闭串口";
                    b_buttonCtrl = true;
                    comboBox_Baud.Enabled = false;
                    comboBox_ComPort.Enabled = false;
                    timeCtrl();
                    MotorCtrl_Start();
                }
            }
            else
            {
                MotorCtrl_Stop();
                button_Enable.Text = "打开串口";
                b_buttonCtrl = false;
                st_Serial_Proxy.SerialPort_Stop();
                comboBox_Baud.Enabled = true;
                comboBox_ComPort.Enabled = true;
                CtrStep = 0xff;
            }

            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Motor_Serial", "Baud", st_Serial_Proxy.Baud.ToString());
            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Motor_Serial", "Port", st_Serial_Proxy.Comport);
            button_Contrl(b_buttonCtrl);
        }

        private void button_Contrl(bool b_ctrl)
        {
            if (b_ctrl)
            {
                button_Up.Enabled = true;
                button_Down.Enabled = true;
                button_Stop.Enabled = true;

                textBox_inteval.Enabled = false;
                textBox_Cmd.Enabled = false;
                textBox_Speed.Enabled = false;

                checkBox_AllMotor.Enabled = false;
                checkBox_Motor_1.Enabled = false;
                checkBox_Motor_2.Enabled = false;
                checkBox_Motor_3.Enabled = false;
                checkBox_Motor_4.Enabled = false;

                checkBox_ReadAll.Enabled = false;
                checkBox_ReadMotor1.Enabled = false;
                checkBox_ReadMotor2.Enabled = false;
                checkBox_ReadMotor3.Enabled = false;
                checkBox_ReadMotor4.Enabled = false;

                Motor_RunCheckLive();
                Motor_CheckReadSpeedLive();
            }
            else
            {
                button_Up.Enabled = false;
                button_Down.Enabled = false;
                button_Stop.Enabled = false;

                textBox_inteval.Enabled = true;
                textBox_Cmd.Enabled = true;
                textBox_Speed.Enabled = true;

                checkBox_AllMotor.Enabled = true;
                checkBox_Motor_1.Enabled = true;
                checkBox_Motor_2.Enabled = true;
                checkBox_Motor_3.Enabled = true;
                checkBox_Motor_4.Enabled = true;

                checkBox_ReadAll.Enabled = true;
                checkBox_ReadMotor1.Enabled = true;
                checkBox_ReadMotor2.Enabled = true;
                checkBox_ReadMotor3.Enabled = true;
                checkBox_ReadMotor4.Enabled = true;
            }

            actCheckErrorCount = 0;
        }

        private void Disable_Status()
        {
            this.pictureBox_Motor_4.Image = global::MultiSensorTest.Properties.Resources.Off;
            this.pictureBox_Motor_2.Image = global::MultiSensorTest.Properties.Resources.Off;
            this.pictureBox_Motor_1.Image = global::MultiSensorTest.Properties.Resources.Off;
            this.pictureBox_Motor_3.Image = global::MultiSensorTest.Properties.Resources.Off;
            actCheckErrorCount = 0;
        }

        private void button_Up_Click(object sender, EventArgs e)
        {
            ActionStatus = 0;
            actCount = 0;
            CtrStep = 0;
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
            Disable_Status();
        }

        private void button_Down_Click(object sender, EventArgs e)
        {
            ActionStatus = 0; 
            actCount = 0;
            CtrStep = 1;
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
            Disable_Status();
        }

        private void button_Stop_Click(object sender, EventArgs e)
        {
            ActionStatus = 0;
            actCount = 0;
            CtrStep = 2;
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
            Disable_Status();
        }

        private void Motor_CheckReadCmd()
        {
            if (b_ReadCmdEnable)
            {
                if (readCmdCnt > 10)
                {
                    if (st_Motor1Status.Motor_Speed == 0 && 
                        st_Motor2Status.Motor_Speed == 0 &&
                        st_Motor3Status.Motor_Speed == 0 &&
                        st_Motor4Status.Motor_Speed == 0)
                    {
                        CtrStep = 0xff;
                        readCmdCnt = 0;
                        b_ReadCmdEnable = false;
                    }
                }
                readCmdCnt++;
            }
        }

        private void Motor_CtrolAction()
        {
            bool res = false;

            if (CtrStep > 2)
            {
                if (CtrStep == 3)
                {
                    Motor_ReadSpeed();   //Read speed
                    if (b_StopEnable)
                    {
                        SendCmdInterval++;
                        if (SendCmdInterval > 10)
                        {
                            CtrStep = 0xff;
                            b_StopEnable = false;
                        }
                    }
                    Motor_CheckReadCmd();
                }
                return;
            }
            else
            {
                if (SendCmdInterval == 0)
                {
                    CtrStep = 3;
                    return;
                }
            }
            b_StopEnable = false;
            switch (CtrStep)
            {
                case 0:
                    res = Motor_DownRun();
                    break;
                case 1:
                    res = Motor_UpRun();
                    break;
                case 2:
                    b_StopEnable = true;
                    res = Motor_StopRun();
                    break;
                default:
                    CtrStep = 0xff;
                    return;
            }

            if (res)
            {
                SendCmdInterval--;
            }
        }

        private void timerAct_Tick(object sender, EventArgs e)
        {
            if (!b_buttonCtrl)
                return;
            Motor_RunAction();
        }

        private void Monitor_Display(bool b_mode, byte[] data, int length)
        {
            string s = "";
            if (length > 0)
            {
                if (b_mode)
                    s = "Send: ";
                else
                    s = "Recv: ";

                for (int i = 0; i < length; i++)
                {
                    s += data[i].ToString("X2");
                    s += " ";
                }
                richTextBox_Monitor.AppendText(s + "\r\n");
                st_Serial_Proxy.SerialSend(data, length);
            }
        }

        private void Motor_RunCheckLive()
        {
            MotorRunLive.Clear() ;
            if (checkBox_Motor_1.Checked)
            {
                MotorRunLive.Add( 0x01 );
            }
            if (checkBox_Motor_2.Checked)
            {
                MotorRunLive.Add(0x02);
            }
            if (checkBox_Motor_3.Checked)
            {
                MotorRunLive.Add(0x03);
            }
            if (checkBox_Motor_4.Checked)
            {
                MotorRunLive.Add(0x04);
            }
        }

        private void Motor_CheckReadSpeedLive()
        {
            actReadSpeedCount = 0;
            MotorReadSpeedLive.Clear();
            if (checkBox_ReadMotor1.Checked)
            {
                MotorReadSpeedLive.Add(0x01);
            }
            if (checkBox_ReadMotor2.Checked)
            {
                MotorReadSpeedLive.Add(0x02);
            }
            if (checkBox_ReadMotor3.Checked)
            {
                MotorReadSpeedLive.Add(0x03);
            }
            if (checkBox_ReadMotor4.Checked)
            {
                MotorReadSpeedLive.Add(0x04);
            }
        }

        private bool Motor_ReadSpeedCmd()
        {
            bool res = false;
            UInt16 crc;
            byte[] Cmd = new byte[8];

            if (MotorReadSpeedLive.Count > 0)
            {
                Cmd[0] = (byte)(MotorReadSpeedLive[actReadSpeedCount]);
                actReadSpeedCount++;
                if (actReadSpeedCount >= MotorReadSpeedLive.Count)
                {
                    actReadSpeedCount = 0;
                    res = true;
                }

                Cmd[1] = 0x03;
                Cmd[2] = 0;
                Cmd[3] = 0x10;
                Cmd[4] = 0;
                Cmd[5] = 0x0b;

                crc = st_CRC_Proxy.CRC16(Cmd, 6);
                Cmd[6] = (byte)(crc);
                Cmd[7] = (byte)(crc >> 8);

                Motor_RunCountOnLive(Cmd[0]);
                Monitor_Display(true, Cmd, 8);
            }

            return res;
        }

        private bool Motor_WriteSpeedCmd( byte type )
        {
            int Speed = 0;
            bool res = false;
            UInt16 crc;
            byte[] Cmd = { 0x01, 0x06, 0x00, 0x40, 0xFF, 0x6A, 0x49, 0xC1 };

            if (MotorRunLive.Count > 0)
            {
                Cmd[0] = (byte)(MotorRunLive[actCount]);
                Motor_RunCountOnLive(Cmd[0]);
                actCount++;
                if (actCount >= MotorRunLive.Count)
                {
                    actCount = 0;
                    res = true;
                }

                if (type == 0x01)       //上升
                {
                    Speed = -Convert.ToUInt16(textBox_Speed.Text);
                }
                else if (type == 0x02)  //下降
                {
                    Speed = Convert.ToUInt16(textBox_Speed.Text);
                }
                else                    //停止
                {
                    Speed = 0;
                }
          
                Cmd[1] = 0x06;
                Cmd[2] = 0;
                Cmd[3] = 0x40;
                Cmd[4] = (byte)(Speed >> 8);
                Cmd[5] = (byte)(Speed);

                crc = st_CRC_Proxy.CRC16(Cmd, 6);
                Cmd[6] = (byte)(crc);
                Cmd[7] = (byte)(crc >> 8);

                Monitor_Display(true, Cmd, 8);
            }

            return res;
        }

        /*
            电机控制
            mode: true---write speed
                  false--Read speed
        */
        private bool Motor_Control(byte type, bool mode)
        {
            bool res = false;
            if (mode)
            {
                res = Motor_WriteSpeedCmd(type);
            }
            else
            {
                res = Motor_ReadSpeedCmd();
            }

            return res;
        }

        /*
            电机控制
            mode: true---write speed
                  false--Read speed
        */

        private bool Motor_UpRun()
        {
            return Motor_Control(0x01, true);
        }

        private bool Motor_DownRun()
        {
            return Motor_Control(0x02, true);
        }

        private bool Motor_StopRun()
        {
            return Motor_Control(0x03, true);
        }

        private bool Motor_ReadSpeed()
        {
            return Motor_Control(0, false);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            richTextBox_Monitor.Clear();
        }

        private void Motortest_FormClosed(object sender, FormClosedEventArgs e)
        {
            dataHandler.Abort();
            st_Serial_Proxy.SerialPort_Stop();
            Application.Exit();
        }

        private void checkBox_AllMotor_CheckedChanged(object sender, EventArgs e)
        {
            Motor_Select();
        }

        private void checkBox_ReadAll_CheckedChanged(object sender, EventArgs e)
        {
            Motor_ReadSpeed_Select();
        }

        private void Motor_ReadSpeed_Select()
        {
            if (checkBox_ReadAll.Checked)
            {
                checkBox_ReadMotor1.Checked = true;
                checkBox_ReadMotor2.Checked = true;
                checkBox_ReadMotor3.Checked = true;
                checkBox_ReadMotor4.Checked = true;
            }
            else
            {
                checkBox_ReadMotor1.Checked = false;
                checkBox_ReadMotor2.Checked = false;
                checkBox_ReadMotor3.Checked = false;
                checkBox_ReadMotor4.Checked = false;
            }
        }

        private void Motor_Select()
        {
            if (checkBox_AllMotor.Checked)
            {
                checkBox_Motor_1.Checked = true;
                checkBox_Motor_2.Checked = true;
                checkBox_Motor_3.Checked = true;
                checkBox_Motor_4.Checked = true;
            }
            else
            {
                checkBox_Motor_1.Checked = false;
                checkBox_Motor_2.Checked = false;
                checkBox_Motor_3.Checked = false;
                checkBox_Motor_4.Checked = false;
            }
        }

        private bool AllMotor_status()
        {
            if (checkBox_Motor_1.Checked || checkBox_Motor_2.Checked ||
               checkBox_Motor_3.Checked || checkBox_Motor_4.Checked)
                return true;
            else
                return false;
        }

        private void DataCommandHander()
        {
            bool res,reswr;

            while (true)
            {
                if (st_Serial_Proxy.b_SerialReceiveReady)
                {
                    st_Serial_Proxy.b_SerialReceiveReady = false;
                    if (st_Serial_Proxy.DataLength > 0)
                    {
                        res = MotorParserReadSpeed(st_Serial_Proxy.RtBuff);
                        reswr = MotorParser_WriteSpeed(st_Serial_Proxy.RtBuff);
                        if (res || reswr )
                        {
                            Monitor_Display(false, st_Serial_Proxy.RtBuff,
                                                   st_Serial_Proxy.DataLength);
                        }
                        st_Serial_Proxy.DataLength = 0;
                    }
                }
            }
        }

        private bool Motor_CheckError()
        {
            bool res = false;

            res = Motor_ReadSpeed();   //Read speed
            if (res)
            {
                actCheckErrorCount++;
                if (actCheckErrorCount > 10)
                {
                    actCheckErrorCount = 0;
                    return true;
                }
            }

            return false;
        }

        private bool Motor_CheckStatusResult()
        {
            bool res = false;

            if(st_Motor1Status.bl_MotorStatus && st_Motor2Status.bl_MotorStatus&&
                st_Motor3Status.bl_MotorStatus && st_Motor4Status.bl_MotorStatus)
            {
                res = true;
            }

            return res;
        }

        private void Motor_RunAction()
        {
            switch ( ActionStatus)
            {
                case 0:
                    if (Motor_CheckError())
                    {
                        ActionStatus = 1;
                    }
                    break;
                case 1:
                    if (Motor_CheckStatusResult())
                    {
                        ActionStatus = 2;
                    }
                    else
                    {
                        if (st_Motor1Status.bl_MotorStatus == false)
                        {
                            richTextBox_Monitor.Text += "motor 1 error \r\n";
                        }
                        if (st_Motor2Status.bl_MotorStatus == false)
                        {
                            richTextBox_Monitor.Text += "motor 2 error\r\n";
                        }
                        if (st_Motor3Status.bl_MotorStatus == false)
                        {
                            richTextBox_Monitor.Text += "motor 3 error\r\n";
                        }
                        if (st_Motor4Status.bl_MotorStatus == false)
                        {
                            richTextBox_Monitor.Text += "motor 4 error\r\n";
                        }
                        ActionStatus = 0xff;
                    }
                    break;
                case 2:
                    Motor_CtrolAction();
                    break;
                case 3:              //Stop mode
                    break;
                default:
                    break;
            }
        }



        private void Motor_StatusRefresh(int address, bool b_res)
        {
            switch (address)
            {
                case 0x01:
                    if (b_res)
                    {
                        this.pictureBox_Motor_1.Image = global::MultiSensorTest.Properties.Resources.On;
                    }
                    else
                    {
                        this.pictureBox_Motor_1.Image = global::MultiSensorTest.Properties.Resources.Off;
                    }
                    break;
                case 0x02:
                    if (b_res)
                    {
                        this.pictureBox_Motor_2.Image = global::MultiSensorTest.Properties.Resources.On;
                    }
                    else
                    {
                        this.pictureBox_Motor_2.Image = global::MultiSensorTest.Properties.Resources.Off;
                    }
                    break;
                case 0x03:
                    if (b_res)
                    {
                        this.pictureBox_Motor_3.Image = global::MultiSensorTest.Properties.Resources.On;
                    }
                    else
                    {
                        this.pictureBox_Motor_3.Image = global::MultiSensorTest.Properties.Resources.Off;
                    }
                    break;
                case 0x04:
                    if (b_res)
                    {
                        this.pictureBox_Motor_4.Image = global::MultiSensorTest.Properties.Resources.On;
                    }
                    else
                    {
                        this.pictureBox_Motor_4.Image = global::MultiSensorTest.Properties.Resources.Off;
                    }
                    break;
            }
        }

        private void Motor_StatusOnLive(int address, bool b_res)
        {
            switch (address)
            {
                case 0x01:
                    st_Motor1Status.bl_MotorStatus = b_res;
                    break;
                case 0x02:
                    st_Motor2Status.bl_MotorStatus = b_res;
                    break;
                case 0x03:
                    st_Motor3Status.bl_MotorStatus = b_res;
                    break;
                case 0x04:
                    st_Motor4Status.bl_MotorStatus = b_res;
                    break;
            }
        }

        private void Motor_RunCountOnLive(int address )
        {
            switch (address)
            {
                case 0x01:
                    st_Motor1Status.MotorRunCtrlCnt++;
                    break;
                case 0x02:
                    st_Motor2Status.MotorRunCtrlCnt++;
                    break;
                case 0x03:
                    st_Motor3Status.MotorRunCtrlCnt++;
                    break;
                case 0x04:
                    st_Motor4Status.MotorRunCtrlCnt++;
                    break;
            }
        }

        private bool MotorParser_WriteSpeed( byte[] data )
        {
            int address;
            UInt16 crc,calCrc;
            bool res = false;

            if (data[1] == 0X06 && data[2] == 0)
            {
                crc = st_CRC_Proxy.CRC16(data, 6);
                calCrc = (UInt16)((data[7] << 8) | data[6]);
                if (crc == calCrc)
                {
                    address = data[0];
                    res = true;
                    Motor_StatusRefresh(address, res);
                    Motor_StatusOnLive(address, res);
                }
            }

            return res;
        }

        private bool MotorParserReadSpeed(byte[] data)
        {
            bool res = false;
            string strSpeed = "";
            UInt16 crc;

            if (data[1] == 0X03 && data[2] == 0X16)
            {
                crc = st_CRC_Proxy.CRC16(data, 25);
                str_MotorRead.Crc = (UInt16)((data[26] << 8) | data[25]);
                if (crc == str_MotorRead.Crc)
                {
                    str_MotorRead.Address = data[0];
                    str_MotorRead.PWM = (float)(((data[3] << 8) | data[4])* 0.001);
                    str_MotorRead.CirecValue = (float)((data[5] << 8 | data[6]) * 0.01);
                    str_MotorRead.Freq = (Int16)((data[7] << 8) | data[8]);
                    str_MotorRead.duStatus = data[24];

                    strSpeed = str_MotorRead.PWM.ToString() + "   " + str_MotorRead.CirecValue.ToString();
                    if (str_MotorRead.Address == 0x01)
                    {
                        textBox_Motor1_Cir.Text = str_MotorRead.CirecValue.ToString();
                        textBox_Motor1_PWM.Text = str_MotorRead.PWM.ToString();
                        textBox1_Freq.Text = str_MotorRead.Freq.ToString();
                        textBox1_dzhuan.Text = str_MotorRead.duStatus.ToString();
                        File.AppendAllText(LogMotorSpeed1, strSpeed);
                        st_Motor1Status.Motor_Speed = str_MotorRead.Freq;
                    }
                    else if (str_MotorRead.Address == 0x02)
                    {
                        textBox_Motor2_Cir.Text = str_MotorRead.CirecValue.ToString();
                        textBox_Motor2_PWM.Text = str_MotorRead.PWM.ToString();
                        textBox2_Freq.Text = str_MotorRead.Freq.ToString();
                        textBox2_dzhuan.Text = str_MotorRead.duStatus.ToString();

                        File.AppendAllText(LogMotorSpeed2, strSpeed);
                        st_Motor2Status.Motor_Speed = str_MotorRead.Freq;
                    }
                    else if (str_MotorRead.Address == 0x03)
                    {
                        textBox_Motor3_Cir.Text = str_MotorRead.CirecValue.ToString();
                        textBox_Motor3_Speed.Text = str_MotorRead.PWM.ToString();
                        textBox3_Freq.Text = str_MotorRead.Freq.ToString();
                        textBox3_dzhuan.Text = str_MotorRead.duStatus.ToString();

                        File.AppendAllText(LogMotorSpeed3, strSpeed);
                        st_Motor3Status.Motor_Speed = str_MotorRead.Freq;
                    }
                    else if (str_MotorRead.Address == 0x04)
                    {
                        textBox_Motor4_Cir.Text = str_MotorRead.CirecValue.ToString();
                        textBox_Motor4_PWM.Text = str_MotorRead.PWM.ToString();
                        textBox4_Freq.Text = str_MotorRead.Freq.ToString();
                        textBox4_dzhuan.Text = str_MotorRead.duStatus.ToString();

                        File.AppendAllText(LogMotorSpeed4, strSpeed);
                        st_Motor4Status.Motor_Speed = str_MotorRead.Freq;
                    }

                    res = true;
                    Motor_StatusRefresh(str_MotorRead.Address, res);
                    Motor_StatusOnLive(str_MotorRead.Address, res);
                }
            }

            return res;
        }
    }

    public class MotorReadSpeed
    {
        public Byte Address;
        public Byte Cmd;
        public Byte Lenght;
        public float PWM;
        public Int16 Speed;
        public float CirecValue;
        public Byte duStatus;
        public Int16 Freq;
        public UInt16 Crc;
    }

    public class MotorStatus
    {
        public bool bl_MotorStatus;
        public int MotorRunCtrlCnt;
        public int Motor_Speed = 0;
    }
}

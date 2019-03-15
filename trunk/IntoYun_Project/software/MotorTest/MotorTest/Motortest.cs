using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ControlPoxy;
using System.Windows.Forms;
using System.Threading;
using System.IO;

namespace MotorTest
{
    public partial class Motortest : Form
    {
        private MotorReadSpeed str_MotorRead = new MotorReadSpeed();
        private ControlPoxy.Serial_Proxy st_Serial_Proxy = new ControlPoxy.Serial_Proxy();
        private ControlPoxy.CRC_Proxy st_CRC_Proxy = new ControlPoxy.CRC_Proxy();

        private string LogMotorSpeed1 = "";
        private string LogMotorSpeed2 = "";
        private string LogMotorSpeed3 = "";
        private string LogMotorSpeed4 = "";

        private int Motor1_Speed = 0;
        private int Motor2_Speed = 0;
        private int Motor3_Speed = 0;
        private int Motor4_Speed = 0;

        private Thread dataHandler;
        private int SendCmdInterval = 0;
        private int CtrStep = 0xff;
        private int Upstep = 0;
        private int readCmdCnt = 0;
        private Boolean b_buttonCtrl = false;
        private Boolean b_StopEnable = false;
        private Boolean b_ReadCmdEnable = false;
        private String ComPort = "COM1";
        string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置

        public Motortest()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
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

            button_Contrl(false);
            textBox_inteval.Text = "50";
            textBox_Cmd.Text = "5";
            textBox_Speed.Text = "150";

            checkBox_AllMotor.Checked = true;

            checkBox_Motor_1.Checked = true;
            checkBox_Motor_2.Checked = true;
            checkBox_Motor_3.Checked = true;
            checkBox_Motor_4.Checked = true;

            LogMotorSpeed1 = System.Environment.CurrentDirectory + "\\Motor_1.log";
            LogMotorSpeed2 = System.Environment.CurrentDirectory + "\\Motor_2.log";
            LogMotorSpeed3 = System.Environment.CurrentDirectory + "\\Motor_3.log";
            LogMotorSpeed4 = System.Environment.CurrentDirectory + "\\Motor_4.log";

            //串口数据处理线程
            dataHandler = new Thread(DataCommandHander);
            dataHandler.Start();

            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
        }

        private void timeCtrl()
        {
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
            timerAction.Interval = Convert.ToUInt16(textBox_inteval.Text);
            timerAction.Start();
        }

        private void button_Enable_Click(object sender, EventArgs e)
        {
            st_Serial_Proxy.Baud = int.Parse(comboBox_Baud.Text);    //设置Baud
            st_Serial_Proxy.Comport = comboBox_ComPort.Text;         //获取端口号
            st_Serial_Proxy.Parity = System.IO.Ports.Parity.Even;    //偶校验
            st_Serial_Proxy.TimeOut = 0;

            if (b_buttonCtrl == false)
            {
                button_Enable.Text = "关闭串口";
                b_buttonCtrl = true;
                st_Serial_Proxy.SerialPort_Start();
                comboBox_Baud.Enabled = false;
                comboBox_ComPort.Enabled = false;
                timeCtrl();
            }
            else
            {
                button_Enable.Text = "打开串口";
                b_buttonCtrl = false;
                st_Serial_Proxy.SerialPort_Stop();
                comboBox_Baud.Enabled = true;
                comboBox_ComPort.Enabled = true;
                CtrStep = 0xff;
            }

            button_Contrl( b_buttonCtrl );
        }

        private void button_Contrl( bool b_ctrl )
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
            }
        }

        private void button_Up_Click(object sender, EventArgs e)
        {
            Upstep = 0;
            CtrStep = 0;
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
        }

        private void button_Down_Click(object sender, EventArgs e)
        {
            CtrStep = 1;
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
        }

        private void button_Stop_Click(object sender, EventArgs e)
        {
            CtrStep = 2;
            SendCmdInterval = Convert.ToUInt16(textBox_Cmd.Text);
        }

        private void Motor_CheckReadCmd()
        {
            if ( b_ReadCmdEnable )
            {
                if (readCmdCnt > 10)
                {
                    if (Motor1_Speed == 0 && Motor2_Speed == 0 &&
                       Motor3_Speed == 0 && Motor4_Speed == 0)
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
            switch ( CtrStep )
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

        private void timerAction_Tick(object sender, EventArgs e)
        {
            if (!b_buttonCtrl)
                return;
            Motor_CtrolAction();
        }

        private void Monitor_Display(bool b_mode, byte[] data, int length)
        {
            string s ="";
            if (length > 0)
            {
                if(b_mode)
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

        /*
            电机控制
            mode: true---write speed
                  false--Read speed
        */
        private bool Motor_Control( byte type, bool mode )
        {
            bool b_SendEnable = false;
            int Speed=0;
            bool res = false;
            UInt16 crc;
            byte addr = 0x01;
            byte[] Cmd = { 0x01, 0x06, 0x00, 0x40, 0xFF, 0x6A, 0x49, 0xC1 };

            if (!AllMotor_status())
                return false;

            switch (Upstep)
            {
                case 0:
                    if (checkBox_Motor_1.Checked)
                    {
                        addr = 0x01;
                        b_SendEnable = true;
                    }
                    else
                    {
                        b_SendEnable = false;
                    }
                    Upstep = 1;
                    break;
                case 1:
                    if (checkBox_Motor_2.Checked)
                    {
                        addr = 0x02;
                        b_SendEnable = true;
                    }
                    else
                    {
                        b_SendEnable = false;
                    }
                    Upstep = 2;
                    break;
                case 2:
                    if (checkBox_Motor_3.Checked)
                    {
                        addr = 0x03;
                        b_SendEnable = true;
                    }
                    else
                    {
                        b_SendEnable = false;
                    }
                    Upstep = 3;
                    break;
                case 3:
                    if (checkBox_Motor_4.Checked)
                    {
                        addr = 0x04;
                        b_SendEnable = true;
                    }
                    else
                    {
                        b_SendEnable = false;
                    }
                    Upstep = 0;
                    res = true;
                    break;
            }

            if (b_SendEnable)
            {
                Cmd[0] = addr;
                if (mode)                   // write speed 
                {
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
                }
                else   //Read speed
                {
                    Cmd[1] = 0x03;
                    Cmd[2] = 0;
                    Cmd[3] = 0x10;
                    Cmd[4] = 0;
                    Cmd[5] = 0x02;
                }

                crc = st_CRC_Proxy.CRC16(Cmd, 6);
                Cmd[6] = (byte)(crc);
                Cmd[7] = (byte)(crc >> 8);

                Monitor_Display(true, Cmd, 8);
                b_ReadCmdEnable = true;
            }

            return res;
        }

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
            bool res;
            while (true)
            {
                if (st_Serial_Proxy.b_SerialReceiveReady)
                {
                    st_Serial_Proxy.b_SerialReceiveReady = false;
                    if (st_Serial_Proxy.DataLength > 0)
                    {
                        res = MotorParserReadSpeed(st_Serial_Proxy.RtBuff);
                        if (res)
                        { 
                            Monitor_Display(false, st_Serial_Proxy.RtBuff,
                                                   st_Serial_Proxy.DataLength);
                        }
                        st_Serial_Proxy.DataLength = 0;
                    }
                }
            }
        }

        private bool MotorParserReadSpeed(byte[] data)
        {
            bool res = false;
            string strSpeed = "";
            UInt16 crc;

            if (data[1] == 0X03 && data[2] == 0X04)
            {
                crc = st_CRC_Proxy.CRC16(data, 7);
                str_MotorRead.Crc = (UInt16)((data[8] << 8) | data[7]);
                if (crc == str_MotorRead.Crc)
                {
                    str_MotorRead.Address = data[0];
                    str_MotorRead.CirecValue = (float)((data[3] << 8 | data[4]) * 0.01);
                    str_MotorRead.Speed = (Int16)((data[5] << 8) | data[6]);
                    strSpeed = str_MotorRead.Speed.ToString() + "   " + str_MotorRead.CirecValue.ToString();
                    if (str_MotorRead.Address == 0x01)
                    {
                        textBox_Motor1_Cir.Text = str_MotorRead.CirecValue.ToString();
                        textBox_Motor1_Speed.Text = str_MotorRead.Speed.ToString();
                        File.AppendAllText(LogMotorSpeed1, strSpeed);
                        Motor1_Speed = str_MotorRead.Speed;
                    }
                    else if (str_MotorRead.Address == 0x02)
                    {
                        textBox_Motor2_Cir.Text = str_MotorRead.CirecValue.ToString();
                        textBox_Motor2_Speed.Text = str_MotorRead.Speed.ToString();
                        File.AppendAllText(LogMotorSpeed2, strSpeed);
                        Motor2_Speed = str_MotorRead.Speed;
                    }
                    else if (str_MotorRead.Address == 0x03)
                    {
                        textBox_Motor3_Cir.Text = str_MotorRead.CirecValue.ToString();
                        textBox_Motor3_Speed.Text = str_MotorRead.Speed.ToString();
                        File.AppendAllText(LogMotorSpeed3, strSpeed);
                        Motor3_Speed = str_MotorRead.Speed;
                    }
                    else if (str_MotorRead.Address == 0x04)
                    {
                        textBox_Motor4_Cir.Text = str_MotorRead.CirecValue.ToString();
                        textBox_Motor4_Speed.Text = str_MotorRead.Speed.ToString();
                        File.AppendAllText(LogMotorSpeed4, strSpeed);
                        Motor4_Speed = str_MotorRead.Speed;
                    }

                    res = true;
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
        public Int16 Speed;
        public float CirecValue;
        public UInt16 Crc;
    };
}

/* End of this file */

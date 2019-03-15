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

namespace MotorSimulation
{
    public partial class Motor : Form
    {
        private byte Motor1_Step = 0;
        private byte Motor2_Step = 0;
        private byte Motor3_Step = 0;
        private byte Motor4_Step = 0;

        private int Motor1_speed = 0;
        private int Motor2_speed = 0;
        private int Motor3_speed = 0;
        private int Motor4_speed = 0;

        private int Motor1_Circu = 0;
        private int Motor2_Circu = 0;
        private int Motor3_Circu = 0;
        private int Motor4_Circu = 0;

        private MotorReadSpeed str_MotorRead = new MotorReadSpeed();
        private MotorWriteSpeed str_MotorWrite = new MotorWriteSpeed();

        Thread dataHandler;
        private Boolean b_buttonCtrl = false;
        ControlPoxy.Serial_Proxy st_Serial_Proxy = new ControlPoxy.Serial_Proxy();
        ControlPoxy.CRC_Proxy st_CRC_Proxy = new ControlPoxy.CRC_Proxy();
        private String ComPort = "COM1";
        string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置

        public Motor()
        {
            InitializeComponent();
        }

        private void Motor_ParserInit()
        {
             Motor1_Step = 0;
             Motor2_Step = 0;
             Motor3_Step = 0;
             Motor4_Step = 0;

             Motor1_speed = 0;
             Motor2_speed = 0;
             Motor3_speed = 0;
             Motor4_speed = 0;

             Motor4_Cir_Init();
        }

        void Motor4_Cir_Init()
        {
            Motor1_Cir.Text = " ";
            Motor2_Cir.Text = " ";
            Motor3_Cir.Text = " ";
            Motor4_Cir.Text = " ";
        }

        private void Motor_Load(object sender, EventArgs e)
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

            Motor_ParserInit();
        }

        private void Motor_FormClosed(object sender, FormClosedEventArgs e)
        {
            st_Serial_Proxy.SerialPort_Stop();
            if(b_buttonCtrl )
            {
                dataHandler.Abort();
            }
            Application.Exit();
        }

        private void DataCommandHander()
        {
            bool res;
            while (true)
            {
                if (st_Serial_Proxy.DataLength > 0)
                {
                    Monitor_Display(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, true);
                    res = Motor_ParserAndRespReadSeed(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                    if (res)
                    {
                        st_Serial_Proxy.DataLength = 0;
                    }
                    res = Motor_ParserReadSpeed(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength );
                    if (res)
                    {
                        st_Serial_Proxy.DataLength = 0;
                    }
                    res = Motor_ParserWriteSpeed(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength);
                    if (res)
                    {
                        st_Serial_Proxy.DataLength = 0;
                    }
                    st_Serial_Proxy.DataLength = 0;
                }
            }
        }

        private void button_CommCtrl_Click(object sender, EventArgs e)
        {
            bool res = false;

            st_Serial_Proxy.Baud = int.Parse(comboBox_Baud.Text);    //设置Baud
            st_Serial_Proxy.Comport = comboBox_ComPort.Text;         //获取端口号
            st_Serial_Proxy.Parity = System.IO.Ports.Parity.Even;    //偶校验
            st_Serial_Proxy.TimeOut = 50;

            if (b_buttonCtrl == false)
            {
                res = st_Serial_Proxy.SerialPort_Start();
                if (res)
                {
                    button_CommCtrl.Text = "关闭串口";
                    b_buttonCtrl = true;

                    comboBox_Baud.Enabled = false;
                    comboBox_ComPort.Enabled = false;
                    dataHandler = new Thread(DataCommandHander);
                    dataHandler.Start();
                }
            }
            else
            {
                button_CommCtrl.Text = "打开串口";
                b_buttonCtrl = false;
                st_Serial_Proxy.SerialPort_Stop();
                comboBox_Baud.Enabled = true;
                comboBox_ComPort.Enabled = true;
                Motor_ParserInit();
                dataHandler.Abort();
            }
        }

        private void Motor_ReadParmaterStimu(byte address, int speed, int circu)
        {
            byte[] data  = new byte[32];
            UInt16 crc;
            int len = 0;


            data[len++] = address;
            data[len++] = 0x03;
            data[len++] = 0X16;

            data[len++] = (byte)(circu >> 8);
            data[len++] = (byte)circu;

            data[len++] = (byte)(speed >> 8);
            data[len++] = (byte)speed;

            for (int i = 0; i < 9; i++)
            {
                data[len++] = (byte)(speed >> 8);
                data[len++] = (byte)speed;
            }

            crc = st_CRC_Proxy.CRC16(data, len);
            data[len++] = (byte)(crc);
            data[len++] = (byte)(crc>>8);

            st_Serial_Proxy.SerialSend(data, len);
            Monitor_Display(data, len, false);
        }

        private bool Motor_ParserAndRespReadSeed(byte[] data, int len )
        {
            byte address;
            UInt16 crc;
            UInt16 Calcrc;
            Random rd = new Random();

            if (len == 0)
                return false;

            if (data[1] == 0X03 && data[3] == 0X10)
            {
                address = data[0];
                crc = st_CRC_Proxy.CRC16(data, 6);
                Calcrc = (UInt16)((data[7] << 8) | data[6]);
                if (crc == Calcrc)
                {
                    switch (address)
                    {
                        case 0x01:
                            Motor1_Circu = rd.Next(10, 20);
                            Motor_ReadParmaterStimu(address, Motor1_speed, Motor1_Circu);
                            break;
                        case 0x02:
                            Motor2_Circu = rd.Next(10, 20);
                            Motor_ReadParmaterStimu(address, Motor2_speed, Motor2_Circu);
                            break;
                        case 0x03:
                            Motor3_Circu = rd.Next(10, 20);
                            Motor_ReadParmaterStimu(address, Motor3_speed, Motor3_Circu);
                            break;
                        case 0x04:
                            Motor4_Circu = rd.Next(10, 20);
                            Motor_ReadParmaterStimu(address, Motor4_speed, Motor4_Circu);
                            break;
                    }
                    Motor_ParamaterRefresh();
                    return true;
                }
            }

            return false;
        }

        private void Motor_ParamaterRefresh()
        {
            Motor1_Cir.Text = Motor1_Circu.ToString();
            Motor2_Cir.Text = Motor2_Circu.ToString();
            Motor3_Cir.Text = Motor3_Circu.ToString();
            Motor4_Cir.Text = Motor4_Circu.ToString();
        }

        private bool Motor_ParserReadSpeed(byte[] data, int len )
        {
            UInt16 crc;

            if (len == 0)
                return false;

            if (data[1] == 0X03 && data[2] == 0X04)
            {
                crc = st_CRC_Proxy.CRC16(data, 7);
                str_MotorRead.Crc = (UInt16)((data[7] << 8) | data[8]);
                if (crc == str_MotorRead.Crc)
                {
                    str_MotorRead.Address = data[0];
                    str_MotorRead.CirecValue = (float)((data[3] << 8 | data[4]) * 0.01);
                    str_MotorRead.Speed = (Int16)((data[5] << 8) | data[6]);
                    if (str_MotorRead.Address == 0x01)
                    {
                        Motor1_Cir.Text = str_MotorRead.CirecValue.ToString();
                        Motor1_speed = str_MotorRead.Speed;
                    }
                    else if (str_MotorRead.Address == 0x02)
                    {
                        Motor2_Cir.Text = str_MotorRead.CirecValue.ToString();
                        Motor2_speed = str_MotorRead.Speed;
                    }
                    else if (str_MotorRead.Address == 0x03)
                    {
                        Motor3_Cir.Text = str_MotorRead.CirecValue.ToString();
                        Motor3_speed = str_MotorRead.Speed;
                    }
                    else if (str_MotorRead.Address == 0x04)
                    {
                        Motor4_Cir.Text = str_MotorRead.CirecValue.ToString();
                        Motor4_speed = str_MotorRead.Speed;
                    }
                    return true;
                }
            }

            return false;
        }

        private bool Motor_ParserWriteSpeed(byte[] data, int len )
        {
            UInt16 crc;

            if (len == 0)
                return false;

            if (data[1] == 0X06 && data[3] == 0X40)
            {
                crc = st_CRC_Proxy.CRC16(data, 6);
                str_MotorWrite.Crc = (UInt16)((data[7] << 8) | data[6]);
                if (crc == str_MotorWrite.Crc)
                {
                    str_MotorWrite.Address = data[0];
                    str_MotorWrite.Speed = (Int16)((data[4] << 8) | data[5]);

                    if (str_MotorWrite.Address == 0x01)
                    {
                        Motor1_speed = str_MotorWrite.Speed;
                        Motor1_Speed.Text = str_MotorWrite.Speed.ToString();
                        if (Motor1_speed == 0)
                            Motor1_Circu = 0;
                        else
                            Motor1_Circu = 10;

                        Motor1_Cir.Text = Motor1_Circu.ToString();
                    }
                    else if (str_MotorWrite.Address == 0x02)
                    {
                        Motor2_speed = str_MotorWrite.Speed;
                        Motor2_Speed.Text = str_MotorWrite.Speed.ToString();
                        if (Motor2_speed == 0)
                            Motor2_Circu = 0;
                        else
                            Motor2_Circu = 10;

                        Motor2_Cir.Text = Motor2_Circu.ToString();
                    }
                    else if (str_MotorWrite.Address == 0x03)
                    {
                        Motor3_speed = str_MotorWrite.Speed;
                        Motor3_Speed.Text = str_MotorWrite.Speed.ToString();
                        if (Motor3_speed == 0)
                            Motor3_Circu = 0;
                        else
                            Motor3_Circu = 10;

                        Motor3_Cir.Text = Motor3_Circu.ToString();
                    }
                    else if (str_MotorWrite.Address == 0x04)
                    {
                        Motor4_speed = str_MotorWrite.Speed;
                        Motor4_Speed.Text = str_MotorWrite.Speed.ToString();
                        if (Motor4_speed == 0)
                            Motor4_Circu = 0;
                        else
                            Motor4_Circu = 10;

                        Motor4_Cir.Text = Motor4_Circu.ToString();
                    }

                    //Motor_ResponseWriteSpeed(str_MotorWrite.Address, str_MotorWrite.Speed);
                    st_Serial_Proxy.SerialSend(data, 8);
                    Monitor_Display(data, 8, false );
                    return true;
                }
            }

            return false;
        }

        private void Motor_ResponseWriteSpeed( byte address, int speed )
        {
            byte[] data = new byte[32];
            UInt16 crc;
            int len = 0;


            data[len++] = address;
            data[len++] = 0x06;
            data[len++] = 0;
            data[len++] = 0;

            data[len++] = (byte)(speed >> 8);
            data[len++] = (byte)speed;

            crc = st_CRC_Proxy.CRC16(data, len);
            data[len++] = (byte)(crc);
            data[len++] = (byte)(crc >> 8);

            st_Serial_Proxy.SerialSend(data, len);
            Monitor_Display(data, len, false);
        }

        private void Motor1_Run( int speed )
        { 

            if( speed > 0 )
            {
                switch( Motor1_Step )
                {
                    case 0:
                        this.pictureBox_Motor1.Image = global::MotorSimulation.Properties.Resources.run1;
                        Motor1_Step = 1;
                        break;
                    case 1:
                        this.pictureBox_Motor1.Image = global::MotorSimulation.Properties.Resources.run2;
                        Motor1_Step = 2;
                        break;
                    case 2:
                        this.pictureBox_Motor1.Image = global::MotorSimulation.Properties.Resources.run3;
                        Motor1_Step = 0;
                        break;
                }
            }
            else if (speed < 0)
            {
                switch (Motor1_Step)
                {
                    case 0:
                        this.pictureBox_Motor1.Image = global::MotorSimulation.Properties.Resources.run3;
                        Motor1_Step = 1;
                        break;
                    case 1:
                        this.pictureBox_Motor1.Image = global::MotorSimulation.Properties.Resources.run2;
                        Motor1_Step = 2;
                        break;
                    case 2:
                        this.pictureBox_Motor1.Image = global::MotorSimulation.Properties.Resources.run1;
                        Motor1_Step = 0;
                        break;
                }
            }

            Motor1_Speed.Text = speed.ToString();
        }

        private void Motor2_Run(int speed)
        {
            if ( speed > 0)
            {
                switch (Motor2_Step)
                {
                    case 0:
                        this.pictureBox_Motor2.Image = global::MotorSimulation.Properties.Resources.run1;
                        Motor2_Step = 1;
                        break;
                    case 1:
                        this.pictureBox_Motor2.Image = global::MotorSimulation.Properties.Resources.run2;
                        Motor2_Step = 2;
                        break;
                    case 2:
                        this.pictureBox_Motor2.Image = global::MotorSimulation.Properties.Resources.run3;
                        Motor2_Step = 0;
                        break;
                }
            }
            else if(speed < 0 )
            {
                switch (Motor2_Step)
                {
                    case 0:
                        this.pictureBox_Motor2.Image = global::MotorSimulation.Properties.Resources.run3;
                        Motor2_Step = 1;
                        break;
                    case 1:
                        this.pictureBox_Motor2.Image = global::MotorSimulation.Properties.Resources.run2;
                        Motor2_Step = 2;
                        break;
                    case 2:
                        this.pictureBox_Motor2.Image = global::MotorSimulation.Properties.Resources.run1;
                        Motor2_Step = 0;
                        break;
                }
            }
            Motor2_Speed.Text = speed.ToString();
        }

        private void Motor3_Run(int speed)
        {
            if ( speed > 0)
            {
                switch (Motor3_Step)
                {
                    case 0:
                        this.pictureBox_Motor3.Image = global::MotorSimulation.Properties.Resources.run1;
                        Motor3_Step = 1;
                        break;
                    case 1:
                        this.pictureBox_Motor3.Image = global::MotorSimulation.Properties.Resources.run2;
                        Motor3_Step = 2;
                        break;
                    case 2:
                        this.pictureBox_Motor3.Image = global::MotorSimulation.Properties.Resources.run3;
                        Motor3_Step = 0;
                        break;
                }
            }
            else if( speed < 0)
            {
                switch (Motor3_Step)
                {
                    case 0:
                        this.pictureBox_Motor3.Image = global::MotorSimulation.Properties.Resources.run3;
                        Motor3_Step = 1;
                        break;
                    case 1:
                        this.pictureBox_Motor3.Image = global::MotorSimulation.Properties.Resources.run2;
                        Motor3_Step = 2;
                        break;
                    case 2:
                        this.pictureBox_Motor3.Image = global::MotorSimulation.Properties.Resources.run1;
                        Motor3_Step = 0;
                        break;
                }
            }
            Motor3_Speed.Text = speed.ToString();
        }

        private void Motor4_Run(int speed)
        {
            if (speed > 0)
            {
                switch (Motor4_Step)
                {
                    case 0:
                        this.pictureBox_Motor4.Image = global::MotorSimulation.Properties.Resources.run1;
                        Motor4_Step = 1;
                        break;
                    case 1:
                        this.pictureBox_Motor4.Image = global::MotorSimulation.Properties.Resources.run2;
                        Motor4_Step = 2;
                        break;
                    case 2:
                        this.pictureBox_Motor4.Image = global::MotorSimulation.Properties.Resources.run3;
                        Motor4_Step = 0;
                        break;
                }
            }
            else if(speed < 0)
            {
                switch (Motor4_Step)
                {
                    case 0:
                        this.pictureBox_Motor4.Image = global::MotorSimulation.Properties.Resources.run3;
                        Motor4_Step = 1;
                        break;
                    case 1:
                        this.pictureBox_Motor4.Image = global::MotorSimulation.Properties.Resources.run2;
                        Motor4_Step = 2;
                        break;
                    case 2:
                        this.pictureBox_Motor4.Image = global::MotorSimulation.Properties.Resources.run1;
                        Motor4_Step = 0;
                        break;
                }
            }
            Motor4_Speed.Text = speed.ToString();
        }

        private void Motor_Run_Ctrl()
        {
            if (!b_buttonCtrl)
                return;

            Motor1_Run(Motor1_speed);
            Motor2_Run(Motor2_speed);
            Motor3_Run(Motor3_speed);
            Motor4_Run(Motor4_speed);
        }
        private void timerAct_Tick(object sender, EventArgs e)
        {
            Motor_Run_Ctrl();
        }

        #region monitor

        private void Monitor_Display(byte[] buff, int lenght, bool type)
        {
            if (type)
                richTextBox_Monitor.AppendText("\r\nRecv:" + "\r\n");
            else
                richTextBox_Monitor.AppendText("\r\nSend:" + "\r\n");

            Monitor_Printf(buff, lenght);
        }

        private void Moitor_String(string str, bool type)
        {
            if (type)
                richTextBox_Monitor.AppendText("\r\n" + "Recv:");
            else
                richTextBox_Monitor.AppendText("\r\n" + "Send:");

            richTextBox_Monitor.AppendText("\r\n" + str + "\r\n");
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

        #endregion

        private void button_Clear_Click(object sender, EventArgs e)
        {
            richTextBox_Monitor.Text = "";
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

    public class MotorWriteSpeed
    {
        public Byte Address;
        public Byte Cmd;
        public Byte Lenght;
        public int Speed;
        public UInt16 Crc;
    };
}

/* End of this file */

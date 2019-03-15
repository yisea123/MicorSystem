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
using ControlPoxy;
using ZedGraph;

namespace MultiSensorTest
{
    public partial class jdSensor : UserControl
    {
        #region 变量定义区
        private byte ReadActAddress;
        private byte Modbusaddress;
        private byte step = 0xff;
        private bool b_ReadSensorValue = false;

        private short x_Value, y_Value;
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

        PointPairList list1;
        PointPairList list2;

        PointPairList list3;
        PointPairList list4;

        #endregion

        #region 初始化
        public jdSensor()
        {
            InitializeComponent();
        }

        public void jdSensor_Stop()
        {
            if (b_SerialEable)
            {
                st_Serial_Proxy.SerialPort_Stop();
                dataHandler.Abort();
            }
        }

        private void jdSensor_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            Serial_ConfigInit();
            SerialPort_IniInit();

            list1 = new PointPairList();
            list2 = new PointPairList();
            list3 = new PointPairList();
            list4 = new PointPairList();
            CreateGraph(zedGraphControl);

            button_Contrl(b_SerialEable);
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
                        res = st_DeviceCtrl_Proxy.InclinometerSenor_Parser(st_Serial_Proxy.RtBuff, st_Serial_Proxy.DataLength, out x_Value, out y_Value);
                        if (res)
                        {
                            Modbusaddress = st_Serial_Proxy.RtBuff[0];
                            Printf_SensorValue( Modbusaddress ); 
                            Parser_jdSensorValue( Modbusaddress );
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
                jdSensor_Stop();
                button_Enable.Text = "打开串口";
                b_SerialEable = false;
                st_Serial_Proxy.SerialPort_Stop();
                comboBox_Baud.Enabled = true;
                comboBox_ComPort.Enabled = true;
            }

            button_Contrl( b_SerialEable );
            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Sensor_Serial", "Baud", st_Serial_Proxy.Baud.ToString());
            st_ConfigIni.SetProjectInfor2Ini(sysCondigIni, "Sensor_Serial", "Port", st_Serial_Proxy.Comport);

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

        #region 倾角传感器

        private void timerAct_Tick(object sender, EventArgs e)
        {
            if (b_ReadSensorValue && b_SerialEable)
            {
                ReadSensor_ValueAction();
            }
        }

        private void Printf_SensorValue(byte addres)
        {
            switch (addres)
            {
                case 1:
                    textBox_Value_X.Text = (x_Value * 0.1).ToString("f2");
                    textBox_Value_Y.Text = (y_Value * 0.1).ToString("f2");
                    textBox1_address.Text = addres.ToString();
                    break;
                case 2:
                    textBox2_Value_X.Text = (x_Value * 0.1).ToString("f2");
                    textBox2_Value_Y.Text = (y_Value * 0.1).ToString("f2");
                    textBox2_Address.Text = addres.ToString();
                    break;
            }
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
                    ReadActAddress = 1;
                    break;
                case 1:
                    byte[] CmdInitExt = new byte[] { 0x02, 0x03, 0, 0x5D, 0, 0x02, 0x55, 0xEA };

                    CmdInitExt[0] = ReadActAddress;
                    int crc = st_CRC_Proxy.CRC16(CmdInitExt, 6);
                    CmdInitExt[6] = (byte)crc;
                    CmdInitExt[7] = (byte)(crc >> 8);
                    st_Serial_Proxy.SerialSend(CmdInitExt, CmdInitExt.Length);
                    Monitor_Display(CmdInitExt, CmdInitExt.Length, false);
                    ReadActAddress++;
                    if (ReadActAddress > 2)
                        ReadActAddress = 1;
                    break;
                default:
                    break;
            }
        }
        #endregion

        #region Button_Ctrl
        private void button_ReadAddr_Click_1(object sender, EventArgs e)
        {
            byte[] CmdInit = new byte[] { 0, 0x03, 0, 0x5D, 0, 0x02, 0x55, 0xEA };

            int crc = st_CRC_Proxy.CRC16(CmdInit, 6);

            CmdInit[6] = (byte)crc;
            CmdInit[7] = (byte)(crc >> 8);
            st_Serial_Proxy.SerialSend(CmdInit, CmdInit.Length);
            Monitor_Display(CmdInit, CmdInit.Length, false);
        }

        private void button_modifyAddress_Click_1(object sender, EventArgs e)
        {
            byte[] CmdInit = new byte[] { 0, 0x06, 0, 0x03, 0, 0, 0x55, 0xEA };

            if (textBox_ModbussAddress.Text.Length == 0)
            {
                MessageBox.Show("请输入正确的通信地址");
            }
            else
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

        private void button_ReadValue_Click_1(object sender, EventArgs e)
        {
            if (textBox_ModbussAddress.Text.Length == 0)
            {
                MessageBox.Show("请先读取通信地址");
            }

           else
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

        private void button_Contrl(bool b_ctrl)
        {
            if (b_ctrl)
            {
                button_ReadAddr.Enabled = true;
                button_ReadValue.Enabled = true;
                button_modifyAddress.Enabled = true;
            }
            else
            {
                button_ReadAddr.Enabled = false;
                button_ReadValue.Enabled = false;
                button_modifyAddress.Enabled = false;
            }
        }

        #endregion

        #region Graph UI
        private void CreateGraph(ZedGraphControl zgc)
        {
            zgc.IsShowPointValues = true;

            // get a reference to the GraphPane
            GraphPane myPane = zgc.GraphPane;

            // Set the Titles
            myPane.Title.Text = "倾角传感器数据";
            myPane.YAxis.Title.Text = "X轴";
            myPane.Y2Axis.Title.Text = "Y轴";
            myPane.YAxis.Title.FontSpec.Size = 12;
            myPane.Y2Axis.Title.FontSpec.Size = 12;
            myPane.YAxis.Scale.FontSpec.Size = 10;//设置y轴的文字大小.
            myPane.Y2Axis.Scale.FontSpec.Size = 10;//设置y轴的文字大小.
            myPane.XAxis.MajorGrid.IsVisible = true;//设置x轴虚线.
            myPane.YAxis.MajorGrid.IsVisible = true;//设置Y轴虚线.
            myPane.Y2Axis.MajorGrid.IsVisible = true;//设置Y轴虚线.

            myPane.XAxis.Title.Text = "时间";
            myPane.XAxis.Type = AxisType.DateAsOrdinal;
            myPane.XAxis.Scale.FormatAuto = true;
            myPane.XAxis.Scale.Format = "hh:mm:ss";
            myPane.XAxis.Scale.MaxAuto = true;
            myPane.XAxis.Scale.FontSpec.Size = 10;//设置x轴的文字大小.

            myPane.Chart.Border.IsVisible = false;//图表区域的边框设置.
            myPane.Legend.IsVisible = false;      //图表的注释标签显示设置项目.

            // Generate a red curve with diamond
            // symbols, and "Porsche" in the legend
            LineItem myCurve1 = myPane.AddCurve("X轴",
                  list1, Color.Red, SymbolType.None);
            myCurve1.Symbol.Fill = new Fill(Color.White);
            myCurve1.Line.Width = 2;                  //设置线宽度

            // Generate a blue curve with circle
            // symbols, and "Piper" in the legend
            LineItem myCurve2 = myPane.AddCurve("Y轴",
                  list2, Color.Blue, SymbolType.None);
            myCurve2.Symbol.Fill = new Fill(Color.White);
            myCurve2.Line.Width = 2;
            // Associate this curve with the Y2 axis
            myCurve2.IsY2Axis = true;
            // Associate this curve with the second Y2 axis
            myCurve2.YAxisIndex = 2;

            LineItem myCurve3= myPane.AddCurve("X轴",
                  list3, Color.Green, SymbolType.None);
            myCurve3.Symbol.Fill = new Fill(Color.White);
            myCurve3.Line.Width = 2;                  //设置线宽度

            // Generate a blue curve with circle
            // symbols, and "Piper" in the legend
            LineItem myCurve4 = myPane.AddCurve("Y轴",
                  list4, Color.Navy, SymbolType.None);
            myCurve4.Symbol.Fill = new Fill(Color.White);
            myCurve4.Line.Width = 2;
            // Associate this curve with the Y2 axis
            myCurve4.IsY2Axis = true;
            // Associate this curve with the second Y2 axis
            myCurve4.YAxisIndex = 2;


            // Show the x axis grid
            myPane.XAxis.MajorGrid.IsVisible = true;

            // Make the Y axis scale red
            myPane.YAxis.Scale.FontSpec.FontColor = Color.Red;
            myPane.YAxis.Title.FontSpec.FontColor = Color.Red;
            // turn off the opposite tics so the Y tics don't show up on the Y2 axis
            myPane.YAxis.MajorTic.IsOpposite = false;
            myPane.YAxis.MinorTic.IsOpposite = false;
            // Don't display the Y zero line
            myPane.YAxis.MajorGrid.IsZeroLine = false;
            // Align the Y axis labels so they are flush to the axis
            myPane.YAxis.Scale.Align = AlignP.Inside;
            myPane.YAxis.Scale.Min = -100;
            myPane.YAxis.Scale.Max = 100;

            // Enable the Y2 axis display
            myPane.Y2Axis.IsVisible = true;
            // Make the Y2 axis scale blue
            myPane.Y2Axis.Scale.FontSpec.FontColor = Color.Blue;
            myPane.Y2Axis.Title.FontSpec.FontColor = Color.Blue;
            // turn off the opposite tics so the Y2 tics don't show up on the Y axis
            myPane.Y2Axis.MajorTic.IsOpposite = false;
            myPane.Y2Axis.MinorTic.IsOpposite = false;
            // Display the Y2 axis grid lines
            myPane.Y2Axis.MajorGrid.IsVisible = true;
            // Align the Y2 axis labels so they are flush to the axis
            myPane.Y2Axis.Scale.Align = AlignP.Inside;
            myPane.Y2Axis.Scale.Min = -100;
            myPane.Y2Axis.Scale.Max = 100;

            // Fill the axis background with a gradient
            myPane.Chart.Fill = new Fill(Color.White, Color.LightGoldenrodYellow, 45.0f);

            // Tell ZedGraph to reconfigure the
            // axes since the data have changed
            zgc.AxisChange();
        }

        private void Parser_jdSensorValue(byte address)
        {
            string date_time;
            DateTime now = DateTime.Now;
            double x = (double)new XDate(now);

            date_time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss:fff,");
            switch (address)
            {
                case 1:
                    list1.Add(x, x_Value * 0.01);
                    list2.Add(x, y_Value * 0.01);
                    break;
                case 2:
                    list3.Add(x, x_Value * 0.01);
                    list4.Add(x, y_Value * 0.01);
                    break;
           }

            if (list1.Count >= 120)
            {
                list1.RemoveAt(0);
            }
            if (list2.Count >= 120)
            {
                list2.RemoveAt(0);
            }

            if (list3.Count >= 120)
            {
                list3.RemoveAt(0);
            }
            if (list4.Count >= 120)
            {
                list4.RemoveAt(0);
            }

            this.zedGraphControl.GraphPane.XAxis.Title.Text = "Time (" + zedGraphControl.GraphPane.XAxis.Scale.Format + ")";
            this.zedGraphControl.AxisChange();
            this.zedGraphControl.Refresh();
        }
        #endregion
    }
}

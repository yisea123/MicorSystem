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
using ZedGraph;

namespace OpenSoftware
{
    public partial class mainWindows : Form
    {
        int countSave = 0;
        string cvsFileName = "";
        float sht2x_temp, sht2x_hum;
        int receiveIndex = -1;
        bool b_UploadEnable = false;
        bool b_buttonCtrl = false;
        Thread dataHandler;
        private String ComPort = "COM1";
        string[] StringBaud = { "115200", "57600", "38400", "19200", "9600", "4800", "2400" };  //串口波特率设置

        private Log_Proxy log = new Log_Proxy("logs");
        Util_Proxy st_unit = new Util_Proxy();
        private ControlPoxy.MCS_Protocol st_MCS_Protocol = new ControlPoxy.MCS_Protocol();
        ControlPoxy.Serial_Proxy st_Serial_Proxy = new ControlPoxy.Serial_Proxy();
        ControlPoxy.CRC_Proxy st_CRC_Proxy = new ControlPoxy.CRC_Proxy();

        PointPairList list1;
        PointPairList list2;
        public mainWindows()
        {
            InitializeComponent();
        }

        private void mainWindows_Load(object sender, EventArgs e)
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
            comboBox_Baud.SelectedIndex = 0;

            dataHandler = new Thread(DataCommandHander);
            dataHandler.Start();

            tools_cypyRight.Text = st_unit.CopyRight;
            tools_version.Text = st_unit.SoftVersion;

            toolsTime_build.Text = "Building: " + System.IO.File.GetLastWriteTime(this.GetType().Assembly.Location).ToString("F");
            textBox_DataLen.Text = "10";
            button_CtrlSht2x.Text = "Start";

            list1 = new PointPairList();
            list2 = new PointPairList();
            CreateGraph(zedGraphControl);
            //SetSize();
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
                                Parser_Sht2xValue();
                            }
                        }
                        st_Serial_Proxy.DataLength = 0;
                    }
                }
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

        private void mainWindows_FormClosed(object sender, FormClosedEventArgs e)
        {
            st_Serial_Proxy.SerialPort_Stop();
            dataHandler.Abort();
            Application.Exit();
        }

        private void button_CommCtrl_Click(object sender, EventArgs e)
        {
            st_Serial_Proxy.Baud = int.Parse(comboBox_Baud.Text);    //设置Baud
            st_Serial_Proxy.Comport = comboBox_ComPort.Text;         //获取端口号
            st_Serial_Proxy.Parity = System.IO.Ports.Parity.None;
            st_Serial_Proxy.TimeOut = 300;

            if (b_buttonCtrl == false)
            {
                button_CommCtrl.Text = "关闭串口";
                b_buttonCtrl = true;
                st_Serial_Proxy.SerialPort_Start();
                comboBox_Baud.Enabled = false;
                comboBox_ComPort.Enabled = false;
            }
            else
            {
                button_CommCtrl.Text = "打开串口";
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

        private void ShowMessage(string msg)
        {
            richTextBox_Monitor.AppendText(msg);
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

        private void CtrCmd_McsBuiding(MCS_Protocol mcs)
        {
            byte[] buff = new byte[256];
            int length = 0;

            length = mcs.MCS_Building(mcs.srcAddr, mcs.tarAddr, mcs.Frum, mcs.CMD, mcs.DataBuf, (byte)mcs.DataLen, buff);

            st_Serial_Proxy.SerialSend(buff, length);

            richTextBox_Monitor.AppendText("Send" + "\r\n");
            Monitor_Display(buff, length);
        }

        private byte DataIDConvert(string sID)
        {
            byte byteID = 0;

            try
            {
                if (sID == "")
                {
                    MessageBox.Show("请输入数据ID!");
                }
                byteID = Convert.ToByte(sID);
            }
            catch { }

            return byteID;
        }

        private void button_ProtocolSend_Click(object sender, EventArgs e)
        {
            byte DataLen = DataIDConvert(textBox_DataLen.Text);
            if (DataLen > 45)
            {
                DataLen = 45;
            }

            ShowMessage("通信协议包测试 \r\n");
            st_MCS_Protocol.srcAddr = 0;
            st_MCS_Protocol.tarAddr = 0;
            st_MCS_Protocol.Frum = 0;
            st_MCS_Protocol.CMD = 0x0010;
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


        #region FileDownload

        private void DownlaodFile_CheckCmd()
        {
            if (st_MCS_Protocol.CMD == 0x8012)
            {
                receiveIndex = st_MCS_Protocol.Frum;
            }
        }
        private void MakePacket_ByMcs(ushort DataLen, byte[] data, ushort frum)
        {
            st_MCS_Protocol.srcAddr = 0;
            st_MCS_Protocol.tarAddr = 0;
            st_MCS_Protocol.Frum = frum;
            st_MCS_Protocol.CMD = 0x0012;
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
                openbinFile.Filter = "下载文件|*.bin;*.hex;*.ZFP";
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
                        System.Threading.Thread.Sleep(350);
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

        private void button_RTC_Click(object sender, EventArgs e)
        {
            byte[] rtc = new byte[6];

            ShowMessage("时间同步 \r\n");
            rtc[0] = (byte)(DateTime.Now.Year - 2000);
            rtc[1] = (byte)(DateTime.Now.Month);
            rtc[2] = (byte)(DateTime.Now.Day);

            rtc[3] = (byte)(DateTime.Now.Hour);
            rtc[4] = (byte)(DateTime.Now.Minute);
            rtc[5] = (byte)(DateTime.Now.Second);

            st_MCS_Protocol.srcAddr = 0;
            st_MCS_Protocol.tarAddr = 0;
            st_MCS_Protocol.Frum = 0;
            st_MCS_Protocol.CMD = 0x0011;
            st_MCS_Protocol.DataLen = 6;

            for (int i = 0; i < rtc.Length; i++)
            {
                st_MCS_Protocol.DataBuf[i] = rtc[i];
            }
            CtrCmd_McsBuiding(st_MCS_Protocol);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int intervalVal = 0;
            byte[] interval = new byte[2];

            if (b_UploadEnable)
            {
                b_UploadEnable = false;
                button_CtrlSht2x.Text = "Start";
                log.Close_CvsFile();
                countSave = 0;
            }
            else
            {
                b_UploadEnable = true;
                button_CtrlSht2x.Text = "Stop";
                intervalVal = 1;
                cvsFileName = DateTime.Now.ToString("yyyy-MM-dd");
                log.Create_CvsFile( cvsFileName );
            }

            interval[0] = (byte)(intervalVal >> 8);
            interval[1] = (byte)(intervalVal);

            st_MCS_Protocol.srcAddr = 0;
            st_MCS_Protocol.tarAddr = 0;
            st_MCS_Protocol.Frum = 0;
            st_MCS_Protocol.CMD = 0x0013;
            st_MCS_Protocol.DataLen = 2;

            for (int i = 0; i < interval.Length; i++)
            {
                st_MCS_Protocol.DataBuf[i] = interval[i];
            }
            CtrCmd_McsBuiding(st_MCS_Protocol);
        }

        private void Parser_Sht2xValue()
        {
            string date_time, header_temp;
            if (st_MCS_Protocol.CMD == 0x8013 && b_UploadEnable )
            {
                if (st_MCS_Protocol.DataLen == 4)
                {
                    sht2x_temp = st_MCS_Protocol.DataBuf[0] << 8 | st_MCS_Protocol.DataBuf[1];
                    sht2x_hum = st_MCS_Protocol.DataBuf[2] << 8 | st_MCS_Protocol.DataBuf[3];

                    textBox_temp.Text = (sht2x_temp*0.01).ToString();
                    textBox_hum.Text = (sht2x_hum*0.01).ToString();

                    DateTime now = DateTime.Now;
                    double x = (double)new XDate(now);

                    date_time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss:fff,");
                    System.Threading.Thread.Sleep(100);
                    if (countSave == 0)
                    {
                        header_temp = "时间" + ",温度（℃）" + ",湿度（H%）";
                        log.Write_CvsFile( header_temp);
                    }
                    else {
                        header_temp = textBox_temp.Text +","+ textBox_hum.Text;
                        log.Write_CvsFile(date_time + header_temp);
                    }
                    countSave++;

                    list1.Add(x, sht2x_temp * 0.01);
                    list2.Add(x, sht2x_hum * 0.01);

                    if (list1.Count >= 120)
                    {
                        list1.RemoveAt(0);
                    }
                    if (list2.Count >= 120)
                    {
                        list2.RemoveAt(0);
                    }
                    this.zedGraphControl.GraphPane.XAxis.Title.Text = "Time (" + zedGraphControl.GraphPane.XAxis.Scale.Format + ")";
                    this.zedGraphControl.AxisChange();
                    this.zedGraphControl.Refresh();
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

        }

        private void SetSize()
        {
            zedGraphControl.Location = new Point(10, 50);
            // Leave a small margin around the outside of the control
            zedGraphControl.Size = new Size(ClientRectangle.Width - 20,
                                    ClientRectangle.Height - 30);
        }

        private void CreateGraph(ZedGraphControl zgc)
        {
            zgc.IsShowPointValues = true;

            // get a reference to the GraphPane
            GraphPane myPane = zgc.GraphPane;

            // Set the Titles
            myPane.Title.Text = "SHT 20 温湿度监控";
            myPane.YAxis.Title.Text = "温度";
            myPane.Y2Axis.Title.Text = "湿度";
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
            LineItem myCurve = myPane.AddCurve("温度",
                  list1, Color.Red, SymbolType.None);
            myCurve.Symbol.Fill = new Fill(Color.White);
            myCurve.Line.Width = 2;                  //设置线宽度

            // Generate a blue curve with circle
            // symbols, and "Piper" in the legend
            LineItem myCurve2 = myPane.AddCurve("湿度",
                  list2, Color.Blue, SymbolType.None);
            myCurve2.Symbol.Fill = new Fill(Color.White);
            myCurve2.Line.Width = 2;

            // Associate this curve with the Y2 axis
            myCurve2.IsY2Axis = true;
            // Associate this curve with the second Y2 axis
            myCurve2.YAxisIndex = 2;

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
            myPane.YAxis.Scale.Min = 0;
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
            myPane.Y2Axis.Scale.Min = 0;
            myPane.Y2Axis.Scale.Max = 100;

            // Fill the axis background with a gradient
            myPane.Chart.Fill = new Fill(Color.White, Color.LightGoldenrodYellow, 45.0f);

            // Tell ZedGraph to reconfigure the
            // axes since the data have changed
            zgc.AxisChange();
        }
    }
}


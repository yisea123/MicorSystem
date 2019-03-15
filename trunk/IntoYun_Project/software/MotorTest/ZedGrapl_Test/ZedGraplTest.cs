using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ZedGraph;

namespace ZedGrapl_Test
{
    public partial class ZedGraplTest : Form
    {
        PointPairList list1;
        PointPairList list2;

        public ZedGraplTest()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            list1 = new PointPairList();
            list2 = new PointPairList();

            // Setup the graph
            CreateGraph(zedGraphControl);
            SetSize();
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
            myPane.Title.Text = "1-10v/adc 动态折线图";
            myPane.YAxis.Title.Text = "电压V";
            myPane.Y2Axis.Title.Text = "码值";
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
            myPane.XAxis.Scale.Format = "ss";
            myPane.XAxis.Scale.MaxAuto = true;
            myPane.XAxis.Scale.FontSpec.Size = 10;//设置x轴的文字大小.

            myPane.Chart.Border.IsVisible = false;//图表区域的边框设置.
            myPane.Legend.IsVisible = false;      //图表的注释标签显示设置项目.

            // Generate a red curve with diamond
            // symbols, and "Porsche" in the legend
            LineItem myCurve = myPane.AddCurve("1-10v",
                  list1, Color.Red, SymbolType.None);
            myCurve.Symbol.Fill = new Fill(Color.White);
            myCurve.Line.Width = 2;                  //设置线宽度

            // Generate a blue curve with circle
            // symbols, and "Piper" in the legend
            LineItem myCurve2 = myPane.AddCurve("adc",
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
            myPane.YAxis.Scale.Max = 15;

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
            myPane.Y2Axis.Scale.Max = 15;

            // Fill the axis background with a gradient
            myPane.Chart.Fill = new Fill(Color.White, Color.LightGoldenrodYellow, 45.0f);

            // Tell ZedGraph to reconfigure the
            // axes since the data have changed
            zgc.AxisChange();
        }

        double _dimVol;
        double _dimVol2;
        double y, z;
        private void timer1_Tick(object sender, EventArgs e)
        {
            DateTime now = DateTime.Now;
            double x = (double)new XDate(now);

             y = _dimVol;
             z = _dimVol2;

            list1.Add(x, y);
            list2.Add(x, z);

            _dimVol++;
            _dimVol2++;

            if (_dimVol > 10)
                _dimVol = 0;

            if (_dimVol2 > 10)
                _dimVol2 = 0;

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
            textBox_dataCount.Text = zedGraphControl.GraphPane.CurveList[0].NPts.ToString() + " ;" + zedGraphControl.GraphPane.CurveList[1].NPts.ToString();
        }
    }
}



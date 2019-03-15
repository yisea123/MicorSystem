using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MultiSensorTest
{
    public partial class MainWin : Form
    {
        MotorCtrl st_MotorCtrl = new MotorCtrl();
        MultiSensorCtrl st_MultiSensorCtrl = new MultiSensorCtrl();
        jdSensor st_jdSensor = new jdSensor();
        DAM0404A st_DAM0404A = new DAM0404A();

        public MainWin()
        {
            InitializeComponent();
        }

        private void MainWin_Load(object sender, EventArgs e)
        {
            panel_Config.Controls.Clear();
            panel_Config.Controls.Add(st_MotorCtrl);
        }

        private void MainWin_FormClosed(object sender, FormClosedEventArgs e)
        {
            st_jdSensor.jdSensor_Stop();
            st_MotorCtrl.MotorCtrl_Stop();
            st_MultiSensorCtrl.MultiSensor_Stop();
            st_DAM0404A.DAM0404A_Stop();
            Application.Exit();
        }

        private void button_Motor_Click(object sender, EventArgs e)
        {
            panel_Config.Controls.Clear();
            panel_Config.Controls.Add(st_MotorCtrl);
        }

        private void button_sensor_Click(object sender, EventArgs e)
        {
            panel_Config.Controls.Clear();
            panel_Config.Controls.Add(st_MultiSensorCtrl);
        }

        private void button_JDsensor_Click(object sender, EventArgs e)
        {
            panel_Config.Controls.Clear();
            panel_Config.Controls.Add(st_jdSensor);
        }

        private void button_DA0404A_Click(object sender, EventArgs e)
        {
            panel_Config.Controls.Clear();
            panel_Config.Controls.Add(st_DAM0404A);
        }
    }
}

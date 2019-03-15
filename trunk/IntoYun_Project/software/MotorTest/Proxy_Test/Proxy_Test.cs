using ControlPoxy;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Proxy_Test
{
    public partial class Proxy_Test : Form
    {
        private Log_Proxy log = new Log_Proxy("logs");
        public Proxy_Test()
        {
            InitializeComponent();
        }

        private void Proxy_Test_Load(object sender, EventArgs e)
        {

        }

        private void button_Log_Click(object sender, EventArgs e)
        {
            createLogFile();
        }

        private void createLogFile()
        {
            string date_time;
            string header_temp = "luge2_ch1" + ",luge2_ch3" + ",luge2_ch5" + ",luge2_ch7,";

            log.Create_CvsFile("11");
            for (int i = 0; i < 100; i++)
            {
                date_time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss:fff, ");
                System.Threading.Thread.Sleep(100);
                log.Write_CvsFile(date_time + header_temp);
            }

            log.Close_CvsFile();

            log.Create_CvsFile("12");
            for (int i = 0; i < 100; i++)
            {
                date_time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss:fff, ");
                log.Write_CvsFile(date_time + header_temp);
            }

            log.Close_CvsFile();


            log.Create_CvsFile("12");
            for (int i = 0; i < 100; i++)
            {
                date_time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss:fff, ");
                log.Write_CvsFile(date_time + header_temp);
            }

            log.Close_CvsFile();

        }
    }
}

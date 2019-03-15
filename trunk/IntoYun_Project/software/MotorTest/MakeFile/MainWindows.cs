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

namespace MakeFile
{
    public partial class MakeFile : Form
    {
        Util_Proxy st_unit = new Util_Proxy();
        Hex2Bin st_Hex2Bin = new Hex2Bin();

        private string hexfile_path = "";
        private string inifile_path = "";
        private bool bl_convertStart = false;

        public MakeFile()
        {
            InitializeComponent();
        }

        private void MakeFile_Load(object sender, EventArgs e)
        {
            progressBar_FwConvert.Maximum = 100;
            tools_cypyRight.Text = st_unit.CopyRight;
            tools_version.Text = st_unit.SoftVersion;

            toolsTime_build.Text = "Building: " + System.IO.File.GetLastWriteTime(this.GetType().Assembly.Location).ToString("F"); 
        }

        private void MakeFile_FormClosed(object sender, FormClosedEventArgs e)
        {
            st_Hex2Bin.FileHex_Stop();
        }

        private void Add_ini_file_Click(object sender, EventArgs e)
        {
            try
            {
                if (openIniFileDialog.ShowDialog() == DialogResult.OK) //打开转换的目标文件
                {
                    if (openIniFileDialog.FileName.Length > 0)
                    {
                        Reset_Action();
                        textBox_iniFile.Text = openIniFileDialog.FileName;
                        inifile_path = openIniFileDialog.FileName;
                        st_Hex2Bin.FileHeader_ReadIni( inifile_path );
                        Ini_Inoformation();
                    }
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void Add_Hex_File_Click(object sender, EventArgs e)
        {
            try
            {
                if (openHexDlg.ShowDialog() == DialogResult.OK) //打开转换的目标文件
                {
                    if (openHexDlg.FileName.Length > 0)
                    {
                        Reset_Action();
                        textBox_HexFile.Text = openHexDlg.FileName;
                        hexfile_path = openHexDlg.FileName;
                    }
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void Hex2BIn_Convert_Click(object sender, EventArgs e)
        {
            st_Hex2Bin.FileHex_Start(hexfile_path);
            bl_convertStart = true;
            textBox_zfp.Text = st_Hex2Bin.fileName_zfp;
        }

        private void Ini_Inoformation()
        {
            FwVender.Text = System.Text.Encoding.ASCII.GetString(st_Hex2Bin.st_header.FwVender);
            Platform.Text = System.Text.Encoding.ASCII.GetString(st_Hex2Bin.st_header.Platform);

            mcsVersion.Text = System.Text.Encoding.ASCII.GetString(st_Hex2Bin.st_header.MCSVer);

            DeviceType.Text = st_Hex2Bin.st_header.DevType.ToString("x");

            BootloaderVersion.Text = System.Text.Encoding.ASCII.GetString(st_Hex2Bin.st_header.BootLaoderfwVer);
            ApplicationVersion.Text = System.Text.Encoding.ASCII.GetString(st_Hex2Bin.st_header.AppfwVer);

        }

        private void timerAct_Tick(object sender, EventArgs e)
        {
            if (bl_convertStart)
            {
                if (st_Hex2Bin.bl_Result)
                {
                    st_Hex2Bin.fileName_zfp = "";
                    bl_convertStart = false;
                    st_Hex2Bin.bl_Result = false;
                    progressBar_FwConvert.Value = 100;
                    textBox_FileSize.Text = st_Hex2Bin.filSize.ToString();
                    textBox_FlashStartAddress.Text = "0x"+st_unit.ByteToString(st_Hex2Bin.st_header.InterFlashStart,4);
                }
                else {
                    progressBar_FwConvert.Value++;
                }
            }
        }

        private void Reset_Action()
        {
            progressBar_FwConvert.Value = 0;
            bl_convertStart = false;
            st_Hex2Bin.bl_Result = false;
        }
    }
}

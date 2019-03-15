namespace MakeFile
{
    partial class MakeFile
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.FwInfor = new System.Windows.Forms.GroupBox();
            this.ApplicationVersion = new System.Windows.Forms.TextBox();
            this.mcsVersion = new System.Windows.Forms.TextBox();
            this.BootloaderVersion = new System.Windows.Forms.TextBox();
            this.Platform = new System.Windows.Forms.TextBox();
            this.DeviceType = new System.Windows.Forms.TextBox();
            this.FwVender = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBox_zfp = new System.Windows.Forms.TextBox();
            this.progressBar_FwConvert = new System.Windows.Forms.ProgressBar();
            this.Hex2BIn_Convert = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.Add_Hex_File = new System.Windows.Forms.Button();
            this.textBox_HexFile = new System.Windows.Forms.TextBox();
            this.Add_ini_file = new System.Windows.Forms.Button();
            this.textBox_iniFile = new System.Windows.Forms.TextBox();
            this.statusStrip5 = new System.Windows.Forms.StatusStrip();
            this.tools_cypyRight = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.dateLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.tools_version = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip_build = new System.Windows.Forms.StatusStrip();
            this.toolsTime_build = new System.Windows.Forms.ToolStripStatusLabel();
            this.openHexDlg = new System.Windows.Forms.OpenFileDialog();
            this.openIniFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBox_FlashStartAddress = new System.Windows.Forms.TextBox();
            this.textBox_FileSize = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.timerAct = new System.Windows.Forms.Timer(this.components);
            this.FwInfor.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.statusStrip5.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.statusStrip_build.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // FwInfor
            // 
            this.FwInfor.Controls.Add(this.ApplicationVersion);
            this.FwInfor.Controls.Add(this.mcsVersion);
            this.FwInfor.Controls.Add(this.BootloaderVersion);
            this.FwInfor.Controls.Add(this.Platform);
            this.FwInfor.Controls.Add(this.DeviceType);
            this.FwInfor.Controls.Add(this.FwVender);
            this.FwInfor.Controls.Add(this.label7);
            this.FwInfor.Controls.Add(this.label6);
            this.FwInfor.Controls.Add(this.label5);
            this.FwInfor.Controls.Add(this.label1);
            this.FwInfor.Controls.Add(this.label4);
            this.FwInfor.Controls.Add(this.label3);
            this.FwInfor.Location = new System.Drawing.Point(4, 289);
            this.FwInfor.Name = "FwInfor";
            this.FwInfor.Size = new System.Drawing.Size(621, 100);
            this.FwInfor.TabIndex = 12;
            this.FwInfor.TabStop = false;
            this.FwInfor.Text = "Firmware Information";
            // 
            // ApplicationVersion
            // 
            this.ApplicationVersion.Location = new System.Drawing.Point(415, 71);
            this.ApplicationVersion.Name = "ApplicationVersion";
            this.ApplicationVersion.ReadOnly = true;
            this.ApplicationVersion.Size = new System.Drawing.Size(151, 21);
            this.ApplicationVersion.TabIndex = 15;
            // 
            // mcsVersion
            // 
            this.mcsVersion.Location = new System.Drawing.Point(113, 71);
            this.mcsVersion.Name = "mcsVersion";
            this.mcsVersion.ReadOnly = true;
            this.mcsVersion.Size = new System.Drawing.Size(151, 21);
            this.mcsVersion.TabIndex = 14;
            // 
            // BootloaderVersion
            // 
            this.BootloaderVersion.Location = new System.Drawing.Point(415, 44);
            this.BootloaderVersion.Name = "BootloaderVersion";
            this.BootloaderVersion.ReadOnly = true;
            this.BootloaderVersion.Size = new System.Drawing.Size(151, 21);
            this.BootloaderVersion.TabIndex = 13;
            // 
            // Platform
            // 
            this.Platform.Location = new System.Drawing.Point(113, 44);
            this.Platform.Name = "Platform";
            this.Platform.ReadOnly = true;
            this.Platform.Size = new System.Drawing.Size(151, 21);
            this.Platform.TabIndex = 12;
            // 
            // DeviceType
            // 
            this.DeviceType.Location = new System.Drawing.Point(415, 17);
            this.DeviceType.Name = "DeviceType";
            this.DeviceType.ReadOnly = true;
            this.DeviceType.Size = new System.Drawing.Size(151, 21);
            this.DeviceType.TabIndex = 11;
            // 
            // FwVender
            // 
            this.FwVender.Location = new System.Drawing.Point(113, 17);
            this.FwVender.Name = "FwVender";
            this.FwVender.ReadOnly = true;
            this.FwVender.Size = new System.Drawing.Size(151, 21);
            this.FwVender.TabIndex = 11;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(290, 74);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(119, 12);
            this.label7.TabIndex = 10;
            this.label7.Text = "Application version";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(11, 74);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(71, 12);
            this.label6.TabIndex = 9;
            this.label6.Text = "mcs version";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(296, 47);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(113, 12);
            this.label5.TabIndex = 8;
            this.label5.Text = "Bootloader version";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(338, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 12);
            this.label1.TabIndex = 6;
            this.label1.Text = "Device type";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(29, 44);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 7;
            this.label4.Text = "Platform";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(29, 17);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 6;
            this.label3.Text = "FwVender";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox_zfp);
            this.groupBox2.Controls.Add(this.progressBar_FwConvert);
            this.groupBox2.Controls.Add(this.Hex2BIn_Convert);
            this.groupBox2.Location = new System.Drawing.Point(5, 157);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(623, 126);
            this.groupBox2.TabIndex = 11;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "文件转换";
            // 
            // textBox_zfp
            // 
            this.textBox_zfp.Location = new System.Drawing.Point(10, 25);
            this.textBox_zfp.Multiline = true;
            this.textBox_zfp.Name = "textBox_zfp";
            this.textBox_zfp.ReadOnly = true;
            this.textBox_zfp.Size = new System.Drawing.Size(509, 49);
            this.textBox_zfp.TabIndex = 9;
            // 
            // progressBar_FwConvert
            // 
            this.progressBar_FwConvert.Location = new System.Drawing.Point(10, 85);
            this.progressBar_FwConvert.Name = "progressBar_FwConvert";
            this.progressBar_FwConvert.Size = new System.Drawing.Size(509, 26);
            this.progressBar_FwConvert.TabIndex = 8;
            // 
            // Hex2BIn_Convert
            // 
            this.Hex2BIn_Convert.Location = new System.Drawing.Point(529, 25);
            this.Hex2BIn_Convert.Name = "Hex2BIn_Convert";
            this.Hex2BIn_Convert.Size = new System.Drawing.Size(86, 38);
            this.Hex2BIn_Convert.TabIndex = 7;
            this.Hex2BIn_Convert.Text = "开始转换";
            this.Hex2BIn_Convert.UseVisualStyleBackColor = true;
            this.Hex2BIn_Convert.Click += new System.EventHandler(this.Hex2BIn_Convert_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Add_Hex_File);
            this.groupBox1.Controls.Add(this.textBox_HexFile);
            this.groupBox1.Controls.Add(this.Add_ini_file);
            this.groupBox1.Controls.Add(this.textBox_iniFile);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(615, 139);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Add File";
            // 
            // Add_Hex_File
            // 
            this.Add_Hex_File.Location = new System.Drawing.Point(522, 83);
            this.Add_Hex_File.Name = "Add_Hex_File";
            this.Add_Hex_File.Size = new System.Drawing.Size(86, 41);
            this.Add_Hex_File.TabIndex = 7;
            this.Add_Hex_File.Text = "Hex文件";
            this.Add_Hex_File.UseVisualStyleBackColor = true;
            this.Add_Hex_File.Click += new System.EventHandler(this.Add_Hex_File_Click);
            // 
            // textBox_HexFile
            // 
            this.textBox_HexFile.Location = new System.Drawing.Point(9, 83);
            this.textBox_HexFile.Multiline = true;
            this.textBox_HexFile.Name = "textBox_HexFile";
            this.textBox_HexFile.ReadOnly = true;
            this.textBox_HexFile.Size = new System.Drawing.Size(508, 50);
            this.textBox_HexFile.TabIndex = 6;
            // 
            // Add_ini_file
            // 
            this.Add_ini_file.Location = new System.Drawing.Point(523, 20);
            this.Add_ini_file.Name = "Add_ini_file";
            this.Add_ini_file.Size = new System.Drawing.Size(86, 43);
            this.Add_ini_file.TabIndex = 2;
            this.Add_ini_file.Text = "INI文件";
            this.Add_ini_file.UseVisualStyleBackColor = true;
            this.Add_ini_file.Click += new System.EventHandler(this.Add_ini_file_Click);
            // 
            // textBox_iniFile
            // 
            this.textBox_iniFile.Location = new System.Drawing.Point(9, 23);
            this.textBox_iniFile.Multiline = true;
            this.textBox_iniFile.Name = "textBox_iniFile";
            this.textBox_iniFile.ReadOnly = true;
            this.textBox_iniFile.Size = new System.Drawing.Size(508, 54);
            this.textBox_iniFile.TabIndex = 0;
            // 
            // statusStrip5
            // 
            this.statusStrip5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.statusStrip5.AutoSize = false;
            this.statusStrip5.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip5.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tools_cypyRight});
            this.statusStrip5.Location = new System.Drawing.Point(225, 447);
            this.statusStrip5.Name = "statusStrip5";
            this.statusStrip5.Size = new System.Drawing.Size(191, 22);
            this.statusStrip5.TabIndex = 17;
            this.statusStrip5.Text = "statusStrip_version";
            // 
            // tools_cypyRight
            // 
            this.tools_cypyRight.Name = "tools_cypyRight";
            this.tools_cypyRight.Size = new System.Drawing.Size(65, 17);
            this.tools_cypyRight.Text = "toolsTime";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.statusStrip1.AutoSize = false;
            this.statusStrip1.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dateLabel,
            this.tools_version});
            this.statusStrip1.Location = new System.Drawing.Point(5, 447);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(220, 22);
            this.statusStrip1.TabIndex = 18;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // dateLabel
            // 
            this.dateLabel.Name = "dateLabel";
            this.dateLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // tools_version
            // 
            this.tools_version.Name = "tools_version";
            this.tools_version.Size = new System.Drawing.Size(28, 17);
            this.tools_version.Text = "too";
            // 
            // statusStrip_build
            // 
            this.statusStrip_build.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.statusStrip_build.AutoSize = false;
            this.statusStrip_build.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip_build.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolsTime_build});
            this.statusStrip_build.Location = new System.Drawing.Point(416, 447);
            this.statusStrip_build.Name = "statusStrip_build";
            this.statusStrip_build.Size = new System.Drawing.Size(211, 22);
            this.statusStrip_build.TabIndex = 17;
            this.statusStrip_build.Text = "statusStrip1";
            // 
            // toolsTime_build
            // 
            this.toolsTime_build.Name = "toolsTime_build";
            this.toolsTime_build.Size = new System.Drawing.Size(65, 17);
            this.toolsTime_build.Text = "toolsTime";
            // 
            // openHexDlg
            // 
            this.openHexDlg.Filter = "HEX文件(*.hex)|*.hex";
            this.openHexDlg.Title = "选择需要转换的HEX文件";
            // 
            // openIniFileDialog
            // 
            this.openIniFileDialog.Filter = "INI文件(*.ini)|*.ini";
            this.openIniFileDialog.Title = "选择需要转换的HEX文件";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.textBox_FlashStartAddress);
            this.groupBox3.Controls.Add(this.textBox_FileSize);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Location = new System.Drawing.Point(5, 395);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(622, 50);
            this.groupBox3.TabIndex = 19;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "File Information";
            // 
            // textBox_FlashStartAddress
            // 
            this.textBox_FlashStartAddress.Location = new System.Drawing.Point(416, 17);
            this.textBox_FlashStartAddress.Name = "textBox_FlashStartAddress";
            this.textBox_FlashStartAddress.ReadOnly = true;
            this.textBox_FlashStartAddress.Size = new System.Drawing.Size(151, 21);
            this.textBox_FlashStartAddress.TabIndex = 1;
            // 
            // textBox_FileSize
            // 
            this.textBox_FileSize.Location = new System.Drawing.Point(112, 17);
            this.textBox_FileSize.Name = "textBox_FileSize";
            this.textBox_FileSize.ReadOnly = true;
            this.textBox_FileSize.Size = new System.Drawing.Size(151, 21);
            this.textBox_FileSize.TabIndex = 1;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(292, 20);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(119, 12);
            this.label8.TabIndex = 0;
            this.label8.Text = "Flash start Address";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(5, 20);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(101, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "File size(Bytes)";
            // 
            // timerAct
            // 
            this.timerAct.Enabled = true;
            this.timerAct.Interval = 1000;
            this.timerAct.Tick += new System.EventHandler(this.timerAct_Tick);
            // 
            // MakeFile
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(634, 472);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.statusStrip_build);
            this.Controls.Add(this.statusStrip5);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.FwInfor);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "MakeFile";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "MakeFile";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MakeFile_FormClosed);
            this.Load += new System.EventHandler(this.MakeFile_Load);
            this.FwInfor.ResumeLayout(false);
            this.FwInfor.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.statusStrip5.ResumeLayout(false);
            this.statusStrip5.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.statusStrip_build.ResumeLayout(false);
            this.statusStrip_build.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox FwInfor;
        private System.Windows.Forms.TextBox ApplicationVersion;
        private System.Windows.Forms.TextBox mcsVersion;
        private System.Windows.Forms.TextBox BootloaderVersion;
        private System.Windows.Forms.TextBox Platform;
        private System.Windows.Forms.TextBox FwVender;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox_zfp;
        private System.Windows.Forms.ProgressBar progressBar_FwConvert;
        private System.Windows.Forms.Button Hex2BIn_Convert;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button Add_Hex_File;
        private System.Windows.Forms.TextBox textBox_HexFile;
        private System.Windows.Forms.Button Add_ini_file;
        private System.Windows.Forms.TextBox textBox_iniFile;
        private System.Windows.Forms.StatusStrip statusStrip5;
        private System.Windows.Forms.ToolStripStatusLabel tools_cypyRight;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel dateLabel;
        private System.Windows.Forms.ToolStripStatusLabel tools_version;
        private System.Windows.Forms.TextBox DeviceType;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.StatusStrip statusStrip_build;
        private System.Windows.Forms.ToolStripStatusLabel toolsTime_build;
        private System.Windows.Forms.OpenFileDialog openHexDlg;
        private System.Windows.Forms.OpenFileDialog openIniFileDialog;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_FileSize;
        private System.Windows.Forms.TextBox textBox_FlashStartAddress;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Timer timerAct;
    }
}


namespace OpenSoftware
{
    partial class mainWindows
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button_ClearBuff = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox_ComPort = new System.Windows.Forms.ComboBox();
            this.button_CommCtrl = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox_Baud = new System.Windows.Forms.ComboBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox_DataLen = new System.Windows.Forms.TextBox();
            this.button_ProtocolSend = new System.Windows.Forms.Button();
            this.button_RTC = new System.Windows.Forms.Button();
            this.richTextBox_Monitor = new System.Windows.Forms.RichTextBox();
            this.progressBar_download = new System.Windows.Forms.ProgressBar();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.FwProcessBar = new System.Windows.Forms.Label();
            this.button1_Stop = new System.Windows.Forms.Button();
            this.filePath = new System.Windows.Forms.TextBox();
            this.button_Start = new System.Windows.Forms.Button();
            this.AddFile = new System.Windows.Forms.Button();
            this.statusStrip_build = new System.Windows.Forms.StatusStrip();
            this.toolsTime_build = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip5 = new System.Windows.Forms.StatusStrip();
            this.tools_cypyRight = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.dateLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.tools_version = new System.Windows.Forms.ToolStripStatusLabel();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBox_temp = new System.Windows.Forms.TextBox();
            this.textBox_hum = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.button_CtrlSht2x = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.zedGraphControl = new ZedGraph.ZedGraphControl();
            this.groupBox1.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.statusStrip_build.SuspendLayout();
            this.statusStrip5.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button_ClearBuff);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.comboBox_ComPort);
            this.groupBox1.Controls.Add(this.button_CommCtrl);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.comboBox_Baud);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(250, 102);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口";
            // 
            // button_ClearBuff
            // 
            this.button_ClearBuff.Location = new System.Drawing.Point(160, 56);
            this.button_ClearBuff.Name = "button_ClearBuff";
            this.button_ClearBuff.Size = new System.Drawing.Size(84, 27);
            this.button_ClearBuff.TabIndex = 24;
            this.button_ClearBuff.Text = "清空缓存";
            this.button_ClearBuff.UseVisualStyleBackColor = true;
            this.button_ClearBuff.Click += new System.EventHandler(this.button_ClearBuff_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "端口号";
            // 
            // comboBox_ComPort
            // 
            this.comboBox_ComPort.FormattingEnabled = true;
            this.comboBox_ComPort.Location = new System.Drawing.Point(62, 20);
            this.comboBox_ComPort.Name = "comboBox_ComPort";
            this.comboBox_ComPort.Size = new System.Drawing.Size(82, 20);
            this.comboBox_ComPort.TabIndex = 4;
            // 
            // button_CommCtrl
            // 
            this.button_CommCtrl.Location = new System.Drawing.Point(160, 17);
            this.button_CommCtrl.Name = "button_CommCtrl";
            this.button_CommCtrl.Size = new System.Drawing.Size(82, 33);
            this.button_CommCtrl.TabIndex = 6;
            this.button_CommCtrl.Text = "打开串口";
            this.button_CommCtrl.UseVisualStyleBackColor = true;
            this.button_CommCtrl.Click += new System.EventHandler(this.button_CommCtrl_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 59);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "波特率";
            // 
            // comboBox_Baud
            // 
            this.comboBox_Baud.FormattingEnabled = true;
            this.comboBox_Baud.Location = new System.Drawing.Point(62, 56);
            this.comboBox_Baud.Name = "comboBox_Baud";
            this.comboBox_Baud.Size = new System.Drawing.Size(82, 20);
            this.comboBox_Baud.TabIndex = 5;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label5);
            this.groupBox7.Controls.Add(this.textBox_DataLen);
            this.groupBox7.Controls.Add(this.button_ProtocolSend);
            this.groupBox7.Controls.Add(this.button_RTC);
            this.groupBox7.Location = new System.Drawing.Point(12, 120);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(250, 89);
            this.groupBox7.TabIndex = 23;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "通信协议测试";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(7, 20);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(113, 12);
            this.label5.TabIndex = 2;
            this.label5.Text = "数据长度（ <=45 ）";
            // 
            // textBox_DataLen
            // 
            this.textBox_DataLen.Location = new System.Drawing.Point(9, 34);
            this.textBox_DataLen.Name = "textBox_DataLen";
            this.textBox_DataLen.Size = new System.Drawing.Size(91, 21);
            this.textBox_DataLen.TabIndex = 1;
            // 
            // button_ProtocolSend
            // 
            this.button_ProtocolSend.Location = new System.Drawing.Point(126, 12);
            this.button_ProtocolSend.Name = "button_ProtocolSend";
            this.button_ProtocolSend.Size = new System.Drawing.Size(80, 28);
            this.button_ProtocolSend.TabIndex = 0;
            this.button_ProtocolSend.Text = "发送数据";
            this.button_ProtocolSend.UseVisualStyleBackColor = true;
            this.button_ProtocolSend.Click += new System.EventHandler(this.button_ProtocolSend_Click);
            // 
            // button_RTC
            // 
            this.button_RTC.Location = new System.Drawing.Point(126, 53);
            this.button_RTC.Name = "button_RTC";
            this.button_RTC.Size = new System.Drawing.Size(80, 30);
            this.button_RTC.TabIndex = 26;
            this.button_RTC.Text = "时间同步";
            this.button_RTC.UseVisualStyleBackColor = true;
            this.button_RTC.Click += new System.EventHandler(this.button_RTC_Click);
            // 
            // richTextBox_Monitor
            // 
            this.richTextBox_Monitor.Location = new System.Drawing.Point(494, 122);
            this.richTextBox_Monitor.Name = "richTextBox_Monitor";
            this.richTextBox_Monitor.Size = new System.Drawing.Size(388, 97);
            this.richTextBox_Monitor.TabIndex = 22;
            this.richTextBox_Monitor.Text = "";
            // 
            // progressBar_download
            // 
            this.progressBar_download.Location = new System.Drawing.Point(8, 64);
            this.progressBar_download.Name = "progressBar_download";
            this.progressBar_download.Size = new System.Drawing.Size(384, 23);
            this.progressBar_download.TabIndex = 24;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.FwProcessBar);
            this.groupBox2.Controls.Add(this.button1_Stop);
            this.groupBox2.Controls.Add(this.filePath);
            this.groupBox2.Controls.Add(this.button_Start);
            this.groupBox2.Controls.Add(this.AddFile);
            this.groupBox2.Controls.Add(this.progressBar_download);
            this.groupBox2.Location = new System.Drawing.Point(268, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(615, 102);
            this.groupBox2.TabIndex = 25;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "下载文件";
            // 
            // FwProcessBar
            // 
            this.FwProcessBar.AutoSize = true;
            this.FwProcessBar.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FwProcessBar.Location = new System.Drawing.Point(398, 68);
            this.FwProcessBar.Name = "FwProcessBar";
            this.FwProcessBar.Size = new System.Drawing.Size(17, 12);
            this.FwProcessBar.TabIndex = 28;
            this.FwProcessBar.Text = "0%";
            // 
            // button1_Stop
            // 
            this.button1_Stop.Location = new System.Drawing.Point(532, 61);
            this.button1_Stop.Name = "button1_Stop";
            this.button1_Stop.Size = new System.Drawing.Size(77, 26);
            this.button1_Stop.TabIndex = 26;
            this.button1_Stop.Text = "终止";
            this.button1_Stop.UseVisualStyleBackColor = true;
            this.button1_Stop.Click += new System.EventHandler(this.button1_Stop_Click);
            // 
            // filePath
            // 
            this.filePath.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.filePath.Location = new System.Drawing.Point(8, 25);
            this.filePath.Name = "filePath";
            this.filePath.Size = new System.Drawing.Size(518, 23);
            this.filePath.TabIndex = 27;
            // 
            // button_Start
            // 
            this.button_Start.Location = new System.Drawing.Point(449, 61);
            this.button_Start.Name = "button_Start";
            this.button_Start.Size = new System.Drawing.Size(77, 26);
            this.button_Start.TabIndex = 27;
            this.button_Start.Text = "开始";
            this.button_Start.UseVisualStyleBackColor = true;
            this.button_Start.Click += new System.EventHandler(this.button_Start_Click);
            // 
            // AddFile
            // 
            this.AddFile.Location = new System.Drawing.Point(532, 20);
            this.AddFile.Name = "AddFile";
            this.AddFile.Size = new System.Drawing.Size(77, 28);
            this.AddFile.TabIndex = 26;
            this.AddFile.Text = "打开文件";
            this.AddFile.UseVisualStyleBackColor = true;
            this.AddFile.Click += new System.EventHandler(this.AddFile_Click);
            // 
            // statusStrip_build
            // 
            this.statusStrip_build.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.statusStrip_build.AutoSize = false;
            this.statusStrip_build.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip_build.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolsTime_build});
            this.statusStrip_build.Location = new System.Drawing.Point(414, 583);
            this.statusStrip_build.Name = "statusStrip_build";
            this.statusStrip_build.Size = new System.Drawing.Size(474, 22);
            this.statusStrip_build.TabIndex = 27;
            this.statusStrip_build.Text = "statusStrip1";
            // 
            // toolsTime_build
            // 
            this.toolsTime_build.Name = "toolsTime_build";
            this.toolsTime_build.Size = new System.Drawing.Size(65, 17);
            this.toolsTime_build.Text = "toolsTime";
            // 
            // statusStrip5
            // 
            this.statusStrip5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.statusStrip5.AutoSize = false;
            this.statusStrip5.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip5.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tools_cypyRight});
            this.statusStrip5.Location = new System.Drawing.Point(223, 583);
            this.statusStrip5.Name = "statusStrip5";
            this.statusStrip5.Size = new System.Drawing.Size(191, 22);
            this.statusStrip5.TabIndex = 28;
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
            this.statusStrip1.Location = new System.Drawing.Point(3, 583);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(220, 22);
            this.statusStrip1.TabIndex = 29;
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
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.button_CtrlSht2x);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.textBox_hum);
            this.groupBox3.Controls.Add(this.textBox_temp);
            this.groupBox3.Location = new System.Drawing.Point(268, 120);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(220, 89);
            this.groupBox3.TabIndex = 30;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "温湿度（sht20）";
            // 
            // textBox_temp
            // 
            this.textBox_temp.Location = new System.Drawing.Point(8, 20);
            this.textBox_temp.Name = "textBox_temp";
            this.textBox_temp.Size = new System.Drawing.Size(93, 21);
            this.textBox_temp.TabIndex = 0;
            // 
            // textBox_hum
            // 
            this.textBox_hum.Location = new System.Drawing.Point(8, 53);
            this.textBox_hum.Name = "textBox_hum";
            this.textBox_hum.Size = new System.Drawing.Size(93, 21);
            this.textBox_hum.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(107, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(17, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "℃";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(109, 53);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(17, 12);
            this.label4.TabIndex = 3;
            this.label4.Text = "H%";
            // 
            // button_CtrlSht2x
            // 
            this.button_CtrlSht2x.Location = new System.Drawing.Point(132, 18);
            this.button_CtrlSht2x.Name = "button_CtrlSht2x";
            this.button_CtrlSht2x.Size = new System.Drawing.Size(75, 50);
            this.button_CtrlSht2x.TabIndex = 4;
            this.button_CtrlSht2x.Text = "button1";
            this.button_CtrlSht2x.UseVisualStyleBackColor = true;
            this.button_CtrlSht2x.Click += new System.EventHandler(this.button1_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // zedGraphControl
            // 
            this.zedGraphControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.zedGraphControl.Location = new System.Drawing.Point(3, 225);
            this.zedGraphControl.Name = "zedGraphControl";
            this.zedGraphControl.ScrollGrace = 0D;
            this.zedGraphControl.ScrollMaxX = 0D;
            this.zedGraphControl.ScrollMaxY = 0D;
            this.zedGraphControl.ScrollMaxY2 = 0D;
            this.zedGraphControl.ScrollMinX = 0D;
            this.zedGraphControl.ScrollMinY = 0D;
            this.zedGraphControl.ScrollMinY2 = 0D;
            this.zedGraphControl.Size = new System.Drawing.Size(884, 355);
            this.zedGraphControl.TabIndex = 31;
            // 
            // mainWindows
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(894, 605);
            this.Controls.Add(this.zedGraphControl);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.statusStrip_build);
            this.Controls.Add(this.statusStrip5);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.richTextBox_Monitor);
            this.Controls.Add(this.groupBox1);
            this.Name = "mainWindows";
            this.Text = "开源项目上位机";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.mainWindows_FormClosed);
            this.Load += new System.EventHandler(this.mainWindows_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.statusStrip_build.ResumeLayout(false);
            this.statusStrip_build.PerformLayout();
            this.statusStrip5.ResumeLayout(false);
            this.statusStrip5.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox_ComPort;
        private System.Windows.Forms.Button button_CommCtrl;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox_Baud;
        private System.Windows.Forms.Button button_ClearBuff;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox_DataLen;
        private System.Windows.Forms.Button button_ProtocolSend;
        private System.Windows.Forms.RichTextBox richTextBox_Monitor;
        private System.Windows.Forms.ProgressBar progressBar_download;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox filePath;
        private System.Windows.Forms.Button AddFile;
        private System.Windows.Forms.Button button1_Stop;
        private System.Windows.Forms.Button button_Start;
        private System.Windows.Forms.Label FwProcessBar;
        private System.Windows.Forms.Button button_RTC;
        private System.Windows.Forms.StatusStrip statusStrip_build;
        private System.Windows.Forms.ToolStripStatusLabel toolsTime_build;
        private System.Windows.Forms.StatusStrip statusStrip5;
        private System.Windows.Forms.ToolStripStatusLabel tools_cypyRight;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel dateLabel;
        private System.Windows.Forms.ToolStripStatusLabel tools_version;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBox_hum;
        private System.Windows.Forms.TextBox textBox_temp;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button_CtrlSht2x;
        private System.Windows.Forms.Timer timer1;
        private ZedGraph.ZedGraphControl zedGraphControl;
    }
}


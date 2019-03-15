namespace McsCommandTest
{
    partial class Form_McsCommand
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
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button_Enable = new System.Windows.Forms.Button();
            this.comboBox_Baud = new System.Windows.Forms.ComboBox();
            this.comboBox_ComPort = new System.Windows.Forms.ComboBox();
            this.button_ClearBuff = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_led1 = new System.Windows.Forms.TextBox();
            this.button_LED1_OFF = new System.Windows.Forms.Button();
            this.button_led1 = new System.Windows.Forms.Button();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.checkBox_AutoTest = new System.Windows.Forms.CheckBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.textBox_cmdCnt = new System.Windows.Forms.TextBox();
            this.textBox_interval = new System.Windows.Forms.TextBox();
            this.button_StopLazyBack_1 = new System.Windows.Forms.Button();
            this.comboBox_deviceType = new System.Windows.Forms.ComboBox();
            this.button_lazy_down = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.button_LazyUp = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox_DataLen = new System.Windows.Forms.TextBox();
            this.button_BluetoothSend = new System.Windows.Forms.Button();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.FwProcessBar = new System.Windows.Forms.Label();
            this.button1_Stop = new System.Windows.Forms.Button();
            this.filePath = new System.Windows.Forms.TextBox();
            this.button_Start = new System.Windows.Forms.Button();
            this.AddFile = new System.Windows.Forms.Button();
            this.progressBar_download = new System.Windows.Forms.ProgressBar();
            this.richTextBox_Monitor = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox2.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 15;
            this.label2.Text = "波特率";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 16;
            this.label1.Text = "端口号";
            // 
            // button_Enable
            // 
            this.button_Enable.Location = new System.Drawing.Point(184, 14);
            this.button_Enable.Name = "button_Enable";
            this.button_Enable.Size = new System.Drawing.Size(90, 30);
            this.button_Enable.TabIndex = 14;
            this.button_Enable.Text = "打开串口";
            this.button_Enable.UseVisualStyleBackColor = true;
            this.button_Enable.Click += new System.EventHandler(this.button_Enable_Click);
            // 
            // comboBox_Baud
            // 
            this.comboBox_Baud.FormattingEnabled = true;
            this.comboBox_Baud.Location = new System.Drawing.Point(58, 53);
            this.comboBox_Baud.Name = "comboBox_Baud";
            this.comboBox_Baud.Size = new System.Drawing.Size(121, 20);
            this.comboBox_Baud.TabIndex = 13;
            // 
            // comboBox_ComPort
            // 
            this.comboBox_ComPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_ComPort.FormattingEnabled = true;
            this.comboBox_ComPort.Location = new System.Drawing.Point(58, 20);
            this.comboBox_ComPort.Name = "comboBox_ComPort";
            this.comboBox_ComPort.Size = new System.Drawing.Size(121, 20);
            this.comboBox_ComPort.TabIndex = 12;
            // 
            // button_ClearBuff
            // 
            this.button_ClearBuff.Location = new System.Drawing.Point(185, 49);
            this.button_ClearBuff.Name = "button_ClearBuff";
            this.button_ClearBuff.Size = new System.Drawing.Size(90, 27);
            this.button_ClearBuff.TabIndex = 19;
            this.button_ClearBuff.Text = "清空缓存";
            this.button_ClearBuff.UseVisualStyleBackColor = true;
            this.button_ClearBuff.Click += new System.EventHandler(this.button_ClearBuff_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.textBox_led1);
            this.groupBox2.Controls.Add(this.button_LED1_OFF);
            this.groupBox2.Controls.Add(this.button_led1);
            this.groupBox2.Location = new System.Drawing.Point(13, 21);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(305, 50);
            this.groupBox2.TabIndex = 20;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "灯控制";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 2;
            this.label4.Text = "数据ID";
            // 
            // textBox_led1
            // 
            this.textBox_led1.Location = new System.Drawing.Point(50, 17);
            this.textBox_led1.Name = "textBox_led1";
            this.textBox_led1.Size = new System.Drawing.Size(40, 21);
            this.textBox_led1.TabIndex = 1;
            // 
            // button_LED1_OFF
            // 
            this.button_LED1_OFF.Location = new System.Drawing.Point(207, 15);
            this.button_LED1_OFF.Name = "button_LED1_OFF";
            this.button_LED1_OFF.Size = new System.Drawing.Size(55, 23);
            this.button_LED1_OFF.TabIndex = 0;
            this.button_LED1_OFF.Text = "关灯";
            this.button_LED1_OFF.UseVisualStyleBackColor = true;
            this.button_LED1_OFF.Click += new System.EventHandler(this.button_LED1_OFF_Click);
            // 
            // button_led1
            // 
            this.button_led1.Location = new System.Drawing.Point(131, 15);
            this.button_led1.Name = "button_led1";
            this.button_led1.Size = new System.Drawing.Size(55, 23);
            this.button_led1.TabIndex = 0;
            this.button_led1.Text = "开灯";
            this.button_led1.UseVisualStyleBackColor = true;
            this.button_led1.Click += new System.EventHandler(this.button_LED1_ON_Click);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.groupBox1);
            this.groupBox5.Controls.Add(this.button_StopLazyBack_1);
            this.groupBox5.Controls.Add(this.comboBox_deviceType);
            this.groupBox5.Controls.Add(this.button_lazy_down);
            this.groupBox5.Controls.Add(this.label3);
            this.groupBox5.Controls.Add(this.button_LazyUp);
            this.groupBox5.Location = new System.Drawing.Point(12, 112);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(306, 193);
            this.groupBox5.TabIndex = 20;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "设备控制";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.checkBox_AutoTest);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.textBox_cmdCnt);
            this.groupBox1.Controls.Add(this.textBox_interval);
            this.groupBox1.Location = new System.Drawing.Point(81, 46);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(219, 130);
            this.groupBox1.TabIndex = 16;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "自动化测试参数";
            // 
            // checkBox_AutoTest
            // 
            this.checkBox_AutoTest.AutoSize = true;
            this.checkBox_AutoTest.Location = new System.Drawing.Point(8, 94);
            this.checkBox_AutoTest.Name = "checkBox_AutoTest";
            this.checkBox_AutoTest.Size = new System.Drawing.Size(108, 16);
            this.checkBox_AutoTest.TabIndex = 3;
            this.checkBox_AutoTest.Text = "自动化测试使能";
            this.checkBox_AutoTest.UseVisualStyleBackColor = true;
            this.checkBox_AutoTest.CheckedChanged += new System.EventHandler(this.checkBox_AutoTest_CheckedChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.ForeColor = System.Drawing.Color.Red;
            this.label8.Location = new System.Drawing.Point(170, 34);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(17, 12);
            this.label8.TabIndex = 2;
            this.label8.Text = "秒";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 58);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 12);
            this.label7.TabIndex = 1;
            this.label7.Text = "命令次数";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 29);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 1;
            this.label6.Text = "时间间隔";
            // 
            // textBox_cmdCnt
            // 
            this.textBox_cmdCnt.Location = new System.Drawing.Point(69, 55);
            this.textBox_cmdCnt.Name = "textBox_cmdCnt";
            this.textBox_cmdCnt.Size = new System.Drawing.Size(94, 21);
            this.textBox_cmdCnt.TabIndex = 0;
            this.textBox_cmdCnt.Text = "10";
            // 
            // textBox_interval
            // 
            this.textBox_interval.Location = new System.Drawing.Point(69, 26);
            this.textBox_interval.Name = "textBox_interval";
            this.textBox_interval.Size = new System.Drawing.Size(94, 21);
            this.textBox_interval.TabIndex = 0;
            this.textBox_interval.Text = "300";
            // 
            // button_StopLazyBack_1
            // 
            this.button_StopLazyBack_1.Location = new System.Drawing.Point(9, 140);
            this.button_StopLazyBack_1.Name = "button_StopLazyBack_1";
            this.button_StopLazyBack_1.Size = new System.Drawing.Size(59, 23);
            this.button_StopLazyBack_1.TabIndex = 3;
            this.button_StopLazyBack_1.Text = "停止";
            this.button_StopLazyBack_1.UseVisualStyleBackColor = true;
            this.button_StopLazyBack_1.Click += new System.EventHandler(this.button_StopLazyBack_1_Click);
            // 
            // comboBox_deviceType
            // 
            this.comboBox_deviceType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_deviceType.FormattingEnabled = true;
            this.comboBox_deviceType.Location = new System.Drawing.Point(66, 20);
            this.comboBox_deviceType.Name = "comboBox_deviceType";
            this.comboBox_deviceType.Size = new System.Drawing.Size(234, 20);
            this.comboBox_deviceType.TabIndex = 13;
            this.comboBox_deviceType.SelectedIndexChanged += new System.EventHandler(this.comboBox_deviceType_SelectedIndexChanged);
            // 
            // button_lazy_down
            // 
            this.button_lazy_down.Location = new System.Drawing.Point(9, 99);
            this.button_lazy_down.Name = "button_lazy_down";
            this.button_lazy_down.Size = new System.Drawing.Size(59, 23);
            this.button_lazy_down.TabIndex = 0;
            this.button_lazy_down.Text = "下降";
            this.button_lazy_down.UseVisualStyleBackColor = true;
            this.button_lazy_down.Click += new System.EventHandler(this.button_LazyDown_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 15;
            this.label3.Text = "设备类型";
            // 
            // button_LazyUp
            // 
            this.button_LazyUp.Location = new System.Drawing.Point(9, 57);
            this.button_LazyUp.Name = "button_LazyUp";
            this.button_LazyUp.Size = new System.Drawing.Size(59, 23);
            this.button_LazyUp.TabIndex = 0;
            this.button_LazyUp.Text = "升起";
            this.button_LazyUp.UseVisualStyleBackColor = true;
            this.button_LazyUp.Click += new System.EventHandler(this.button_LazyUp_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label5);
            this.groupBox7.Controls.Add(this.textBox_DataLen);
            this.groupBox7.Controls.Add(this.button_BluetoothSend);
            this.groupBox7.Location = new System.Drawing.Point(360, 12);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(451, 86);
            this.groupBox7.TabIndex = 21;
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
            this.textBox_DataLen.Size = new System.Drawing.Size(60, 21);
            this.textBox_DataLen.TabIndex = 1;
            // 
            // button_BluetoothSend
            // 
            this.button_BluetoothSend.Location = new System.Drawing.Point(142, 20);
            this.button_BluetoothSend.Name = "button_BluetoothSend";
            this.button_BluetoothSend.Size = new System.Drawing.Size(80, 35);
            this.button_BluetoothSend.TabIndex = 0;
            this.button_BluetoothSend.Text = "发送数据";
            this.button_BluetoothSend.UseVisualStyleBackColor = true;
            this.button_BluetoothSend.Click += new System.EventHandler(this.button_BluetoothSend_Click);
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.groupBox2);
            this.groupBox8.Controls.Add(this.groupBox5);
            this.groupBox8.Location = new System.Drawing.Point(12, 119);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(331, 528);
            this.groupBox8.TabIndex = 22;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "设备测试";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.comboBox_ComPort);
            this.groupBox9.Controls.Add(this.comboBox_Baud);
            this.groupBox9.Controls.Add(this.button_Enable);
            this.groupBox9.Controls.Add(this.button_ClearBuff);
            this.groupBox9.Controls.Add(this.label1);
            this.groupBox9.Controls.Add(this.label2);
            this.groupBox9.Location = new System.Drawing.Point(12, 12);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(331, 86);
            this.groupBox9.TabIndex = 24;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "串口";
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.FwProcessBar);
            this.groupBox11.Controls.Add(this.button1_Stop);
            this.groupBox11.Controls.Add(this.filePath);
            this.groupBox11.Controls.Add(this.button_Start);
            this.groupBox11.Controls.Add(this.AddFile);
            this.groupBox11.Controls.Add(this.progressBar_download);
            this.groupBox11.Location = new System.Drawing.Point(360, 112);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(451, 85);
            this.groupBox11.TabIndex = 26;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "下载文件";
            // 
            // FwProcessBar
            // 
            this.FwProcessBar.AutoSize = true;
            this.FwProcessBar.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FwProcessBar.Location = new System.Drawing.Point(244, 63);
            this.FwProcessBar.Name = "FwProcessBar";
            this.FwProcessBar.Size = new System.Drawing.Size(17, 12);
            this.FwProcessBar.TabIndex = 28;
            this.FwProcessBar.Text = "0%";
            // 
            // button1_Stop
            // 
            this.button1_Stop.Location = new System.Drawing.Point(371, 52);
            this.button1_Stop.Name = "button1_Stop";
            this.button1_Stop.Size = new System.Drawing.Size(74, 26);
            this.button1_Stop.TabIndex = 26;
            this.button1_Stop.Text = "终止";
            this.button1_Stop.UseVisualStyleBackColor = true;
            this.button1_Stop.Click += new System.EventHandler(this.button1_Stop_Click);
            // 
            // filePath
            // 
            this.filePath.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.filePath.Location = new System.Drawing.Point(8, 20);
            this.filePath.Name = "filePath";
            this.filePath.Size = new System.Drawing.Size(357, 23);
            this.filePath.TabIndex = 27;
            // 
            // button_Start
            // 
            this.button_Start.Location = new System.Drawing.Point(282, 52);
            this.button_Start.Name = "button_Start";
            this.button_Start.Size = new System.Drawing.Size(74, 26);
            this.button_Start.TabIndex = 27;
            this.button_Start.Text = "开始";
            this.button_Start.UseVisualStyleBackColor = true;
            this.button_Start.Click += new System.EventHandler(this.button_Start_Click);
            // 
            // AddFile
            // 
            this.AddFile.Location = new System.Drawing.Point(371, 20);
            this.AddFile.Name = "AddFile";
            this.AddFile.Size = new System.Drawing.Size(74, 28);
            this.AddFile.TabIndex = 26;
            this.AddFile.Text = "打开文件";
            this.AddFile.UseVisualStyleBackColor = true;
            this.AddFile.Click += new System.EventHandler(this.AddFile_Click);
            // 
            // progressBar_download
            // 
            this.progressBar_download.Location = new System.Drawing.Point(9, 54);
            this.progressBar_download.Name = "progressBar_download";
            this.progressBar_download.Size = new System.Drawing.Size(229, 21);
            this.progressBar_download.TabIndex = 24;
            // 
            // richTextBox_Monitor
            // 
            this.richTextBox_Monitor.Location = new System.Drawing.Point(360, 204);
            this.richTextBox_Monitor.Multiline = true;
            this.richTextBox_Monitor.Name = "richTextBox_Monitor";
            this.richTextBox_Monitor.ReadOnly = true;
            this.richTextBox_Monitor.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.richTextBox_Monitor.Size = new System.Drawing.Size(451, 443);
            this.richTextBox_Monitor.TabIndex = 27;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form_McsCommand
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(820, 659);
            this.Controls.Add(this.richTextBox_Monitor);
            this.Controls.Add(this.groupBox11);
            this.Controls.Add(this.groupBox9);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.groupBox8);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form_McsCommand";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Mcs命令测试";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form_McsCommand_FormClosed);
            this.Load += new System.EventHandler(this.Form_McsCommand_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_Enable;
        private System.Windows.Forms.ComboBox comboBox_Baud;
        private System.Windows.Forms.ComboBox comboBox_ComPort;
        private System.Windows.Forms.Button button_ClearBuff;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button button_led1;
        private System.Windows.Forms.TextBox textBox_led1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button_LED1_OFF;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Button button_lazy_down;
        private System.Windows.Forms.Button button_LazyUp;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Button button_BluetoothSend;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox_DataLen;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.Button button_StopLazyBack_1;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Label FwProcessBar;
        private System.Windows.Forms.Button button1_Stop;
        private System.Windows.Forms.TextBox filePath;
        private System.Windows.Forms.Button button_Start;
        private System.Windows.Forms.Button AddFile;
        private System.Windows.Forms.ProgressBar progressBar_download;
        private System.Windows.Forms.ComboBox comboBox_deviceType;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox richTextBox_Monitor;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox_interval;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox_cmdCnt;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.CheckBox checkBox_AutoTest;
        private System.Windows.Forms.Timer timer1;
    }
}


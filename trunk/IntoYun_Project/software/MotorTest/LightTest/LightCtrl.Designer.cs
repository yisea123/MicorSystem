namespace LightTest
{
    partial class LightControl
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
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.comboBox_ComPort = new System.Windows.Forms.ComboBox();
            this.comboBox_Baud = new System.Windows.Forms.ComboBox();
            this.button_Enable = new System.Windows.Forms.Button();
            this.button_ClearBuff = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.richTextBox_Monitor = new System.Windows.Forms.RichTextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.hScrollBar_bright = new System.Windows.Forms.HScrollBar();
            this.hScrollBar_yellow = new System.Windows.Forms.HScrollBar();
            this.button_turnOnLight = new System.Windows.Forms.Button();
            this.button_configAddress = new System.Windows.Forms.Button();
            this.button_turnOff = new System.Windows.Forms.Button();
            this.button_CheckStatus = new System.Windows.Forms.Button();
            this.textBox_Address = new System.Windows.Forms.TextBox();
            this.groupBox9.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
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
            this.groupBox9.Size = new System.Drawing.Size(283, 86);
            this.groupBox9.TabIndex = 25;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "串口";
            // 
            // comboBox_ComPort
            // 
            this.comboBox_ComPort.FormattingEnabled = true;
            this.comboBox_ComPort.Location = new System.Drawing.Point(58, 20);
            this.comboBox_ComPort.Name = "comboBox_ComPort";
            this.comboBox_ComPort.Size = new System.Drawing.Size(121, 20);
            this.comboBox_ComPort.TabIndex = 12;
            // 
            // comboBox_Baud
            // 
            this.comboBox_Baud.FormattingEnabled = true;
            this.comboBox_Baud.Location = new System.Drawing.Point(58, 53);
            this.comboBox_Baud.Name = "comboBox_Baud";
            this.comboBox_Baud.Size = new System.Drawing.Size(121, 20);
            this.comboBox_Baud.TabIndex = 13;
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
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 16;
            this.label1.Text = "端口号";
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
            // richTextBox_Monitor
            // 
            this.richTextBox_Monitor.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBox_Monitor.Location = new System.Drawing.Point(301, 12);
            this.richTextBox_Monitor.Name = "richTextBox_Monitor";
            this.richTextBox_Monitor.Size = new System.Drawing.Size(382, 419);
            this.richTextBox_Monitor.TabIndex = 26;
            this.richTextBox_Monitor.Text = "";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Controls.Add(this.button_turnOnLight);
            this.groupBox1.Controls.Add(this.button_configAddress);
            this.groupBox1.Controls.Add(this.button_turnOff);
            this.groupBox1.Controls.Add(this.button_CheckStatus);
            this.groupBox1.Controls.Add(this.textBox_Address);
            this.groupBox1.Location = new System.Drawing.Point(13, 116);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(282, 315);
            this.groupBox1.TabIndex = 27;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "灯控制命令";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.hScrollBar_bright);
            this.groupBox2.Controls.Add(this.hScrollBar_yellow);
            this.groupBox2.Location = new System.Drawing.Point(12, 194);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(261, 112);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "调光";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(219, 78);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "白光";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(219, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 6;
            this.label3.Text = "黄光";
            // 
            // hScrollBar_bright
            // 
            this.hScrollBar_bright.Location = new System.Drawing.Point(17, 73);
            this.hScrollBar_bright.Name = "hScrollBar_bright";
            this.hScrollBar_bright.Size = new System.Drawing.Size(185, 17);
            this.hScrollBar_bright.TabIndex = 5;
            this.hScrollBar_bright.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar_bright_Scroll);
            // 
            // hScrollBar_yellow
            // 
            this.hScrollBar_yellow.Location = new System.Drawing.Point(17, 32);
            this.hScrollBar_yellow.Name = "hScrollBar_yellow";
            this.hScrollBar_yellow.Size = new System.Drawing.Size(185, 17);
            this.hScrollBar_yellow.TabIndex = 5;
            this.hScrollBar_yellow.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar_yellow_Scroll);
            // 
            // button_turnOnLight
            // 
            this.button_turnOnLight.Location = new System.Drawing.Point(12, 61);
            this.button_turnOnLight.Name = "button_turnOnLight";
            this.button_turnOnLight.Size = new System.Drawing.Size(75, 23);
            this.button_turnOnLight.TabIndex = 4;
            this.button_turnOnLight.Text = "开灯";
            this.button_turnOnLight.UseVisualStyleBackColor = true;
            this.button_turnOnLight.Click += new System.EventHandler(this.button_turnOnLight_Click);
            // 
            // button_configAddress
            // 
            this.button_configAddress.Location = new System.Drawing.Point(12, 20);
            this.button_configAddress.Name = "button_configAddress";
            this.button_configAddress.Size = new System.Drawing.Size(75, 23);
            this.button_configAddress.TabIndex = 3;
            this.button_configAddress.Text = "配置地址";
            this.button_configAddress.UseVisualStyleBackColor = true;
            this.button_configAddress.Click += new System.EventHandler(this.button_configAddress_Click);
            // 
            // button_turnOff
            // 
            this.button_turnOff.Location = new System.Drawing.Point(12, 101);
            this.button_turnOff.Name = "button_turnOff";
            this.button_turnOff.Size = new System.Drawing.Size(75, 23);
            this.button_turnOff.TabIndex = 2;
            this.button_turnOff.Text = "关灯";
            this.button_turnOff.UseVisualStyleBackColor = true;
            this.button_turnOff.Click += new System.EventHandler(this.button_turnOff_Click);
            // 
            // button_CheckStatus
            // 
            this.button_CheckStatus.Location = new System.Drawing.Point(12, 141);
            this.button_CheckStatus.Name = "button_CheckStatus";
            this.button_CheckStatus.Size = new System.Drawing.Size(75, 23);
            this.button_CheckStatus.TabIndex = 1;
            this.button_CheckStatus.Text = "查询状态";
            this.button_CheckStatus.UseVisualStyleBackColor = true;
            this.button_CheckStatus.Click += new System.EventHandler(this.button_CheckStatus_Click);
            // 
            // textBox_Address
            // 
            this.textBox_Address.Location = new System.Drawing.Point(123, 20);
            this.textBox_Address.Name = "textBox_Address";
            this.textBox_Address.Size = new System.Drawing.Size(139, 21);
            this.textBox_Address.TabIndex = 0;
            // 
            // LightControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(695, 439);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.richTextBox_Monitor);
            this.Controls.Add(this.groupBox9);
            this.Name = "LightControl";
            this.Text = "灯控制测试";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.LightControl_FormClosed);
            this.Load += new System.EventHandler(this.LightControl_Load);
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.ComboBox comboBox_ComPort;
        private System.Windows.Forms.ComboBox comboBox_Baud;
        private System.Windows.Forms.Button button_Enable;
        private System.Windows.Forms.Button button_ClearBuff;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RichTextBox richTextBox_Monitor;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox_Address;
        private System.Windows.Forms.Button button_CheckStatus;
        private System.Windows.Forms.Button button_configAddress;
        private System.Windows.Forms.Button button_turnOff;
        private System.Windows.Forms.Button button_turnOnLight;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.HScrollBar hScrollBar_bright;
        private System.Windows.Forms.HScrollBar hScrollBar_yellow;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
    }
}


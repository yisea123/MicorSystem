namespace MultiSensorTest
{
    partial class MultiSensorCtrl
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.hScrollBar_bright = new System.Windows.Forms.HScrollBar();
            this.hScrollBar_yellow = new System.Windows.Forms.HScrollBar();
            this.button_turnOnLight = new System.Windows.Forms.Button();
            this.button_configAddress = new System.Windows.Forms.Button();
            this.button_turnOff = new System.Windows.Forms.Button();
            this.button_CheckStatus = new System.Windows.Forms.Button();
            this.textBox_Address = new System.Windows.Forms.TextBox();
            this.textBox_time = new System.Windows.Forms.TextBox();
            this.button_ReadEnable = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox_PresenceID = new System.Windows.Forms.TextBox();
            this.button_readPresenceData = new System.Windows.Forms.Button();
            this.textBox_PresenceRes = new System.Windows.Forms.TextBox();
            this.button_PresenceSensor = new System.Windows.Forms.Button();
            this.richTextBox_Monitor = new System.Windows.Forms.RichTextBox();
            this.倾角传感器 = new System.Windows.Forms.GroupBox();
            this.button_modifyAddress = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBox_Value_X = new System.Windows.Forms.TextBox();
            this.textBox_Value_Y = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_ModbussAddress = new System.Windows.Forms.TextBox();
            this.button_ReadValue = new System.Windows.Forms.Button();
            this.button_ReadAddr = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.comboBox_ComPort = new System.Windows.Forms.ComboBox();
            this.comboBox_Baud = new System.Windows.Forms.ComboBox();
            this.button_Enable = new System.Windows.Forms.Button();
            this.button_ClearBuff = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.timerSensor = new System.Windows.Forms.Timer(this.components);
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.倾角传感器.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox4);
            this.groupBox3.Controls.Add(this.button_turnOnLight);
            this.groupBox3.Controls.Add(this.button_configAddress);
            this.groupBox3.Controls.Add(this.button_turnOff);
            this.groupBox3.Controls.Add(this.button_CheckStatus);
            this.groupBox3.Controls.Add(this.textBox_Address);
            this.groupBox3.Location = new System.Drawing.Point(320, 108);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(295, 218);
            this.groupBox3.TabIndex = 40;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "灯控制命令";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.hScrollBar_bright);
            this.groupBox4.Controls.Add(this.hScrollBar_yellow);
            this.groupBox4.Location = new System.Drawing.Point(15, 96);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(261, 112);
            this.groupBox4.TabIndex = 6;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "调光";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(219, 78);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(29, 12);
            this.label6.TabIndex = 6;
            this.label6.Text = "白光";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(219, 32);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(29, 12);
            this.label7.TabIndex = 6;
            this.label7.Text = "黄光";
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
            this.button_turnOff.Location = new System.Drawing.Point(102, 61);
            this.button_turnOff.Name = "button_turnOff";
            this.button_turnOff.Size = new System.Drawing.Size(75, 23);
            this.button_turnOff.TabIndex = 2;
            this.button_turnOff.Text = "关灯";
            this.button_turnOff.UseVisualStyleBackColor = true;
            this.button_turnOff.Click += new System.EventHandler(this.button_turnOff_Click);
            // 
            // button_CheckStatus
            // 
            this.button_CheckStatus.Location = new System.Drawing.Point(187, 61);
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
            // textBox_time
            // 
            this.textBox_time.Location = new System.Drawing.Point(105, 23);
            this.textBox_time.Name = "textBox_time";
            this.textBox_time.Size = new System.Drawing.Size(66, 21);
            this.textBox_time.TabIndex = 39;
            // 
            // button_ReadEnable
            // 
            this.button_ReadEnable.Location = new System.Drawing.Point(6, 20);
            this.button_ReadEnable.Name = "button_ReadEnable";
            this.button_ReadEnable.Size = new System.Drawing.Size(84, 27);
            this.button_ReadEnable.TabIndex = 38;
            this.button_ReadEnable.Text = "读使能";
            this.button_ReadEnable.UseVisualStyleBackColor = true;
            this.button_ReadEnable.Click += new System.EventHandler(this.button_ReadEnable_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox_PresenceID);
            this.groupBox1.Controls.Add(this.button_readPresenceData);
            this.groupBox1.Controls.Add(this.textBox_PresenceRes);
            this.groupBox1.Controls.Add(this.button_PresenceSensor);
            this.groupBox1.Location = new System.Drawing.Point(12, 342);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(603, 52);
            this.groupBox1.TabIndex = 37;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "人体检测传感器";
            // 
            // textBox_PresenceID
            // 
            this.textBox_PresenceID.Location = new System.Drawing.Point(110, 17);
            this.textBox_PresenceID.Name = "textBox_PresenceID";
            this.textBox_PresenceID.Size = new System.Drawing.Size(132, 21);
            this.textBox_PresenceID.TabIndex = 1;
            // 
            // button_readPresenceData
            // 
            this.button_readPresenceData.Location = new System.Drawing.Point(269, 15);
            this.button_readPresenceData.Name = "button_readPresenceData";
            this.button_readPresenceData.Size = new System.Drawing.Size(92, 23);
            this.button_readPresenceData.TabIndex = 0;
            this.button_readPresenceData.Text = "读使能";
            this.button_readPresenceData.UseVisualStyleBackColor = true;
            this.button_readPresenceData.Click += new System.EventHandler(this.button_ReadPresenceDataClick);
            // 
            // textBox_PresenceRes
            // 
            this.textBox_PresenceRes.Location = new System.Drawing.Point(367, 17);
            this.textBox_PresenceRes.Name = "textBox_PresenceRes";
            this.textBox_PresenceRes.Size = new System.Drawing.Size(132, 21);
            this.textBox_PresenceRes.TabIndex = 1;
            // 
            // button_PresenceSensor
            // 
            this.button_PresenceSensor.Location = new System.Drawing.Point(13, 17);
            this.button_PresenceSensor.Name = "button_PresenceSensor";
            this.button_PresenceSensor.Size = new System.Drawing.Size(91, 23);
            this.button_PresenceSensor.TabIndex = 0;
            this.button_PresenceSensor.Text = "读地址";
            this.button_PresenceSensor.UseVisualStyleBackColor = true;
            this.button_PresenceSensor.Click += new System.EventHandler(this.button_PresenceSensor_Click);
            // 
            // richTextBox_Monitor
            // 
            this.richTextBox_Monitor.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBox_Monitor.BackColor = System.Drawing.SystemColors.Control;
            this.richTextBox_Monitor.Location = new System.Drawing.Point(12, 400);
            this.richTextBox_Monitor.Name = "richTextBox_Monitor";
            this.richTextBox_Monitor.Size = new System.Drawing.Size(603, 219);
            this.richTextBox_Monitor.TabIndex = 36;
            this.richTextBox_Monitor.Text = "";
            // 
            // 倾角传感器
            // 
            this.倾角传感器.Controls.Add(this.button_modifyAddress);
            this.倾角传感器.Controls.Add(this.groupBox2);
            this.倾角传感器.Controls.Add(this.textBox_ModbussAddress);
            this.倾角传感器.Controls.Add(this.button_ReadValue);
            this.倾角传感器.Controls.Add(this.button_ReadAddr);
            this.倾角传感器.Location = new System.Drawing.Point(12, 108);
            this.倾角传感器.Name = "倾角传感器";
            this.倾角传感器.Size = new System.Drawing.Size(277, 218);
            this.倾角传感器.TabIndex = 35;
            this.倾角传感器.TabStop = false;
            this.倾角传感器.Text = "倾角传感器测试";
            // 
            // button_modifyAddress
            // 
            this.button_modifyAddress.Location = new System.Drawing.Point(13, 48);
            this.button_modifyAddress.Name = "button_modifyAddress";
            this.button_modifyAddress.Size = new System.Drawing.Size(92, 23);
            this.button_modifyAddress.TabIndex = 31;
            this.button_modifyAddress.Text = "修改地址";
            this.button_modifyAddress.UseVisualStyleBackColor = true;
            this.button_modifyAddress.Click += new System.EventHandler(this.button_modifyAddress_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox_Value_X);
            this.groupBox2.Controls.Add(this.textBox_Value_Y);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Location = new System.Drawing.Point(13, 106);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 80);
            this.groupBox2.TabIndex = 30;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "倾角";
            // 
            // textBox_Value_X
            // 
            this.textBox_Value_X.Location = new System.Drawing.Point(17, 20);
            this.textBox_Value_X.Name = "textBox_Value_X";
            this.textBox_Value_X.Size = new System.Drawing.Size(132, 21);
            this.textBox_Value_X.TabIndex = 1;
            // 
            // textBox_Value_Y
            // 
            this.textBox_Value_Y.Location = new System.Drawing.Point(17, 47);
            this.textBox_Value_Y.Name = "textBox_Value_Y";
            this.textBox_Value_Y.Size = new System.Drawing.Size(132, 21);
            this.textBox_Value_Y.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(155, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(11, 12);
            this.label3.TabIndex = 16;
            this.label3.Text = "X";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(155, 50);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(11, 12);
            this.label4.TabIndex = 16;
            this.label4.Text = "Y";
            // 
            // textBox_ModbussAddress
            // 
            this.textBox_ModbussAddress.Location = new System.Drawing.Point(110, 20);
            this.textBox_ModbussAddress.Name = "textBox_ModbussAddress";
            this.textBox_ModbussAddress.Size = new System.Drawing.Size(132, 21);
            this.textBox_ModbussAddress.TabIndex = 1;
            // 
            // button_ReadValue
            // 
            this.button_ReadValue.Location = new System.Drawing.Point(13, 77);
            this.button_ReadValue.Name = "button_ReadValue";
            this.button_ReadValue.Size = new System.Drawing.Size(92, 23);
            this.button_ReadValue.TabIndex = 0;
            this.button_ReadValue.Text = "读使能";
            this.button_ReadValue.UseVisualStyleBackColor = true;
            this.button_ReadValue.Click += new System.EventHandler(this.button_ReadValue_Click);
            // 
            // button_ReadAddr
            // 
            this.button_ReadAddr.Location = new System.Drawing.Point(13, 18);
            this.button_ReadAddr.Name = "button_ReadAddr";
            this.button_ReadAddr.Size = new System.Drawing.Size(91, 23);
            this.button_ReadAddr.TabIndex = 0;
            this.button_ReadAddr.Text = "读地址";
            this.button_ReadAddr.UseVisualStyleBackColor = true;
            this.button_ReadAddr.Click += new System.EventHandler(this.button_ReadAddr_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(189, 28);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(95, 12);
            this.label5.TabIndex = 33;
            this.label5.Text = "时间间隔（毫秒)";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.comboBox_ComPort);
            this.groupBox9.Controls.Add(this.comboBox_Baud);
            this.groupBox9.Controls.Add(this.button_Enable);
            this.groupBox9.Controls.Add(this.button_ClearBuff);
            this.groupBox9.Controls.Add(this.label1);
            this.groupBox9.Controls.Add(this.label2);
            this.groupBox9.Location = new System.Drawing.Point(12, 15);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(283, 86);
            this.groupBox9.TabIndex = 34;
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
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.textBox_time);
            this.groupBox5.Controls.Add(this.label5);
            this.groupBox5.Controls.Add(this.button_ReadEnable);
            this.groupBox5.Location = new System.Drawing.Point(320, 15);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(295, 86);
            this.groupBox5.TabIndex = 41;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "读控制参数";
            // 
            // timerSensor
            // 
            this.timerSensor.Enabled = true;
            this.timerSensor.Interval = 1000;
            this.timerSensor.Tick += new System.EventHandler(this.timerAct_Tick);
            // 
            // MultiSensorCtrl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.richTextBox_Monitor);
            this.Controls.Add(this.倾角传感器);
            this.Controls.Add(this.groupBox9);
            this.Name = "MultiSensorCtrl";
            this.Size = new System.Drawing.Size(806, 643);
            this.Load += new System.EventHandler(this.MultiSensorCtrl_Load);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.倾角传感器.ResumeLayout(false);
            this.倾角传感器.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.HScrollBar hScrollBar_bright;
        private System.Windows.Forms.HScrollBar hScrollBar_yellow;
        private System.Windows.Forms.Button button_turnOnLight;
        private System.Windows.Forms.Button button_configAddress;
        private System.Windows.Forms.Button button_turnOff;
        private System.Windows.Forms.Button button_CheckStatus;
        private System.Windows.Forms.TextBox textBox_Address;
        private System.Windows.Forms.TextBox textBox_time;
        private System.Windows.Forms.Button button_ReadEnable;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox_PresenceID;
        private System.Windows.Forms.Button button_readPresenceData;
        private System.Windows.Forms.TextBox textBox_PresenceRes;
        private System.Windows.Forms.Button button_PresenceSensor;
        private System.Windows.Forms.RichTextBox richTextBox_Monitor;
        private System.Windows.Forms.GroupBox 倾角传感器;
        private System.Windows.Forms.Button button_modifyAddress;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox_Value_X;
        private System.Windows.Forms.TextBox textBox_Value_Y;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_ModbussAddress;
        private System.Windows.Forms.Button button_ReadValue;
        private System.Windows.Forms.Button button_ReadAddr;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.ComboBox comboBox_ComPort;
        private System.Windows.Forms.ComboBox comboBox_Baud;
        private System.Windows.Forms.Button button_Enable;
        private System.Windows.Forms.Button button_ClearBuff;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Timer timerSensor;
    }
}

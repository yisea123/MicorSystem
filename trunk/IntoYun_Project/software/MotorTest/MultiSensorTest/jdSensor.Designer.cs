namespace MultiSensorTest
{
    partial class jdSensor
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
            this.倾角传感器 = new System.Windows.Forms.GroupBox();
            this.button_modifyAddress = new System.Windows.Forms.Button();
            this.textBox_ModbussAddress = new System.Windows.Forms.TextBox();
            this.button_ReadValue = new System.Windows.Forms.Button();
            this.button_ReadAddr = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox2_Value_X = new System.Windows.Forms.TextBox();
            this.textBox2_Value_Y = new System.Windows.Forms.TextBox();
            this.textBox2_Address = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBox_Value_X = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox1_address = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_Value_Y = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.comboBox_ComPort = new System.Windows.Forms.ComboBox();
            this.comboBox_Baud = new System.Windows.Forms.ComboBox();
            this.button_Enable = new System.Windows.Forms.Button();
            this.button_ClearBuff = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.zedGraphControl = new ZedGraph.ZedGraphControl();
            this.richTextBox_Monitor = new System.Windows.Forms.RichTextBox();
            this.timerAct = new System.Windows.Forms.Timer(this.components);
            this.倾角传感器.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.SuspendLayout();
            // 
            // 倾角传感器
            // 
            this.倾角传感器.Controls.Add(this.button_modifyAddress);
            this.倾角传感器.Controls.Add(this.textBox_ModbussAddress);
            this.倾角传感器.Controls.Add(this.button_ReadValue);
            this.倾角传感器.Controls.Add(this.button_ReadAddr);
            this.倾角传感器.Location = new System.Drawing.Point(257, 12);
            this.倾角传感器.Name = "倾角传感器";
            this.倾角传感器.Size = new System.Drawing.Size(216, 82);
            this.倾角传感器.TabIndex = 29;
            this.倾角传感器.TabStop = false;
            this.倾角传感器.Text = "倾角传感器测试";
            // 
            // button_modifyAddress
            // 
            this.button_modifyAddress.Location = new System.Drawing.Point(13, 48);
            this.button_modifyAddress.Name = "button_modifyAddress";
            this.button_modifyAddress.Size = new System.Drawing.Size(91, 26);
            this.button_modifyAddress.TabIndex = 31;
            this.button_modifyAddress.Text = "修改地址";
            this.button_modifyAddress.UseVisualStyleBackColor = true;
            this.button_modifyAddress.Click += new System.EventHandler(this.button_modifyAddress_Click_1);
            // 
            // textBox_ModbussAddress
            // 
            this.textBox_ModbussAddress.Location = new System.Drawing.Point(110, 20);
            this.textBox_ModbussAddress.Name = "textBox_ModbussAddress";
            this.textBox_ModbussAddress.Size = new System.Drawing.Size(93, 21);
            this.textBox_ModbussAddress.TabIndex = 1;
            // 
            // button_ReadValue
            // 
            this.button_ReadValue.Location = new System.Drawing.Point(111, 50);
            this.button_ReadValue.Name = "button_ReadValue";
            this.button_ReadValue.Size = new System.Drawing.Size(92, 23);
            this.button_ReadValue.TabIndex = 0;
            this.button_ReadValue.Text = "读使能";
            this.button_ReadValue.UseVisualStyleBackColor = true;
            this.button_ReadValue.Click += new System.EventHandler(this.button_ReadValue_Click_1);
            // 
            // button_ReadAddr
            // 
            this.button_ReadAddr.Location = new System.Drawing.Point(13, 18);
            this.button_ReadAddr.Name = "button_ReadAddr";
            this.button_ReadAddr.Size = new System.Drawing.Size(91, 23);
            this.button_ReadAddr.TabIndex = 0;
            this.button_ReadAddr.Text = "读地址";
            this.button_ReadAddr.UseVisualStyleBackColor = true;
            this.button_ReadAddr.Click += new System.EventHandler(this.button_ReadAddr_Click_1);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox2_Value_X);
            this.groupBox1.Controls.Add(this.textBox2_Value_Y);
            this.groupBox1.Controls.Add(this.textBox2_Address);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Location = new System.Drawing.Point(646, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(169, 82);
            this.groupBox1.TabIndex = 30;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "2号倾角";
            // 
            // textBox2_Value_X
            // 
            this.textBox2_Value_X.Location = new System.Drawing.Point(17, 17);
            this.textBox2_Value_X.Name = "textBox2_Value_X";
            this.textBox2_Value_X.ReadOnly = true;
            this.textBox2_Value_X.Size = new System.Drawing.Size(52, 21);
            this.textBox2_Value_X.TabIndex = 1;
            // 
            // textBox2_Value_Y
            // 
            this.textBox2_Value_Y.Location = new System.Drawing.Point(92, 19);
            this.textBox2_Value_Y.Name = "textBox2_Value_Y";
            this.textBox2_Value_Y.ReadOnly = true;
            this.textBox2_Value_Y.Size = new System.Drawing.Size(52, 21);
            this.textBox2_Value_Y.TabIndex = 1;
            // 
            // textBox2_Address
            // 
            this.textBox2_Address.Location = new System.Drawing.Point(74, 51);
            this.textBox2_Address.Name = "textBox2_Address";
            this.textBox2_Address.Size = new System.Drawing.Size(70, 21);
            this.textBox2_Address.TabIndex = 1;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(75, 22);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(11, 12);
            this.label5.TabIndex = 16;
            this.label5.Text = "X";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(150, 22);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(11, 12);
            this.label6.TabIndex = 16;
            this.label6.Text = "Y";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(15, 56);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 16;
            this.label8.Text = "通信地址";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox_Value_X);
            this.groupBox2.Controls.Add(this.textBox2);
            this.groupBox2.Controls.Add(this.textBox1_address);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.textBox_Value_Y);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Location = new System.Drawing.Point(479, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(161, 82);
            this.groupBox2.TabIndex = 30;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "1号倾角";
            // 
            // textBox_Value_X
            // 
            this.textBox_Value_X.Location = new System.Drawing.Point(6, 19);
            this.textBox_Value_X.Name = "textBox_Value_X";
            this.textBox_Value_X.ReadOnly = true;
            this.textBox_Value_X.Size = new System.Drawing.Size(51, 21);
            this.textBox_Value_X.TabIndex = 1;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(167, 47);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(51, 21);
            this.textBox2.TabIndex = 1;
            // 
            // textBox1_address
            // 
            this.textBox1_address.Location = new System.Drawing.Point(72, 50);
            this.textBox1_address.Name = "textBox1_address";
            this.textBox1_address.Size = new System.Drawing.Size(70, 21);
            this.textBox1_address.TabIndex = 1;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(144, 23);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(11, 12);
            this.label7.TabIndex = 16;
            this.label7.Text = "Y";
            // 
            // textBox_Value_Y
            // 
            this.textBox_Value_Y.Location = new System.Drawing.Point(91, 17);
            this.textBox_Value_Y.Name = "textBox_Value_Y";
            this.textBox_Value_Y.ReadOnly = true;
            this.textBox_Value_Y.Size = new System.Drawing.Size(51, 21);
            this.textBox_Value_Y.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(63, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(11, 12);
            this.label3.TabIndex = 16;
            this.label3.Text = "X";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 53);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 16;
            this.label4.Text = "通信地址";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.comboBox_ComPort);
            this.groupBox9.Controls.Add(this.comboBox_Baud);
            this.groupBox9.Controls.Add(this.button_Enable);
            this.groupBox9.Controls.Add(this.button_ClearBuff);
            this.groupBox9.Controls.Add(this.label1);
            this.groupBox9.Controls.Add(this.label2);
            this.groupBox9.Location = new System.Drawing.Point(23, 12);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(228, 82);
            this.groupBox9.TabIndex = 28;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "串口";
            // 
            // comboBox_ComPort
            // 
            this.comboBox_ComPort.FormattingEnabled = true;
            this.comboBox_ComPort.Location = new System.Drawing.Point(58, 20);
            this.comboBox_ComPort.Name = "comboBox_ComPort";
            this.comboBox_ComPort.Size = new System.Drawing.Size(64, 20);
            this.comboBox_ComPort.TabIndex = 12;
            // 
            // comboBox_Baud
            // 
            this.comboBox_Baud.FormattingEnabled = true;
            this.comboBox_Baud.Location = new System.Drawing.Point(58, 53);
            this.comboBox_Baud.Name = "comboBox_Baud";
            this.comboBox_Baud.Size = new System.Drawing.Size(64, 20);
            this.comboBox_Baud.TabIndex = 13;
            // 
            // button_Enable
            // 
            this.button_Enable.Location = new System.Drawing.Point(128, 20);
            this.button_Enable.Name = "button_Enable";
            this.button_Enable.Size = new System.Drawing.Size(90, 21);
            this.button_Enable.TabIndex = 14;
            this.button_Enable.Text = "打开串口";
            this.button_Enable.UseVisualStyleBackColor = true;
            this.button_Enable.Click += new System.EventHandler(this.button_Enable_Click);
            // 
            // button_ClearBuff
            // 
            this.button_ClearBuff.Location = new System.Drawing.Point(128, 47);
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
            // zedGraphControl
            // 
            this.zedGraphControl.Location = new System.Drawing.Point(23, 100);
            this.zedGraphControl.Name = "zedGraphControl";
            this.zedGraphControl.ScrollGrace = 0D;
            this.zedGraphControl.ScrollMaxX = 0D;
            this.zedGraphControl.ScrollMaxY = 0D;
            this.zedGraphControl.ScrollMaxY2 = 0D;
            this.zedGraphControl.ScrollMinX = 0D;
            this.zedGraphControl.ScrollMinY = 0D;
            this.zedGraphControl.ScrollMinY2 = 0D;
            this.zedGraphControl.Size = new System.Drawing.Size(869, 443);
            this.zedGraphControl.TabIndex = 30;
            // 
            // richTextBox_Monitor
            // 
            this.richTextBox_Monitor.BackColor = System.Drawing.SystemColors.Control;
            this.richTextBox_Monitor.Location = new System.Drawing.Point(23, 549);
            this.richTextBox_Monitor.Name = "richTextBox_Monitor";
            this.richTextBox_Monitor.ReadOnly = true;
            this.richTextBox_Monitor.Size = new System.Drawing.Size(869, 70);
            this.richTextBox_Monitor.TabIndex = 31;
            this.richTextBox_Monitor.Text = "";
            // 
            // timerAct
            // 
            this.timerAct.Enabled = true;
            this.timerAct.Interval = 300;
            this.timerAct.Tick += new System.EventHandler(this.timerAct_Tick);
            // 
            // jdSensor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.richTextBox_Monitor);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.zedGraphControl);
            this.Controls.Add(this.倾角传感器);
            this.Controls.Add(this.groupBox9);
            this.Name = "jdSensor";
            this.Size = new System.Drawing.Size(954, 636);
            this.Load += new System.EventHandler(this.jdSensor_Load);
            this.倾角传感器.ResumeLayout(false);
            this.倾角传感器.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox 倾角传感器;
        private System.Windows.Forms.Button button_modifyAddress;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox2_Value_X;
        private System.Windows.Forms.TextBox textBox2_Value_Y;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox_Value_X;
        private System.Windows.Forms.TextBox textBox_Value_Y;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_ModbussAddress;
        private System.Windows.Forms.Button button_ReadValue;
        private System.Windows.Forms.Button button_ReadAddr;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.ComboBox comboBox_ComPort;
        private System.Windows.Forms.ComboBox comboBox_Baud;
        private System.Windows.Forms.Button button_Enable;
        private System.Windows.Forms.Button button_ClearBuff;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private ZedGraph.ZedGraphControl zedGraphControl;
        private System.Windows.Forms.RichTextBox richTextBox_Monitor;
        private System.Windows.Forms.Timer timerAct;
        private System.Windows.Forms.TextBox textBox1_address;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox2_Address;
        private System.Windows.Forms.Label label8;
    }
}

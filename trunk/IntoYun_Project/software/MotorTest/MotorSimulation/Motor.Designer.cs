namespace MotorSimulation
{
    partial class Motor
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
            this.button_CommCtrl = new System.Windows.Forms.Button();
            this.comboBox_Baud = new System.Windows.Forms.ComboBox();
            this.comboBox_ComPort = new System.Windows.Forms.ComboBox();
            this.pictureBox_Motor1 = new System.Windows.Forms.PictureBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.Motor4_Cir = new System.Windows.Forms.Label();
            this.Motor3_Cir = new System.Windows.Forms.Label();
            this.Motor2_Cir = new System.Windows.Forms.Label();
            this.Motor1_Cir = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.Motor4_Speed = new System.Windows.Forms.Label();
            this.Motor3_Speed = new System.Windows.Forms.Label();
            this.Motor2_Speed = new System.Windows.Forms.Label();
            this.Motor1_Speed = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.pictureBox_Motor4 = new System.Windows.Forms.PictureBox();
            this.pictureBox_Motor3 = new System.Windows.Forms.PictureBox();
            this.pictureBox_Motor2 = new System.Windows.Forms.PictureBox();
            this.timerAct = new System.Windows.Forms.Timer(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button_Clear = new System.Windows.Forms.Button();
            this.richTextBox_Monitor = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Motor1)).BeginInit();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Motor4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Motor3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Motor2)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(5, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "波特率";
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
            // button_CommCtrl
            // 
            this.button_CommCtrl.Location = new System.Drawing.Point(135, 16);
            this.button_CommCtrl.Name = "button_CommCtrl";
            this.button_CommCtrl.Size = new System.Drawing.Size(74, 32);
            this.button_CommCtrl.TabIndex = 6;
            this.button_CommCtrl.Text = "打开串口";
            this.button_CommCtrl.UseVisualStyleBackColor = true;
            this.button_CommCtrl.Click += new System.EventHandler(this.button_CommCtrl_Click);
            // 
            // comboBox_Baud
            // 
            this.comboBox_Baud.FormattingEnabled = true;
            this.comboBox_Baud.Location = new System.Drawing.Point(62, 63);
            this.comboBox_Baud.Name = "comboBox_Baud";
            this.comboBox_Baud.Size = new System.Drawing.Size(59, 20);
            this.comboBox_Baud.TabIndex = 5;
            // 
            // comboBox_ComPort
            // 
            this.comboBox_ComPort.FormattingEnabled = true;
            this.comboBox_ComPort.Location = new System.Drawing.Point(62, 23);
            this.comboBox_ComPort.Name = "comboBox_ComPort";
            this.comboBox_ComPort.Size = new System.Drawing.Size(59, 20);
            this.comboBox_ComPort.TabIndex = 4;
            // 
            // pictureBox_Motor1
            // 
            this.pictureBox_Motor1.Image = global::MotorSimulation.Properties.Resources.run1;
            this.pictureBox_Motor1.Location = new System.Drawing.Point(24, 86);
            this.pictureBox_Motor1.Name = "pictureBox_Motor1";
            this.pictureBox_Motor1.Size = new System.Drawing.Size(49, 50);
            this.pictureBox_Motor1.TabIndex = 9;
            this.pictureBox_Motor1.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.label14);
            this.panel1.Controls.Add(this.label12);
            this.panel1.Controls.Add(this.label10);
            this.panel1.Controls.Add(this.Motor4_Cir);
            this.panel1.Controls.Add(this.Motor3_Cir);
            this.panel1.Controls.Add(this.Motor2_Cir);
            this.panel1.Controls.Add(this.Motor1_Cir);
            this.panel1.Controls.Add(this.label8);
            this.panel1.Controls.Add(this.label13);
            this.panel1.Controls.Add(this.label11);
            this.panel1.Controls.Add(this.label9);
            this.panel1.Controls.Add(this.Motor4_Speed);
            this.panel1.Controls.Add(this.Motor3_Speed);
            this.panel1.Controls.Add(this.Motor2_Speed);
            this.panel1.Controls.Add(this.Motor1_Speed);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.pictureBox_Motor4);
            this.panel1.Controls.Add(this.pictureBox_Motor3);
            this.panel1.Controls.Add(this.pictureBox_Motor2);
            this.panel1.Controls.Add(this.pictureBox_Motor1);
            this.panel1.Location = new System.Drawing.Point(12, 107);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(567, 230);
            this.panel1.TabIndex = 10;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.ForeColor = System.Drawing.Color.Red;
            this.label6.Location = new System.Drawing.Point(345, 18);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(47, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "4号电机";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.Color.Red;
            this.label5.Location = new System.Drawing.Point(239, 18);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 10;
            this.label5.Text = "3号电机";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.Red;
            this.label4.Location = new System.Drawing.Point(133, 18);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 12);
            this.label4.TabIndex = 10;
            this.label4.Text = "2号电机";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.ForeColor = System.Drawing.Color.Red;
            this.label14.Location = new System.Drawing.Point(329, 175);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(53, 12);
            this.label14.TabIndex = 10;
            this.label14.Text = "电流值：";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.ForeColor = System.Drawing.Color.Red;
            this.label12.Location = new System.Drawing.Point(229, 175);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(53, 12);
            this.label12.TabIndex = 10;
            this.label12.Text = "电流值：";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.ForeColor = System.Drawing.Color.Red;
            this.label10.Location = new System.Drawing.Point(133, 175);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(53, 12);
            this.label10.TabIndex = 10;
            this.label10.Text = "电流值：";
            // 
            // Motor4_Cir
            // 
            this.Motor4_Cir.AutoSize = true;
            this.Motor4_Cir.ForeColor = System.Drawing.Color.Red;
            this.Motor4_Cir.Location = new System.Drawing.Point(385, 175);
            this.Motor4_Cir.Name = "Motor4_Cir";
            this.Motor4_Cir.Size = new System.Drawing.Size(11, 12);
            this.Motor4_Cir.TabIndex = 10;
            this.Motor4_Cir.Text = "0";
            // 
            // Motor3_Cir
            // 
            this.Motor3_Cir.AutoSize = true;
            this.Motor3_Cir.ForeColor = System.Drawing.Color.Red;
            this.Motor3_Cir.Location = new System.Drawing.Point(288, 175);
            this.Motor3_Cir.Name = "Motor3_Cir";
            this.Motor3_Cir.Size = new System.Drawing.Size(11, 12);
            this.Motor3_Cir.TabIndex = 10;
            this.Motor3_Cir.Text = "0";
            // 
            // Motor2_Cir
            // 
            this.Motor2_Cir.AutoSize = true;
            this.Motor2_Cir.ForeColor = System.Drawing.Color.Red;
            this.Motor2_Cir.Location = new System.Drawing.Point(187, 175);
            this.Motor2_Cir.Name = "Motor2_Cir";
            this.Motor2_Cir.Size = new System.Drawing.Size(11, 12);
            this.Motor2_Cir.TabIndex = 10;
            this.Motor2_Cir.Text = "0";
            // 
            // Motor1_Cir
            // 
            this.Motor1_Cir.AutoSize = true;
            this.Motor1_Cir.ForeColor = System.Drawing.Color.Red;
            this.Motor1_Cir.Location = new System.Drawing.Point(79, 175);
            this.Motor1_Cir.Name = "Motor1_Cir";
            this.Motor1_Cir.Size = new System.Drawing.Size(11, 12);
            this.Motor1_Cir.TabIndex = 10;
            this.Motor1_Cir.Text = "0";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.ForeColor = System.Drawing.Color.Red;
            this.label8.Location = new System.Drawing.Point(22, 175);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 10;
            this.label8.Text = "电流值：";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.ForeColor = System.Drawing.Color.Red;
            this.label13.Location = new System.Drawing.Point(317, 153);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(65, 12);
            this.label13.TabIndex = 10;
            this.label13.Text = "运行速度：";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.ForeColor = System.Drawing.Color.Red;
            this.label11.Location = new System.Drawing.Point(217, 153);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(65, 12);
            this.label11.TabIndex = 10;
            this.label11.Text = "运行速度：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.ForeColor = System.Drawing.Color.Red;
            this.label9.Location = new System.Drawing.Point(119, 153);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 12);
            this.label9.TabIndex = 10;
            this.label9.Text = "运行速度：";
            // 
            // Motor4_Speed
            // 
            this.Motor4_Speed.AutoSize = true;
            this.Motor4_Speed.ForeColor = System.Drawing.Color.Red;
            this.Motor4_Speed.Location = new System.Drawing.Point(385, 153);
            this.Motor4_Speed.Name = "Motor4_Speed";
            this.Motor4_Speed.Size = new System.Drawing.Size(11, 12);
            this.Motor4_Speed.TabIndex = 10;
            this.Motor4_Speed.Text = "0";
            // 
            // Motor3_Speed
            // 
            this.Motor3_Speed.AutoSize = true;
            this.Motor3_Speed.ForeColor = System.Drawing.Color.Red;
            this.Motor3_Speed.Location = new System.Drawing.Point(288, 153);
            this.Motor3_Speed.Name = "Motor3_Speed";
            this.Motor3_Speed.Size = new System.Drawing.Size(11, 12);
            this.Motor3_Speed.TabIndex = 10;
            this.Motor3_Speed.Text = "0";
            // 
            // Motor2_Speed
            // 
            this.Motor2_Speed.AutoSize = true;
            this.Motor2_Speed.ForeColor = System.Drawing.Color.Red;
            this.Motor2_Speed.Location = new System.Drawing.Point(187, 153);
            this.Motor2_Speed.Name = "Motor2_Speed";
            this.Motor2_Speed.Size = new System.Drawing.Size(11, 12);
            this.Motor2_Speed.TabIndex = 10;
            this.Motor2_Speed.Text = "0";
            // 
            // Motor1_Speed
            // 
            this.Motor1_Speed.AutoSize = true;
            this.Motor1_Speed.ForeColor = System.Drawing.Color.Red;
            this.Motor1_Speed.Location = new System.Drawing.Point(79, 153);
            this.Motor1_Speed.Name = "Motor1_Speed";
            this.Motor1_Speed.Size = new System.Drawing.Size(11, 12);
            this.Motor1_Speed.TabIndex = 10;
            this.Motor1_Speed.Text = "0";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.ForeColor = System.Drawing.Color.Red;
            this.label7.Location = new System.Drawing.Point(8, 153);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(65, 12);
            this.label7.TabIndex = 10;
            this.label7.Text = "运行速度：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.Red;
            this.label3.Location = new System.Drawing.Point(22, 18);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 10;
            this.label3.Text = "1号电机";
            // 
            // pictureBox_Motor4
            // 
            this.pictureBox_Motor4.Image = global::MotorSimulation.Properties.Resources.run1;
            this.pictureBox_Motor4.Location = new System.Drawing.Point(343, 86);
            this.pictureBox_Motor4.Name = "pictureBox_Motor4";
            this.pictureBox_Motor4.Size = new System.Drawing.Size(49, 50);
            this.pictureBox_Motor4.TabIndex = 9;
            this.pictureBox_Motor4.TabStop = false;
            // 
            // pictureBox_Motor3
            // 
            this.pictureBox_Motor3.Image = global::MotorSimulation.Properties.Resources.run1;
            this.pictureBox_Motor3.Location = new System.Drawing.Point(241, 86);
            this.pictureBox_Motor3.Name = "pictureBox_Motor3";
            this.pictureBox_Motor3.Size = new System.Drawing.Size(49, 50);
            this.pictureBox_Motor3.TabIndex = 9;
            this.pictureBox_Motor3.TabStop = false;
            // 
            // pictureBox_Motor2
            // 
            this.pictureBox_Motor2.Image = global::MotorSimulation.Properties.Resources.run1;
            this.pictureBox_Motor2.Location = new System.Drawing.Point(135, 86);
            this.pictureBox_Motor2.Name = "pictureBox_Motor2";
            this.pictureBox_Motor2.Size = new System.Drawing.Size(49, 50);
            this.pictureBox_Motor2.TabIndex = 9;
            this.pictureBox_Motor2.TabStop = false;
            // 
            // timerAct
            // 
            this.timerAct.Enabled = true;
            this.timerAct.Tick += new System.EventHandler(this.timerAct_Tick);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button_Clear);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.comboBox_ComPort);
            this.groupBox1.Controls.Add(this.button_CommCtrl);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.comboBox_Baud);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(250, 89);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口";
            // 
            // button_Clear
            // 
            this.button_Clear.Location = new System.Drawing.Point(135, 55);
            this.button_Clear.Name = "button_Clear";
            this.button_Clear.Size = new System.Drawing.Size(75, 28);
            this.button_Clear.TabIndex = 9;
            this.button_Clear.Text = "Clear";
            this.button_Clear.UseVisualStyleBackColor = true;
            this.button_Clear.Click += new System.EventHandler(this.button_Clear_Click);
            // 
            // richTextBox_Monitor
            // 
            this.richTextBox_Monitor.Location = new System.Drawing.Point(12, 343);
            this.richTextBox_Monitor.Multiline = true;
            this.richTextBox_Monitor.Name = "richTextBox_Monitor";
            this.richTextBox_Monitor.ReadOnly = true;
            this.richTextBox_Monitor.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.richTextBox_Monitor.Size = new System.Drawing.Size(567, 239);
            this.richTextBox_Monitor.TabIndex = 13;
            // 
            // Motor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(591, 594);
            this.Controls.Add(this.richTextBox_Monitor);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Motor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "模拟电机";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Motor_FormClosed);
            this.Load += new System.EventHandler(this.Motor_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Motor1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Motor4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Motor3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Motor2)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_CommCtrl;
        private System.Windows.Forms.ComboBox comboBox_Baud;
        private System.Windows.Forms.ComboBox comboBox_ComPort;
        private System.Windows.Forms.PictureBox pictureBox_Motor1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox pictureBox_Motor4;
        private System.Windows.Forms.PictureBox pictureBox_Motor3;
        private System.Windows.Forms.PictureBox pictureBox_Motor2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label Motor4_Cir;
        private System.Windows.Forms.Label Motor3_Cir;
        private System.Windows.Forms.Label Motor2_Cir;
        private System.Windows.Forms.Label Motor1_Cir;
        private System.Windows.Forms.Label Motor4_Speed;
        private System.Windows.Forms.Label Motor3_Speed;
        private System.Windows.Forms.Label Motor2_Speed;
        private System.Windows.Forms.Label Motor1_Speed;
        private System.Windows.Forms.Timer timerAct;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button_Clear;
        private System.Windows.Forms.TextBox richTextBox_Monitor;
    }
}


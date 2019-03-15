namespace MotorTest
{
    partial class Motortest
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
            this.comboBox_ComPort = new System.Windows.Forms.ComboBox();
            this.comboBox_Baud = new System.Windows.Forms.ComboBox();
            this.button_Enable = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_inteval = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBox_Cmd = new System.Windows.Forms.TextBox();
            this.textBox_Speed = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.checkBox_Motor_4 = new System.Windows.Forms.CheckBox();
            this.checkBox_Motor_3 = new System.Windows.Forms.CheckBox();
            this.button_Stop = new System.Windows.Forms.Button();
            this.checkBox_Motor_2 = new System.Windows.Forms.CheckBox();
            this.button_Down = new System.Windows.Forms.Button();
            this.checkBox_Motor_1 = new System.Windows.Forms.CheckBox();
            this.button_Up = new System.Windows.Forms.Button();
            this.checkBox_AllMotor = new System.Windows.Forms.CheckBox();
            this.richTextBox_Monitor = new System.Windows.Forms.RichTextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.timerAction = new System.Windows.Forms.Timer(this.components);
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.label13 = new System.Windows.Forms.Label();
            this.textBox_Motor4_Speed = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.textBox_Motor4_Cir = new System.Windows.Forms.TextBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBox_Motor3_Speed = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.textBox_Motor3_Cir = new System.Windows.Forms.TextBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textBox_Motor2_Speed = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox_Motor2_Cir = new System.Windows.Forms.TextBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox_Motor1_Speed = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_Motor1_Cir = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBox_ComPort
            // 
            this.comboBox_ComPort.FormattingEnabled = true;
            this.comboBox_ComPort.Location = new System.Drawing.Point(52, 20);
            this.comboBox_ComPort.Name = "comboBox_ComPort";
            this.comboBox_ComPort.Size = new System.Drawing.Size(88, 21);
            this.comboBox_ComPort.TabIndex = 0;
            // 
            // comboBox_Baud
            // 
            this.comboBox_Baud.FormattingEnabled = true;
            this.comboBox_Baud.Location = new System.Drawing.Point(52, 62);
            this.comboBox_Baud.Name = "comboBox_Baud";
            this.comboBox_Baud.Size = new System.Drawing.Size(88, 21);
            this.comboBox_Baud.TabIndex = 1;
            // 
            // button_Enable
            // 
            this.button_Enable.Location = new System.Drawing.Point(146, 20);
            this.button_Enable.Name = "button_Enable";
            this.button_Enable.Size = new System.Drawing.Size(86, 29);
            this.button_Enable.TabIndex = 2;
            this.button_Enable.Text = "打开串口";
            this.button_Enable.UseVisualStyleBackColor = true;
            this.button_Enable.Click += new System.EventHandler(this.button_Enable_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "端口号";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 62);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "波特率";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox3);
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Location = new System.Drawing.Point(3, 108);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(261, 446);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "平台控制";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.textBox_inteval);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.textBox_Cmd);
            this.groupBox3.Controls.Add(this.textBox_Speed);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Location = new System.Drawing.Point(6, 176);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(245, 117);
            this.groupBox3.TabIndex = 9;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "控制参数";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(219, 25);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(20, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "ms";
            // 
            // textBox_inteval
            // 
            this.textBox_inteval.Location = new System.Drawing.Point(124, 20);
            this.textBox_inteval.Name = "textBox_inteval";
            this.textBox_inteval.Size = new System.Drawing.Size(89, 20);
            this.textBox_inteval.TabIndex = 5;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(64, 85);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(43, 13);
            this.label6.TabIndex = 6;
            this.label6.Text = "写速度";
            // 
            // textBox_Cmd
            // 
            this.textBox_Cmd.Location = new System.Drawing.Point(124, 55);
            this.textBox_Cmd.Name = "textBox_Cmd";
            this.textBox_Cmd.Size = new System.Drawing.Size(89, 20);
            this.textBox_Cmd.TabIndex = 5;
            // 
            // textBox_Speed
            // 
            this.textBox_Speed.Location = new System.Drawing.Point(124, 85);
            this.textBox_Speed.Name = "textBox_Speed";
            this.textBox_Speed.Size = new System.Drawing.Size(89, 20);
            this.textBox_Speed.TabIndex = 5;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(30, 59);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(79, 13);
            this.label5.TabIndex = 6;
            this.label5.Text = "发送命令次数";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(103, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "发送命令时间间隔";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.checkBox_Motor_4);
            this.groupBox2.Controls.Add(this.checkBox_Motor_3);
            this.groupBox2.Controls.Add(this.button_Stop);
            this.groupBox2.Controls.Add(this.checkBox_Motor_2);
            this.groupBox2.Controls.Add(this.button_Down);
            this.groupBox2.Controls.Add(this.checkBox_Motor_1);
            this.groupBox2.Controls.Add(this.button_Up);
            this.groupBox2.Controls.Add(this.checkBox_AllMotor);
            this.groupBox2.Location = new System.Drawing.Point(6, 22);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(245, 148);
            this.groupBox2.TabIndex = 8;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "电机";
            // 
            // checkBox_Motor_4
            // 
            this.checkBox_Motor_4.AutoSize = true;
            this.checkBox_Motor_4.Location = new System.Drawing.Point(20, 117);
            this.checkBox_Motor_4.Name = "checkBox_Motor_4";
            this.checkBox_Motor_4.Size = new System.Drawing.Size(62, 17);
            this.checkBox_Motor_4.TabIndex = 0;
            this.checkBox_Motor_4.Text = "Motor 4";
            this.checkBox_Motor_4.UseVisualStyleBackColor = true;
            // 
            // checkBox_Motor_3
            // 
            this.checkBox_Motor_3.AutoSize = true;
            this.checkBox_Motor_3.Location = new System.Drawing.Point(20, 93);
            this.checkBox_Motor_3.Name = "checkBox_Motor_3";
            this.checkBox_Motor_3.Size = new System.Drawing.Size(62, 17);
            this.checkBox_Motor_3.TabIndex = 0;
            this.checkBox_Motor_3.Text = "Motor 3";
            this.checkBox_Motor_3.UseVisualStyleBackColor = true;
            // 
            // button_Stop
            // 
            this.button_Stop.Location = new System.Drawing.Point(135, 105);
            this.button_Stop.Name = "button_Stop";
            this.button_Stop.Size = new System.Drawing.Size(87, 29);
            this.button_Stop.TabIndex = 0;
            this.button_Stop.Text = "停止";
            this.button_Stop.UseVisualStyleBackColor = true;
            this.button_Stop.Click += new System.EventHandler(this.button_Stop_Click);
            // 
            // checkBox_Motor_2
            // 
            this.checkBox_Motor_2.AutoSize = true;
            this.checkBox_Motor_2.Location = new System.Drawing.Point(20, 69);
            this.checkBox_Motor_2.Name = "checkBox_Motor_2";
            this.checkBox_Motor_2.Size = new System.Drawing.Size(62, 17);
            this.checkBox_Motor_2.TabIndex = 0;
            this.checkBox_Motor_2.Text = "Motor 2";
            this.checkBox_Motor_2.UseVisualStyleBackColor = true;
            // 
            // button_Down
            // 
            this.button_Down.Location = new System.Drawing.Point(135, 60);
            this.button_Down.Name = "button_Down";
            this.button_Down.Size = new System.Drawing.Size(87, 33);
            this.button_Down.TabIndex = 0;
            this.button_Down.Text = "下降";
            this.button_Down.UseVisualStyleBackColor = true;
            this.button_Down.Click += new System.EventHandler(this.button_Down_Click);
            // 
            // checkBox_Motor_1
            // 
            this.checkBox_Motor_1.AutoSize = true;
            this.checkBox_Motor_1.Location = new System.Drawing.Point(20, 46);
            this.checkBox_Motor_1.Name = "checkBox_Motor_1";
            this.checkBox_Motor_1.Size = new System.Drawing.Size(62, 17);
            this.checkBox_Motor_1.TabIndex = 0;
            this.checkBox_Motor_1.Text = "Motor 1";
            this.checkBox_Motor_1.UseVisualStyleBackColor = true;
            // 
            // button_Up
            // 
            this.button_Up.Location = new System.Drawing.Point(135, 16);
            this.button_Up.Name = "button_Up";
            this.button_Up.Size = new System.Drawing.Size(87, 34);
            this.button_Up.TabIndex = 0;
            this.button_Up.Text = "上升";
            this.button_Up.UseVisualStyleBackColor = true;
            this.button_Up.Click += new System.EventHandler(this.button_Up_Click);
            // 
            // checkBox_AllMotor
            // 
            this.checkBox_AllMotor.AutoSize = true;
            this.checkBox_AllMotor.Location = new System.Drawing.Point(20, 22);
            this.checkBox_AllMotor.Name = "checkBox_AllMotor";
            this.checkBox_AllMotor.Size = new System.Drawing.Size(67, 17);
            this.checkBox_AllMotor.TabIndex = 0;
            this.checkBox_AllMotor.Text = "All Motor";
            this.checkBox_AllMotor.UseVisualStyleBackColor = true;
            this.checkBox_AllMotor.CheckedChanged += new System.EventHandler(this.checkBox_AllMotor_CheckedChanged);
            // 
            // richTextBox_Monitor
            // 
            this.richTextBox_Monitor.Location = new System.Drawing.Point(270, 119);
            this.richTextBox_Monitor.Name = "richTextBox_Monitor";
            this.richTextBox_Monitor.ReadOnly = true;
            this.richTextBox_Monitor.Size = new System.Drawing.Size(474, 435);
            this.richTextBox_Monitor.TabIndex = 5;
            this.richTextBox_Monitor.Text = "";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(146, 57);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(86, 29);
            this.button1.TabIndex = 6;
            this.button1.Text = "清空缓存";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // timerAction
            // 
            this.timerAction.Enabled = true;
            this.timerAction.Interval = 50;
            this.timerAction.Tick += new System.EventHandler(this.timerAction_Tick);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.comboBox_ComPort);
            this.groupBox4.Controls.Add(this.button1);
            this.groupBox4.Controls.Add(this.comboBox_Baud);
            this.groupBox4.Controls.Add(this.button_Enable);
            this.groupBox4.Controls.Add(this.label2);
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Location = new System.Drawing.Point(7, 2);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(257, 100);
            this.groupBox4.TabIndex = 7;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "串口";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.groupBox9);
            this.groupBox5.Controls.Add(this.groupBox8);
            this.groupBox5.Controls.Add(this.groupBox7);
            this.groupBox5.Controls.Add(this.groupBox6);
            this.groupBox5.Location = new System.Drawing.Point(270, 2);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(473, 111);
            this.groupBox5.TabIndex = 8;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "电机参数（Read）";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.label13);
            this.groupBox9.Controls.Add(this.textBox_Motor4_Speed);
            this.groupBox9.Controls.Add(this.label14);
            this.groupBox9.Controls.Add(this.textBox_Motor4_Cir);
            this.groupBox9.Location = new System.Drawing.Point(354, 23);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(110, 77);
            this.groupBox9.TabIndex = 9;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Motor 4";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(4, 48);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(31, 13);
            this.label13.TabIndex = 1;
            this.label13.Text = "电流";
            // 
            // textBox_Motor4_Speed
            // 
            this.textBox_Motor4_Speed.Location = new System.Drawing.Point(40, 20);
            this.textBox_Motor4_Speed.Name = "textBox_Motor4_Speed";
            this.textBox_Motor4_Speed.Size = new System.Drawing.Size(55, 20);
            this.textBox_Motor4_Speed.TabIndex = 0;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(3, 22);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(31, 13);
            this.label14.TabIndex = 1;
            this.label14.Text = "速度";
            // 
            // textBox_Motor4_Cir
            // 
            this.textBox_Motor4_Cir.Location = new System.Drawing.Point(41, 46);
            this.textBox_Motor4_Cir.Name = "textBox_Motor4_Cir";
            this.textBox_Motor4_Cir.Size = new System.Drawing.Size(55, 20);
            this.textBox_Motor4_Cir.TabIndex = 0;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.label11);
            this.groupBox8.Controls.Add(this.textBox_Motor3_Speed);
            this.groupBox8.Controls.Add(this.label12);
            this.groupBox8.Controls.Add(this.textBox_Motor3_Cir);
            this.groupBox8.Location = new System.Drawing.Point(238, 23);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(110, 77);
            this.groupBox8.TabIndex = 9;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Motor 3";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(4, 48);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(31, 13);
            this.label11.TabIndex = 1;
            this.label11.Text = "电流";
            // 
            // textBox_Motor3_Speed
            // 
            this.textBox_Motor3_Speed.Location = new System.Drawing.Point(40, 20);
            this.textBox_Motor3_Speed.Name = "textBox_Motor3_Speed";
            this.textBox_Motor3_Speed.Size = new System.Drawing.Size(55, 20);
            this.textBox_Motor3_Speed.TabIndex = 0;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(3, 22);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(31, 13);
            this.label12.TabIndex = 1;
            this.label12.Text = "速度";
            // 
            // textBox_Motor3_Cir
            // 
            this.textBox_Motor3_Cir.Location = new System.Drawing.Point(41, 46);
            this.textBox_Motor3_Cir.Name = "textBox_Motor3_Cir";
            this.textBox_Motor3_Cir.Size = new System.Drawing.Size(55, 20);
            this.textBox_Motor3_Cir.TabIndex = 0;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label9);
            this.groupBox7.Controls.Add(this.textBox_Motor2_Speed);
            this.groupBox7.Controls.Add(this.label10);
            this.groupBox7.Controls.Add(this.textBox_Motor2_Cir);
            this.groupBox7.Location = new System.Drawing.Point(122, 22);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(110, 77);
            this.groupBox7.TabIndex = 9;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Motor 2";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(4, 48);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(31, 13);
            this.label9.TabIndex = 1;
            this.label9.Text = "电流";
            // 
            // textBox_Motor2_Speed
            // 
            this.textBox_Motor2_Speed.Location = new System.Drawing.Point(40, 20);
            this.textBox_Motor2_Speed.Name = "textBox_Motor2_Speed";
            this.textBox_Motor2_Speed.Size = new System.Drawing.Size(55, 20);
            this.textBox_Motor2_Speed.TabIndex = 0;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(3, 22);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(31, 13);
            this.label10.TabIndex = 1;
            this.label10.Text = "速度";
            // 
            // textBox_Motor2_Cir
            // 
            this.textBox_Motor2_Cir.Location = new System.Drawing.Point(41, 46);
            this.textBox_Motor2_Cir.Name = "textBox_Motor2_Cir";
            this.textBox_Motor2_Cir.Size = new System.Drawing.Size(55, 20);
            this.textBox_Motor2_Cir.TabIndex = 0;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.label8);
            this.groupBox6.Controls.Add(this.textBox_Motor1_Speed);
            this.groupBox6.Controls.Add(this.label7);
            this.groupBox6.Controls.Add(this.textBox_Motor1_Cir);
            this.groupBox6.Location = new System.Drawing.Point(6, 20);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(110, 77);
            this.groupBox6.TabIndex = 9;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Motor 1";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(4, 48);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(31, 13);
            this.label8.TabIndex = 1;
            this.label8.Text = "电流";
            // 
            // textBox_Motor1_Speed
            // 
            this.textBox_Motor1_Speed.Location = new System.Drawing.Point(40, 20);
            this.textBox_Motor1_Speed.Name = "textBox_Motor1_Speed";
            this.textBox_Motor1_Speed.Size = new System.Drawing.Size(55, 20);
            this.textBox_Motor1_Speed.TabIndex = 0;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(3, 22);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(31, 13);
            this.label7.TabIndex = 1;
            this.label7.Text = "速度";
            // 
            // textBox_Motor1_Cir
            // 
            this.textBox_Motor1_Cir.Location = new System.Drawing.Point(41, 46);
            this.textBox_Motor1_Cir.Name = "textBox_Motor1_Cir";
            this.textBox_Motor1_Cir.Size = new System.Drawing.Size(55, 20);
            this.textBox_Motor1_Cir.TabIndex = 0;
            // 
            // Motortest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(747, 564);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.richTextBox_Monitor);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Motortest";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "电机控制";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Motortest_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox_ComPort;
        private System.Windows.Forms.ComboBox comboBox_Baud;
        private System.Windows.Forms.Button button_Enable;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button_Stop;
        private System.Windows.Forms.Button button_Down;
        private System.Windows.Forms.Button button_Up;
        private System.Windows.Forms.Timer timerAction;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.RichTextBox richTextBox_Monitor;
        private System.Windows.Forms.TextBox textBox_inteval;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox_Cmd;
        private System.Windows.Forms.TextBox textBox_Speed;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox checkBox_Motor_4;
        private System.Windows.Forms.CheckBox checkBox_Motor_3;
        private System.Windows.Forms.CheckBox checkBox_Motor_2;
        private System.Windows.Forms.CheckBox checkBox_Motor_1;
        private System.Windows.Forms.CheckBox checkBox_AllMotor;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.TextBox textBox_Motor1_Speed;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox textBox_Motor4_Speed;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox textBox_Motor4_Cir;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBox_Motor3_Speed;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBox_Motor3_Cir;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBox_Motor2_Speed;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBox_Motor2_Cir;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox_Motor1_Cir;
    }
}


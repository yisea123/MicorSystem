namespace MultiSensorTest
{
    partial class MainWin
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
            this.panel_Config = new System.Windows.Forms.Panel();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.button_DA0404A = new System.Windows.Forms.Button();
            this.button_JdSensor = new System.Windows.Forms.Button();
            this.button_Motor = new System.Windows.Forms.Button();
            this.button_sensor = new System.Windows.Forms.Button();
            this.groupBox11.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel_Config
            // 
            this.panel_Config.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_Config.BackColor = System.Drawing.SystemColors.ControlLight;
            this.panel_Config.Location = new System.Drawing.Point(149, 2);
            this.panel_Config.Name = "panel_Config";
            this.panel_Config.Size = new System.Drawing.Size(946, 631);
            this.panel_Config.TabIndex = 29;
            // 
            // groupBox11
            // 
            this.groupBox11.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.groupBox11.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.groupBox11.Controls.Add(this.button_DA0404A);
            this.groupBox11.Controls.Add(this.button_JdSensor);
            this.groupBox11.Controls.Add(this.button_Motor);
            this.groupBox11.Controls.Add(this.button_sensor);
            this.groupBox11.Location = new System.Drawing.Point(0, 2);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(152, 631);
            this.groupBox11.TabIndex = 28;
            this.groupBox11.TabStop = false;
            // 
            // button_DA0404A
            // 
            this.button_DA0404A.Location = new System.Drawing.Point(12, 190);
            this.button_DA0404A.Name = "button_DA0404A";
            this.button_DA0404A.Size = new System.Drawing.Size(116, 38);
            this.button_DA0404A.TabIndex = 2;
            this.button_DA0404A.Text = "模拟器";
            this.button_DA0404A.UseVisualStyleBackColor = true;
            this.button_DA0404A.Click += new System.EventHandler(this.button_DA0404A_Click);
            // 
            // button_JdSensor
            // 
            this.button_JdSensor.Location = new System.Drawing.Point(12, 129);
            this.button_JdSensor.Name = "button_JdSensor";
            this.button_JdSensor.Size = new System.Drawing.Size(116, 38);
            this.button_JdSensor.TabIndex = 1;
            this.button_JdSensor.Text = "倾斜传感器";
            this.button_JdSensor.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.button_JdSensor.UseVisualStyleBackColor = true;
            this.button_JdSensor.Click += new System.EventHandler(this.button_JDsensor_Click);
            // 
            // button_Motor
            // 
            this.button_Motor.Location = new System.Drawing.Point(12, 20);
            this.button_Motor.Name = "button_Motor";
            this.button_Motor.Size = new System.Drawing.Size(116, 38);
            this.button_Motor.TabIndex = 1;
            this.button_Motor.Text = "电机";
            this.button_Motor.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.button_Motor.UseVisualStyleBackColor = true;
            this.button_Motor.Click += new System.EventHandler(this.button_Motor_Click);
            // 
            // button_sensor
            // 
            this.button_sensor.Location = new System.Drawing.Point(12, 73);
            this.button_sensor.Name = "button_sensor";
            this.button_sensor.Size = new System.Drawing.Size(116, 38);
            this.button_sensor.TabIndex = 1;
            this.button_sensor.Text = "Sensor";
            this.button_sensor.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.button_sensor.UseVisualStyleBackColor = true;
            this.button_sensor.Click += new System.EventHandler(this.button_sensor_Click);
            // 
            // MainWin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1090, 635);
            this.Controls.Add(this.panel_Config);
            this.Controls.Add(this.groupBox11);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.Name = "MainWin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "智能家居调试软件";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainWin_FormClosed);
            this.Load += new System.EventHandler(this.MainWin_Load);
            this.groupBox11.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel_Config;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Button button_sensor;
        private System.Windows.Forms.Button button_Motor;
        private System.Windows.Forms.Button button_JdSensor;
        private System.Windows.Forms.Button button_DA0404A;
    }
}


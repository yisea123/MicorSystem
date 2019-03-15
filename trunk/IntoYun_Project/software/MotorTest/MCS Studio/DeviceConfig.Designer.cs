namespace MCS_Studio
{
    partial class DeviceConfig
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
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button_config_SSID = new System.Windows.Forms.Button();
            this.button_read_SSID = new System.Windows.Forms.Button();
            this.button_config_PWD = new System.Windows.Forms.Button();
            this.button_read_PWD = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_PWD = new System.Windows.Forms.TextBox();
            this.textBox_SSID = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button_configProjectID = new System.Windows.Forms.Button();
            this.button_readProjectID = new System.Windows.Forms.Button();
            this.button_configSecret = new System.Windows.Forms.Button();
            this.button_ReadSecret = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_secret = new System.Windows.Forms.TextBox();
            this.textBox_ProjectID = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox_DeviceID = new System.Windows.Forms.TextBox();
            this.button_readDeviceID = new System.Windows.Forms.Button();
            this.button_configDeviceID = new System.Windows.Forms.Button();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button_config_SSID);
            this.groupBox2.Controls.Add(this.button_read_SSID);
            this.groupBox2.Controls.Add(this.button_config_PWD);
            this.groupBox2.Controls.Add(this.button_read_PWD);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.textBox_PWD);
            this.groupBox2.Controls.Add(this.textBox_SSID);
            this.groupBox2.Location = new System.Drawing.Point(26, 210);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(737, 107);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Wifi信息";
            // 
            // button_config_SSID
            // 
            this.button_config_SSID.Location = new System.Drawing.Point(634, 31);
            this.button_config_SSID.Name = "button_config_SSID";
            this.button_config_SSID.Size = new System.Drawing.Size(75, 23);
            this.button_config_SSID.TabIndex = 2;
            this.button_config_SSID.Text = "配置";
            this.button_config_SSID.UseVisualStyleBackColor = true;
            this.button_config_SSID.Click += new System.EventHandler(this.button_config_SSID_Click);
            // 
            // button_read_SSID
            // 
            this.button_read_SSID.Location = new System.Drawing.Point(553, 30);
            this.button_read_SSID.Name = "button_read_SSID";
            this.button_read_SSID.Size = new System.Drawing.Size(75, 23);
            this.button_read_SSID.TabIndex = 2;
            this.button_read_SSID.Text = "读取";
            this.button_read_SSID.UseVisualStyleBackColor = true;
            this.button_read_SSID.Click += new System.EventHandler(this.button_read_SSID_Click);
            // 
            // button_config_PWD
            // 
            this.button_config_PWD.Location = new System.Drawing.Point(634, 65);
            this.button_config_PWD.Name = "button_config_PWD";
            this.button_config_PWD.Size = new System.Drawing.Size(75, 23);
            this.button_config_PWD.TabIndex = 2;
            this.button_config_PWD.Text = "配置";
            this.button_config_PWD.UseVisualStyleBackColor = true;
            this.button_config_PWD.Click += new System.EventHandler(this.button_config_PWD_Click);
            // 
            // button_read_PWD
            // 
            this.button_read_PWD.Location = new System.Drawing.Point(553, 64);
            this.button_read_PWD.Name = "button_read_PWD";
            this.button_read_PWD.Size = new System.Drawing.Size(75, 23);
            this.button_read_PWD.TabIndex = 2;
            this.button_read_PWD.Text = "读取";
            this.button_read_PWD.UseVisualStyleBackColor = true;
            this.button_read_PWD.Click += new System.EventHandler(this.button_read_PWD_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 70);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "密码";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 34);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 1;
            this.label4.Text = "SSID";
            // 
            // textBox_PWD
            // 
            this.textBox_PWD.Location = new System.Drawing.Point(77, 67);
            this.textBox_PWD.Name = "textBox_PWD";
            this.textBox_PWD.Size = new System.Drawing.Size(469, 21);
            this.textBox_PWD.TabIndex = 0;
            // 
            // textBox_SSID
            // 
            this.textBox_SSID.Location = new System.Drawing.Point(77, 31);
            this.textBox_SSID.Name = "textBox_SSID";
            this.textBox_SSID.Size = new System.Drawing.Size(469, 21);
            this.textBox_SSID.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button_configProjectID);
            this.groupBox1.Controls.Add(this.button_readProjectID);
            this.groupBox1.Controls.Add(this.button_configDeviceID);
            this.groupBox1.Controls.Add(this.button_readDeviceID);
            this.groupBox1.Controls.Add(this.button_configSecret);
            this.groupBox1.Controls.Add(this.button_ReadSecret);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.textBox_DeviceID);
            this.groupBox1.Controls.Add(this.textBox_secret);
            this.groupBox1.Controls.Add(this.textBox_ProjectID);
            this.groupBox1.Location = new System.Drawing.Point(18, 23);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(737, 151);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "项目信息";
            // 
            // button_configProjectID
            // 
            this.button_configProjectID.Location = new System.Drawing.Point(634, 31);
            this.button_configProjectID.Name = "button_configProjectID";
            this.button_configProjectID.Size = new System.Drawing.Size(75, 23);
            this.button_configProjectID.TabIndex = 2;
            this.button_configProjectID.Text = "配置";
            this.button_configProjectID.UseVisualStyleBackColor = true;
            this.button_configProjectID.Click += new System.EventHandler(this.button_ConfigProjectID_Click);
            // 
            // button_readProjectID
            // 
            this.button_readProjectID.Location = new System.Drawing.Point(553, 30);
            this.button_readProjectID.Name = "button_readProjectID";
            this.button_readProjectID.Size = new System.Drawing.Size(75, 23);
            this.button_readProjectID.TabIndex = 2;
            this.button_readProjectID.Text = "读取";
            this.button_readProjectID.UseVisualStyleBackColor = true;
            this.button_readProjectID.Click += new System.EventHandler(this.button_readProjectID_Click);
            // 
            // button_configSecret
            // 
            this.button_configSecret.Location = new System.Drawing.Point(634, 65);
            this.button_configSecret.Name = "button_configSecret";
            this.button_configSecret.Size = new System.Drawing.Size(75, 23);
            this.button_configSecret.TabIndex = 2;
            this.button_configSecret.Text = "配置";
            this.button_configSecret.UseVisualStyleBackColor = true;
            this.button_configSecret.Click += new System.EventHandler(this.button_configSecret_Click);
            // 
            // button_ReadSecret
            // 
            this.button_ReadSecret.Location = new System.Drawing.Point(553, 64);
            this.button_ReadSecret.Name = "button_ReadSecret";
            this.button_ReadSecret.Size = new System.Drawing.Size(75, 23);
            this.button_ReadSecret.TabIndex = 2;
            this.button_ReadSecret.Text = "读取";
            this.button_ReadSecret.UseVisualStyleBackColor = true;
            this.button_ReadSecret.Click += new System.EventHandler(this.button_ReadSecret_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 70);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "项目密钥";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "项目ID";
            // 
            // textBox_secret
            // 
            this.textBox_secret.Location = new System.Drawing.Point(77, 67);
            this.textBox_secret.Name = "textBox_secret";
            this.textBox_secret.Size = new System.Drawing.Size(469, 21);
            this.textBox_secret.TabIndex = 0;
            // 
            // textBox_ProjectID
            // 
            this.textBox_ProjectID.Location = new System.Drawing.Point(77, 31);
            this.textBox_ProjectID.Name = "textBox_ProjectID";
            this.textBox_ProjectID.Size = new System.Drawing.Size(469, 21);
            this.textBox_ProjectID.TabIndex = 0;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 110);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 1;
            this.label5.Text = "设备标识";
            // 
            // textBox_DeviceID
            // 
            this.textBox_DeviceID.Location = new System.Drawing.Point(77, 107);
            this.textBox_DeviceID.Name = "textBox_DeviceID";
            this.textBox_DeviceID.Size = new System.Drawing.Size(469, 21);
            this.textBox_DeviceID.TabIndex = 0;
            // 
            // button_readDeviceID
            // 
            this.button_readDeviceID.Location = new System.Drawing.Point(553, 104);
            this.button_readDeviceID.Name = "button_readDeviceID";
            this.button_readDeviceID.Size = new System.Drawing.Size(75, 23);
            this.button_readDeviceID.TabIndex = 2;
            this.button_readDeviceID.Text = "读取";
            this.button_readDeviceID.UseVisualStyleBackColor = true;
            this.button_readDeviceID.Click += new System.EventHandler(this.button_ReadDeviceID_Click);
            // 
            // button_configDeviceID
            // 
            this.button_configDeviceID.Location = new System.Drawing.Point(634, 105);
            this.button_configDeviceID.Name = "button_configDeviceID";
            this.button_configDeviceID.Size = new System.Drawing.Size(75, 23);
            this.button_configDeviceID.TabIndex = 2;
            this.button_configDeviceID.Text = "配置";
            this.button_configDeviceID.UseVisualStyleBackColor = true;
            this.button_configDeviceID.Click += new System.EventHandler(this.button_configDeviceID_Click);
            // 
            // DeviceConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "DeviceConfig";
            this.Size = new System.Drawing.Size(859, 534);
            this.Load += new System.EventHandler(this.DeviceConfig_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button button_config_SSID;
        private System.Windows.Forms.Button button_read_SSID;
        private System.Windows.Forms.Button button_config_PWD;
        private System.Windows.Forms.Button button_read_PWD;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_PWD;
        private System.Windows.Forms.TextBox textBox_SSID;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button_configProjectID;
        private System.Windows.Forms.Button button_readProjectID;
        private System.Windows.Forms.Button button_configSecret;
        private System.Windows.Forms.Button button_ReadSecret;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_secret;
        private System.Windows.Forms.TextBox textBox_ProjectID;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox_DeviceID;
        private System.Windows.Forms.Button button_configDeviceID;
        private System.Windows.Forms.Button button_readDeviceID;
    }
}

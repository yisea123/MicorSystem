namespace MCS_Studio
{
    partial class MainWindows
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
            this.statusStrip3 = new System.Windows.Forms.StatusStrip();
            this.st_ToolInfor = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip4 = new System.Windows.Forms.StatusStrip();
            this.toolVersionInfor = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.dateLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolsTime = new System.Windows.Forms.ToolStripStatusLabel();
            this.panel_Config = new System.Windows.Forms.Panel();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.Button_SerialCtrl = new System.Windows.Forms.Button();
            this.cbx_ComBaud = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.cmbox_ComPort = new System.Windows.Forms.ComboBox();
            this.label16 = new System.Windows.Forms.Label();
            this.button_Device = new System.Windows.Forms.Button();
            this.button_system = new System.Windows.Forms.Button();
            this.statusStrip3.SuspendLayout();
            this.statusStrip4.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusStrip3
            // 
            this.statusStrip3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.statusStrip3.AutoSize = false;
            this.statusStrip3.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip3.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.st_ToolInfor});
            this.statusStrip3.Location = new System.Drawing.Point(712, 630);
            this.statusStrip3.Name = "statusStrip3";
            this.statusStrip3.Size = new System.Drawing.Size(287, 22);
            this.statusStrip3.TabIndex = 30;
            this.statusStrip3.Text = "statusStrip1";
            // 
            // st_ToolInfor
            // 
            this.st_ToolInfor.Name = "st_ToolInfor";
            this.st_ToolInfor.Size = new System.Drawing.Size(75, 17);
            this.st_ToolInfor.Text = "status_label";
            // 
            // statusStrip4
            // 
            this.statusStrip4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.statusStrip4.AutoSize = false;
            this.statusStrip4.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip4.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolVersionInfor});
            this.statusStrip4.Location = new System.Drawing.Point(359, 630);
            this.statusStrip4.Name = "statusStrip4";
            this.statusStrip4.Size = new System.Drawing.Size(353, 22);
            this.statusStrip4.TabIndex = 29;
            this.statusStrip4.Text = "statusStrip1";
            // 
            // toolVersionInfor
            // 
            this.toolVersionInfor.Name = "toolVersionInfor";
            this.toolVersionInfor.Size = new System.Drawing.Size(65, 17);
            this.toolVersionInfor.Text = "toolsTime";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.statusStrip1.AutoSize = false;
            this.statusStrip1.Dock = System.Windows.Forms.DockStyle.None;
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dateLabel,
            this.toolsTime});
            this.statusStrip1.Location = new System.Drawing.Point(1, 630);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(358, 22);
            this.statusStrip1.TabIndex = 28;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // dateLabel
            // 
            this.dateLabel.Name = "dateLabel";
            this.dateLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // toolsTime
            // 
            this.toolsTime.Name = "toolsTime";
            this.toolsTime.Size = new System.Drawing.Size(65, 17);
            this.toolsTime.Text = "toolsTime";
            // 
            // panel_Config
            // 
            this.panel_Config.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel_Config.BackColor = System.Drawing.SystemColors.ControlLight;
            this.panel_Config.Location = new System.Drawing.Point(177, 1);
            this.panel_Config.Name = "panel_Config";
            this.panel_Config.Size = new System.Drawing.Size(822, 626);
            this.panel_Config.TabIndex = 27;
            // 
            // groupBox11
            // 
            this.groupBox11.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.groupBox11.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.groupBox11.Controls.Add(this.groupBox3);
            this.groupBox11.Controls.Add(this.button_Device);
            this.groupBox11.Controls.Add(this.button_system);
            this.groupBox11.Location = new System.Drawing.Point(1, 1);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(179, 626);
            this.groupBox11.TabIndex = 26;
            this.groupBox11.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.Button_SerialCtrl);
            this.groupBox3.Controls.Add(this.cbx_ComBaud);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.cmbox_ComPort);
            this.groupBox3.Controls.Add(this.label16);
            this.groupBox3.Location = new System.Drawing.Point(11, 20);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(159, 130);
            this.groupBox3.TabIndex = 14;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "串口";
            // 
            // Button_SerialCtrl
            // 
            this.Button_SerialCtrl.Location = new System.Drawing.Point(35, 79);
            this.Button_SerialCtrl.Name = "Button_SerialCtrl";
            this.Button_SerialCtrl.Size = new System.Drawing.Size(101, 34);
            this.Button_SerialCtrl.TabIndex = 17;
            this.Button_SerialCtrl.Text = "打开串口";
            this.Button_SerialCtrl.UseVisualStyleBackColor = true;
            this.Button_SerialCtrl.Click += new System.EventHandler(this.Button_SerialCtrl_Click);
            // 
            // cbx_ComBaud
            // 
            this.cbx_ComBaud.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbx_ComBaud.FormattingEnabled = true;
            this.cbx_ComBaud.Location = new System.Drawing.Point(63, 44);
            this.cbx_ComBaud.Name = "cbx_ComBaud";
            this.cbx_ComBaud.Size = new System.Drawing.Size(87, 20);
            this.cbx_ComBaud.TabIndex = 16;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 49);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(53, 12);
            this.label11.TabIndex = 15;
            this.label11.Text = "波特率：";
            // 
            // cmbox_ComPort
            // 
            this.cmbox_ComPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbox_ComPort.FormattingEnabled = true;
            this.cmbox_ComPort.Location = new System.Drawing.Point(63, 18);
            this.cmbox_ComPort.Name = "cmbox_ComPort";
            this.cmbox_ComPort.Size = new System.Drawing.Size(87, 20);
            this.cmbox_ComPort.TabIndex = 12;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(6, 21);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(41, 12);
            this.label16.TabIndex = 0;
            this.label16.Text = "端口号";
            // 
            // button_Device
            // 
            this.button_Device.Location = new System.Drawing.Point(11, 234);
            this.button_Device.Name = "button_Device";
            this.button_Device.Size = new System.Drawing.Size(159, 52);
            this.button_Device.TabIndex = 1;
            this.button_Device.Text = "Wifi模块参数";
            this.button_Device.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.button_Device.UseVisualStyleBackColor = true;
            this.button_Device.Click += new System.EventHandler(this.button_Device_Click);
            // 
            // button_system
            // 
            this.button_system.Location = new System.Drawing.Point(11, 169);
            this.button_system.Name = "button_system";
            this.button_system.Size = new System.Drawing.Size(159, 50);
            this.button_system.TabIndex = 1;
            this.button_system.Text = "系统配置";
            this.button_system.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.button_system.UseVisualStyleBackColor = true;
            this.button_system.Click += new System.EventHandler(this.button_system_Click);
            // 
            // MainWindows
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1001, 652);
            this.Controls.Add(this.statusStrip3);
            this.Controls.Add(this.statusStrip4);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.panel_Config);
            this.Controls.Add(this.groupBox11);
            this.Name = "MainWindows";
            this.Text = "MCS Studio";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainWindows_FormClosed);
            this.Load += new System.EventHandler(this.MainWindows_Load);
            this.statusStrip3.ResumeLayout(false);
            this.statusStrip3.PerformLayout();
            this.statusStrip4.ResumeLayout(false);
            this.statusStrip4.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.StatusStrip statusStrip3;
        private System.Windows.Forms.ToolStripStatusLabel st_ToolInfor;
        private System.Windows.Forms.StatusStrip statusStrip4;
        private System.Windows.Forms.ToolStripStatusLabel toolVersionInfor;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel dateLabel;
        private System.Windows.Forms.ToolStripStatusLabel toolsTime;
        private System.Windows.Forms.Panel panel_Config;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button Button_SerialCtrl;
        private System.Windows.Forms.ComboBox cbx_ComBaud;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ComboBox cmbox_ComPort;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Button button_Device;
        private System.Windows.Forms.Button button_system;
    }
}


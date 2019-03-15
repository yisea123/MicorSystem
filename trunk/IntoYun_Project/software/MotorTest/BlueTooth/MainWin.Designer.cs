namespace BlueTooth
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
            this.button_Enable = new System.Windows.Forms.Button();
            this.comboBox_Baud = new System.Windows.Forms.ComboBox();
            this.comboBox_ComPort = new System.Windows.Forms.ComboBox();
            this.richTextBox_Monitor = new System.Windows.Forms.RichTextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button_ClearBuff = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button_Enable
            // 
            this.button_Enable.Location = new System.Drawing.Point(188, 12);
            this.button_Enable.Name = "button_Enable";
            this.button_Enable.Size = new System.Drawing.Size(90, 48);
            this.button_Enable.TabIndex = 8;
            this.button_Enable.Text = "打开串口";
            this.button_Enable.UseVisualStyleBackColor = true;
            this.button_Enable.Click += new System.EventHandler(this.button_Enable_Click);
            // 
            // comboBox_Baud
            // 
            this.comboBox_Baud.FormattingEnabled = true;
            this.comboBox_Baud.Location = new System.Drawing.Point(61, 45);
            this.comboBox_Baud.Name = "comboBox_Baud";
            this.comboBox_Baud.Size = new System.Drawing.Size(121, 20);
            this.comboBox_Baud.TabIndex = 7;
            // 
            // comboBox_ComPort
            // 
            this.comboBox_ComPort.FormattingEnabled = true;
            this.comboBox_ComPort.Location = new System.Drawing.Point(61, 12);
            this.comboBox_ComPort.Name = "comboBox_ComPort";
            this.comboBox_ComPort.Size = new System.Drawing.Size(121, 20);
            this.comboBox_ComPort.TabIndex = 6;
            // 
            // richTextBox_Monitor
            // 
            this.richTextBox_Monitor.Location = new System.Drawing.Point(3, 71);
            this.richTextBox_Monitor.Name = "richTextBox_Monitor";
            this.richTextBox_Monitor.ReadOnly = true;
            this.richTextBox_Monitor.Size = new System.Drawing.Size(591, 472);
            this.richTextBox_Monitor.TabIndex = 9;
            this.richTextBox_Monitor.Text = "";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 10;
            this.label2.Text = "波特率";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 11;
            this.label1.Text = "端口号";
            // 
            // button_ClearBuff
            // 
            this.button_ClearBuff.Location = new System.Drawing.Point(299, 15);
            this.button_ClearBuff.Name = "button_ClearBuff";
            this.button_ClearBuff.Size = new System.Drawing.Size(90, 42);
            this.button_ClearBuff.TabIndex = 12;
            this.button_ClearBuff.Text = "清空缓存";
            this.button_ClearBuff.UseVisualStyleBackColor = true;
            this.button_ClearBuff.Click += new System.EventHandler(this.button_ClearBuff_Click);
            // 
            // MainWin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(599, 546);
            this.Controls.Add(this.button_ClearBuff);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_Enable);
            this.Controls.Add(this.comboBox_Baud);
            this.Controls.Add(this.comboBox_ComPort);
            this.Controls.Add(this.richTextBox_Monitor);
            this.MaximizeBox = false;
            this.Name = "MainWin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "蓝牙控制测试";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainWin_FormClosed);
            this.Load += new System.EventHandler(this.MainWin_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_Enable;
        private System.Windows.Forms.ComboBox comboBox_Baud;
        private System.Windows.Forms.ComboBox comboBox_ComPort;
        private System.Windows.Forms.RichTextBox richTextBox_Monitor;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_ClearBuff;
    }
}


namespace Proxy_Test
{
    partial class Proxy_Test
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
            this.button_Log = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button_Log
            // 
            this.button_Log.Location = new System.Drawing.Point(47, 30);
            this.button_Log.Name = "button_Log";
            this.button_Log.Size = new System.Drawing.Size(115, 46);
            this.button_Log.TabIndex = 0;
            this.button_Log.Text = "test log";
            this.button_Log.UseVisualStyleBackColor = true;
            this.button_Log.Click += new System.EventHandler(this.button_Log_Click);
            // 
            // Proxy_Test
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button_Log);
            this.Name = "Proxy_Test";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Proxy_Test_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_Log;
    }
}


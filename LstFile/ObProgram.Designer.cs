namespace LstFile
{
    partial class ObProgram
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ObProgram));
            this.labelTitle = new System.Windows.Forms.Label();
            this.labelText = new System.Windows.Forms.Label();
            this.labelOb1 = new System.Windows.Forms.Label();
            this.labelOb2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonClose = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // labelTitle
            // 
            this.labelTitle.AutoSize = true;
            this.labelTitle.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.labelTitle.Location = new System.Drawing.Point(218, 8);
            this.labelTitle.Name = "labelTitle";
            this.labelTitle.Size = new System.Drawing.Size(84, 21);
            this.labelTitle.TabIndex = 0;
            this.labelTitle.Text = "Lst File++ ";
            // 
            // labelText
            // 
            this.labelText.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.labelText.AutoSize = true;
            this.labelText.BackColor = System.Drawing.Color.Transparent;
            this.labelText.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelText.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.labelText.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Italic);
            this.labelText.Location = new System.Drawing.Point(1, 40);
            this.labelText.Name = "labelText";
            this.labelText.Size = new System.Drawing.Size(580, 26);
            this.labelText.TabIndex = 1;
            this.labelText.Text = "Lst file++ - it is program, will have created an .lst file with all the frames(fo" +
    "rmat .wrl; .tga; .bmp) .";
            this.labelText.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            this.labelText.UseCompatibleTextRendering = true;
            this.labelText.Click += new System.EventHandler(this.labelText_Click);
            // 
            // labelOb1
            // 
            this.labelOb1.AutoSize = true;
            this.labelOb1.Location = new System.Drawing.Point(1, 78);
            this.labelOb1.Name = "labelOb1";
            this.labelOb1.Size = new System.Drawing.Size(129, 13);
            this.labelOb1.TabIndex = 2;
            this.labelOb1.Text = "Open - open your frame(s)";
            // 
            // labelOb2
            // 
            this.labelOb2.AutoSize = true;
            this.labelOb2.Location = new System.Drawing.Point(1, 165);
            this.labelOb2.Name = "labelOb2";
            this.labelOb2.Size = new System.Drawing.Size(384, 13);
            this.labelOb2.TabIndex = 2;
            this.labelOb2.Text = "Pixacker - its program, will have open your files and saved in 1 file(in developi" +
    "ng)";
            this.labelOb2.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1, 137);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(375, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "CriSpis - its program, will have create list for Triangulator pack(correct packin" +
    "g)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(165, 78);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(92, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "X - clear input text";
            this.label2.Visible = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(321, 78);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(133, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Clear lst - clear your frames";
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(218, 195);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(64, 20);
            this.buttonClose.TabIndex = 3;
            this.buttonClose.Text = "OK";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(1, 106);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(159, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "Save - saved your frame(s) in list";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(165, 106);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(167, 13);
            this.label5.TabIndex = 2;
            this.label5.Text = "Create - created  list for your goals";
            // 
            // ObProgram
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(582, 222);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.labelOb2);
            this.Controls.Add(this.labelOb1);
            this.Controls.Add(this.labelText);
            this.Controls.Add(this.labelTitle);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(590, 250);
            this.MinimumSize = new System.Drawing.Size(590, 250);
            this.Name = "ObProgram";
            this.Text = "About the program";
            this.Load += new System.EventHandler(this.ObProgram_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelTitle;
        private System.Windows.Forms.Label labelText;
        private System.Windows.Forms.Label labelOb1;
        private System.Windows.Forms.Label labelOb2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
    }
}
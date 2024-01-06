namespace LstFile
{
    partial class ObAvtore
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ObAvtore));
            this.labelAuthor = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.labelYear = new System.Windows.Forms.Label();
            this.buttonOKOvAvtore = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // labelAuthor
            // 
            this.labelAuthor.AutoSize = true;
            this.labelAuthor.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.labelAuthor.Location = new System.Drawing.Point(9, 27);
            this.labelAuthor.Name = "labelAuthor";
            this.labelAuthor.Size = new System.Drawing.Size(140, 15);
            this.labelAuthor.TabIndex = 0;
            this.labelAuthor.Text = "Author: Sadochok(BISEC)";
            this.labelAuthor.Click += new System.EventHandler(this.labelAuthor_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.label1.Location = new System.Drawing.Point(9, 44);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(231, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "For: Heroes of Annihilated Empires Reborn";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.label2.Location = new System.Drawing.Point(109, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 15);
            this.label2.TabIndex = 0;
            this.label2.Text = "Lst File++";
            // 
            // labelYear
            // 
            this.labelYear.AutoSize = true;
            this.labelYear.Location = new System.Drawing.Point(214, 94);
            this.labelYear.Name = "labelYear";
            this.labelYear.Size = new System.Drawing.Size(31, 13);
            this.labelYear.TabIndex = 0;
            this.labelYear.Text = "2021";
            // 
            // buttonOKOvAvtore
            // 
            this.buttonOKOvAvtore.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.buttonOKOvAvtore.Location = new System.Drawing.Point(53, 71);
            this.buttonOKOvAvtore.Name = "buttonOKOvAvtore";
            this.buttonOKOvAvtore.Size = new System.Drawing.Size(138, 30);
            this.buttonOKOvAvtore.TabIndex = 1;
            this.buttonOKOvAvtore.Text = "OK";
            this.buttonOKOvAvtore.UseVisualStyleBackColor = true;
            this.buttonOKOvAvtore.Click += new System.EventHandler(this.buttonOKOvAvtore_Click);
            // 
            // ObAvtore
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(248, 114);
            this.Controls.Add(this.buttonOKOvAvtore);
            this.Controls.Add(this.labelYear);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.labelAuthor);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ObAvtore";
            this.Text = "About the Author";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelAuthor;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelYear;
        private System.Windows.Forms.Button buttonOKOvAvtore;
    }
}
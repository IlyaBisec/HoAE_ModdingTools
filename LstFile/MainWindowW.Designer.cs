namespace LstFile
{
    partial class MainWindowW
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindowW));
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.listBoxFiles = new System.Windows.Forms.ListBox();
            this.buttonClearList = new System.Windows.Forms.Button();
            this.buttonCleatPole = new System.Windows.Forms.Button();
            this.labelFileList = new System.Windows.Forms.Label();
            this.laberFormatFiles = new System.Windows.Forms.Label();
            this.buttonExit = new System.Windows.Forms.Button();
            this.buttonOpen = new System.Windows.Forms.Button();
            this.buttonSaveAs = new System.Windows.Forms.Button();
            this.buttonEdit = new System.Windows.Forms.Button();
            this.buttonObAvtore = new System.Windows.Forms.Button();
            this.buttonObProgram = new System.Windows.Forms.Button();
            this.labelNameLst = new System.Windows.Forms.Label();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.buttonCreateLst = new System.Windows.Forms.Button();
            this.buttonHideWindow = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(10, 596);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(79, 21);
            this.comboBox1.TabIndex = 0;
            this.comboBox1.Visible = false;
            // 
            // listBoxFiles
            // 
            this.listBoxFiles.AllowDrop = true;
            this.listBoxFiles.FormattingEnabled = true;
            this.listBoxFiles.Location = new System.Drawing.Point(116, 26);
            this.listBoxFiles.Name = "listBoxFiles";
            this.listBoxFiles.Size = new System.Drawing.Size(197, 277);
            this.listBoxFiles.TabIndex = 1;
            // 
            // buttonClearList
            // 
            this.buttonClearList.Location = new System.Drawing.Point(256, 4);
            this.buttonClearList.Name = "buttonClearList";
            this.buttonClearList.Size = new System.Drawing.Size(56, 20);
            this.buttonClearList.TabIndex = 2;
            this.buttonClearList.Text = "Clear list";
            this.buttonClearList.UseVisualStyleBackColor = true;
            this.buttonClearList.Click += new System.EventHandler(this.buttonClearList_Click);
            // 
            // buttonCleatPole
            // 
            this.buttonCleatPole.Location = new System.Drawing.Point(283, 562);
            this.buttonCleatPole.Name = "buttonCleatPole";
            this.buttonCleatPole.Size = new System.Drawing.Size(21, 20);
            this.buttonCleatPole.TabIndex = 3;
            this.buttonCleatPole.Text = "X";
            this.buttonCleatPole.UseVisualStyleBackColor = true;
            this.buttonCleatPole.Visible = false;
            this.buttonCleatPole.Click += new System.EventHandler(this.buttonCleatPole_Click);
            // 
            // labelFileList
            // 
            this.labelFileList.AutoSize = true;
            this.labelFileList.Font = new System.Drawing.Font("Segoe UI", 11F);
            this.labelFileList.Location = new System.Drawing.Point(116, 6);
            this.labelFileList.Name = "labelFileList";
            this.labelFileList.Size = new System.Drawing.Size(64, 20);
            this.labelFileList.TabIndex = 4;
            this.labelFileList.Text = "Files list:";
            // 
            // laberFormatFiles
            // 
            this.laberFormatFiles.AutoSize = true;
            this.laberFormatFiles.Font = new System.Drawing.Font("Segoe UI", 11F);
            this.laberFormatFiles.Location = new System.Drawing.Point(10, 571);
            this.laberFormatFiles.Name = "laberFormatFiles";
            this.laberFormatFiles.Size = new System.Drawing.Size(90, 20);
            this.laberFormatFiles.TabIndex = 5;
            this.laberFormatFiles.Text = "Format files:";
            this.laberFormatFiles.Visible = false;
            // 
            // buttonExit
            // 
            this.buttonExit.Font = new System.Drawing.Font("Segoe UI", 11F);
            this.buttonExit.Location = new System.Drawing.Point(10, 275);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(100, 28);
            this.buttonExit.TabIndex = 6;
            this.buttonExit.Text = "Exit";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // buttonOpen
            // 
            this.buttonOpen.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.buttonOpen.Location = new System.Drawing.Point(10, 26);
            this.buttonOpen.Name = "buttonOpen";
            this.buttonOpen.Size = new System.Drawing.Size(100, 29);
            this.buttonOpen.TabIndex = 8;
            this.buttonOpen.Text = "Open";
            this.buttonOpen.UseVisualStyleBackColor = true;
            this.buttonOpen.Click += new System.EventHandler(this.buttonOpen_Click);
            // 
            // buttonSaveAs
            // 
            this.buttonSaveAs.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.buttonSaveAs.Location = new System.Drawing.Point(10, 61);
            this.buttonSaveAs.Name = "buttonSaveAs";
            this.buttonSaveAs.Size = new System.Drawing.Size(100, 29);
            this.buttonSaveAs.TabIndex = 9;
            this.buttonSaveAs.Text = "Save";
            this.buttonSaveAs.UseVisualStyleBackColor = true;
            this.buttonSaveAs.Click += new System.EventHandler(this.buttonSaveAs_Click);
            // 
            // buttonEdit
            // 
            this.buttonEdit.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.buttonEdit.Location = new System.Drawing.Point(327, 600);
            this.buttonEdit.Name = "buttonEdit";
            this.buttonEdit.Size = new System.Drawing.Size(100, 29);
            this.buttonEdit.TabIndex = 10;
            this.buttonEdit.Text = "Edit";
            this.buttonEdit.UseVisualStyleBackColor = true;
            this.buttonEdit.Visible = false;
            // 
            // buttonObAvtore
            // 
            this.buttonObAvtore.Location = new System.Drawing.Point(10, 195);
            this.buttonObAvtore.Name = "buttonObAvtore";
            this.buttonObAvtore.Size = new System.Drawing.Size(100, 29);
            this.buttonObAvtore.TabIndex = 11;
            this.buttonObAvtore.Text = "Author";
            this.buttonObAvtore.UseVisualStyleBackColor = true;
            this.buttonObAvtore.Click += new System.EventHandler(this.buttonObAvtore_Click);
            // 
            // buttonObProgram
            // 
            this.buttonObProgram.Location = new System.Drawing.Point(10, 135);
            this.buttonObProgram.Name = "buttonObProgram";
            this.buttonObProgram.Size = new System.Drawing.Size(100, 54);
            this.buttonObProgram.TabIndex = 12;
            this.buttonObProgram.Text = "About the program";
            this.buttonObProgram.UseVisualStyleBackColor = true;
            this.buttonObProgram.Click += new System.EventHandler(this.buttonObProgram_Click);
            // 
            // labelNameLst
            // 
            this.labelNameLst.AutoSize = true;
            this.labelNameLst.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.labelNameLst.Location = new System.Drawing.Point(107, 562);
            this.labelNameLst.Name = "labelNameLst";
            this.labelNameLst.Size = new System.Drawing.Size(91, 19);
            this.labelNameLst.TabIndex = 13;
            this.labelNameLst.Text = "Name Lst file:";
            this.labelNameLst.Visible = false;
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(189, 562);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(86, 20);
            this.textBoxName.TabIndex = 14;
            this.textBoxName.Visible = false;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // buttonCreateLst
            // 
            this.buttonCreateLst.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.buttonCreateLst.Location = new System.Drawing.Point(107, 572);
            this.buttonCreateLst.Name = "buttonCreateLst";
            this.buttonCreateLst.Size = new System.Drawing.Size(196, 52);
            this.buttonCreateLst.TabIndex = 15;
            this.buttonCreateLst.Text = "Create and Save lst!";
            this.buttonCreateLst.UseVisualStyleBackColor = true;
            this.buttonCreateLst.Visible = false;
            this.buttonCreateLst.Click += new System.EventHandler(this.buttonCreateLst_Click);
            // 
            // buttonHideWindow
            // 
            this.buttonHideWindow.Location = new System.Drawing.Point(10, 230);
            this.buttonHideWindow.Name = "buttonHideWindow";
            this.buttonHideWindow.Size = new System.Drawing.Size(100, 29);
            this.buttonHideWindow.TabIndex = 16;
            this.buttonHideWindow.Text = "Creaspis";
            this.buttonHideWindow.UseVisualStyleBackColor = true;
            this.buttonHideWindow.Click += new System.EventHandler(this.buttonHideWindow_Click);
            // 
            // MainWindowW
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(319, 322);
            this.Controls.Add(this.buttonHideWindow);
            this.Controls.Add(this.buttonCreateLst);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.labelNameLst);
            this.Controls.Add(this.buttonObProgram);
            this.Controls.Add(this.buttonObAvtore);
            this.Controls.Add(this.buttonEdit);
            this.Controls.Add(this.buttonSaveAs);
            this.Controls.Add(this.buttonOpen);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.laberFormatFiles);
            this.Controls.Add(this.labelFileList);
            this.Controls.Add(this.buttonCleatPole);
            this.Controls.Add(this.buttonClearList);
            this.Controls.Add(this.listBoxFiles);
            this.Controls.Add(this.comboBox1);
            this.Cursor = System.Windows.Forms.Cursors.Default;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainWindowW";
            this.Text = "Lst File++";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.ListBox listBoxFiles;
        private System.Windows.Forms.Button buttonClearList;
        private System.Windows.Forms.Button buttonCleatPole;
        private System.Windows.Forms.Label labelFileList;
        private System.Windows.Forms.Label laberFormatFiles;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Button buttonOpen;
        private System.Windows.Forms.Button buttonSaveAs;
        private System.Windows.Forms.Button buttonEdit;
        private System.Windows.Forms.Button buttonObAvtore;
        private System.Windows.Forms.Button buttonObProgram;
        private System.Windows.Forms.Label labelNameLst;
        private System.Windows.Forms.TextBox textBoxName;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button buttonCreateLst;
        private System.Windows.Forms.Button buttonHideWindow;
    }
}
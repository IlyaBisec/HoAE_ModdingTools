using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using static System.Windows.Forms.DataFormats;

namespace LstFile
{
    //==================Обьявление=============================
    public partial class MainWindowW : Form
    {
        
        SaveFileDialog save;
        

       
        public MainWindowW()
        {
            InitializeComponent();
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void buttonObAvtore_Click(object sender, EventArgs e)
        {
            ObAvtore avtor = new ObAvtore(this);
            avtor.Show();
        }
        private void buttonObProgram_Click(object sender, EventArgs e)
        {
            ObProgram program = new ObProgram(this);
            program.Show();
        }
        private void buttonHideWindow_Click(object sender, EventArgs e)
        {
            DopMenu dop = new DopMenu(this);
            dop.Show();
        }
        //====================Open=====================
        private void buttonOpen_Click(object sender, EventArgs e)
        {
            

            OpenFileDialog open = new OpenFileDialog();
            open.Multiselect = true;

            open.DefaultExt = ".tga";
            open.Filter = "differents files(*.tga; *.bmp; *.wrl)|*.tga; *.bmp; *.wrl|" + "All files (*.*)|*.*";

            if (open.ShowDialog() == DialogResult.OK)
            {
                StreamReader stream = new StreamReader(open.FileName);


                
                string filename = open.FileName;
               
               
                foreach (String fname in open.SafeFileNames)
                {
                  
                    listBoxFiles.Items.Add(fname); //filename == fname
                    listBoxFiles.Text = filename;
                   
                }
                stream.Close();

            }
            
        }
        //==================Save=============================
        private void buttonSaveAs_Click(object sender, EventArgs e)
        {
            save = new SaveFileDialog();

            save.DefaultExt = ".lst";
            save.Filter = "list file(*.lst)|*.lst|" + "All files (*.lst*)|*.lst*";
            saveFileDialog1.FileName = ".lst";
            int i;
            if (save.ShowDialog() == DialogResult.OK && listBoxFiles.Items.Count > 0)
            {
                StreamWriter sw = new StreamWriter(save.FileName);

               for(i = 0; i < listBoxFiles.Items.Count; i++)
                {
                    sw.WriteLine((string)listBoxFiles.Items[i]);
                }
                sw.Close();
             

            }
            save.Dispose();
         
        }
        //==================Clear=============================
        private void buttonClearList_Click(object sender, EventArgs e)
        {
            listBoxFiles.Items.Clear();
        }

        private void buttonCleatPole_Click(object sender, EventArgs e)
        {
            textBoxName.Clear();
        }
        //==================Create=============================
        private void buttonCreateLst_Click(object sender, EventArgs e)
        {
            save = new SaveFileDialog();
            save.DefaultExt = ".lst";
            save.Filter = "list file(*.lst)|*.lst|" + "All files (*.lst*)|*.lst*";
            if (save.ShowDialog() == DialogResult.OK)
            {
                StreamReader saver = new StreamReader(save.FileName);
                foreach (var item in listBoxFiles.Items)
                    //saver.WriteLine(item.ToString());
                    saver.Close();



            }

        }

       
    }
}


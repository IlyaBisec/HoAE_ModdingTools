using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Linq;



namespace LstFile
{

    public partial class DopMenu : Form
    {

        public DopMenu()
        {
            InitializeComponent();
        }

        public DopMenu(MainWindowW main)
        {
            InitializeComponent();
        }

        private void buttonClearF_Click(object sender, EventArgs e)
        {
            textBoxFiles.Clear();
        }

        //==================Open=============================
        private void buttonOpenF_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Multiselect = true;
            open.DefaultExt = "*.xml";
            open.Filter = "base HoAER files(*.xml; *.txt; *.lst)|*.xml; *.txt; *.lst|" + "(*.lst; *.md; *.rsr)|*.lst; *.md; *.rsr|" + "All files (*.*)|*.*";

            if (open.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                foreach (String files in open.FileNames)
                    textBoxFiles.Text = System.IO.File.ReadAllText(open.FileName, Encoding.Default);
              
            }
            // foreach (string file in open.FileNames)
        }


        //==================Save=============================
        private void buttonSaveF_Click(object sender, EventArgs e)
        {
            SaveFileDialog save = new SaveFileDialog();

            save.DefaultExt = ".txt";
            save.Filter = "Pixacker  files(*.lst; *.txt)|*.lst; *.txt|" + "(*.xml; *.rsr; *.nds; *.md; *.log)|*.xml; *.rsr; *.nds; *.md; *.log|" + "All files (*.lst*)|*.lst*";
            saveFileDialog1.FileName = ".txt";
            if (save.ShowDialog() == DialogResult.OK)
            {
                //  File.WriteAllText(save.FileName, textBoxFiles.Text, Encoding.Default);
                StreamWriter writer = File.CreateText(save.FileName);
                string line;
                int i;

                for (i = 0; i < textBoxFiles.Lines.Length; i++)
                {
                    line = textBoxFiles.Lines[i].ToString();
                    writer.WriteLine(line);
                }
                writer.Close();
            }
        }
        private void richTextBoxFiles_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBoxFiles_TextChanged(object sender, EventArgs e)
        {

        }
        //=============================Clear==========================================
        private void buttonCkearNubmerOfAnim_Click(object sender, EventArgs e)
        {
            textBoxNumberOfFramesAnim.Clear();
        }
        private void buttonClearNubOfCamDo_Click(object sender, EventArgs e)
        {
            textBoxNumOfCamDo.Clear();
        }
        private void buttonClearNumbFrameAnimDo_Click(object sender, EventArgs e)
        {
            textBoxNumFrAnDo.Clear();
        }
        private void buttonClearNumberOfCam_Click(object sender, EventArgs e)
        {
            textBoxNumberOfCameras.Clear();
        }

        private void buttonClearAnimFrameName_Click(object sender, EventArgs e)
        {
            textBoxAnimFrameName.Clear();
        }


        //CREASPIS
        //===================================Create=============================================
        private void buttonCreateCreaspis_Click(object sender, EventArgs e)
        {
            SaveFileDialog create = new SaveFileDialog();


            create.DefaultExt = ".lst";
            create.Filter = "HoAER files(*.lst)|*.lst|" + "All files (*.*)|*.*";

            //numberFrameAnim
            int kS = Convert.ToInt32(textBoxNumberOfFramesAnim.Text); // Start number of frame anima
            int kF = Convert.ToInt32(textBoxNumFrAnDo.Text);// Finish number of frame anima

            //numberCameras
            int iS = Convert.ToInt32(textBoxNumberOfCameras.Text); // Start Number of cameras
            int iF = Convert.ToInt32(textBoxNumOfCamDo.Text); // Finish Number of cameras

            string nameFrame = textBoxAnimFrameName.Text; //frame name 

            //Range
            IEnumerable<int> numberFrameAnim = Enumerable.Range(kS, kF);
            IEnumerable<int> numberCameras = Enumerable.Range(iS, iF);


            if (create.ShowDialog() == DialogResult.OK)
            {
                StreamWriter writer = File.CreateText(create.FileName);

                foreach (int k in numberFrameAnim)
                {
                    foreach (int i in numberCameras)
                    {
                        writer.WriteLine(nameFrame + i.ToString() + '0' + '0' + k.ToString().PadLeft(2, '0') + ".tga");
                        // Python f.writelines('A' + str(k) + '0' + '0' + str(i).zfill(2) + '.tga \n')
                    }
                }
                writer.Close();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void listBoxFiles_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace LstFile
{
    public partial class ObProgram : Form
    {
        public ObProgram()
        {
            InitializeComponent();
        }
        public ObProgram(MainWindowW main)
        {
            InitializeComponent();

        }
        private void labelText_Click(object sender, EventArgs e)
        {
            labelText.Height = 260;
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void ObProgram_Load(object sender, EventArgs e)
        {

        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace LstFile
{
    public partial class ObAvtore : Form
    {
        public ObAvtore()
        {
            InitializeComponent();
        }
        public ObAvtore(MainWindowW main)
        {
            InitializeComponent();
            
        }
        private void labelAuthor_Click(object sender, EventArgs e)
        {

        }

        private void buttonOKOvAvtore_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}

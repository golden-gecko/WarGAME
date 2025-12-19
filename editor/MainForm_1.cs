using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Xml;
using System.Windows.Forms;

namespace WarGAME.Editor
{
    public partial class mainForm : Form
    {
        private string fileName;

        public mainForm()
        {
            InitializeComponent();
        }

        private void treeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            FileInfo fileInfo = new FileInfo(e.Node.Text);

            if (fileInfo.Attributes == FileAttributes.Directory)
            {
                string[] fileList = Directory.GetFileSystemEntries(e.Node.Text);

                e.Node.Nodes.Clear();

                foreach (string fileName in fileList)
                {
                    e.Node.Nodes.Add(fileName);
                }

            }
            else if ((fileInfo.Extension == ".xml") || (fileInfo.Extension == ".material"))
            {
                log.ForeColor = Color.Green;
                log.AppendText("INFO\tFile loaded\t" + e.Node.Text + ".\n");
                log.ScrollToCaret();

                script.LoadFile(e.Node.Text, RichTextBoxStreamType.PlainText);

                fileName = e.Node.Text;
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            log.ForeColor = Color.Green;
            log.AppendText("INFO\tFile saved\t" + fileName + ".\n");           

            script.SaveFile(fileName, RichTextBoxStreamType.PlainText);
        }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            log.ForeColor = Color.Green;
            log.AppendText("INFO\tFile deleted\t" + treeView.SelectedNode.Text + ".\n");

            File.Delete(treeView.SelectedNode.Text);
        }
    }
}
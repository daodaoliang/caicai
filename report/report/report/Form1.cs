using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
namespace report
{
    public partial class Form1 : Form
    {
        enum QueryType
        {
            PaiMing,
            TuiCai,
            YingYe
        }
        public Form1()
        {
            InitializeComponent();
        }

        private QueryType m_queryType;

        private void Form1_Load(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Maximized;

        }

        private string[] reportNames = { "report.Report1.rdlc" ,
                                       "report.TuiCai.rdlc",
                                       "report.Yingye.rdlc"};

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            switch(treeView1.SelectedNode.Text)
            {
                case "菜例销售排名":
                    showPaiMing();
                    break;
                case "退菜查询":
                    showTuiCai();
                    break;
                case "营业报表":
                    showYingYe();
                    break;
                default:
                    break;
            }
        }

        //显示排名信息
        private void showPaiMing()
        {
            m_queryType = QueryType.PaiMing;
        }

        //显示退菜信息
        private void showTuiCai()
        {
            m_queryType = QueryType.TuiCai;
        }

        //显示营业报表
        private void showYingYe()
        {
            m_queryType = QueryType.YingYe;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            reportViewer1.Reset();
            reportViewer1.LocalReport.ReportEmbeddedResource = reportNames[(int)m_queryType];
            reportViewer1.RefreshReport();
        }
    }
}

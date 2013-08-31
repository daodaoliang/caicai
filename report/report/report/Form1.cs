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
        public enum QueryType
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
            initUi();
        }

        private string[] m_reportNames = { "report.Report1.rdlc" ,
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
        private void showQueryTime()
        {
            flowLayoutPanel1.Controls.Clear();
            flowLayoutPanel1.Controls.Add(m_from);
            flowLayoutPanel1.Controls.Add(m_fromPicker);
            flowLayoutPanel1.Controls.Add(m_to);
            flowLayoutPanel1.Controls.Add(m_toPicker);            
        }

        //显示排名信息
        private void showPaiMing()
        {
            //显示查询条件
            showQueryTime();      
            //个性化查询条件控件
            m_label1.Text = "类别";
            flowLayoutPanel1.Controls.Add(m_label1);
            flowLayoutPanel1.Controls.Add(m_query1);
            flowLayoutPanel1.Controls.Add(m_queryButton);
            //设置包表类型
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


        private DataProvider m_dataProvider = new DataProvider();
        private TextBox m_query1 = new TextBox();
        private TextBox m_query2 = new TextBox();
        private TextBox m_query3 = new TextBox();
        private TextBox m_query4 = new TextBox();
        private TextBox m_query5 = new TextBox();
        private Label m_label1 = new Label();
        private Label m_label2 = new Label();
        private Label m_label3 = new Label();
        private Label m_label4 = new Label();
        private Label m_label5 = new Label();
        private Label m_from = new Label();
        private Label m_to = new Label();
        private DateTimePicker m_fromPicker = new DateTimePicker();
        private DateTimePicker m_toPicker = new DateTimePicker();
        private Button m_queryButton = new Button();
        private void initUi()
        {
            m_label2.Size = new Size(55, 23);
            m_label1.Size = new Size(55, 23);
            m_label3.Size = new Size(55, 23);
            m_label4.Size = new Size(55, 23);
            m_label5.Size = new Size(55, 23);
            m_to.Size = new Size(55, 23);
            m_from.Size = new Size(55, 23);
            m_toPicker.Size = new System.Drawing.Size(105, 30);
            m_fromPicker.Size = new System.Drawing.Size(105, 30);
            m_query1.Size = new System.Drawing.Size(105, 30);
            m_query2.Size = new System.Drawing.Size(105, 30);
            m_query3.Size = new System.Drawing.Size(105, 30);
            m_query4.Size = new System.Drawing.Size(105, 30);
            m_query5.Size = new System.Drawing.Size(105, 30);
            m_to.Text = "到";
            m_from.Text = "从";
            m_label1.TextAlign = ContentAlignment.MiddleRight;
            m_label2.TextAlign = ContentAlignment.MiddleRight;
            m_label3.TextAlign = ContentAlignment.MiddleRight;
            m_label4.TextAlign = ContentAlignment.MiddleRight;
            m_label5.TextAlign = ContentAlignment.MiddleRight;
            m_to.TextAlign = ContentAlignment.MiddleRight;
            m_from.TextAlign = ContentAlignment.MiddleRight;
            m_queryButton.Text = "查询";
            m_queryButton.Click += new EventHandler(m_queryButton_Click);    
        }

        void m_queryButton_Click(object sender, EventArgs e)
        {
            string[] queryList = new string[5];
            queryList[0] = m_query1.Text;
            queryList[1] = m_query2.Text;
            queryList[2] = m_query3.Text;
            queryList[3] = m_query4.Text;
            queryList[4] = m_query5.Text;
            string beginTime = m_fromPicker.Text;
            string endTime = m_toPicker.Text;
            DataTable dt = m_dataProvider.getData(m_queryType, beginTime, endTime, queryList);
            reportViewer1.Reset();
            reportViewer1.LocalReport.ReportEmbeddedResource = m_reportNames[(int)m_queryType];
            reportViewer1.LocalReport.DataSources.Add(new Microsoft.Reporting.WinForms.ReportDataSource(
                "DataSet2", dt));
            reportViewer1.RefreshReport();
        }
    }
}

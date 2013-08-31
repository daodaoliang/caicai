using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using DataBase;
using System.Configuration;
namespace report
{
    class DataProvider
    {
        private string m_connectString = ConfigurationManager.ConnectionStrings["report.Properties.Settings.restaurantdbConnectionString"].ToString();
        public DataTable getData(Form1.QueryType queryType, string beginTime, string endTime, string[] queryString)
        {
            switch (queryType)
            {
                case Form1.QueryType.PaiMing:
                    return PaiMingData(beginTime, endTime, queryString);
                case Form1.QueryType.TuiCai:
                    return TuiCaiData(beginTime, endTime, queryString);
                case Form1.QueryType.YingYe:
                    return YingYeData(beginTime, endTime, queryString);
                default:
                    break;
            }
            return new DataTable();
        }

        private DataTable PaiMingData(string beginTime, string endTime, string[] queryString)
        {
            //这里写好数据
            string sql = "SELECT dishestype, dishesid, dishesname, " +
                            "SUM(if(handletype=0,dishescount,-1*dishescount)) as totalcount, " +
                            "SUM(if(handletype=0,dishescount,-1*dishescount) * dishesprice) as totalmoney " +
                            "from orderdetailview ";
            if (beginTime != null && endTime != null)
            {
                sql += "where (handletime between '" + beginTime + "' and '" + endTime + "') ";
            }
            if (queryString[0] != "")
            {
                sql += " and dishestype = '" + queryString[0] + "' ";
            }
            sql += " GROUP BY dishesid, dishestype";

            DataSet ds = SqlHelper_MySql.ExecuteDataset(m_connectString, CommandType.Text, sql);
            if (ds.Tables.Count > 0)
            {
                DataTable dt = ds.Tables[0];
                //实在懒的去整sql的百分比语句了，先取出来再搞一下
                dt.Columns.Add("preCount");
                dt.Columns.Add("preMoney");
                double totalCount = 0;
                double totalMoney = 0;
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    totalCount += Convert.ToDouble(dt.Rows[i].ItemArray[3]);
                    totalMoney += Convert.ToDouble(dt.Rows[i].ItemArray[4]);
                }
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    dt.Rows[i].SetField<double>("preCount", Convert.ToDouble(dt.Rows[i].ItemArray[3]) / totalCount);
                    dt.Rows[i].SetField<double>("preMoney", Convert.ToDouble(dt.Rows[i].ItemArray[4]) / totalMoney);
                }

                return ds.Tables[0];
            }
            else
            {
                return new DataTable();
            }
        }

        private DataTable TuiCaiData(string beginTime, string endTime, string[] queryString)
        {
            return new DataTable();
        }

        private DataTable YingYeData(string beginTime, string endTime, string[] queryString)
        {
            return new DataTable();
        }
        private DataTable KaiKaData(string beginTime,string endTime,string[] quertString)
        {
            string sql = "select memcardid,member.`name`,member.membertypeid,userinfo.nickname,handletime from memcarddetail " +
                 "left join userinfo on memcarddetail.operatorid = userinfo.userid left join member on memcarddetail.memcardid = member.cardid " +
                 "where memcarddetail.handletype = 6";
            if (beginTime != null && endTime != null)
            {
                sql += "where (handletime between '" + beginTime + "' and '" + endTime + "') ";
            }
            DataSet ds = SqlHelper_MySql.ExecuteDataset(m_connectString, CommandType.Text, sql);
            if (ds.Tables.Count > 0)
            {
                DataTable dt = ds.Tables[0];
            }
            return new DataTable();
        }

    }
}

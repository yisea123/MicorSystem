using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControlPoxy
{
    public class Util_Proxy
    {

        public string CopyRight = "CopyRight: mingfei.tang";
        public string SoftVersion = "Version: V1.10";

        public string ByteToString(byte[] buff, int len)
        {
            string str = "";

            for (int i = 0; i < len; i++)
            {
                str += buff[i].ToString("X2");
            }
            return str;
        }

        public string ByteToAscii(byte[] buff)
        {
            string str = "";

            str = System.Text.Encoding.ASCII.GetString(buff);

            return str;
        }

        public byte[] AscllToByte(string s )
        {
            return System.Text.Encoding.ASCII.GetBytes (s);
        }

        public byte[] GetByteArray(string str )
        {
            List<byte> bytList = new List<byte>();

            if (str.Length == 0)
                return null;

            int length = str.Length / 2;
            string[] ssArray = new string[length];
            for (int i = 0; i < length; i++)
            {
                ssArray[i] = str.Substring(i * 2, 2);
            }

            foreach (var s in ssArray)
            {
                //将十六进制的字符串转换成数值
                bytList.Add(Convert.ToByte(s, 16));
            }

            //返回字节数组
            return bytList.ToArray();
        }

        public void GetByteUInt32( byte[]buff, UInt32 data )
        {
            buff[0] = (byte)(data >> 24);
            buff[1] = (byte)(data >> 16);
            buff[2] = (byte)(data >> 8);
            buff[3] = (byte)(data);
        }

        public void DataTimeCommandConvert(dateByte date )
        {
            string dateTextstring = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss fff");
            string[] res = String_Parser(dateTextstring);
          
            //year
            date.year = UInt16.Parse(res[0]);
            //Month
            date.month = (byte)(UInt16.Parse(res[1]));
            //day
            date.dateOfMonth = (byte)(UInt16.Parse(res[2]));

            //hour
            date.hour = (byte)(UInt16.Parse(res[3]));
            //minute
            date.minute = (byte)(UInt16.Parse(res[4]));
            //second
            date.second = (byte)(UInt16.Parse(res[5]));
            //millsecond
            date.millSecond = (byte)(UInt16.Parse(res[6]));
        }

        private string[] String_Parser(string s)
        {
            string[] s_res = new string[] { };

            if (s.Length > 0)
            {
                s_res = s.Split('-', ' ', ':');
            }

            return s_res;
        }
    }

    public class ModbusStruc
    {
        public byte address;
        public byte cmd;
        public byte length;
        public byte[] data = new byte[32];
    }

    public class dateByte
    {
        public UInt16 year;
        public byte month;
        public byte dateOfMonth;
        public byte hour;
        public byte minute;
        public byte second;

        public UInt16 millSecond;
    }
}

/* End of this file */

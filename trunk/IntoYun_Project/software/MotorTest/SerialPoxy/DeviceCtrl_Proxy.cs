using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControlPoxy
{
    public class DeviceCtrl_Proxy
    {
        ModbusStruc st_ModbusStruc = new ModbusStruc();
        CRC_Proxy st_CRC_Proxy = new CRC_Proxy();
        /// <summary>
        /// 解析灯ID
        /// </summary>
        /// <param name="packet"></param>
        /// <param name="address"></param>
        /// <returns></returns>
        public bool LightCtrl_AddressParser( byte [] packet, int len, byte[] address)
        {
            if (len > 0)
            {
                if (packet[0] == 0x1A)
                {
                    Buffer.BlockCopy(packet, 0, address, 0, 5);
                    return true;
                }
            }

            return false;
        }


        /// <summary>
        /// 解析Presence ID和数据 
        /// </summary>
        /// <param name="packet"></param>
        /// <param name="id"></param>
        /// <param name="res"></param>
        /// <returns></returns>
        public bool Presence_IDParser(byte[] packet, int len, out string id, out string res)
        {
            string str = "";
            id = "";
            res = "";

            if ( len > 0 )
             {
                if (packet[0] == 'I' && packet[1] == 'D')
                {
                    str = System.Text.Encoding.ASCII.GetString(packet);
                    string[] strarr = str.Split('=', '\r', ' ');

                    //解析ID
                    id = strarr[1];

                    //解析数据
                    if (strarr[2] == "BT")
                    {
                        res = strarr[3];
                    }
                    return true;
                }
            }

            return false;
        }

        public bool InclinometerSenor_Parser(byte[] packet, int lenght, out short x, out short y)
        {
            short crc;
            short calCrc;
            int len = 0;

            x = 0;
            y = 0;

            if (lenght == 0)
                return false;

            st_ModbusStruc.address = packet[0];
            st_ModbusStruc.cmd = packet[1];
            st_ModbusStruc.length = packet[2];

            for (int i = 0; i < st_ModbusStruc.length; i++)
            {
                len++;
                st_ModbusStruc.data[i] = packet[3 + i];
            }

            calCrc = (short)st_CRC_Proxy.CRC16(packet, (int)(len+3));
            crc =(short) (packet[3 + st_ModbusStruc.length]| packet[3 + st_ModbusStruc.length + 1]<<8);

            if (calCrc == crc)
            {
                x = (short)(st_ModbusStruc.data[0] << 8 | st_ModbusStruc.data[1]);
                y = (short)(st_ModbusStruc.data[2] << 8 | st_ModbusStruc.data[3]);
                return true;
            }
            else
                return false;
        }
    }
}

/* End of this file */
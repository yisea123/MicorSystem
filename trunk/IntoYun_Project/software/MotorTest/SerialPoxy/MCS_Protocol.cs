using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControlPoxy
{
    public class MCS_Protocol
    {
        CRC_Proxy str_CRC_Proxy = new CRC_Proxy();

        public bool b_result = false;
        public UInt16 Frum;
        public UInt16 CMD;
        public UInt16 DataLen;
        public byte srcAddr;
        public byte tarAddr;
        public byte[] DataBuf = new byte[1024*512];

        private const byte FRAME_HEADER = 0x5B;
        private const byte FRAME_END = 0x5D;
        private const byte PROTOCOL_HEADER_OFFSET = 0;
        private const byte PROTOCOL_SOURADDR_OFFSET = 1;
        private const byte PROTOCOL_TARADDR_OFFSET = 2;
        private const byte PROTOCOL_FUMN_OFFSET = 3;
        private const byte PROTOCOL_CMD_OFFSET = 5;
        private const byte PROTOCOL_DATA_LENGTH_OFFSET = 7;
        private const byte PROTOCOL_DATA_OFFSET = 8;

        public int MCS_Building(byte srcAddr, byte tarAddr, int frum, int CMD, byte[] data, byte datalen, byte[] buff)
        {
            int i, j;
            int crc16;

            i = 0;
            buff[i++] = 0x5B;                //帧头

            buff[i++] = srcAddr;             //源地址
            buff[i++] = tarAddr;             //目的地址

            buff[i++] = (byte)(frum >> 8);   //帧指针
            buff[i++] = (byte)(frum & 0xff);

            buff[i++] = (byte)(CMD >> 8);    //命令码
            buff[i++] = (byte)(CMD & 0xff);

            buff[i++] = datalen;              //数据长度

            if (datalen > 0)
            {
                for (j = 0; j < datalen; j++)
                {
                    buff[i++] = data[j];        //数据
                }
            }

            crc16 = str_CRC_Proxy.CRC16(buff, i);

            buff[i++] = (byte)(crc16 & 0xff);     //CRC
            buff[i++] = (byte)(crc16 >> 8);

            buff[i++] = 0x5D;                     //帧尾

            return i;
        }

        public Boolean MCS_ProtocolPaeser(byte[] Recv)
        {
            UInt16 CRC16, CALCRC16;
            UInt16 PACKELEN;

            b_result = false;
            PACKELEN = 0;
            //判断数据包头
            if (Recv[PROTOCOL_HEADER_OFFSET] != FRAME_HEADER)
            {
                return b_result;
            }
            PACKELEN += 1;

            //源地址
            srcAddr = Recv[PROTOCOL_SOURADDR_OFFSET];
            PACKELEN += 1;

            //目的地址
            tarAddr = Recv[PROTOCOL_TARADDR_OFFSET];
            PACKELEN += 1;

            //取Frum
            Frum = (UInt16)((UInt16)((Recv[PROTOCOL_FUMN_OFFSET] << 8) & 0XFF00) + (UInt16)((Recv[PROTOCOL_FUMN_OFFSET + 1]) & 0X00FF));
            PACKELEN += 2;

            //取cmd
            CMD = (UInt16)((UInt16)((Recv[PROTOCOL_CMD_OFFSET] << 8) & 0XFF00) + (UInt16)((Recv[PROTOCOL_CMD_OFFSET + 1]) & 0X00FF));
            PACKELEN += 2;

            //取data length
            DataLen = Recv[PROTOCOL_DATA_LENGTH_OFFSET];
            PACKELEN += 1;

            //copy data
            if (DataLen > 0)
            {
                for (int j = 0; j < DataLen; j++)
                {
                    DataBuf[j] = Recv[PROTOCOL_DATA_OFFSET + j];
                }
            }
            PACKELEN += DataLen;

            //计算CRC
            CRC16 = str_CRC_Proxy.CRC16(Recv, PACKELEN);

            //取CRC
            CALCRC16 = (UInt16)((UInt16)((Recv[PACKELEN + 1] << 8) & 0XFF00) + (UInt16)((Recv[PACKELEN]) & 0X00FF));

            if (CRC16 == CALCRC16)
            {
                b_result = true;
                return b_result;
            }

            return b_result;
        }
    }
}

/* End of this file */


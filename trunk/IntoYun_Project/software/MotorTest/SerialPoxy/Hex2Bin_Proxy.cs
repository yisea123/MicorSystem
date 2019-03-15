using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ControlPoxy
{
    public class Hex2Bin
    {
        byte[] FileBin = new byte[1024 * 512];
        byte[] fileHeader = new byte[128];
        int binFileLength = 0;
        
        string hexFileName = "";
        bool b_startEnable = false;
        StreamReader readHexFile;
        private Thread dataHandler;

        CRC_Proxy st_crc = new CRC_Proxy();
        Util_Proxy st_Util = new Util_Proxy();
        ConfigIni GetProjectInfor2Ini = new ConfigIni();
        Hashtable ht = new Hashtable();

        public HeaderStruct st_header = new HeaderStruct();
        public bool bl_Result = false;
        public string fileName_zfp = "";
        public UInt32 filSize = 0;

        public void FileHex_Start( string fileName )
        {
            if (fileName == "")
                return;

            hexFileName = fileName;   //Hex file path
            binFileLength = 0;
            filSize = 0;
            bl_Result = false;

            string file = Path.GetFileName(hexFileName);
            fileName_zfp = hexFileName.Substring(0, hexFileName.IndexOf(file)) + fileName_zfp + ".ZFP";

            readHexFile = new StreamReader(fileName);
            dataHandler = new Thread(FileHex_ConvetThreading);
            dataHandler.Start();
            b_startEnable = true;
        }

        public void FileHex_Stop()
        {
            if( b_startEnable )
            {
                dataHandler.Abort();
                b_startEnable = false;
                ht.Clear();
            }
        }

        /// <summary>
        /// *** Hex 文件格式 ***
        /// 
        /// 第一个字节: 表示本行数据的长度
        /// 第二、三字节：表示本行数据的起始地址
        /// 第四字节： 表示数据类型
        /// 数据类型有：0x00、0x01、0x02、0x03、0x04、0x05。
        ///'00' Data Rrecord：用来记录数据，HEX文件的大部分记录都是数据记录
        ///'01' End of File Record: 用来标识文件结束，放在文件的最后，标识HEX文件的结尾
        ///'02' Extended Segment Address Record: 用来标识扩展段地址的记录
        ///'03' Start Segment Address Record:开始段地址记录
        ///'04' Extended Linear Address Record: 用来标识扩展线性地址的记录
        ///'05' Start Linear Address Record:开始线性地址记录
        /// </summary>
        /// <param name="data"></param>
        private void FileHexConvert( byte[] data)
        {
            if ( data.Length > 0 )
            {
                byte dataLen = data[0];
                UInt16 address = (UInt16)(data[1] << 8 | data[2]);
                byte type = data[3];
                switch (type)
                {
                    case 0:
                        for (int i = 0; i < dataLen; i++ )
                        {
                            FileBin[binFileLength++] = data[4+i];   //parser bin
                        }
                        break;
                    case 0x01:
       
                        FileStream fBin = new FileStream(fileName_zfp, FileMode.Create);
                        BinaryWriter BinWrite = new BinaryWriter(fBin);

                        filSize = (UInt32)(binFileLength + 128);
                        st_Util.GetByteUInt32(st_header.InterFileSize, filSize);
                        FileHeader_Maker(fileHeader, st_header);
                        BinWrite.Write(fileHeader, 0, 128);
                        BinWrite.Write(FileBin, 0, binFileLength); 
                        BinWrite.Flush();
                        BinWrite.Close();
                        bl_Result = true;
                        fBin.Close();
                        FileHex_Stop();
                        break;
                    case 0x02:
                        break;
                    case 0x03:
                        break;
                    case 0x04:
                        break;
                    case 0x05:
                        break;
                }
            }
        }

        private void FileHex_ConvetThreading()
        {
            Hex_ClassFormat st_hexFormat = new Hex_ClassFormat();
            while (true)
            {
                string  readLinedata = readHexFile.ReadLine();
                if (readLinedata == null)
                {
                    break;
                }
                else
                {
                    if ( readLinedata.Substring(0, 1) == ":" )
                    {
                        string strbin = readLinedata.Substring(1, readLinedata.Length-1);
                        byte[] byteArray = st_Util.GetByteArray(strbin);
                        FileHexConvert(byteArray);
                    }
                }
            }
        }

        public int FileHeader_Maker(byte [] buff , HeaderStruct fileHeader )
        {
            int length = 0;

            //FwVender
            for (int i = 0; i < fileHeader.FwVender.Length; i++)
            {
                buff[length++] = fileHeader.FwVender[i];
            }

            //platform
            for (int i = 0; i < fileHeader.Platform.Length; i++)
            {
                buff[length++] = fileHeader.Platform[i];
            }

            //Application firmware version 
            for (int i = 0; i < fileHeader.AppfwVer.Length; i++ )
            {
                buff[length++] = fileHeader.AppfwVer[i];
            }

            //Bootloader firmware version 
            for (int i = 0; i < fileHeader.BootLaoderfwVer.Length; i++)
            {
                buff[length++] = fileHeader.BootLaoderfwVer[i];
            }

            //mcs  version 
            for (int i = 0; i < fileHeader.MCSVer.Length; i++)
            {
                buff[length++] = fileHeader.MCSVer[i];
            }

            //Inter flash Filesize
            for (int i = 0; i < fileHeader.InterFileSize.Length; i++)
            {
                buff[length++] = fileHeader.InterFileSize[i];
            }

            //Inter Flash Start
            for (int i = 0; i < fileHeader.InterFlashStart.Length; i++)
            {
                buff[length++] = fileHeader.InterFlashStart[i];
            }

            //Inter Flash End
            for (int i = 0; i < fileHeader.InterFlashEnd.Length; i++)
            {
                buff[length++] = fileHeader.InterFlashEnd[i];
            }

            //Ext Flash filesize
            for (int i = 0; i < fileHeader.ExtentFileSize.Length; i++)
            {
                buff[length++] = fileHeader.ExtentFileSize[i];
            }

            //Ext Flash Start
            for (int i = 0; i < fileHeader.ExtentFlashStart.Length; i++)
            {
                buff[length++] = fileHeader.ExtentFlashStart[i];
            }

            //Ext Flash End
            for (int i = 0; i < fileHeader.ExtentFlashEnd.Length; i++)
            {
                buff[length++] = fileHeader.ExtentFlashEnd[i];
            }

            //Device type
            buff[length++] = fileHeader.DevType;

            //Reserve
            for (int i = 0; i < fileHeader.Reserve.Length; i++)
            {
                buff[length++] = fileHeader.Reserve[i];
            }

            //CRC16
            UInt16 crc = st_crc.CRC16(buff, length);
            fileHeader.CRC16[0] = (byte)(crc >> 8);
            fileHeader.CRC16[1] = (byte)(crc);
            for (int i = 0; i < fileHeader.CRC16.Length; i++)
            {
                buff[length++] = fileHeader.CRC16[i];
            }

            return length;
        }

        private void iniFileCovertToHeader(HeaderStruct fileHeader)
        {
            string hts;

             hts = ht["FwVender"].ToString();
            for (int i = 0; i < hts.Length; i++)
            {
                var temp = Encoding.Default.GetBytes(hts);
                fileHeader.FwVender[i] = temp[i];
            }

            hts = ht["Platform"].ToString();
            for (int i = 0; i < hts.Length; i++)
            {
                var temp = Encoding.Default.GetBytes(hts);
                fileHeader.Platform[i] = temp[i];
            }

            hts = ht["DevType"].ToString();
            fileHeader.DevType = (byte)Int16.Parse(hts.Substring(2, 2), NumberStyles.HexNumber);

            hts = ht["MCS_Ver"].ToString();
            for (int i = 0; i < hts.Length; i++)
            {
                var temp = Encoding.Default.GetBytes(hts);
                fileHeader.MCSVer[i] = temp[i];
            }

            hts = ht["BlVer"].ToString();
            for (int i = 0; i < hts.Length; i++)
            {
                var temp = Encoding.Default.GetBytes(hts);
                fileHeader.BootLaoderfwVer[i] = temp[i];
            }

            hts = ht["AppfwVer"].ToString();
            for (int i = 0; i < hts.Length; i++)
            {
                var temp = Encoding.Default.GetBytes(hts);
                fileHeader.AppfwVer[i] = temp[i];
            }

            hts = ht["Start"].ToString();
            for (int i=0; i < 4; i++ )
            {
                fileHeader.InterFlashStart[i] =(byte)Int16.Parse(hts.Substring(2 * (i + 1), 2), NumberStyles.HexNumber);
            }

            hts = ht["End"].ToString();
            for (int i = 0; i < 4; i++)
            {
                fileHeader.InterFlashEnd[i] = (byte)Int16.Parse(hts.Substring(2 * (i + 1), 2), NumberStyles.HexNumber);
            }
        }

        public void FileHeader_ReadIni( string fileName )
        {
            ht.Clear();
            //Project name
            string Project_val = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "Target", "Project");
            ht.Add("Project", Project_val);
            fileName_zfp = Project_val;

            //Platform
            string Platform_val = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "Target", "Platform");
            ht.Add("Platform", Platform_val);

            //company information
            string FwVender = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "Target", "FwVender");
            ht.Add("FwVender", FwVender);

            //device type
            string DevType = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "Target", "DevType");
            ht.Add("DevType", DevType);

            //MCS version
            string MCS_Ver = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "Target", "MCS_Ver");
            ht.Add("MCS_Ver", MCS_Ver);

            //Bootleader Firmware version
            string BlVer = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "Target", "BlVer");
            ht.Add("BlVer", BlVer);

            //Application Firmware version
            string AppfwVer = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "Target", "AppfwVer");
            ht.Add("AppfwVer", AppfwVer);

            /*
             * ---------------------  flash information ---------------------------------------------------
             */

            //Internal Flash memory end address
            string startAddress = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "INFO", "Start");
            ht.Add("Start", startAddress);

            //Internal Flash memory end address
            string endAddress = GetProjectInfor2Ini.GetProjectInfor2Ini((string)fileName, "INFO", "End");
            ht.Add("End", endAddress);

            //add header structure
            iniFileCovertToHeader(st_header);
        }
    }

    public class Hex_ClassFormat
    {
        public byte dataLen;
        public byte type;
        public byte address;
        public byte[] data = new Byte[32];
    }

    public class HeaderStruct
    {
        public Byte[] FwVender = new Byte[32];
        public Byte[] Platform = new Byte[16];
                                
        public Byte[] AppfwVer = new Byte[8];
        public Byte[] BootLaoderfwVer = new Byte[8];
        public Byte[] MCSVer = new Byte[8];

        public Byte[] InterFileSize = new Byte[4];
        public Byte[] InterFlashStart = new Byte[4];
        public Byte[] InterFlashEnd = new Byte[4];

        public Byte[] ExtentFileSize = new Byte[4];
        public Byte[] ExtentFlashStart = new Byte[4];
        public Byte[] ExtentFlashEnd = new Byte[4];

        public Byte DevType;

        public Byte[] Reserve = new Byte[29];
        public Byte[] CRC16 = new Byte[2];
    }
}


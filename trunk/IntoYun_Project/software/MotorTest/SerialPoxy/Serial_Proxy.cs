using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControlPoxy
{
    public class Serial_Proxy
    {
        public int DataLength;
        public byte[] RtBuff = new byte[1024 * 10];
        public bool b_SerialPortStaus = false;
        public bool b_SerialReceiveReady = false;
        private System.IO.Ports.SerialPort serialPortMode = new System.IO.Ports.SerialPort();

        private string comport;
        private int baud;
        private Parity parity;
        private int timeOut;

        public int TimeOut
        {
            get { return timeOut; }

            set{  timeOut = value; }
        }

        public string Comport
        {
            get{ return comport; }

            set{ comport = value; }
        }

        public int Baud
        {
            get{ return baud; }

            set{ baud = value; }
        }

        public Parity Parity
        {
            get{ return parity; }

            set{ parity = value; }
        }

        public bool SerialPort_Start()
        {
            return serial_Inial();
        }

        public void SerialPort_Stop()
        {
            if (serialPortMode.IsOpen)
            {
                serialPortMode.Close();
                b_SerialPortStaus = false;
                this.serialPortMode.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPortMode_DataReceived);
            }
        }
        public void SerialSend(byte[] data, int len)
        {
            if (b_SerialPortStaus)
            {
                serialPortMode.Write(data, 0, len);
            }
        }

        public int SerialPort_ReaDBuff(byte[] buff)
        {
            int length = 0;

            if (DataLength > 0)
            {
                if (DataLength > buff.Length)
                {
                    length = buff.Length;
                }
                else
                {
                    length = DataLength;
                }
                RtBuff.CopyTo(buff, length);
                DataLength = 0;
            }

            return length;
        }

        private bool serial_Inial()
        {
            serialPortMode.BaudRate = Baud;
            serialPortMode.PortName = Comport;
            serialPortMode.DataBits = 8;
            serialPortMode.Parity = parity;

            if (b_SerialPortStaus == true)
            {
                if (serialPortMode.IsOpen)
                {
                    serialPortMode.Close();
                    this.serialPortMode.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPortMode_DataReceived);
                }
                b_SerialPortStaus = false;
            }
            else
            {
                if (!serialPortMode.IsOpen)
                {
                    serialPortMode.Open();
                    b_SerialPortStaus = true;
                    this.serialPortMode.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPortMode_DataReceived);
                }
            }

            return b_SerialPortStaus;
        }


        /// <summary>
        /// serial port receive data packet 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void serialPortMode_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                if (TimeOut > 0)
                {
                    System.Threading.Thread.Sleep(TimeOut);
                }

                DataLength = serialPortMode.BytesToRead;
                if (DataLength > 0)
                {
                    if (DataLength > RtBuff.Length)
                        DataLength = RtBuff.Length;

                    serialPortMode.Read(RtBuff, 0, DataLength);
                    b_SerialReceiveReady = true;
                }
            }
            catch
            {

            }
        }

    }
}

/* End of this file */

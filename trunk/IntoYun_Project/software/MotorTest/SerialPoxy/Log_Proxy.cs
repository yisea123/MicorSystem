using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControlPoxy
{
    public class Log_Proxy: IDisposable
    {
        private bool disposed = false;
        private string _LogPath = "";
        private string _logFolder;
        private StreamWriter logStream;
        FileStream fs;
        public Log_Proxy(string logFolder )
        {
            _logFolder = logFolder;
        }

        public void Create_CvsFile( string fName )
        {
            try
            {
                disposed = false;
                Directory.CreateDirectory(System.Environment.CurrentDirectory + "/" + _logFolder);
                _LogPath = string.Format(@"{0}\{1}\{2}.csv", System.Environment.CurrentDirectory, _logFolder, fName);
                fs = new FileStream(_LogPath, System.IO.FileMode.Create, System.IO.FileAccess.Write);
                logStream = new StreamWriter(fs, System.Text.Encoding.UTF8);
            }
            catch
            {

            }
        }

        public void Write_CvsFile(string message)
        {
            Write_CvsFile("{0}", message);
        }

        private void Write_CvsFile(string format, params object[] obj)
        {
            try
            {
                logStream.WriteLine(string.Format("{0}", string.Format(format, obj)));
                logStream.Flush();
            }
            catch 
            {

            }
        }

        public void Close_CvsFile()
        {
            logStream.Close();
        }

        ~Log_Proxy()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            try
            {
                Dispose(true);
            }
            catch
            {

            }
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (disposed)
            {
                return;
            }

            if (disposing)
            {
                if (logStream != null)
                {
                    logStream.Flush();
                    logStream.Close();
                    logStream.Dispose();
                }
            }
            disposed = true;
        }

    }
}

/* End of this file */

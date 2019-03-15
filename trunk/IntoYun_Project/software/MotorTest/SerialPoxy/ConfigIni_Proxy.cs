using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ControlPoxy
{
    public class ConfigIni
    {

        public string  GetProjectInfor2Ini(string file, string section, string key)
        {
           return ConfigFile.GetValString(file, section, key, "");
        }

        public void SetProjectInfor2Ini(string file,string section, string key, string val)
        {
            try
            {
                ConfigFile.setProfile(file, section, key, val);
            }
            catch
            { }
        }

        class ConfigFile
        {
            [DllImport("kernel32")]
            private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);

            [DllImport("kernel32")]
            private static extern int GetPrivateProfileInt(string section, string key, int val, string filePath);

            [DllImport("kernel32")]
            private static extern int GetPrivateProfileString(
                string section, string key, string def, StringBuilder retVal, int size, string filePath);

            public static void setProfile(string path, string section, string key, string val)
            {
                // DirectoryInfo dir = new DirectoryInfo(Application.StartupPath).Parent.Parent;
                //在当前目录下，写一个config.ini文件
                //string path = Application.StartupPath + "//config.ini";
                WritePrivateProfileString(section, key, val, path);
            }

            public static string GetValString(string path, string section, string key, string def)
            {
                //取得config.ini路径
                // string s = System.Windows.Forms.Application.ExecutablePath;
                //在当前目录下，写一个config.ini文件
                //string path = Application.StartupPath + "//config.ini";
                StringBuilder str = new StringBuilder(255);
                GetPrivateProfileString(section, key, def, str, 255, path);
                return str.ToString();
            }
        }

    }
}

/* End of this file */

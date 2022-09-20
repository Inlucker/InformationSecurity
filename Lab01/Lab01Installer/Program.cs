using System;
using System.Management;
using System.IO;
using System.Text;

namespace Lab01Installer
{
  class Program
  {
    static void Main(string[] args)
    {
      try
      {
        ManagementObjectSearcher searcher =
            new ManagementObjectSearcher("root\\CIMV2",
            "SELECT * FROM Win32_Processor");
        string serial_number = "";

        foreach (ManagementObject queryObj in searcher.Get())
        {
          Console.WriteLine("-----------------------------------");
          Console.WriteLine("Win32_Processor instance");
          Console.WriteLine("-----------------------------------");
          Console.WriteLine("ProcessorId: {0}", queryObj["ProcessorId"]);

          serial_number = queryObj["ProcessorId"].ToString();

          Directory.CreateDirectory(System.Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"/.Lab01");
          string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"/.Lab01/processorid";
          using (FileStream fs = File.Create(path))
          {
            byte[] info = new UTF8Encoding(true).GetBytes(serial_number);
            fs.Write(info, 0, info.Length);
          }
        }
      }
      catch (ManagementException e)
      {
        Console.WriteLine("An error occurred while querying for WMI data: " + e.Message);
      }
    }
  }
}

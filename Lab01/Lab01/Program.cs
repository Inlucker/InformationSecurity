using System;
using System.Management;
using System.IO;

namespace Lab01
{
  class Program
  {
    static void Main(string[] args)
    {
      string processor_id = "";
      try
      {
        ManagementObjectSearcher searcher =
            new ManagementObjectSearcher("root\\CIMV2",
            "SELECT * FROM Win32_Processor");

        foreach (ManagementObject queryObj in searcher.Get())
        {
          processor_id = queryObj["ProcessorId"].ToString();
        }
      }
      catch (ManagementException e)
      {
        Console.WriteLine("An error occurred while querying for WMI data: " + e.Message);
        return;
      }

      string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"/.Lab01/processorid";
      string saved_processor_id = "";

      if (File.Exists(path))
      {
        using (StreamReader sr = File.OpenText(path))
        {
          string s = "";
          while ((s = sr.ReadLine()) != null)
            saved_processor_id = s;
        }
      }

      if (saved_processor_id != processor_id)
      {
        Console.WriteLine("You can't execute this programm on this computer");
        return;
      }

      Console.WriteLine("Hello World!");
    }
  }
}

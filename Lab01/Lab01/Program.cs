using System;
using System.Management;
using System.IO;

namespace Lab01
{
  class Program
  {
    static void Main(string[] args)
    {
      string unique_data = "";
      try
      {
        ManagementObjectSearcher searcher =
            new ManagementObjectSearcher("root\\CIMV2",
            "SELECT * FROM Win32_NetworkAdapter");

        foreach (ManagementObject queryObj in searcher.Get())
        {
          try
          {
            unique_data = queryObj["MACAddress"].ToString();
            break;
          }
          catch {}
        }
      }
      catch (ManagementException e)
      {
        Console.WriteLine("An error occurred while querying for WMI data: " + e.Message);
        return;
      }

      string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"/.Lab01/macadress";
      string saved_unique_data = "";

      if (File.Exists(path))
      {
        using (StreamReader sr = File.OpenText(path))
        {
          string s = "";
          while ((s = sr.ReadLine()) != null)
            saved_unique_data = s;
        }
      }

      if (saved_unique_data != unique_data)
      {
        Console.WriteLine("You can't execute this programm on this computer");
        Console.WriteLine("Для завершения нажмите любую клавишу...");
        Console.ReadKey();
        return;
      }

      Console.WriteLine("Hello World!");
      Console.WriteLine("Для завершения нажмите любую клавишу...");
      Console.ReadKey();
    }
  }
}

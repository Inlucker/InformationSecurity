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
            "SELECT * FROM Win32_NetworkAdapter");
        string unique_data = "";

        foreach (ManagementObject queryObj in searcher.Get())
        {
          Console.WriteLine("-----------------------------------");
          Console.WriteLine("Win32_NetworkAdapter instance");
          Console.WriteLine("-----------------------------------");
          Console.WriteLine("MACAddress: {0}", queryObj["MACAddress"]);

          try
          {
            unique_data = queryObj["MACAddress"].ToString();
            break;
          }
          catch //(System.NullReferenceException e)
          {
            //Console.WriteLine(e.Message);
          }
        }

        Directory.CreateDirectory(System.Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"/.Lab01");
        string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"/.Lab01/macadress";
        using (FileStream fs = File.Create(path))
        {
          byte[] info = new UTF8Encoding(true).GetBytes(unique_data);
          fs.Write(info, 0, info.Length);
        }
      }
      catch (ManagementException e)
      {
        Console.WriteLine("An error occurred while querying for WMI data: " + e.Message);
      }

      string command = "dotnet publish ./Lab01src/Lab01.csproj -r win-x64 -p:PublishSingleFile=true --self-contained false";
      System.Diagnostics.Process process = System.Diagnostics.Process.Start("cmd.exe", "/C " + command);
      process.WaitForExit();

      Console.WriteLine(Directory.GetCurrentDirectory());

      try
      {
        File.Move("./Lab01src/bin/Debug/netcoreapp3.1/win-x64/publish/Lab01.exe", "./Lab01.exe", true);
        Directory.Delete("./Lab01src/bin", true);
        Directory.Delete("./Lab01src/obj", true);
      }
      catch(Exception e)
      {
        Console.WriteLine(e.Message);
      }

      Console.WriteLine("Для завершения нажмите любую клавишу...");
      Console.ReadKey();
    }
  }
}

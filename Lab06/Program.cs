using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hafman
{
  class Program
  {
    static void Main(string[] args)
    {
      Hafman h = new Hafman();
      string in_file_name = "text.txt";
      //in_file_name = "text2.txt";
      //in_file_name = "Lab01.exe";
      //in_file_name = "nginx-1.23.1.zip";
      string out_file_name = "zip_" + in_file_name;
      h.compressData(in_file_name);
      Console.WriteLine("Compressed");
      h.decompressData(out_file_name);
      Console.WriteLine("Decompressed");

      Console.ReadLine();
    }
  }
}

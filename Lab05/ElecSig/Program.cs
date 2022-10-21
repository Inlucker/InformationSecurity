using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ElecSig
{
  class Program
  {
    static void Main(string[] args)
    {
      ElecSig elecSig = new ElecSig();
      string file_name = "text.txt";
      string file_name2 = "text2.txt";
      //file_name = "nginx1.zip";
      //file_name2 = "nginx2.zip";
      string sig_file_name = file_name + ".sig";
      byte[] sig = elecSig.makeSigForFile(file_name);
      elecSig.writeSigToFile(sig_file_name, sig);
      Console.WriteLine("Made signature \"" + sig_file_name + "\" for file \"" + file_name + "\"");
      bool res1 = elecSig.checkSig(file_name, sig_file_name);
      bool res2 = elecSig.checkSig(file_name2, sig_file_name);

      Console.WriteLine("Signature from file \"" + sig_file_name + "\" for file \"" + file_name + "\" is " + res1);
      Console.WriteLine("Signature from file \"" + sig_file_name + "\" for file \"" + file_name2 + "\" is " + res2);
      Console.ReadLine();
    }
  }
}

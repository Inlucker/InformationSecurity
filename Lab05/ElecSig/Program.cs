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
      string sig_file_name = file_name + ".sig";
      string file_name2 = "text2.txt";
      byte[] sig = elecSig.makeSigForFile(file_name);
      elecSig.writeSigToFile(sig_file_name, sig);
      Console.WriteLine("Made signature \"" + sig_file_name + "\" for file \"" + file_name + "\"");
      bool res1 = elecSig.checkSig("text.txt", "text.txt.sig");
      bool res2 = elecSig.checkSig("text2.txt", "text.txt.sig");

      Console.WriteLine("Signature from file \"" + sig_file_name + "\" for file \"" + file_name + "\" is " + res1);
      Console.WriteLine("Signature from file \"" + sig_file_name + "\" for file \"" + file_name2 + "\" is " + res2);
      Console.ReadLine();
    }
  }
}

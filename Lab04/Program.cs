using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RSA
{
  class Program
  {
    static void Main(string[] args)
    {
      RSA rsa = new RSA();

      String file_name = "test.txt";
      //file_name = "nginx-1.23.1.zip";
      String ciphered_file_name = "ciphered_" + file_name;
      String deciphered_file_name = "deciphered_" + file_name;;

      string msg = "Hello Arseny! Hello Ilya!";
      Console.WriteLine(msg);
      /*long[] cipher_msg = rsa.encipherIntoArray(msg);
      foreach (long l in cipher_msg)
        Console.WriteLine(l);
      string deciphered_msg = rsa.decipherFromArray(cipher_msg);
      Console.WriteLine(deciphered_msg);*/
      byte[] cipher_array = rsa.encipherIntoBytes(msg);
      rsa.encipherFile(file_name, ciphered_file_name);
      /*foreach (byte b in cipher_array)
         Console.WriteLine(b);*/
      string deciphered_msg = rsa.decipherFromBytes(cipher_array);
      rsa.decipherFile(ciphered_file_name, deciphered_file_name);
      Console.WriteLine(deciphered_msg);

      Console.ReadLine();
    }
  }
}

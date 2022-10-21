using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;
using System.IO;

namespace ElecSig
{
  class ElecSig
  {
    public ElecSig()
    {
      hmac = new HMACSHA256();
      rsaProvider = new RSACryptoServiceProvider();
      //file_hash1 = new byte[0];
      //file_hash2 = new byte[0];
      //elec_sig = new byte[0];
    }

    public byte[] makeSigForFile(string file_name)
    {
      byte[] file_hash1 = new byte[0];
      using (FileStream ifstream = File.OpenRead(file_name))
      {
        byte[] buffer = new byte[ifstream.Length];
        ifstream.Read(buffer, 0, buffer.Length);
        file_hash1 = hmac.ComputeHash(buffer);

        // декодируем байты в строку
        //string textFromFile = Encoding.Default.GetString(buffer);
      }

      byte[] elec_sig = rsaProvider.Encrypt(file_hash1, false);
      return elec_sig;
    }

    public void writeSigToFile(string file_name, byte[] elec_sig)
    {
      using (FileStream ofstream = File.Open(file_name, FileMode.Create, FileAccess.Write))
      {
        ofstream.Write(elec_sig, 0, elec_sig.Length);
      }
    }

    public bool checkSig(string file_name, string sig_file_name)
    {
      byte[] file_hash2 = new byte[0];
      using (FileStream ifstream = File.OpenRead(file_name))
      {
        byte[] buf = new byte[ifstream.Length];
        ifstream.Read(buf, 0, buf.Length);
        file_hash2 = hmac.ComputeHash(buf);
      }

      byte[] sig;
      using (FileStream ifstream = File.OpenRead(sig_file_name))
      {
        sig = new byte[ifstream.Length];
        ifstream.Read(sig, 0, sig.Length);
      }
      byte[] decrypted_sig = rsaProvider.Decrypt(sig, false);

      if (file_hash2.Length != decrypted_sig.Length)
        return false;
      int len = file_hash2.Length;

      for (int i = 0; i < len; i++)
      {
        if (file_hash2[i] != decrypted_sig[i])
          return false;
      }
      return true;
    }

    public HMACSHA256 hmac;
    public RSACryptoServiceProvider rsaProvider;
    //byte[] file_hash1;
    //byte[] file_hash2;
    //byte[] elec_sig;


  }
}

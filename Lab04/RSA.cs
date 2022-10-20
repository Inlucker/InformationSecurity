using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace RSA
{
  class RSA
  {
    public RSA()
    {
      //long fi = Fi(); // 986040
      byte_size = getByteSize();
    }
    public void encipherFile(string in_file_name, string out_file_name)
    {
      using (FileStream ifstream = File.OpenRead(in_file_name))
      using (FileStream ofstream = File.OpenWrite(out_file_name))
      {
        long M = ifstream.ReadByte();
        while (M != -1)
        {
          long lres = fastExp(M, E);
          byte[] C = BitConverter.GetBytes(lres);

          for (int j = 0; j < byte_size; j++)
            ofstream.WriteByte(C[j]);

          M = ifstream.ReadByte();
        }
      }
    }
    public void decipherFile(string in_file_name, string out_file_name)
    {
      using (FileStream ifstream = File.OpenRead(in_file_name))
      using (FileStream ofstream = File.OpenWrite(out_file_name))
      {
        byte[] C = new byte[8];
        int n = ifstream.Read(C, 0, byte_size);
        while (n == 3)
        {
          long lres = BitConverter.ToInt64(C, 0);
          lres = fastExp(lres, D);
          byte M = Convert.ToByte(lres);

          ofstream.WriteByte(M);

          n = ifstream.Read(C, 0, byte_size);
        }
      }
    }
    public byte[] encipherIntoBytes(string msg)
    {
      int len = msg.Length;
      byte[] res = new byte[byte_size * len];
      for (int i = 0; i < len; i++)
      {
        long M = msg[i];
        long lres = fastExp(M, E);
        //byte[] C = new byte[3];
        byte[] C = BitConverter.GetBytes(lres);

        for (int j = 0; j < byte_size; j++)
          res[byte_size * i + j] = C[j];
      }

      return res;
    }
    public string decipherFromBytes(byte[] arr)
    {
      int len = arr.Length / byte_size;
      string res = "";
      for (int i = 0; i < len; i++)
      {
        byte[] C = new byte[8];
        for (int j = 0; j < byte_size; j++)
          C[j] = arr[byte_size * i + j];

        long lres = BitConverter.ToInt64(C, 0);
        lres = fastExp(lres, D);
        char c = (char)lres;

        res += c;
      }

      return res;
    }
    public long[] encipherIntoArray(string msg)
    {
      int len = msg.Length;
      long[] res = new long[len];
      for (int i = 0; i < len; i++)
      {
        long M = msg[i];
        long lres = fastExp(M, E);

        res[i] = lres;
      }
      return res;
    }

    public string decipherFromArray(long[] cipher_msg)
    {
      string res = "";

      int len = cipher_msg.Length;
      for (int i = 0; i < len; i++)
      {
        long C = cipher_msg[i];
        long lres = fastExp(C, D);
        char c = (char)lres;

        res += c;
      }
      return res;
    }

    long fastExp(long a, long e)
    {
      long res = 1;
      while (e != 0)
      {
        if ((e & 1) != 0)
        {
          res = (res * a) % N;
        }
        a = (a * a) % N;
        e >>= 1;
      }
      return res;
    }
    int getByteSize()
    {
      int bits = 1;
      int t = 2;
      while (t < N)
      {
        t *= 2;
        bits++;
      }
      return bits / 8 + 1;
    }
    long Fi() { return (P - 1) * (Q - 1); } // 986040
    long P = 991;
    long Q = 997;
    long N = 991 * 997; //988027
    long E = 591619; //взаимно простое с Fi и < Fi
    long D = 473299;
    int byte_size = 3;
  }
}

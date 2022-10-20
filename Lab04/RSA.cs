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
      P = 199;
      Q = 211;
      N = P * Q; //41989
      Console.WriteLine(Fi()); //41580
      //E = 24947; //взаимно простое с Fi и < Fi
      E = getE();
      /*gcd(E, Fi(), out D, out y);
      if (D < 0)
        D += Fi();*/
      //D = 33263;
      D = getD();
      byte_size = getByteSize();
    }
    public void encipherFile(string in_file_name, string out_file_name)
    {
      using (FileStream ifstream = File.OpenRead(in_file_name))
      using (FileStream ofstream = File.Open(out_file_name, FileMode.Create, FileAccess.Write))
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
      using (FileStream ofstream = File.Open(out_file_name, FileMode.Create, FileAccess.Write))
      {
        byte[] C = new byte[8];
        int n = ifstream.Read(C, 0, byte_size);
        int count = 0;
        while (n == byte_size)
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
    bool evklid(long a, long b)
    {
      long tmp;
      while (b != 1 && b != 0)
      {
        tmp = a % b;
        a = b;
        b = tmp;
      }
      return (b == 1);
    }
    long getE()
    {
      long fi = Fi();
      long tmp = Convert.ToInt64(fi * 0.6);
      while (!evklid(fi, tmp))
        tmp--;
      return tmp;
    }
    long gcd(long a, long b, out long x, out long y)
    {
      if (a == 0)
      {
        x = 0; y = 1;
        return b;
      }
      long x1, y1;
      long d = gcd(b % a, a, out x1, out y1);
      x = y1 - (b / a) * x1;
      y = x1;
      return d;
    }
    long extEvklid(long A, long B)
    {
      long R = A % B;
      long[,] E = new long[2, 2];
      E[0, 0] = 1;
      E[0, 1] = 0;
      E[1, 0] = 0;
      E[1, 1] = 1;
      while (R != 0)
      {
        R = A % B;
        long q = A / B;
        long[,] tmpE = new long[2, 2];
        for (int i = 0; i < 2; i++)
          for (int j = 0; j < 2; j++)
            tmpE[i, j] = E[i, j];
            long[,] E2 = new long[2, 2];
        E2[0, 0] = 0;
        E2[0, 1] = 1;
        E2[1, 0] = 1;
        E2[1, 1] = -q;

        E[0, 0] = tmpE[0, 0] * E2[0, 0] + tmpE[0, 1] * E2[1, 0];
        E[0, 1] = tmpE[0, 0] * E2[0, 1] + tmpE[0, 1] * E2[1, 1];
        E[1, 0] = tmpE[1, 0] * E2[0, 0] + tmpE[1, 1] * E2[1, 0];
        E[1, 1] = tmpE[1, 0] * E2[0, 1] + tmpE[1, 1] * E2[1, 1];

        long tmpB = A % B;
        A = B;
        B = tmpB;
      }
      long res = E[1, 0];
      return res;
    }
    long getD()
    {
      long res = extEvklid(Fi(), E);
      if (res < 0)
        res += Fi();
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
      int res = bits / 8;
      if (bits % 8 != 0)
        res++;
      return res;
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

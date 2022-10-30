using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.IO;

namespace Hafman
{

  class Hafman
  {
    public void decompressData(string file_name)
    {
      long eof_pos = 0;
      bool eof = false;
      //GetEnd of File
      using (FileStream ifstream = File.OpenRead(file_name))
      {
        while(ifstream.ReadByte() != -1)
          eof_pos = ifstream.Position;
      }
      using (FileStream ifstream = File.OpenRead(file_name))
      using (FileStream ofstream = File.Open("unzip_" + file_name, FileMode.Create, FileAccess.Write))
      {
        //ReadFreqTable
        Dictionary<byte, int> freq_table = new Dictionary<byte, int>();
        byte[] bytes = new byte[5];
        ifstream.Read(bytes, 0, bytes.Length);

        //Console.WriteLine("Decompress:");
        while (bytes[0] != 1 || bytes[1] != 0 || bytes[2] != 0 || bytes[3] != 0 || bytes[4] != 0)
        {
          int frq = BitConverter.ToInt32(bytes, 1);
          Console.Write((char)bytes[0] + " ");
          Console.WriteLine(frq);
          freq_table.Add(bytes[0], (int)frq);
          ifstream.Read(bytes, 0, bytes.Length);
        }
        int free_bits_number = ifstream.ReadByte();
        createDecodeTable(freq_table, out Dictionary<byte, BitArray> decode_table);

        //ReadData
        int n = ifstream.ReadByte();
        int i = 0;
        BitArray read_bits = new BitArray(i);
        while (n != -1)
        {
          if (ifstream.Position == eof_pos)
            eof = true;
          byte read_b = (byte)n;
          BitArray bits = new BitArray(new byte[] { read_b });
          for (int j = 0; j < 8; j++)
          {
            if (eof && j >= free_bits_number)
              break;
            BitArray new_read_bits = new BitArray(++i);
            for (int k = 0; k < read_bits.Length; k++)
              new_read_bits[k] = read_bits[k];
            new_read_bits[i - 1] = bits[j];
            read_bits = new_read_bits;

            if (findCode(read_bits, out byte write_b, ref decode_table))
            {
              ofstream.WriteByte(write_b);
              i = 0;
              read_bits = new BitArray(i);
            }
          }

          n = ifstream.ReadByte();
        }


      }
    }
    public void compressData(string file_name)
    {
      Dictionary<byte, int> freq_table = createFreqTable(file_name);
      //writeFreqTable(file_name, freq_table);
      createDecodeTable(freq_table, out Dictionary<byte, BitArray> decode_table);

      using (FileStream ifstream = File.OpenRead(file_name))
      using (FileStream ofstream = File.Open("zip_" + file_name, FileMode.Create, FileAccess.Write))
      //using (FileStream ofstream = File.OpenWrite("zip_" + file_name))
      {
        //writeFreqTable
        foreach (KeyValuePair<byte, int> entry in freq_table)
        {
          ofstream.WriteByte(entry.Key);
          byte[] write_bytes = BitConverter.GetBytes(entry.Value);
          ofstream.Write(write_bytes, 0, 4);
        }
        byte[] end_of_freq_table = new byte[] { 1, 0, 0, 0, 0};
        ofstream.Write(end_of_freq_table, 0, end_of_freq_table.Length);
        long free_bits_number_place = ofstream.Position;
        ofstream.WriteByte(0);

        //write data
        int i = 0;
        BitArray write_byte = new BitArray(8);
        int n = ifstream.ReadByte();
        while (n != -1)
        {
          byte read_b = (byte)n;
          BitArray bits = decode_table[read_b];
          for (int j = 0; j < bits.Length; j++)
          {
            write_byte[i++] = bits[j];
            if (i == 8)
            {
              ofstream.WriteByte(ConvertToByte(write_byte));
              i = 0;
            }
          }

          n = ifstream.ReadByte();
        }

        if (i != 0)
        {
          byte free_bits_number = (byte)(i);
          for (int j = i; j < 8; j++)
            write_byte[i++] = true;
          ofstream.WriteByte(ConvertToByte(write_byte));
          ofstream.Seek(free_bits_number_place, SeekOrigin.Begin);
          ofstream.WriteByte(free_bits_number);
        }
      }
    }
    Dictionary<byte, int> createFreqTable(string file_name)
    {
      Dictionary<byte, int> freq_table = new Dictionary<byte, int>();

      using (FileStream ifstream = File.OpenRead(file_name))
      {
        int n = ifstream.ReadByte();
        while (n != -1)
        {
          byte b = (byte)n;
          if (freq_table.ContainsKey(b))
            freq_table[b]++;
          else
            freq_table.Add(b, 1);

          n = ifstream.ReadByte();
        }
      }
      return freq_table;
    }
    void createDecodeTable(Dictionary<byte, int> f_table, out Dictionary<byte, BitArray> decode_table)
    {
      Dictionary<byte[], int> tree_node_table = new Dictionary<byte[], int>();
      foreach (KeyValuePair<byte, int> entry in f_table)
        tree_node_table.Add(new byte[]{ entry.Key }, entry.Value);

      while (tree_node_table.Count != 1)
      {
        var sortedDict = from entry in tree_node_table orderby entry.Value ascending select entry;
        KeyValuePair<byte[], int> k1 = sortedDict.ElementAt<KeyValuePair<byte[], int>>(0);
        KeyValuePair<byte[], int> k2 = sortedDict.ElementAt<KeyValuePair<byte[], int>>(1);
        byte[] tn1 = k1.Key;
        byte[] tn2 = k2.Key;
        //TreeNode new_node = new TreeNode(new TreeNode(tn1), new TreeNode(tn2), tn1.Concat(tn2).ToArray());

        tree_node_table.Add(tn1.Concat(tn2).ToArray(), k1.Value + k2.Value);
        tree_node_table.Remove(tn1);
        tree_node_table.Remove(tn2);
      }

      byte[] root_str = tree_node_table.ElementAt<KeyValuePair<byte[], int>>(0).Key;
      TreeNode tree_root = new TreeNode(root_str, new BitArray(0));
      decode_table = new Dictionary<byte, BitArray>();
      createTree(root_str, tree_root, ref decode_table);

      Console.WriteLine("Compress:");
      foreach (KeyValuePair<byte, BitArray> entry in decode_table)
      {
        Console.Write((char)entry.Key + " ");
        BitArray bit_arr = entry.Value;
        for (int i = 0; i < bit_arr.Length; i++)
        {
          if (bit_arr[i])
            Console.Write("1");
          else
            Console.Write("0");
        }
        Console.WriteLine();
      }
    }
    void createTree(byte[] root_str, TreeNode parent, ref Dictionary<byte, BitArray> decode_table)
    {
      if (root_str.Length <= 1)
      {
        if (parent.code.Length > 0)
          decode_table.Add(root_str[0], parent.code);
        else
          decode_table.Add(root_str[0], new BitArray(1, true));
        return;
      }

      int mid = root_str.Length / 2 + root_str.Length % 2;
      byte[] l_str = new byte[mid];
      byte[] r_str = new byte[root_str.Length - mid];
      for (int i = 0; i < mid; i++)
        l_str[i] = root_str[i];
      for (int i = mid; i < root_str.Length; i++)
        r_str[i - mid] = root_str[i];

      parent.addLeftChild(l_str);
      parent.addRightChild(r_str);

      createTree(l_str, parent.l_child, ref decode_table);
      createTree(r_str, parent.r_child, ref decode_table);
    }
    byte ConvertToByte(BitArray bits)
    {
      if (bits.Count != 8)
      {
        throw new ArgumentException("bits");
      }
      byte[] bytes = new byte[1];
      bits.CopyTo(bytes, 0);
      return bytes[0];
    }
    bool findCode(BitArray bits, out byte write_b, ref Dictionary<byte, BitArray> decode_table)
    {
      write_b = 0;
      //bool res = false;
      foreach (KeyValuePair<byte, BitArray> entry in decode_table)
      {
        bool flag = false;
        if (entry.Value.Length == bits.Length)
        {
          flag = true;
          for (int i = 0; i < bits.Length; i++)
            if (entry.Value[i] ^ bits[i])
            {
              flag = false;
              break;
            }
        }
        if (flag)
        {
          write_b = entry.Key;
          return true;
        }
      }
      return false;
    }

    //Dictionary<byte, int> freq_table = new Dictionary<byte, int>();
    //TreeNode tree_root;
    //Dictionary<byte, BitArray> decode_table = new Dictionary<byte, BitArray>();
  }
}

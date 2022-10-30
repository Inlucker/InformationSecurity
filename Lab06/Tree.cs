using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace Hafman
{
  class TreeNode
  {
    public TreeNode(byte[] v, BitArray bit_arr, TreeNode p = null)
    {
      value = v;
      parent = p;
      code = bit_arr;
    }
    /*public TreeNode(TreeNode lc, TreeNode rc, byte[] v)
    {
      l_child = lc;
      r_child = rc;
      value = v;
    }*/
    public void addLeftChild(byte[] b)
    {
      BitArray lba = new BitArray(code.Length + 1);
      for (int i = 0; i < code.Length; i++)
        lba[i] = code[i];
      lba[code.Length] = true;
      l_child = new TreeNode(b, lba, this);
    }
    public void addRightChild(byte[] b)
    {
      BitArray rba = new BitArray(code.Length + 1);
      for (int i = 0; i < code.Length; i++)
        rba[i] = code[i];
      rba[code.Length] = false;
      r_child = new TreeNode(b, rba, this);
    }
    public TreeNode parent { get; set; } = null;
    public TreeNode l_child { get; set; } = null;
    public TreeNode r_child { get; set; } = null;
    public byte[] value { get; set; }
    public BitArray code { get; set; }
}
}

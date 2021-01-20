using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Binary_tree
{
    class Program
    {
        class stack
        {
            private int[] _stack;
            private int top;
            public stack(int value)
            {
                _stack = new int[value];
                top = -1;
            }

            public bool IsEmpty()
            {
                if (top == -1) return true;
                else return false;
            }

            public void Push(int date)
            {
                if (top >= _stack.Length)
                {
                    Console.WriteLine("栈已满");
                }
                else
                {
                    _stack[++top] = date;
                }
            }

            public int Pop()
            {
                if (this.IsEmpty())
                {
                    Console.WriteLine("栈已空");
                    return -1;
                }
                else
                {
                    Console.WriteLine("    [" + _stack[top - 1] + "]    ");
                    return _stack[top--];
                }
            }
        }   //栈
        class TreeNode
        {
            public int value;
            public TreeNode left_node;
            public TreeNode right_node;
            public TreeNode(int value)
            {
                this.value = value;
                this.left_node = null;
                this.right_node = null;
            }
        }
        class BinaryTree
        {
            public TreeNode rootnode;
            public BinaryTree(int[] data)   //将数组data   建立二叉树
            {
                for (int i = 0; i<data.Length; i++)
                {
                    Add_Tree(data[i]);
                }
            }
            void Add_Tree(int value)  //将一个value放入二叉树
            {
                TreeNode newnode = rootnode;
                if(newnode==null)
                {
                    rootnode = new TreeNode(value);
                    return;
                }
                while(true)
                {
                    if(value<newnode.value)  //向左子树移动
                    {
                        if(newnode.left_node==null)
                        {
                            newnode.left_node = new TreeNode(value);
                            return;
                        }
                        else
                        {
                            newnode = newnode.left_node;
                        }
                    }
                    else
                    {
                        if(newnode.right_node==null)
                        {
                            newnode.right_node = new TreeNode(value);
                            return;
                        }
                        else
                        {
                            newnode = newnode.right_node;
                        }
                    }
                }
            }
            public void Inorder(TreeNode node)    //中序遍历
            {
                if(node!=null)
                {
                    Inorder(node.left_node);
                    Console.WriteLine("   "+node.value+"   ");
                    Inorder(node.right_node);
                }
            }
            public void Preorder(TreeNode node )   //前序遍历
            {
                if(node!=null)
                {
                    Console.WriteLine("   " + node.value + "  ");
                    Preorder(node.left_node);
                    Preorder(node.right_node);
                }
            }
            public void Postorder(TreeNode node) //后序遍历
            {
                if (node != null)
                {
                    Postorder(node.left_node);
                    Postorder(node.right_node);
                    Console.WriteLine("   "+node.value+"   ");
                }
            }
            public bool FindTreeNode(int value)
            {
                TreeNode node = rootnode;
                while(true)
                {
                    if (node.value == value)
                        return true;
                    else if (node.value > value)
                        node = node.left_node;
                    else if (node.value < value) 
                        node = node.right_node;
                    if (node == null)
                        return false;
                }
            }
            public void DeleteTreeNode(int value)
            {
                if (!FindTreeNode(value))
                {
                    Console.WriteLine("未找到该节点");
                    return;
                }
                TreeNode tem=rootnode;
                TreeNode tmp=rootnode;
                while(true)
                {
                    TreeNode node = rootnode;
                    if (node.value < value)
                    {
                        tmp = tem;
                        tem = tem.left_node;
                    }
                    else if (node.value > value)
                    {
                        tem = tmp;
                        tmp = tmp.right_node;
                    }
                    else
                        break;
                }
                   
            }



        }


        static void Main(string[] args)
        {
            int[] content = { 6, 43, 576, 4, 2345, 6544, 64, 33, 46, 564 };
            BinaryTree tree= new BinaryTree(content);
            Console.WriteLine("中序遍历");
            tree.Inorder(tree.rootnode);
            #region 数组实现二叉树
            //int i, level;
            //int[] data = { 6, 3, 5, 9, 7, 8, 4, 2 };
            //int[] btree = new int[16];
            //btree[0] = 0;
            //Console.WriteLine();
            //for (i = 0; i < 8; i++)
            //{
            //    for (level = 1; btree[level] != 0;)
            //    {
            //        if (data[i] > btree[level])
            //            level = level * 2 + 1;

            //        else
            //            level *= 2;
            //    }
            //    btree[level] = data[i];
            //}
            //Console.WriteLine("二叉树的内容为；");
            //for (i = 1; i < 16; i++)
            //    Console.Write(btree[i] + "   ");
            //Console.WriteLine();
            //Console.ReadKey();
            #endregion
        }
    }
}

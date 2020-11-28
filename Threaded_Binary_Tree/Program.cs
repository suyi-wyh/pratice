using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Threaded_Binary_Tree
{
    class ThreadNode
    {
        public int value;
        public int left_Thread;
        public int right_Thread;
        public ThreadNode left_node;
        public ThreadNode right_node;
        public ThreadNode(int value)
        {
            this.value = value;
            this.left_Thread = 0;
            this.right_Thread = 0;
            this.left_node = null;
            this.right_node = null;
        }
    }

    class Thread_Binary_Tree
    {
        public ThreadNode rootnode;
        public Thread_Binary_Tree()  //构造函数：：无传入参数
        {
            rootnode = null;
        }
        public Thread_Binary_Tree(int[] data)
        {
            for (int i = 0; i < data.Length; i++)
                Addnode(data[i]);
        }
        public void Addnode(int value)
        {
            ThreadNode newnode = new ThreadNode(value);
            ThreadNode current;
            ThreadNode parent;
            ThreadNode previous = new ThreadNode(value);
            int pos;
            if (rootnode == null)
            {
                rootnode = newnode;
                rootnode.left_node = rootnode;
                rootnode.right_node = null;
                rootnode.left_Thread = 0;
                rootnode.right_Thread = 1;
                return;
            }
            current = rootnode.right_node;
            if (current == null)
            {
                rootnode.right_node = newnode;
                newnode.left_node = rootnode;
                newnode.right_node = rootnode;
                return;
            }
            parent = rootnode;
            pos = 0;
            while (current != null)
            {
                if (current.value > value)
                {
                    if (pos != -1)
                    {
                        pos = -1;
                        previous = parent;
                    }
                    parent = current;
                    if (current.left_Thread == 1)
                        current = current.left_node;
                    else
                        current = null;
                }
                else
                {
                    if(pos!=1)
                    {
                        pos = 1;
                        previous = parent;
                    }
                    parent = current;
                    if (current.right_Thread == 1)
                        current = current.right_node;
                    else
                        current = null;
                }
            }
            if(parent.value>value)
            {
                parent.left_Thread = 1;
                parent.left_node = newnode;
                newnode.left_node = previous;
                newnode.right_node = parent;
            }
            else
            {
                parent.right_Thread = 1;
                parent.right_node = newnode;
                newnode.left_node = parent;
                newnode.right_node = previous;
            }
            return;
        }

        public void Inorder()
        {
            ThreadNode tempnode;
            tempnode = rootnode;
            do
            {
                if (tempnode.right_Thread == 0)
                    tempnode = tempnode.right_node;
                else
                {
                    tempnode = tempnode.right_node;
                    while (tempnode.left_Thread != 0)
                    {
                        tempnode = tempnode.left_node;
                    }
                }
                if (tempnode != rootnode)
                    Console.WriteLine("[" + tempnode.value + "]");
            } while (tempnode != rootnode);
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("线索二叉树经建立后，经中序遍历有排序的结果");
            Console.WriteLine("除了第一个数字作为线索二叉树的开头结点外");
            int[] data1 = {0,10,20,30,100,399,453,43,237,373,655 };
            Thread_Binary_Tree tree1 = new Thread_Binary_Tree(data1);
            Console.WriteLine("================================");
            Console.WriteLine("范例1");
            Console.WriteLine("排序结果为：");
            tree1.Inorder();
            int[] data2 = { 0, 101, 118, 87, 12, 765, 65 };
            Thread_Binary_Tree tree2 = new Thread_Binary_Tree(data2);
            Console.WriteLine("================================");
            Console.WriteLine("范例2");
            Console.WriteLine("排序结果为：");
            tree2.Inorder();
            Console.ReadKey();
        }
    }
}

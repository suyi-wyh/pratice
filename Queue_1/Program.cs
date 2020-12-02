using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Console;

namespace Queue_1
{

    class Program
    {
        public static int front = -1, rear = -1, max = 20;
        public static int val;
        public static int[] queue = new int[max];

        static void Main(string[] args)
        {
            string strM;
            int M = 0;
            while (rear < max - 1 && M != 3)
            {
                Console.WriteLine("[1]存入一个数据 [2]取出一个数值 [3]结束：");
                strM = Console.ReadLine();
                M = int.Parse(strM);
                switch (M)
                {
                    case 1:
                        Write("\n请输入数值：");
                        strM = ReadLine();
                        val = int.Parse(strM);
                        rear++;
                        Console.WriteLine(rear);
                        queue[rear] = val;
                        break;
                    case 2:
                        if (rear > front)
                        {
                            front++;
                            Console.WriteLine($"front{front}");
                            Console.WriteLine($"\n[取出数值为]：{queue[front]}");
                            queue[front] = 0;
                        }
                        else
                            Console.WriteLine("queue is empty");
                        break;
                    default:
                        WriteLine();
                        break;
                }
                if (rear == max - 1)
                    Console.WriteLine("队列已经满了");
            }
            Console.WriteLine("输出队列数据");
            if (front >= rear)
                Console.WriteLine("队列已经空了");
            else
            {
                while (rear > front)
                {
                    front++;
                    Console.WriteLine($"[{queue[front]}]");
                }
            }
            Console.ReadKey();
        }
       
    }
}

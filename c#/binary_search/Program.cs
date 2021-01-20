using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace binary_search
{

    class Program
    {
        public static int BinarySearch(int[] data,int mun,int val)
        {
            int high, mid, low;
            low = 0;
            high = mun - 1;
            while( low<=high )
            {
                mid = (high + low) / 2;
                if (val < data[mid])
                {
                    high = mid - 1;
                }
                else if (val > data[mid])
                {
                    low = mid + 1;
                }
                else
                {
                    return mid;
                }
            }
            return -1;
        }

        public static int[] CreakNum(int val)
        {
            int[] num = new int[val];
            int a = 1;
            Random rnd = new Random((int)DateTime.Now.Ticks);
            for(int i=0;i<val;i++)
            {
                a += (rnd.Next(100) % 5 + 1);
                num[i] = a;
            }
            return num;
        }
        static void Main(string[] args)
        {
            int[] num = CreakNum(50);
            Console.WriteLine("请输入查找值：");
            int val = int.Parse(Console.ReadLine());
            for(int i =0;i<50;i++)
            {
                Console.WriteLine(num[i]);
                Console.WriteLine(i);
            }
           
            int flag=BinarySearch(num, 50, val);
            if (-1 == flag)
                Console.WriteLine("No value");
            else
                Console.WriteLine($"在{flag}处找到{val}");
            Console.ReadKey();
        }
    }
}

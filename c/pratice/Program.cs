
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace guibing
{
    class Program
    {
        const int SIZE = 10;
        static int process = 0;
        private static int[] sortArray = { 310, 40, 453, 34, 546, 35, 5, 634, 6543, 54, 75 };
        static void ShowArray()
        {
            for (int i = 0; i < SIZE; ++i)
                Console.WriteLine($"   {sortArray[i]}   ");
        }

        static void Sort(int[] d, int size, int lf, int rg)
        {
            int i, j, tmp;
            int lf_idx;
            int rg_idx;
            int t;
            //第一项键值为的d[lf]
            if (lf < rg)
            {
                lf_idx = lf + 1;
                rg_idx = rg;
                while (true)
                {
                    Console.Write($"[处理过程] {process++}]=>");
                    for (t = 0; t < size; t++)
                        Console.Write($"[{d[t]}]");
                    Console.WriteLine();
                    for (i = lf + 1; i <= rg; ++i) //从左往右找出一个键值大于的d[lf]的
                    {
                        if (d[i] >= d[lf])
                        {
                            lf_idx = i;
                            break;
                        }
                        lf_idx++;
                    }

                    for (j = rg; j >= lf + 1; j--) //从右往左找一个键值小于d[lf]的
                    {
                        if (d[j] < d[lf])
                        {
                            rg_idx = j;
                            break;
                        }
                        --rg_idx;
                    }


                    if (lf_idx < rg_idx)
                    {
                        tmp = d[lf_idx];
                        d[lf_idx] = d[rg_idx];
                        d[rg_idx] = tmp;
                    }
                    else
                        break;
                }

                if (lf_idx >= rg_idx)    //若lf_idx大于rg_idx 则将d[lf]和d[rg_idx]互换
                {
                    tmp = d[lf];
                    d[lf] = d[rg_idx];
                    d[rg_idx] = tmp;
                    Sort(d, size, lf, rg_idx - 1);
                    Sort(d, size, rg_idx + 1, rg);
                }
            }

        }
        static void Main(string[] args)
        {
            Sort(sortArray, SIZE, 0, 9);
            Console.WriteLine("------------");
            ShowArray();
        }
    }
}

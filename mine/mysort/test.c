#include"mysort.h"


int main()
{
	int num[] = {25,67,3,7,23,7,28,23,785};
	int nums[] = {9,8,7,6,5,4,3,2,1 };
	QuickSort(num, 0,8);
	for (int i = 0; i < 9; i++)
		printf("%d \n", num[i]);
	int a = 1;
	int b = 2;
	printf("%d  %d\n", a, b);
	Swap(&a,&b);
	printf("%d  %d\n", a, b);
	
}
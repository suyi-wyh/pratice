#include"mysort.h"


int main()
{
	int num[] = {65,12,456,423,43,56,123,654,76};
	int nums[] = {9,8,7,6,5,4,3,2,1 };
	int tmp[9];
	MergeSort(num, 0,8,tmp);
	for (int i = 0; i < 9; i++)
		printf("%d \n", num[i]);
	int a = 1;
	int b = 2;
	printf("%d  %d\n", a, b);
	Swap(&a,&b);
	printf("%d  %d\n", a, b);
	
}
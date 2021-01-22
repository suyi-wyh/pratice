#include"mysort.h"


int main()
{
	int num[] = { 1,2,3,4,5,6,7,8,9 };
	int nums[] = {9,8,7,6,5,4,3,2,1 };
	SelectSort(nums, 9);
	for (int i = 0; i < 9; i++)
		printf("%d \n", nums[i]);
	int a = 1;
	int b = 2;
	printf("%d  %d\n", a, b);
	Swap(&a,&b);
	printf("%d  %d\n", a, b);
	
}
//#include<stdio.h>
//#include<stdlib.h>
//
//int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
//{
//	int KNum = K;
//	int KSize=0;
//	int carrybit=0,i=ASize-1;
//	while (KNum)
//	{
//		++KSize;
//		KNum /= 10;
//	}
//	int AKSize = (ASize > KSize ? ASize + 1 : KSize + 1);
//	int qwe = AKSize;
//	int* AK = (int*)malloc(AKSize * sizeof(int));
//	while (AKSize)
//	{
//		int Y = K % 10;
//		K /= 10;
//		if (i >= 0)
//		{
//			*(AK + AKSize - 1) = Y + *(A + i) + carrybit;
//			i--;
//		}
//		else
//		{
//			*(AK + AKSize - 1) = Y + carrybit;
//		}
//		if (*(AK + AKSize - 1) >= 10)
//		{
//			*(AK + AKSize - 1) = *(AK + AKSize - 1) % 10;
//			carrybit = 1;
//		}
//		else
//			carrybit = 0;
//		--AKSize;
//	}
//	for (int aas = 0; aas < qwe; ++aas)
//		printf("%d",*(A+aas));
//	return returnSize;
//}
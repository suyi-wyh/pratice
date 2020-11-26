#include <stdio.h>
#include<stdlib.h>


int IsCmpString(char* a, char* b)
{
	int flag;
	char* p, *t;
	p = a;
	t = b;
	for (; *t!='\0'; ++t);
	while (*p!='\0')
	{
		--t;
		if (*p != *t)
			break;
		++p;
	}
	if (*p == '\0')
		flag = 1;
	else
		flag = 0;
	return flag;
}


char* zuoxuan(char a[], int x)
{
	char t;
	char * p ,* h;
	for (int i = 0; i < x; i++)
	{
		p = a;
		t = *p;
		while (*(p+1) != '\0')
		{
			*p = *(p + 1);
			++p;
		}
		*p = t;
	}
	return a;
}


//-------------------------
//-------------------------
//-------------------------
//-------------------------




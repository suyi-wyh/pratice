#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DATATYPE int

typedef struct Heap
{
	DATATYPE* _val;
	DATATYPE _size;
	DATATYPE _capacity;
}Heap;

void Swap(DATATYPE* a,DATATYPE* b);

DATATYPE* BubbleSort(DATATYPE* data, DATATYPE nums);

DATATYPE* InsertSort(DATATYPE* data, DATATYPE nums);

DATATYPE* SelectSort(DATATYPE* data, DATATYPE nums);

DATATYPE* ShellSort(DATATYPE* data, DATATYPE nums);


void AdJustDown(DATATYPE* data, int n, int root);
void AdJustUp(DATATYPE* data, int n, int child);
Heap* HeapInit(DATATYPE* data, int n);
DATATYPE HeapTop(Heap* heap);
DATATYPE HeapPop(Heap* heap);
void HeapPush(Heap* heap, int val);
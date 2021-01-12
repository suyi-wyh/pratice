#pragma once
#include<stdlib.h>
#include<stdio.h>


typedef int QUEUE_TYPE;


typedef struct queuenode
{
	QUEUE_TYPE _front;
	struct queuenode* next;
}queue;


void QueueInit(queue* que);
int QueueEmpty(queue *que);
void QueuePush(queue *que ,QUEUE_TYPE num);
void QueuePop(queue *que);
void QueueDestory(queue *que);
int QueueFront(queue *que);
int QueueBack(queue *que);
int QueueNums(queue* que);

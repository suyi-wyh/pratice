#pragma once
#include<stdlib.h>
#include<stdio.h>


typedef int QUEUE_TYPE;

typedef struct queuenode
{
	QUEUE_TYPE _data;
	struct queuenode* _next;
}queuenode;

typedef struct queue
{
	queuenode* _front;
	queuenode* _tail;
}queue;


queue* QueueInit();
int QueueEmpty(queue *que);
void QueuePush(queue *que ,QUEUE_TYPE num);
void QueuePop(queue *que);
void QueueDestory(queue *que);
queuenode* QueueFront(queue* que);
queuenode* QueueBack(queue *que);
int QueueNums(queue* que);

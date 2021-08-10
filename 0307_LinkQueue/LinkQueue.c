//
// Created by zhanzhao on 2021/8/10.
//

#include "../Status.h"

typedef int QElemType;

typedef  struct QNode{
    QElemType data;
    struct QNode* next;
}QNode,* QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

 Status InitQueue(LinkQueue* Q){
     if(Q == NULL) return ERROR;

     (*Q).front = (*Q).rear = (QueuePtr) malloc(sizeof(QNode));

     if(!(*Q).front) exit(OVERFLOW);

     (*Q).front->next = NULL;

     return OK;
 }
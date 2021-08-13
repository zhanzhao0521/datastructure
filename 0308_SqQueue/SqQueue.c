//
// Created by zhanzhao on 2021/8/13.
//


#include "../Status.h"
/* 宏定义 */
#define MAXQSIZE 1000   //最大队列长度

/* 循环队列元素类型定义 */
typedef int QElemType;

typedef struct{
    QElemType* base; //动态分配存储空间
    int front;       //头指针，若队列不空，指向对头元素
    int rear;        //尾指针，若队列不空，指向队列尾元素的下一个位置
} SqQueue;

/*
 * 初始化
 *
 * 构造一个空的顺序队列。
 * 初始化成功则返回OK，否则返回ERROR。
 *
 *【注】
 * 这里的队列是循环队列
 */
Status InitQueue(SqQueue* Q){
    if(Q == NULL) return ERROR;

    (*Q).base = (QElemType*) malloc(MAXQSIZE * sizeof(QElemType));

    if(!(*Q).base) exit(OVERFLOW);

    (*Q).front = (*Q).rear = 0;

    return OK;
}
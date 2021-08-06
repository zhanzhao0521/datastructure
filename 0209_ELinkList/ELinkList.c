//
// Created by zhanzhao on 2021/8/6.
//

#include "../Status.h"

/*
 * ████ 注意 ████
 *
 * 教材中的线性链表命名为LinkList，
 * 这里为了与单链表区分，故将其命名为ELinkList。
 * 线性链表可以理解成对普通链表的一种扩展。
 */

typedef struct LNode{
    ElemType data;
    struct LNode* next;
} LNode,* Link,* Position;

typedef struct{
    Link head,tail;
    int len;
} ELinkList;

Status MakeNode(Link* p,ElemType e){
    if(p == NULL) return ERROR;

    *p = (Link) malloc(sizeof(LNode));

    if(*p == NULL) return ERROR;

    (*p)->data = e;
    (*p)->next = NULL;

    return OK;
}
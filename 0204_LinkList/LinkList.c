//
// Created by zhanzhao on 2021/4/30.
//
#include "../Status.h"

//理解结构体和结构体标签：https://blog.csdn.net/way88liu/article/details/42043335

//线性表的单链表存储结构
//typedef struct LNode
//{
//    ElemType data;
//    struct LNode *next;
//} LNode;
//typedef struct Node *LinkList ;

typedef struct LNode{
    ElemType data; //数据结点
    struct LNode* next;//指向下一个结点的指针
} LNode, *LinkList;

/*
 * 初始化
 *
 * 只是初始化一个头节点
 * 初始化成功返回OK,否则返回ERROR
 */
Status InitList(LinkList* L) {
    (*L) = (LinkList) malloc(sizeof(LNode));
    if(*L == NULL) {
        exit(OVERFLOW);
    }

    (*L)->next = NULL;

    return OK;
}

/*
 * 销毁(结构)
 *
 * 释放链表所占内存，头结点也会被清理。
 */
Status DestroyList(LinkList* L){
    LinkList p;

    if(L == NULL || *L == NULL)
        return ERROR;

    p = *L;

    while (p){
        p = (*L)->next;
        free(*L);
        (*L) = p;
    }
    *L = NULL;

    return OK;

}

Status ClearList(LinkList L){
    LinkList pre, p;

    if(L == NULL) return ERROR;
    p = L->next;

    while (p){
        pre = p;
        p = p->next;
        free(pre);
    }
    L->next = NULL;

    return OK;
}

/*
 * 判空
 *
 * 判断链表中是否包含有效数据。
 *
 * 返回值：
 * TRUE : 链表为空
 * FALSE: 链表不为空
 */
Status ListEmpty(LinkList L){
    if(L != NULL && L->next == NULL)
        return TRUE;
    else
        return FALSE;
}

/*
 * 计数
 *
 * 返回链表包含的有效元素的数量。
 */
Status ListLength(LinkList L){
    LinkList  p;
    int i;

    if(L == NULL || L->next == NULL)
        return 0;

    i = 0;

    p = L->next;

    while (p){
        i++;
        p = p->next;
    }
    return i;
}

/*
 * 单链表的读取
 *
 * 获得链表第i个数据的算法思路：
 * 1.声明一个指针p指向链表第一个结点，初始化j从1开始
 * 2.当j<i时，就遍历链表，让p的指针向后移动，不断指向下一节点，j累加
 * 3.若到链表末尾p为空，则说明第i个结点不存在
 * 4.否则查找成功，返回结点p的数据
 */
Status GetElem(LinkList L,int i,ElemType *e)
{
    int j;
    LinkList p;
    // 确保链表存在且不为空表
    if(L == NULL || L->next == NULL) {
        return ERROR;
    }

    p = L->next;
    j = 1;
    // 寻找第i个结点，且保证该结点的后继不为NULL
    while (p && j<i)
    {
        p = p->next;
        ++j;
    }
    // 如果遍历到头了，或者i的值不合规(比如i<=0)，说明没找到合乎目标的结点
    if (!p || j>i)
        return ERROR;
    *e = p->data;
    return OK;
}






/*
 *单链表第i个数据插入结点的算法思路：
 * 1.声明一指针p指向链表头结点，初始化j从1开始
 * 2.当j<i时，就遍历链表，让p的指针向后移动，不断指向下一结点，j累计加1
 * 3.若到链表末尾p为空，则说明第i个结点不存在
 * 4.否则查找成功，在系统中生成一个空结点s
 * 5.将数据元素e赋值给s->data
 * 6.单链表的插入标准语句 s->next = p->next; p->next = s;
 */
Status ListInsert(LinkList L,int i,ElemType e)
{
    int j;
    LinkList p,s;

    if(L == NULL) return 0;

    p = L;
    j = 1;
    while (p && j<i)
    {
        p = p->next;
        ++j;
    }



}

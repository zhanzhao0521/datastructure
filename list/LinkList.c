//
// Created by zhanzhao on 2021/4/30.
//
#include "./listtype.h"

//理解结构体和结构体标签：https://blog.csdn.net/way88liu/article/details/42043335

//线性表的单链表存储结构
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *LinkList ;



//单链表的读取
/**
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
    p = L->next;
    j = 1;
    while (p && j<i)
    {
        p = p->next;
        ++j;
    }
    if (!p || j>i)
        return ERROR;
    *e = p->data;
    return OK;
}
/**
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
    p = L;
    j = 1;
    while (p && j<i)
    {
        p = p->next;
    }
}




int main(void)
{
    return 0;
}

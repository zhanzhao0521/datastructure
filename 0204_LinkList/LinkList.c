//
// Created by zhanzhao on 2021/4/30.
//
/*===============================
 * 线性表的链式存储结构（链表）
 *
 * 包含算法: 2.8、2.9、2.10、2.11
 ================================*/
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

    while (p != NULL){
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

    while (p != NULL){
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
    if (p == NULL || j > i)
        return ERROR;
    *e = p->data;
    return OK;
}

/*
 * 查找
 * 返回链表中首个与e相等的元素位序
 * 如果不存在这样的元素，则返回0
 */
int LocateElem(LinkList L,ElemType e){
    int i;
    LinkList p;

    if(L == NULL || L->next == NULL)
       return ERROR;

    i = 1;
    p = L->next;

    while (p && p->data == e){
      i++;
      p = p->next;
    }

    if(p != NULL)
        return i;
    else
        return 0;
}

/*
 * 前驱
 *
 * 获取元素cur_e的前驱，
 * 如果存在，将其存储到pre_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status PriorElem(LinkList L,ElemType cur_e,ElemType* pre_e){
    LinkList pre,next;
    if(L == NULL || L->next == NULL) return ERROR;

    pre = L->next;

    //第一个元素没有前驱
    if(pre->data == cur_e) return ERROR;

    next = pre->next;

    while (next != NULL && next->data != cur_e){
        pre = next;
        next = next->next;
    }
    if(next == NULL) return ERROR;

    *pre_e = pre->data;

    return OK;
}
/*
 * 后继
 *
 * 获取元素cur_e的后继，
 * 如果存在，将其存储到next_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status NextElem(LinkList L,ElemType cur_e,ElemType* next_e){
    LinkList pre;

    // 确保链表存在且不为空表
    if(L == NULL || L->next == NULL) {
        return ERROR;
    }
    pre = L->next;

    while (pre->next != NULL && pre->data != cur_e){
        pre = pre->next;
    }

    // 如果没找到cur_e，或者找到了，但它没有后继，均返回ERROR
    if(pre->next == NULL) return ERROR;


    *next_e = pre->next->data;

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
    while (p !=NULL && j<i)
    {
        p = p->next;
        ++j;
    }

    if(p == NULL || j>j) return ERROR;

    s = (LinkList)malloc(sizeof(LNode));

    if(s == NULL) exit(OVERFLOW);

    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;

}
/*
 * ████████ 算法2.10 ████████
 *
 * 删除
 *
 * 删除链表第i个位置上的元素，并将被删除元素存储到e中。
 * 删除成功则返回OK，否则返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数
 */
Status ListDelete(LinkList L,int i,ElemType* e){
    LinkList p,q;
    int j;

    if(L == NULL || L->next == NULL) return ERROR;

    p = L;
    j = 0;
    // 寻找第i-1个结点，且保证该结点的后继不为NULL
    while (p->next != NULL && j < i-1){
        p = p->next;
        ++j;
    }
    // 如果遍历到头了，或者i的值不合规(比如i<=0)，说明没找到合乎目标的结点
    if(p->next == NULL || j > i - 1 ) return ERROR;

    //删除第i个结点
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);

    return OK;

}

//遍历
void ListTraverse(LinkList L,void(Visit)(ElemType)){
    LNode* p;

    if(L == NULL || L->next == NULL) return;

    p = L->next;

    while (p != NULL){
        Visit(p->data);
        p = p->next;
    }
    printf("\n");
}

/*
 * 头插法创建结点
 */
Status CreateList_Head(LinkList* L, int n){
    int i;
    LinkList p;
    //建立头节点
    *L = (LinkList) malloc(sizeof(LNode));
    (*L)->next = NULL;
    printf("请输入%d个降序元素：",n);
    for (i = 1; i <= n; ++i) {
        //生成新节点
        p = (LinkList) malloc(sizeof(LNode));
        scanf("%d",&(p->data));
        p->next = (*L)->next;
        (*L)->next = p;
    }
    return OK;
}
/*
 * 尾插法创建链表
 */
Status CreateList_Tail(LinkList* L,int n){
    int i;
    LinkList p,q;

    *L = (LinkList) malloc(sizeof(LNode));
    (*L)->next = NULL;

    q = *L;

    printf("请输入%d个升序元素：", n);

    for (i = 1; i <= n ; ++i) {
        p = (LinkList) malloc(sizeof(LNode));
        scanf("%d",&(p->data));
        q->next = p;
        q = q->next;
    }
    q->next = NULL;
    return OK;

}
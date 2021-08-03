//
// Created by zhanzhao on 2021/7/29.
//

/*=====================
 * 双向循环链表
 *
 * 包含算法: 2.18、2.19
 ======================*/
#include "../Status.h"

/*
 * 双向循环链表结构
 *
 * 注：这里的双向循环链表存在头结点
 */
typedef struct DuLNode{
    ElemType data;
    struct DuLNode* prior;//前驱
    struct DuLNode* next;//后继
} DuLNode,*DuLinkList;
/*
 * 初始化
 *
 * 初始化成功则返回OK，否则返回ERROR。
 */
Status InitList(DuLinkList* L){
    *L = (DuLinkList) malloc(sizeof(DuLNode));
    if(*L == NULL) exit(OVERFLOW);

    (*L)->next = (*L)->prior = *L;

    return OK;
}
/*
 * 置空(内容)
 *
 * 这里需要释放双向循环链表中非头结点处的空间。
 */
Status ClearList(DuLinkList L){
    DuLinkList p,q;

    if(L == NULL) return ERROR;

    p = L->next;

    while (p != L){
        q = p->next;
        free(p);
        p = q;
    }

    L->next = L->prior = L;
    return OK;
}

/*
 * 销毁(结构)
 *
 * 释放双向循环链表所占内存。
 */
Status DestroyList(DuLinkList* L){
    if(L == NULL || *L == NULL)
        return ERROR;

    ClearList(*L);

    free(*L);

    *L = NULL;

    return OK;
}
/*
 * 判空
 *
 * 判断双向循环链表中是否包含有效数据。
 *
 * 返回值：
 * TRUE : 双向循环链表为空
 * FALSE: 双向循环链表不为空
 */
Status ListEmpty(DuLinkList L){
    if(L != NULL && L->next == L && L->prior == L)
        return TRUE;
    else
        return FALSE;
}
/*
 * 计数
 *
 * 返回双向循环链表包含的有效元素的数量。
 */
int ListLength(DuLinkList L){
    DuLinkList p;
    int i;
    if(L == NULL || L->next == NULL || L->prior == L) return 0;

    i = 0;

    p = L->next;

    while (p != L){
        i++;
        p = p->next;
    }

    return i;
}


/*
 * 取值
 *
 * 获取双向循环链表中第i个元素，将其存储到e中。
 * 如果可以找到，返回OK，否则，返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数，但这不符合编码的通用约定。
 * 通常，i的含义应该指索引，即从0开始计数。
 */
Status GetElem(DuLinkList L,int i,ElemType* e){
    DuLinkList p;
    int j;
    if(L == NULL || L->next == L || L->prior == L ) return ERROR;

    p = L;
    j = 0;

    while (p->next != L && j < i-1){
        p = p->next;
        ++j;
    }

    if( p->next == L || j > i-1 ) return ERROR;

    *e = p->next->data;

    return OK;
}


/*
 * 查找
 *
 * 返回双向循环链表中首个与e满足相等关系的元素位序。
 * 如果不存在这样的元素，则返回0。
 *
 *【备注】
 * 元素e是Compare函数第二个形参
 */
int LocateElem(DuLinkList L,ElemType e){

    int i;
    DuLinkList p;

    if(L == NULL || L->next == L || L->prior == L) return 0;

    i = 1;
    p = L->next;

    while (p != L && !(p->data == e)){
        i++;
        p = p->next;
    }

    if(p != L) return i;
    else return 0;

}
/*
 * 前驱
 *
 * 获取元素cur_e的前驱，
 * 如果存在，将其存储到pre_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status PriorElem(DuLinkList L,ElemType cur_e,ElemType* pre_e){
    DuLinkList p;
    // 确保双向循环链表存在
    if(L == NULL || L->next == L || L->prior == L) {
        return ERROR;
    }
    p = L->next;

    // 第一个元素没有前驱
    if(p->data == cur_e) return ERROR;

    p = p->next;

    while (p != L && p->data != cur_e)
        p = p->next;

    if(p == L) return ERROR;

    *pre_e = p->next->data;

    return OK;
}
/*
 * 后继
 *
 * 获取元素cur_e的后继，
 * 如果存在，将其存储到next_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status NextElem(DuLinkList L,ElemType cur_e,ElemType* next_e){
    DuLinkList p;

    if(L == NULL || L->next == L || L->prior == L)
        return ERROR;

    p = L->next;

    while (p->next != L && p->data != cur_e)
        p = p->next;

    if(p->next == L)
        return ERROR;

    *next_e = p->next->data;

    return OK;
}


/*
 * ████████ 算法2.18 ████████
 *
 * 插入
 *
 * 向双向循环链表第i个位置上插入e，插入成功则返回OK，否则返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数
 */
Status ListInsert(DuLinkList L,int i,ElemType e ){
    DuLinkList p,s;

    if(L == NULL) return ERROR;

    if((p = GetElem(L,i)) == NULL) return ERROR;

    s = (DuLinkList) malloc((sizeof(DuLNode)));

    if(s == NULL) exit(OVERFLOW);

    s->data = e;

    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;

    return  OK;

}

/*
 * 获取循环链表L上第i个元素的引用
 */
DuLinkList GetEleP(DuLinkList L,int i){
    DuLinkList  p;
    int count;

    if(L == NULL) return NULL;

    if(i<1) return NULL;

    p = L;
    count=0;

    while ( p->next != L && count <i ){
        p = p->next;
        ++count;
    }

    if(count == i)
        return p;

    if( count + 1 < i) return NULL;

    return L;
}
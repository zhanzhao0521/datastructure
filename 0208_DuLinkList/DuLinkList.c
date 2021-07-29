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
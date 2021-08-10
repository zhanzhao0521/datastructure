//
// Created by zhanzhao on 2021/8/6.
//
/*=======================
 * 扩展的单链表（线性链表）
 *
 * 包含算法: 2.20
 ========================*/
#include "../Status.h"
#include "limits.h"

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

/*
 * 内存分配
 *
 * 为线性链表申请一个结点，并存入指定的数据e。
 */
Status MakeNode(Link* p,ElemType e){
    if(p == NULL) return ERROR;

    *p = (Link) malloc(sizeof(LNode));

    if(*p == NULL) return ERROR;

    (*p)->data = e;
    (*p)->next = NULL;

    return OK;
}
/*
 * 内存回收
 *
 * 释放线性链表中指定的结点。
 */
void FreeNode(Link* p){
    if(p == NULL || *p == NULL)
        return;

    free(*p);

    *p = NULL;
}


/*
 * 初始化
 *
 * 初始化成功则返回OK，否则返回ERROR。
 */
Status InitList(ELinkList* L){
    Link p;

    if(L == NULL) return ERROR;

    p = (Link) malloc(sizeof(LNode));

    if(p == NULL) exit(OVERFLOW);

    p->next = NULL;

    (*L).head = (*L).tail = p;
    (*L).len = 0;

    return OK;
}

Status ClearList(ELinkList* L){
    Link p,q;

    if(L == NULL || (*L).head == NULL || (*L).len<=0) return ERROR;

    p = (*L).head->next;

    while (p != NULL){
        q = p->next;
        free(p);
        p = q;
    }

    (*L).head->next = NULL;
    (*L).tail = (*L).head;
    (*L).len = 0;

    return OK;

}


Status DestroyList(ELinkList* L){
    if(L == NULL || (*L).head == NULL) return ERROR;

    ClearList(L);
    free((*L).head);
    (*L).head = (*L).tail = NULL;

    return OK;

}

Status ListEmpty(ELinkList L){
    return L.len <= 0 ? TRUE : FALSE;
}


int ListLength(ELinkList L){
    return L.len;
}


Position LocateElem(ELinkList L,ElemType e){
    Position p;

    if(L.len <= 0) return NULL;

    p = L.head->next;

    while (p != NULL && p->data != e){
        p = p->next;
    }
    return p;
}

/*
 * 查找
 *
 * 查找链表L中第i(允许为0)个结点，并将其引用存入p，且返回OK
 * 如果i值不合规，则返回ERROR
 * 特别注意，当i为0时，p存储的是头结点的引用
 */
Status LocatePos(ELinkList L,int i,Link *p){
    int j;
    Link r;
    if(i < 0 || i>L.len) return ERROR;

    if(L.head == NULL) return ERROR;

    if(i == 0){
        *p = L.head;
        return OK;
    }
    j = 0;
    r = L.head;

    while (r != NULL && j < i){
        j++;
        r = r->next;
    }

    if( r == NULL) return ERROR;

    *p = r;

    return OK;
}

/*
 * 插入
 *
 * 将s结点插入到h结点后面，成为h后面的第一个结点
 *
 *【备注】
 * 教材中对于该方法的描述有些问题，这里是修正过的版本
 */
Status InsFirst(ELinkList* L,Link h,Link s){

    if(L == NULL || (*L).head == NULL || h == NULL || s == NULL)
        return ERROR;

    s->next = h->next;
    h->next = s;

    if(h == (*L).tail)
        (*L).tail = h->next;

    (*L).len++;

    return OK;

}

/*
 * 删除
 *
 * 删除h结点后的第一个结点，并用q存储被删除结点的引用
 *
 *【备注】
 * 教材中对于该方法的定义略显粗糙，这里是修正过的版本
 */
Status DelFirst(ELinkList* L,Link h,Link* q){
    if(L == NULL || (*L).head == NULL || h == NULL || q == NULL)
        return ERROR;

    if(h->next == NULL)
        return ERROR;

    *q = h->next;

    h->next = (*q)->next;

    (*q)->next = NULL;

    if(h->next == NULL)
        (*L).tail = h;

    (*L).len--;

    return OK;
}
/*
 * 前向插入
 *
 * 将s结点插入到p结点之前，并将p指向新结点
 */
Status InsBefore(ELinkList* L,Link* p,Link s){
    Link pre;

    if(L == NULL || (*L).head == NULL || p == NULL || s == NULL) return ERROR;

    pre = (*L).head;

    while (pre != NULL && pre->next != (*p))
        pre = pre->next;
    if(pre == NULL) return ERROR;

    s->next = *p;
    pre->next = s;
    *p = s;
    (*L).len++;

    return OK;
}


/*
 * 后向插入
 *
 * 将s结点插入到p结点之前，并将p指向新结点
 */
Status InsAfter(ELinkList* L,Link *p,Link s){
    Link r;

    if(L == NULL || (*L).head == NULL || p == NULL  || s == NULL) return ERROR;


    r = (*L).head;

    while ( r != NULL && r != (*p) )
        r = r->next;

    if(r == NULL) return ERROR;

    if(*p == (*L).tail)
        (*L).tail = s;

    s->next = (*p)->next;
    (*p)->next = s;
    *p = s;

    (*L).len++;
    return OK;

}
/*
 * 向尾部添加
 *
 * 将s所指的一串结点链接在链表L后面
 */
Status Append(ELinkList* L,Link s){
    int count;

    if(L == NULL || (*L).head == NULL || s == NULL)
        return ERROR;

    count = 0;
    (*L).tail->next = s;

    while (s != NULL){
        (*L).tail = s;
        s = s->next;
        count++;
    }

    (*L).len += count;
    return OK;
}


/*
 * 从尾部移除
 *
 * 将链表的尾结点移除，并将被移除的结点引用存储在q中
 */
Status Remove(ELinkList* L,Link* q){
    Link p;

    if(L == NULL || (*L).head == NULL || q == NULL) return ERROR;

    if((*L).len == 0){
        *q = NULL;
        return ERROR;
    }

    *q = (*L).tail;

    p = (*L).head;

    while (p->next != (*L).tail)
        p = p->next;

    p->next = NULL;
    (*L).tail = p;

    (*L).len--;

    return OK;
}

/*
 * ████████ 算法2.20 ████████
 *
 * 插入
 *
 * 向链表第i个位置上插入e，插入成功则返回OK，否则返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数
 * 可以看做是算法2.9的改写
 */
Status ListInsert(ELinkList* L,int i,ElemType e){
    Link h,s;

    if(L == NULL || (*L).head == NULL) return ERROR;
    // 确保i值合规[1, len+1]
    if(i<1 || i>(*L).len+1) return ERROR;
    // 查找第i-1个元素的引用，存储在h中
    if(LocatePos(*L,i-1, &h) == ERROR) return ERROR;
    // 分配新结点s
    if(MakeNode(&s,e) == ERROR) return ERROR;
    // 将s结点插入到h结点后面，成为h后面的第一个结点
    if(InsFirst(L,h,s) == ERROR)  return ERROR;

    return OK;

}


/*
 * 删除
 *
 * 删除链表第i个位置上的元素，并将被删除元素存储到e中。
 * 删除成功则返回OK，否则返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数
 * 可以看做是算法2.10的改写
 */
Status ListDelete(ELinkList* L,int i,ElemType* e){
    Link h,q;

    if(L == NULL || (*L).head == NULL)
        return ERROR;

    if(i < 1 || i > (*L).len) return ERROR;

    if(LocatePos(*L,i-1,&h) == ERROR)
        return ERROR;

    if(DelFirst(L,h,&q) == ERROR ) return ERROR;

    *e = q->data;

    FreeNode(&q);

    return OK;

}

void ListTraverse(ELinkList L,void(Visit)(ElemType)){
    Link p;

    if(L.len <= 0 ) return;

    p = L.head->next;

    while (p != NULL){
        Visit(p->data);
        p = p->next;
    }
    printf("\n");
}

/*━━━━━━━━━━━━━━━━━━━━━━ 链表扩展操作 ━━━━━━━━━━━━━━━━━━━━━━*/

/*
 * 取值
 *
 * 获取结点p的元素值。
 */
ElemType GetCurElem(Link p){
    if(p == NULL) return INT_MIN;

    return p->data;
}

/*
 * 设值
 *
 * 为结点p设置元素值。
 */
Status SetCurElem(Link p,ElemType e){
    if(p == NULL) return ERROR;

    p->data = e;

    return OK;
}

/*
 * 头结点
 *
 * 获取头结点引用。
 */
Position GetHead(ELinkList L){
    return L.head;
}
/*
 * 尾结点
 *
 * 获取尾结点引用。
 */
Position GetLast(ELinkList L){
    return L.tail;
}


/*
 * 前驱
 *
 * 获取结点p的前驱，如果不存在，则返回NULL。
 */
Position PriorPos(ELinkList L,Link p){
    Link pre;

    if(L.head == NULL) return NULL;


    if(p == NULL) return NULL;

    pre = L.head;

    if(pre->next == p) return NULL;
    // 第一个结点无前驱
    while (pre != NULL && pre->next != p){
        pre = pre->next;
    }

    return pre;

}

/*
 * 后继
 *
 * 获取结点p的后继，如果不存在，则返NULL。
 */
Position NextPos(ELinkList L,Link p){

    if(L.head == NULL || p ==  NULL) return NULL;

    return p->next;
}
//
// Created by zhanzhao on 2021/4/30.
//
/*=============================
 * 线性表的顺序存储结构（顺序表）
 *
 * 包含算法: 2.3、2.4、2.5、2.6
 =============================*/
#include "../Status.h"
/**
 * 线性表
 * 优点：
 *  无须为表示表中元素之间的逻辑关系而增加额外的存储空间
 *  可以快速地存取表中任一位置的元素
 * 缺点：
 *  插入和删除操作需要移动大量元素
 *  当线性表长度变化较大时，难以确定存储空间的容量
 *  造成存储空间的“碎片”
 *
 */

//线性表的顺序存储结构
typedef struct{
    ElemType* data;
    int length;
} SqList;

//初始化线性表
Status InitList(SqList* L){
    L->data = (ElemType*) malloc( sizeof(ElemType) * MAXSIZE);
    if(!L->data) exit(OVERFLOW);
    L->length = 0;
    return OK;
}

//销毁线性表
Status DestroyList(SqList *L)
{
    if (L == NULL || L->data == NULL) return ERROR;
    free(L->data);//释放存储空间
    L->data = NULL;
    L->length = 0;
    return OK;
}
//清空线性表
Status ClearList(SqList *L)
{
    //确保顺序结构存在
    if (L == NULL || L->data == NULL) return ERROR;
    L->length = 0;
    return OK;
}
//求线性表的长度
int ListLength(SqList L)
{
    return L.length;
}

//判空
int ListEmpty(SqList L)
{
    return L.length == 0 ? TRUE : FALSE;
}

/*
 * 取值
 *
 * 获取顺序表中第i个元素，将其存储到e中。
 * 如果可以找到，返回OK，否则，返回ERROR。
 *
 *【备注】
 * 教材中i的含义是元素位置，从1开始计数，但这不符合编码的通用约定。
 * 通常，i的含义应该指索引，即从0开始计数。
 *
 */
Status GetElem(SqList L, int i, ElemType* e)
{

    //因为i的含义是位置，所以其合法范围为[i,length]
    if(i < 1 || i > L.length) return ERROR;
    *e = L.data[i - 1];
    return OK;
}
//顺序表的查找
//平均查找长度ASL(Average Search Length)期望值
//如果不存在这样的元素，则返回0。
int LocateElem(SqList L,ElemType e)
{
    int i;
    for (int i = 0; i < L.length; i++)
        if(L.data[i] == e) return i+1;//查找成功，返回序号
    return ERROR;
}


/*
 * 插入算法的思路：
 * 1.如果插入位置不合理，抛出异常；
 * 2.如果线性表长度大于等于数组长度，则抛出异常或动态增加容量
 * 3.从最后一个元素开始向前遍历到第i个位置，分别将他们都向后移动一个位置；
 * 4.将要插入元素填入位置i处
 * 表长加1
 */
//插入操作--不扩容版本
Status ListInsert(SqList* L,int i,ElemType e){
    int k;
    if(L->length == MAXSIZE) return ERROR;
    if(i < 1 || i > L->length + 1) return ERROR;

    for ( k=L->length-1; k >= i-1; k--)
        L->data[k+1] = L->data[k];
    L->data[i-1] = e;
    L->length++;
    return OK;
}
/*
 * 删除算法的思路：
 * 1.如果删除位置不合理，抛出异常；
 * 2.取出删除元素
 * 3.从删除元素位置开始遍历到最后一个元素位置，分别将它们都向前移动一个位置
 * 4.表长减1
 */
//删除操作
Status ListDelete(SqList* L,int i,ElemType* e){
    int k;
    // 确保顺序表结构存在
    if(L->length == 0)  return ERROR;

    // i值越界
    if(i < 1 || i > (*L).length)   return ERROR;

    *e = L->data[i-1];
    if(i<L->length)
        for (k = i; k < L->length; k++)
            L->data[k-1] = L->data[k];
    L->length--;
    return OK;
}

Status ListTraverse(SqList L, void(Visit)(ElemType) ){
    int i;
    for(i = 0; i < L.length; i++) {
        Visit(L.data[i]);
    }
    printf("\n");
}
/*
 * 前驱
 *
 * 获取元素cur_e的前驱，
 * 如果存在，将其存储到pre_e中，返回OK，
 * 如果不存在，则返回ERROR。
 */
Status PriorElem(SqList L,ElemType cur_e,ElemType* pre_e){
    int i;

    if(L.data == NULL || L.length<2)
        return ERROR;

    i = 0;

    while (i < L.length && L.data[i] != cur_e)
        ++i;

    if(i == 0 || i>=L.length)
        return ERROR;

    *pre_e = L.data[i-1];

    return OK;
}

Status NextElem(SqList L,ElemType cur_e,ElemType* next_e){
    int i;

    if(L.data == NULL || L.length<2)
        return ERROR;

    i = 0;

    while (i < L.length-1 && L.data[i] != cur_e)
        ++i;
    // 如果cur_e是最后1个元素(没有前驱)，或者没找到元素cur_e，返回ERROR
    if( i >= L.length-1 )
        return ERROR;
    *next_e = L.data[i+1];
    return OK;
}
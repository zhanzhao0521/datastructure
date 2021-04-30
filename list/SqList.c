//
// Created by zhanzhao on 2021/4/30.
//
#include "./listtype.h"
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
typedef struct
{
    ElemType *data;
    int length;
} SqList;


//初始化线性表
Status InitList(SqList *L)
{
    L->data = (ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    if (!L->data) exit(OVERFLOW);
    L->length = 0;
    return OK;
}

//销毁线性表
void DestroyList(SqList *L)
{
    if (L->data)
        free(L->data);//释放存储空间
}
//清空线性表
void ClearList(SqList *L)
{
    L->length = 0;
}
//求线性表的长度
int ListLength(SqList L)
{
    return L.length;
}

int ListEmpty(SqList L)
{
    if (L.length == 0 )
        return TRUE;
    else
        return FALSE;
}


//获得第i个位置的元素
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length == 0 || i<1 || i>L.length)
        return ERROR;
    *e = L.data[i-1];
    return OK;
}

//顺序表的查找
//平均查找长度ASL(Average Search Length)期望值
int LocateElem(SqList L,ElemType e)
{
    int i;
    for (i = 0; i < L.length; i++)
        if (L.data[i] == e) return i+1;//查找成功，返回序号
    return ERROR;
}


/**
 * 插入算法的思路：
 * 1.如果插入位置不合理，抛出异常；
 * 2.如果线性表长度大于等于数组长度，则抛出异常或动态增加容量
 * 3.从最后一个元素开始向前遍历到第i个位置，分别将他们都向后移动一个位置；
 * 4.将要插入元素填入位置i处
 * 表长加1
 */
//插入操作
Status ListInsert(SqList *L,int i,ElemType e)
{
    int k;
    if(L->length == MAXSIZE)
        return ERROR;
    if(i<1 || i>L->length+1)
        return ERROR;
    if(i<=L->length)
    {
        for(k=L->length-1;k>=i-1;k--)
            L->data[k+1] = L->data[k];
    }
    L->data[i-1] = e;
    L->length++;
    return OK;
}
/**
 * 删除算法的思路：
 * 1.如果删除位置不合理，抛出异常；
 * 2.取出删除元素
 * 3.从删除元素位置开始遍历到最后一个元素位置，分别将它们都向前移动一个位置
 * 4.表长减1
 */
//删除操作
Status ListDelete(SqList *L,int i,ElemType *e)
{
    int k;
    if(L->length == 0)
        return ERROR;
    if(i<1 || i>L->length)
        return ERROR;
    *e = L->data[i-1];
    if(i<L->length){
        for(k=i;k<L->length;k++)
            L->data[k-1] = L->data[k];
    }
    L->length--;
    return OK;
}


int main(void)
{
    return 0;
}
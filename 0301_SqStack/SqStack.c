//
// Created by zhanzhao on 2021/8/10.
//

/*=========================
 * 栈的顺序存储结构（顺序栈）
 ==========================*/

/* 宏定义 */
#define STACK_INIT_SIZE 100     // 顺序栈存储空间的初始分配量
#define STACKINCREMENT  10      // 顺序栈存储空间的分配增量

#include "../Status.h"

/* 顺序栈元素类型定义 */
typedef int SElemType;
// 顺序栈元素结构
typedef struct{
    SElemType* base;
    SElemType* top;
    int stacksize;
}SqStack;

/*
 * 初始化
 *
 * 构造一个空栈。初始化成功则返回OK，否则返回ERROR。
 */
Status InitStack(SqStack* S){
    if(S == NULL) return ERROR;

    (*S).base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof (SElemType));
    if((*S).base == NULL) exit(OVERFLOW);

    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;

    return OK;
}

/*
 * 销毁(结构)
 *
 * 释放顺序栈所占内存。
 */
Status DestroyStack(SqStack* S){
    if(S == NULL) return ERROR;

    free((*S).base);

    (*S).base = NULL;
    (*S).top = NULL;
    (*S).stacksize = 0;

    return OK;
}
/*
 * 置空(内容)
 *
 * 只是清理顺序栈中存储的数据，不释放顺序栈所占内存。
 */
Status ClearStack(SqStack* S){
    if(S == NULL || (*S).base == NULL) return ERROR;

    (*S).top = (*S).base;

    return OK;
}
/*
 * 判空
 *
 * 判断顺序栈中是否包含有效数据。
 *
 * 返回值：
 * TRUE : 顺序栈为空
 * FALSE: 顺序栈不为空
 */
Status StackEmpty(SqStack S){
    if(S.top == S.base) return TRUE;
    else return FALSE;
}

int StackLength(SqStack S){
    if(S.base == NULL)return 0;
    return (int)(S.top - S.base);
}

/*
 * 取值
 *
 * 返回栈顶元素，并用e接收。
 */
Status GetTop(SqStack S,SElemType* e){
    if(S.base == NULL || S.base == S.top) return 0;

    *e = *(S.top - 1);

    return OK;
}

/*
 * 入栈
 *
 * 将元素e压入到栈顶。
 */
Status Push(SqStack* S,SElemType e){
    if(S == NULL || (*S).base == NULL) return ERROR;
    // 栈满时，追加存储空间
    if((*S).top - (*S).base >= (*S).stacksize){
        (*S).base = (SElemType*) realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
        if((*S).base == NULL) exit(OVERFLOW);

        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }

    // 进栈先赋值，栈顶指针再自增
    *(S->top++) = e;
    //等于
    //*(S->top) = e;
    //S->top++;
    return OK;
}

/*
 * 出栈
 *
 * 将栈顶元素弹出，并用e接收。
 */
Status Pop(SqStack* S,SElemType* e){
    if(S == NULL || (*S).base == NULL) return ERROR;

    if((*S).top == (*S).base) return ERROR;
    // 出栈栈顶指针先递减，再赋值
    *e =*(--S->top);

    return OK;
}

/*
 * 遍历
 *
 * 用visit函数访问顺序栈S
 */
Status StackTraverse(SqStack S,void(Visit)(SElemType)){
    SElemType* p = S.base;
    if(S.base == NULL)return ERROR;

    while (p < S.top){
        Visit(*p++);
    }
    printf("\n");
    return OK;
}

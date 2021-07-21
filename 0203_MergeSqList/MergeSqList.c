//
// Created by zhanzhao on 2021/7/21.
//

#include "../0201_SqList/SqList.c"

/*
 * ████████ 算法2.2 ████████
 *
 * 非递减链表归并：C=A+B
 *
 * 归并顺序表La和Lb，生成新的顺序表Lc。
 * 其中，La、Lb、Lc均为非递减序列。
 */
void MergeSqList(SqList La,SqList Lb,SqList* Lc){
    int La_len,Lb_len;
    int i,j,k;
    ElemType ai,bj;

    i = j = 1;
    k = 0;

    InitList(Lc);

    La_len = ListLength(La);
    Lb_len = ListLength(Lb);

    // 如果La及Lb均未遍历完
    while(i <= La_len && j <= Lb_len) {
        GetElem(La, i, &ai);
        GetElem(Lb, j, &bj);

        // 比较遍历到的元素，先将比较小的元素加入顺序表Lc
        if(ai <= bj) {
            ListInsert(Lc, ++k, ai);
            i++;
        } else {
            ListInsert(Lc, ++k, bj);
            j++;
        }
    }

    // 如果Lb已遍历完，但La还未遍历完，将La中剩余元素加入Lc
    while(i <= La_len) {
        GetElem(La, i++, &ai);
        ListInsert(Lc, ++k, ai);
    }

    // 如果La已遍历完，但Lb还未遍历完，将Lb中剩余元素加入Lc
    while(j <= Lb_len) {
        GetElem(Lb, j++, &bj);
        ListInsert(Lc, ++k, bj);
    }

}
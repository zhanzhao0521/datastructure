//
// Created by zhanzhao on 2021/7/22.
//

#include "stdio.h"
#include "MergeList.c"

int main(int argc, char** argv) {
    LinkList La, Lb, Lc;

    int n = 5;

    printf("作为示例，La长度设定为 %d ，Lb长度设定为 %d ，创建La和Lb...\n", n, n);

    CreateList_Head(&La, n);
    printf("La = ");
    ListTraverse(La, PrintElem);

    CreateList_Tail(&Lb, n);
    printf("Lb = ");
    ListTraverse(Lb, PrintElem);

    printf("归并La和Lb为Lc = ");
    MergeList(&La, &Lb, &Lc);
    ListTraverse(Lc, PrintElem);

    return 0;
}


//
// Created by zhanzhao on 2021/7/21.
//

#include "../0201_SqList/SqList.c"

void Union(SqList* La,SqList Lb){
    int La_len,Lb_len;
    int i;
    ElemType e;

    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);

    for (i = 1; i <= Lb_len; i++) {
        GetElem(Lb,i,&e);

        if(!LocateElem(*La,e))
            ListInsert(La,++La_len,e);
    }
}
//
// Created by zhanzhao on 2021/8/10.
//

#include "../0209_ELinkList/ELinkList.c"


Status MergeEList(ELinkList* La,ELinkList* Lb,ELinkList* Lc,int(Compare)(ElemType,ElemType)){
    Link ha,hb,pa,pb,q;
    ElemType a,b;

    if(InitList(Lc) == ERROR) return ERROR;

    ha = GetHead(*La);
    hb = GetHead(*Lb);

    if(ha == NULL || hb == NULL) return ERROR;

    pa = NextPos(*La,ha);
    pb = NextPos(*La,hb);

    while (pa != NULL && pb != NULL){
        a = GetCurElem(pa);
        b = GetCurElem(pb);

        // 如果La<=Lb
        if(Compare(a, b)<=0) {
            // 摘下La中首个元素
            DelFirst(La, ha, &q);

            // 将上述摘下的元素追加到Lc中
            Append(Lc, q);

            // 依然是获取La中第1个元素
            pa = NextPos(*La, ha);
        } else {
            // 摘下Lb中首个元素
            DelFirst(Lb, hb, &q);

            // 将上述摘下的元素追加到Lc中
            Append(Lc, q);

            // 依然是获取La中第1个元素
            pb = NextPos(*Lb, hb);
        }
    }

    if(pa!=NULL){
        Append(Lc,pa);
    } else{
        Append(Lc,pb);
    }

    FreeNode(&(La->head));
    FreeNode(&(Lb->head));

    La->tail = NULL;
    Lb->tail = NULL;

    La->len = 0;
    Lb->len = 0;

    return OK;
}
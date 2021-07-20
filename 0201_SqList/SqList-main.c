#include <stdio.h>
#include "SqList.c"                                //**02 线性表**//

// 判断data>e是否成立
Status CmpGreater(ElemType data, ElemType e) {
    return data > e ? TRUE : FALSE;
}

int main(int argc, char** argv) {
    SqList L;   // 待操作的顺序表

    int i;
    ElemType e;

    printf("████████▉ InitList \n");
    {
        printf("█ 初始化顺序表 L ...\n");
        InitList(&L);
    }
    PressEnterToContinue();


    printf("█████████ ListEmpty \n");
    {
        ListEmpty(L) ? printf("█ L 为空！！\n") : printf("█ L 不为空！\n");
    }
    PressEnterToContinue();


    printf("█████████ ListInsert \n");
    {
        for (i = 1;  i<=8 ; i++) {
            printf("█ 作为示范，在 L 第 %d 个位置插入\"%d\"...\n",i,2*i);
            ListInsert(&L,i,2 * i);
        }
    }
    PressEnterToContinue();


    printf("█████████ ListEmpty \n");
    {
        ListEmpty(L) ? printf("█ L 为空！！\n") : printf("█ L 不为空！\n");
    }
    PressEnterToContinue();


    printf("█████████ ListTraverse \n");
    {
        printf("█ L 中的元素为：L = ");
        ListTraverse(L,PrintElem);
    }
    PressEnterToContinue();


    printf("█████████ ListLength \n");
    {
        i = ListLength(L);
        printf("█ L 的长度为 %d \n",i);
    }
    PressEnterToContinue();


    printf("█████████ ListDelete \n");
    {
        printf("█ 删除前的元素：L = ");
        ListTraverse(L,PrintElem);

        printf("█ 尝试删除 L 中第 6 个元素...\n");
        if(ListDelete(&L,6,&e) == OK)
            printf("删除成功，被删除的元素是：\"%d\"\n",e);
        else
            printf("删除失败，第 6 个元素不存在！\n");
        printf("█ 删除后的元素：L = ");
        ListTraverse(L,PrintElem);
    }
    PressEnterToContinue();

    printf("████████ GetElem \n");
    {
        GetElem(L,4,&e);
        printf("█ L 中第 4 个位置的元素为 \"%d\" \n",e);
    }
    PressEnterToContinue();


    printf("███████ LocateElem \n");
    {
        int k = getchar();
        i = LocateElem(L,k);
        if(i>0)
            printf("元素 %d 在 L 序号为：%d 的位置 \n",k,i);
        else
            printf("在L上没有找到 \"%d\" 元素\n",k);
    }
    PressEnterToContinue();
    return 0;
}

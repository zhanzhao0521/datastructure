#include <stdio.h>
#include <string.h>         // 提供 strstr 原型
#include "MergeEList.c"     //**▲02 线性表**//


/*
 * 比较
 *
 * 比较e1和e2的大小，返回值含义如下：
 *  < 0：e1 < e2
 *  = 0：e1 = e2
 *  > 0：e1 > e2
 */
int Cmp(ElemType e1, ElemType e2) {
    return e1 - e2;
}

/*
 * 尾插法创建链表
 *
 *
 *【备注】
 *
 * 这里为了方便测试，避免每次运行都手动输入数据，
 * 因而允许选择从预设的文件path中读取测试数据。
 *
 * 如果需要从控制台读取数据，则path为NULL或者为空串，
 * 如果需要从文件中读取数据，则需要在path中填写文件名信息。
 */
void CreateList_Tail(ELinkList* L) {
    int i, n;
    ElemType e;

    // 读取指定集合中元素的数量
    printf("请输入元素数量：");
    scanf("%d", &n);

    InitList(L);

    printf("请输入 %d 个元素：", n);
    for(i = 1; i <= n; i++) {
        scanf("%d", &e);
        ListInsert(L, i, e);
    }

}


int main(int argc, char** argv) {
    ELinkList La, Lb, Lc;
    
    printf("创建La和Lb以待测试...\n");
    
    CreateList_Tail(&La);
    printf("La= ");
    ListTraverse(La, PrintElem);
    
    CreateList_Tail(&Lb);
    printf("Lb= ");
    ListTraverse(Lb, PrintElem);
    
    MergeEList(&La, &Lb, &Lc, Cmp);
    printf("合并La和Lb为 Lc = ");
    ListTraverse(Lc, PrintElem);
    
    return 0;
}

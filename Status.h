//
// Created by zhanzhao on 2021/4/30.
//

#ifndef DATASTRUCTURE_STATUS_H
#define DATASTRUCTURE_STATUS_H

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;
/* 布尔类型 */
typedef int Boolean;
Boolean debug = TRUE;
void PressEnterToContinue() {
    fflush(stdin);

    // 处于测试阶段时，可以让debug=TRUE，手动输入换行，以便让程序暂停下来，观察每一步的输出
    if(debug) {
        printf("\nPress Enter to Continue...");
        getchar();

        // 发布时，可以让debug=FALSE，自动添加换行，直接出结果
    } else {
        printf("\n");
    }

    fflush(stdin);
}
void PrintElem(ElemType e) {
    printf("%d ", e);
}

#endif //DATASTRUCTURE_STATUS_H

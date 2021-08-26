//
// Created by zhanzhao on 2021/8/10.
//
#include "../0209_ELinkList/ELinkList.c"

typedef ELinkList Polynomial;

typedef struct {
    float coef;     // 多项式系数
    int expn;       // 多项式指数
} Elem;         // 重新定义扩展的线性表中元素类型

/*━━━━━━━━━━━━━━━━━━━━━━ 一元多项式操作 ━━━━━━━━━━━━━━━━━━━━━━*/

/*
 * ████████ 算法2.22 ████████
 *
 * 创建
 *
 * 根据输入的系数和指数，创建项数为m的一元多项式
 *
 *
 *【备注】
 *
 * 教材中默认从控制台读取数据。
 * 这里为了方便测试，避免每次运行都手动输入数据，
 * 因而允许选择从预设的文件path中读取测试数据。
 *
 * 如果需要从控制台读取数据，则path为NULL或者为空串，
 * 如果需要从文件中读取数据，则需要在path中填写文件名信息。
 */

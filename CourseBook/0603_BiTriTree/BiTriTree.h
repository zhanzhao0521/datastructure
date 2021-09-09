//
// Created by zhanzhao on 2021/9/7.
//

#ifndef CLION_BITRITREE_H
#define CLION_BITRITREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Status.h"

typedef char TElemType;

typedef struct BiTriTNode{
    TElemType data;
    struct BiTriTNode* lchild;
    struct BiTriTNode* rchild;
    struct BiTriTNode* parent;
} BiTriTNode;

/* 指向二叉树结点的指针 */
typedef BiTriTNode* BiTriTree;


/*
 * 初始化
 *
 * 构造空二叉树。
 */
Status InitBiTree(BiTriTree* T);

/*
 * 销毁
 *
 * 释放二叉树所占内存。
 *
 *【注】
 * 二叉树的三叉链表存储结构可以销毁，但是没必要销毁。
 * 因为三叉链表销毁后的状态与置空后的状态是一致的。
 */
Status DestroyBiTree(BiTriTree* T);

/*
 * 置空
 *
 * 清理二叉树中的数据，使其成为空树。
 */
Status ClearBiTree(BiTriTree* T);

/*
 * ████████ 算法6.4 ████████
 *
 * 创建
 *
 * 按照预设的定义来创建二叉树。
 * 这里约定使用【先序序列】来创建二叉树。
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
void CreateBiTree(BiTriTree* T);

/*
 * 判空
 *
 * 判断二叉树是否为空树。
 */
Status BiTreeEmpty(BiTriTree T);

/*
 * 树深
 *
 * 返回二叉树的深度（层数）。
 */
int BiTreeDepth(BiTriTree T);

/*
 * 取值
 *
 * 返回二叉树中指定结点的值。
 */
TElemType Value(BiTriTree T, TElemType e);

/*
 * 赋值
 *
 * 为二叉树指定的结点赋值。
 */
Status Assign(BiTriTree T, TElemType e, TElemType value);

/*
 * 根
 *
 * 返回二叉树的根结点。
 */
TElemType Root(BiTriTree T);

/*
 * 双亲
 *
 * 返回二叉树中结点e的双亲结点。
 */
TElemType Parent(BiTriTree T, TElemType e);

/*
 * 左孩子
 *
 * 返回二叉树中结点e的左孩子结点。
 */
TElemType LeftChild(BiTriTree T, TElemType e);

/*
 * 右孩子
 *
 * 返回二叉树中结点e的右孩子结点。
 */
TElemType RightChild(BiTriTree T, TElemType e);

/*
 * 左兄弟
 *
 * 返回二叉树中结点e的左兄弟结点。
 */
TElemType LeftSibling(BiTriTree T, TElemType e);

/*
 * 右兄弟
 *
 * 返回二叉树中结点e的右兄弟结点。
 */
TElemType RightSibling(BiTriTree T, TElemType e);

/*
 * 插入
 *
 * 已知c为与T不相交的非空二叉树，且c的右子树为空，
 * 根据LR的取值(0或1)，将c插入为T中结点p的左子树/右子树，
 * 并且，将p结点原有的左子树/右子树嫁接为二叉树c的右子树。
 */
Status InsertChild(BiTriTree T, TElemType p, int LR, BiTriTree c);

/*
 * 删除
 *
 * 根据LR的取值(0或1)，删除结点p的左子树/右子树。
 */
Status DeleteChild(BiTriTree T, TElemType p, int LR);

/*
 * ████████ 算法6.1 ████████
 *
 * 先序遍历
 */
Status PreOrderTraverse(BiTriTree T, Status(Visit)(TElemType));

/*
 * 中序遍历
 */
Status InOrderTraverse(BiTriTree T, Status(Visit)(TElemType));

/*
 * 后序遍历
 */
Status PostOrderTraverse(BiTriTree T, Status(Visit)(TElemType));

/*
 * 层序遍历
 */
Status LevelOrderTraverse(BiTriTree T, Status(Visit)(TElemType));


/*━━━━━━━━━━━━━━━━━━━━━━ 仅限内部使用的函数 ━━━━━━━━━━━━━━━━━━━━━━*/

// 返回指向二叉树结点e的指针
static BiTriTree EPtr(BiTriTree T, TElemType e);

// 先序遍历的内部实现
static Status PreTraverse(BiTriTree T, Status(Visit)(TElemType));

// 中序遍历的内部实现
static Status InTraverse(BiTriTree T, Status(Visit)(TElemType));

// 后序遍历的内部实现
static Status PostTraverse(BiTriTree T, Status(Visit)(TElemType));


/*━━━━━━━━━━━━━━━━━━━━━━ 图形化输出 ━━━━━━━━━━━━━━━━━━━━━━*/

// 以图形化形式输出当前结构，仅限内部测试使用
void PrintTree(BiTriTree T);

#endif //CLION_BITRITREE_H

//
// Created by zhanzhao on 2021/9/7.
//
/*=======================
 * 二叉树的三叉链表存储结构
 ========================*/
#include "BiTriTree.h"
#include "LinkQueue.h"
#include "SqStack.h"
/*
 * 初始化
 *
 * 构造空二叉树。
 */
Status InitBiTree(BiTriTree* T){
    if(T == NULL) return ERROR;

    *T = NULL;

    return OK;
}
/*
 * 销毁
 *
 * 释放二叉树所占内存。
 *
 *【注】
 * 二叉树的三叉链表存储结构可以销毁，但是没必要销毁。
 * 因为三叉链表销毁后的状态与置空后的状态是一致的。
 */
Status DestroyBiTree(BiTriTree* T){
    return ERROR;
}
/*
 * 置空
 *
 * 清理二叉树中的数据，使其成为空树。
 */
Status ClearBiTree(BiTriTree* T){
    if(T == NULL) return ERROR;

    if(*T){
        if((*T)->lchild != NULL)
            ClearBiTree(&((*T)->lchild));
        if((*T)->rchild != NULL)
            ClearBiTree(&((*T)->rchild));
        free(*T);
        *T = NULL;
    }
}
/*
 * ████████ 算法6.4 ████████
 *
 * 创建
 *
 * 按照预设的定义来创建二叉树。
 * 这里约定使用【先序序列】来创建二叉树。
 *
 */
void CreateBiTree(BiTriTree* T){
    TElemType ch;
    scanf("%c", &ch);
    if(ch == '^') *T = NULL;
    else{
        *T = (BiTriTree) malloc(sizeof(BiTriTNode));
        if(!(*T)) exit(OVERFLOW);

        (*T)->data = ch;
        (*T)->parent = NULL;

        CreateBiTree(&((*T)->lchild));
        if((*T)->lchild != NULL){
            (*T)->lchild->parent = *T;
        }

        CreateBiTree(&((*T)->rchild));
        if((*T)->rchild != NULL){
            (*T)->rchild->parent = *T;
        }
    }
}
/*
 * 判空
 *
 * 判断二叉树是否为空树。
 */
Status BiTreeEmpty(BiTriTree T){
    return T == NULL ? TRUE : FALSE;
}

/*
 * 树深
 *
 * 返回二叉树的深度（层数）。
 */
int BiTreeDepth(BiTriTree T){
    int LD, RD;
    if(T == NULL) return 0;
    else{
        LD = BiTreeDepth(T->lchild);
        RD = BiTreeDepth(T->rchild);
        return (LD >= RD ? LD : RD) + 1;
    }
}
/*
 * 取值
 *
 * 返回二叉树中指定结点的值。
 */
TElemType Value(BiTriTree T, TElemType e){
    BiTriTree p;

    if(BiTreeEmpty(T)) return '\0';

    p = EPtr(T , e);

    if(p == NULL) return '\0';
    else return p->data;
}
/*
 * 赋值
 *
 * 为二叉树指定的结点赋值。
 */
Status Assign(BiTriTree T,TElemType e,TElemType value){
    BiTriTree p;

    if(BiTreeEmpty(T)) return ERROR;

    p = EPtr(T,e);

    if(p == NULL) return ERROR;
    else{
        p->data = value;
        return OK;
    }
}

/*
 * 根
 *
 * 返回二叉树的根结点。
 */
TElemType Root(BiTriTree T){
    if(BiTreeEmpty(T)) return '\0';

    return T->data;
}

/*
 * 双亲
 *
 * 返回二叉树中结点e的双亲结点。
 */
TElemType Parent(BiTriTree T,TElemType e){
    BiTriTree p;

    if(BiTreeEmpty(T)) return '\0';

    p = EPtr(T,e);

    if(p == NULL || p->parent == NULL) return '\0';
    else return p->parent->data;
}
/*
 * 左孩子
 *
 * 返回二叉树中结点e的左孩子结点。
 */
TElemType LeftChild(BiTriTree T,TElemType e){
    BiTriTree p;

    if(BiTreeEmpty(T)) return '\0';

    p = EPtr(T,e);

    if(p != NULL && p->lchild != NULL)
        return p->lchild->data;

    return '\0';
}

/*
 * 右孩子
 *
 * 返回二叉树中结点e的右孩子结点。
 */
TElemType RightChild(BiTriTree T,TElemType e){
    BiTriTree p;

    if(BiTreeEmpty(T)) return '\0';

    p = EPtr(T,e);

    if(p != NULL && p->rchild != NULL)
        return p->rchild->data;

    return '\0';
}

TElemType LeftSibling(BiTriTree T, TElemType e){
    BiTriTree p;
    if(BiTreeEmpty(T)) return '\0';

    p = EPtr(T,e);

    if(p != NULL && p->parent != NULL && p->parent->lchild != NULL)
        return p->parent->lchild->data;

    return '\0';
}
/*
 * 右兄弟
 *
 * 返回二叉树中结点e的右兄弟结点。
 */
TElemType RightSibling(BiTriTree T,TElemType e){
    BiTriTree p;

    if(BiTreeEmpty(T))
        return '\0';

    p = EPtr(T, e);

    if(p != NULL && p->parent != NULL && p->parent->rchild != NULL)
        return p->parent->rchild->data;

    return '\0';
}

/*
 * 插入
 *
 * 已知c为与T不相交的非空二叉树，且c的右子树为空，
 * 根据LR的取值(0或1)，将c插入为T中结点p的左子树/右子树，
 * 并且，将p结点原有的左子树/右子树嫁接为二叉树c的右子树。
 */
Status InsertChild(BiTriTree T, TElemType p, int LR, BiTriTree c){
    BiTriTree p_ptr;

    if(BiTreeEmpty(c))
        return ERROR;

    p_ptr = EPtr(T, p);

    if(p_ptr == NULL)
        return ERROR;


    if(LR == 0) {
        if(p_ptr->lchild != NULL){
            c->rchild = p_ptr->lchild;
            p_ptr->lchild->parent = c;
        }
        p_ptr->lchild = c;
        c->parent = p_ptr;
    }else{
        if(p_ptr->rchild != NULL){
            c->rchild = p_ptr->rchild;
            p_ptr->rchild->parent = c;
        }
        p_ptr->rchild = c;
        c->parent = p_ptr;
    }

    return OK;
}


Status DeleteChild(BiTriTree T, TElemType p,int LR){
    BiTriTree p_ptr;

    if(BiTreeEmpty(T)) return ERROR;

    p_ptr = EPtr(T, p);

    if(p_ptr == NULL) return ERROR;

    if(LR == 0)
        ClearBiTree(&(p_ptr->lchild));
    else
        ClearBiTree(&(p_ptr->rchild));

    return OK;
}

Status PreOrderTraverse(BiTriTree T,Status(Visit)(TElemType)){
    if(T){
        Visit(T->data);
        PreOrderTraverse(T->lchild,Visit);
        PreOrderTraverse(T->rchild,Visit);
    }
    return OK;
}

Status InOrderTraverse(BiTriTree T,Status(Visit)(TElemType)){
    if(T){
        PreOrderTraverse(T->lchild,Visit);
        Visit(T->data);
        PreOrderTraverse(T->rchild,Visit);
    }
    return OK;
}

Status PostOrderTraverse(BiTriTree T,Status(Visit)(TElemType)){
    if(T){
        PreOrderTraverse(T->lchild,Visit);
        PreOrderTraverse(T->rchild,Visit);
        Visit(T->data);
    }
    return OK;
}

/*
 * 层序遍历
 */
Status LevelOrderTraverse(BiTriTree T,Status(Visit)(TElemType)){
    LinkQueue Q;
    BiTriTree e;

    if(T == NULL){
        printf("\n");
        return OK;
    }

    InitQueue(&Q);

    EnQueue(&Q,T);

    while (!QueueEmpty(Q)){
        DeQueue(&Q,&e);
        if(!Visit(e->data))
            return ERROR;

        if(e->lchild != NULL)
            EnQueue(&Q,e->lchild);

        if(e->rchild != NULL)
            EnQueue(&Q,e->rchild);
    }
    printf("\n");
    return OK;

}

/*━━━━━━━━━━━━━━━━━━━━━━ 仅限内部使用的函数 ━━━━━━━━━━━━━━━━━━━━━━*/

static BiTriTree EPtr(BiTriTree T,TElemType e){
    BiTriTree pl, pr;

    if(T == NULL) return NULL;

    if(T->data == e) return T;

    pl = EPtr(T->lchild, e);
    if(pl != NULL) return pl;

    pr = EPtr(T->rchild, e);
    if(pr != NULL) return pr;

    return NULL;
}

/*━━━━━━━━━━━━━━━━━━━━━━ 图形化输出 ━━━━━━━━━━━━━━━━━━━━━━*/

// 以图形化形式输出当前结构，仅限内部测试使用
void PrintTree(BiTriTree T) {
    int level, width;
    int i, j, k, w;
    int begin;
    int distance;
    TElemType** tmp;
    LinkQueue Q;
    BiTriTree e;

    // 遇到空树则无需继续计算
    if(BiTreeEmpty(T)) {
        printf("\n");
        return;
    }

    level = BiTreeDepth(T);         // （完全）二叉树结构高度
    width = (int)pow(2, level)-1;   // （完全）二叉树结构宽度

    // 动态创建行
    tmp = (TElemType**)malloc(level* sizeof(TElemType*));

    // 动态创建列
    for(i = 0; i < level; i++) {
        tmp[i] = (TElemType*)malloc(width* sizeof(TElemType));

        // 初始化内存值为空字符
        memset(tmp[i], '\0', width);
    }

    // 借助队列实现层序遍历
    InitQueue(&Q);
    EnQueue(&Q, T);

    // 遍历树中所有元素，将其安排到二维数组tmp中合适的位置
    for(i = 0; i < level; i++) {
        w        = (int) pow(2, i);             // 二叉树当前层的宽度
        distance = width / w;                   // 二叉树当前层的元素间隔
        begin    = width / (int) pow(2, i + 1); // 二叉树当前层首个元素之前的空格数

        for(k = 0; k < w; k++) {
            DeQueue(&Q, &e);

            if(e == NULL) {
                EnQueue(&Q, NULL);
                EnQueue(&Q, NULL);
            } else {
                j = begin + k * (1 + distance);
                tmp[i][j] = e->data;

                // 左孩子入队
                EnQueue(&Q, e->lchild);

                // 右孩子入队
                EnQueue(&Q, e->rchild);
            }
        }
    }

    for(i = 0; i < level; i++) {
        for(j = 0; j < width; j++) {
            if(tmp[i][j] != '\0') {
                printf("%c", tmp[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

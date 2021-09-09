/*=======================
 * 线索二叉树
 *
 * 包含算法: 6.5、6.6、6.7
 ========================*/

#include "BiThrTree.h"

/*
 * 创建
 *
 * 按照预设的定义来创建二叉树。
 * 这里约定使用【先序序列】来创建二叉树。
 */
void CreateBiTree(BiThrTree* T){
    TElemType ch;
    scanf("%c",&ch);
    if(ch == '^') *T = NULL;
    else{
        *T = (BiThrTree) malloc(sizeof(BiThrNode));
        if(!(*T)) exit(OVERFLOW);
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
}

/**线索二叉树
 *
 * 增设了一个头结点：
 * LTag = 0, lchild指向根节点
 * RTag = 1, rchild指向遍历序列中最后一个结点
 * 遍历序列中第一个结点的lc域和最后一个结点的rc域都指向头结点
 *
 * */

Status InOrderThreading(BiThrTree* Thrt,BiThrTree T){
    // 建立头结点
    *Thrt = (BiThrTree) malloc(sizeof(BiThrNode));
    if(!*Thrt) {
        exit(OVERFLOW);
    }

    (*Thrt)->data = '\0';

    (*Thrt)->LTag = Link;       // 左孩子，需要指向二叉树的根结点
    (*Thrt)->RTag = Thread;     // 右指针，需要指向中序序列最后一个元素，以便逆中序遍历线索二叉树

    (*Thrt)->rchild = *Thrt;

    // 若二叉树为空，则左指针回指
    if(!T) {
        (*Thrt)->lchild = *Thrt;
    } else {
        (*Thrt)->lchild = T;    // 指向二叉树头结点
        pre = *Thrt;            // 记录前驱信息，初始化为线索二叉树头结点

        InTheading(T);          // 中序遍历，以进行中序线索化

        pre->rchild = *Thrt;    // 最后一个结点指回线索二叉树头结点
        pre->RTag = Thread;     // 最后一个结点线索化
        (*Thrt)->rchild = pre;  // 头结点指向最后一个结点，建立双向联系
    }

    return OK;

}

/*
 * ████████ 算法6.5 ████████
 *
 * 中序遍历中序全线索二叉树（非递归算法）。
 *
 * 注：该方法可以验证后继线索是否正确
 */
Status InOrderTraverse_Thr(BiThrTree T, Status(Visit)(TElemType)) {
    BiThrTree p = T->lchild;    // p指向二叉树根结点（不同于线索二叉树的头结点）

    // 空树或遍历结束时，p==T
    while(p != T) {
        // 如果存在左孩子，则持续向左访问
        while(p->LTag == Link) {
            p = p->lchild;
        }

        // 访问左子树为空的结点（最左边）
        if(!Visit(p->data)) {
            return ERROR;
        }

        // 如果存在后继线索（即没有右子树）
        while(p->RTag == Thread && p->rchild != T) {
            p = p->rchild;   // 将p指向其后继
            Visit(p->data);  // 访问后继结点
        }

        // 访问右子树
        p = p->rchild;
    }

    printf("\n");

    return OK;
}

/*━━━━━━━━━━━━━━━━━━━━━━ 辅助函数 ━━━━━━━━━━━━━━━━━━━━━━*/

/*
 * 逆中序遍历中序全线索二叉树（非递归算法）。
 *
 * 注：该方法可以验证前驱线索是否正确
 */
Status InOrderTraverse_Thr_Inverse(BiThrTree T, Status(Visit)(TElemType)) {
    BiThrTree p = T->rchild;    // p指向二叉树中序遍历的最后一个结点，这也相当于是T的左子树上中序遍历的最后一个结点

    // 空树或遍历结束时，p==T
    while(p != T) {
        // 访问结点p，该结点是某棵左子树上中序遍历的最后一个结点
        if(!Visit(p->data)) {
            return ERROR;
        }

        // 如果存在前驱线索（即没有左子树）
        while(p->LTag == Thread && p->lchild != T) {
            p = p->lchild;   // 将p指向其前驱
            Visit(p->data);  // 访问前驱结点
        }

        // 向左前进一步，可能遇到左子树，也可能遇到终点T
        p = p->lchild;

        // 如果没有遇到终点，即存在左子树，则找到该左子树上中序遍历的最后一个结点
        if(p != T) {
            while(p->RTag == Link) {
                p = p->rchild;
            }
        }
    }

    printf("\n");

    return OK;
}



static void InTheading(BiThrTree p){
    if(p == NULL) {
        return;
    }

    InTheading(p->lchild);  // 线索化左子树

    // 如果当前结点的左子树为空，则需要建立前驱线索
    if(!p->lchild) {
        p->LTag = Thread;
        p->lchild = pre;

    } else {
        p->LTag = Link;
    }

    // 如果前驱结点的右子树为空，则为前驱结点建立后继线索
    if(!pre->rchild) {
        pre->RTag = Thread;
        pre->rchild = p;

    } else {
        pre->RTag = Link;
    }

    pre = p;                // pre向前挪一步

    InTheading(p->rchild);  // 线索化右子树
}
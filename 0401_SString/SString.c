//
// Created by zhanzhao on 2021/8/24.
//

#include "../Status.h"
#include <string.h>
#include <stdio.h>

#define MAXSTRLEN 255
/*
 * 串的顺序存储类型定义
 *
 * 注：有效元素从SString的1号单元开始存储
 *     SString的0号单元用来存储其长度
 */
typedef unsigned char SString[MAXSTRLEN + 1]; // 0号单元存放串的长度

/*
 * 初始化
 *
 * 构造一个值为chars的串T。
 *
 *【注】
 * 该操作属于最小操作子集
 */
Status StrAssign(SString T,const char* chars){
    int i, len;

    len = (int) strlen(chars);

    // chars 过长
    if(len > MAXSTRLEN) return ERROR;

    T[0] = len;

    for (i = 1;  i <= len ; i++)
        T[i] = chars[i - 1];

    return OK;
}

/*
 * 销毁
 *
 * 将串S销毁。
 *
 *【注】
 * 顺序串的结构无法销毁
 */
Status DestroyString(SString S){
    return OK;
}

/*
 * 清空
 *
 * 将串S清空。
 */
Status ClearString(SString S){
    S[0] = 0;
    return OK;
}

/*
 * 判空
 *
 * 判断串S中是否包含有效数据。
 *
 * 返回值：
 * TRUE : 串S为空
 * FALSE: 串S不为空
 */
Status StrEmpty(SString S){
    return S[0] == 0 ? TRUE :FALSE;
}

/*
 * 计数
 *
 * 返回串S中元素的个数。
 *
 *【注】
 * 该操作属于最小操作子集
 */
int StrLength(SString S){
    return S[0];
}

int StrCompare(SString S, SString T){
    int i = 1;

    while (i <= S[0] && i <= T[0]){
        if(S[i] != T[i])
            return S[i] - T[i];
        i++;
    }
    return S[0] - T[0];
}

/*
 * ████████ 算法4.3 ████████
 *
 * 求子串
 *
 * 用Sub返回S[pos, pos+len-1]。
 * 返回值指示是否截取成功。
 *
 *【注】
 * 该操作属于最小操作子集
 */
Status SubString(SString Sub, SString S, int pos, int len){
    int i;

    if(pos < 1 || pos > S[0] || len < 0 || pos + len -1 > S[0]) return ERROR;

    // 复制元素
    for (i = 1; i <= len; i++)
        Sub[i] = S[pos + i - 1];
    // 确定新长度
    Sub[0] = len;

    return OK;
}


/*
 * ████████ 算法4.1 ████████
 *
 * 查找
 *
 * 从pos处开始搜索模式串T在主串S中首次出现的位置，如果不存在，则返回0。
 * 如果查找成功，返回匹配的位置。
 *
 *【注】
 * 1.此实现需要依赖串的最小操作子集
 * 2.该实现比较低效
 */
int Index_1(SString S, SString T,int pos){
    int i,n,m;
    SString sub;

    if(pos < 1 || pos > S[0] || StrEmpty(T)) return ERROR;

    n = StrLength(S);
    m = StrLength(T);
    i = pos;
    // 保证长度不越界
    while (i <= n - m + 1){
        // 获取S[i, i+m-1]
         SubString(sub, S, i, m);
         if(StrCompare(sub, T) != 0)
             ++i;
         else
             return i;
    }
    return 0;
}

/*
 * ████████ 算法4.5 ████████
 *
 * 查找
 *
 * 从pos处开始搜索模式串T在主串S中首次出现的位置，如果不存在，则返回0。
 * 如果查找成功，返回匹配的位置。
 *
 *【注】
 * 1.此实现不依赖串的最小操作子集
 * 2.该实现比较低效
 */
int Index_2(SString S, SString T, int pos){
    int i = pos;
    int j = 1;

    if(pos < 1 || pos > S[0] || StrEmpty(T)) return 0;

    while (i <= S[0] && j <= T[0]){
        // 遇到相同字符，则继续比较后继字符
        if(S[i] == T[j]){
            i++;
            j++;
        // 遇到不同的字符，则游标需要回退，重新比较
        }else{
            i = i - (j - 1) + 1;// j-1代表徒劳地前进了j-1个元素，在第j个元素上功亏一篑
            j = 1;// 游标j回到串T的第一个位置
        }
    }

    if( j > T[0] && T[0] > 0)
        return i - T[0];
    else
        return 0;
}


/*
 * 插入
 *
 * 将串T插入到主串S的pos位置处。
 */
Status StrInsert(SString S, int pos, SString T){
    int i;

    if(pos < 1 || pos > S[0] + 1 || S[0] + T[0] > MAXSTRLEN) return ERROR;

    if(StrEmpty(T)) return OK;

    for(i = S[0]; i>= pos; i--)
        S[i + T[0]] = S[i];

    for (i = pos; i <= pos + T[0] - 1 ; i++)
        S[i] = T[i - pos +  1];

    S[0] += T[0];

    return OK;

}

/*
 * 删除
 *
 * 删除S[pos, pos+len-1]。
 */
Status StrDelete(SString S, int pos, int len){
    int i;

    if(pos < 1 || pos + len -1 > S[0] || len < 0) return ERROR;

    if(len == 0 ) return OK;

    for (i = pos + len; i <= S[0]; i++)
        S[i - len] = S[i];

    S[0] -= len;

    return OK;
}

/*
 * 复制
 *
 * 将串S复制到串T。
 */
Status StrCopy(SString T, SString S){
    int i;
    for (i = 0;  i <= S[0]; i++)
        T[i] = S[i];

    return OK;
}


/*
 * 替换
 *
 * 用V替换主串S中出现的所有与T相等的且不重叠的子串。
 *
 *【注】
 * 1.该操作依赖最小操作子集
 * 2.该实现比较低效
 */
Status Replace(SString S, SString T,SString V){
    int i;

    if(StrEmpty(S) || StrEmpty(T)) return ERROR;

    i = Index_2(S,T,1);
    while (i != 0 && S[0] - T[0] + V[0] <= MAXSTRLEN){
        StrDelete(S,i, StrLength(T));
        StrInsert(S,i,V);

        i += StrLength(V);

        i = Index_2(S,T,i);
    }
    // S中的T已全部被替换 true
    // S中尚有T，但是V已经插不进去了 false
    return i == 0 ? OK : ERROR;
}

Status Concat(SString T,SString S1,SString S2){
    int i;
    int uncut;  // 新串是否完整

    // 完全不需要裁剪
    if(S1[0] + S2[0] <= MAXSTRLEN) {
        // 复制S1到T中
        for(i = 1; i <= S1[0]; i++) {
            T[i] = S1[i];
        }

        // 复制S2到T中
        for(i = S1[0] + 1; i <= S1[0] + S2[0]; i++) {
            T[i] = S2[i - S1[0]];
        }

        // 设置新长度
        T[0] = S1[0] + S2[0];

        // 未裁剪，完整
        uncut = TRUE;

        // 需要裁剪S2
    } else if(S1[0] <= MAXSTRLEN) {
        // 复制S1到T中
        for(i = 1; i <= S1[0]; i++) {
            T[i] = S1[i];
        }

        // 将S2的一部分复制到T中
        for(i = S1[0] + 1; i <= MAXSTRLEN; i++) {
            T[i] = S2[i - S1[0]];
        }

        // 设置新长度
        T[0] = MAXSTRLEN;

        uncut = FALSE;

        // 只需要复制S1的一部分
    } else {
        // 连同长度信息一起复制
        for(i = 0; i <= MAXSTRLEN; i++) {
            T[i] = S1[i];
        }

        uncut = FALSE;
    }

    return uncut;

}

#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】空间复杂度 O(N) 与堆内存生命周期
 * -----------------------------------------------------------------------------
 * 1. 核心思想：算法所需额外内存空间随数据规模 N 线性增长（如 malloc 申请大小为 N 的数组）。
 * 2. 内存闭环：申请堆空间 (malloc) 后必须显式释放 (free)，防止内存泄漏。
 * -----------------------------------------------------------------------------
 */

// 动态创建并初始化长度为 n 的数组 -> 空间复杂度 O(N)
int* createArray(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }
    return arr;
}

int main(void) {
    int n = 5;
    int *my_arr = createArray(n);

    if (my_arr != NULL) {
        printf("动态数组内容: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", my_arr[i]);
        }
        printf("\n");

        free(my_arr); // 释放堆内存
        my_arr = NULL;
    }

    return 0;
}

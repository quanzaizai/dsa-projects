#include <stdio.h>

/**
 * 【知识点】顺序表/数组 —— 线性查找 (Linear Search)
 * -----------------------------------------------------------------------------
 * 1. 核心思想：从头到尾逐个比对目标值，找到则返回下标，未找到返回 -1。
 * 2. 时间复杂度：最好 O(1)，最坏/平均 O(N)。
 * -----------------------------------------------------------------------------
 */

int linear_search(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int main(void) {
    int arr[] = {15, 32, 48, 64, 80};
    int size = sizeof(arr) / sizeof(arr[0]);

    int target = 48;
    int index = linear_search(arr, size, target);

    if (index != -1) {
        printf("找到目标 %d，所在下标为: %d\n", target, index);
    } else {
        printf("未找到目标 %d\n", target);
    }

    return 0;
}

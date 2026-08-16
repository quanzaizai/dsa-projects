#include <stdio.h>

#define CAPACITY 10

/**
 * 【知识点】顺序表/数组 —— 元素插入
 * -----------------------------------------------------------------------------
 * 1. 插入逻辑：将目标位置 index 及其后面的元素依次向后移动一位，腾出空位填入新值。
 * 2. 时间复杂度：平均 O(N)（最好尾插 O(1)，最坏头插 O(N)）。
 * -----------------------------------------------------------------------------
 */

int insert(int arr[], int *size, int capacity, int index, int value) {
    if (*size >= capacity || index < 0 || index > *size) return 0; // 容量满或下标越界

    // 从后向前依次后移
    for (int i = *size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    (*size)++;
    return 1;
}

int main(void) {
    int arr[CAPACITY] = {10, 20, 30, 40};
    int size = 4;

    printf("插入前: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    insert(arr, &size, CAPACITY, 2, 99); // 在下标 2 处插入 99

    printf("在下标 2 插入 99 后: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

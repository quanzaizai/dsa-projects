#include <stdio.h>

/**
 * 【知识点】顺序表/数组 —— 元素删除
 * -----------------------------------------------------------------------------
 * 1. 删除逻辑：将目标位置 index 后面的元素依次向前移动一位进行覆盖，长度 size 减 1。
 * 2. 时间复杂度：平均 O(N)。
 * -----------------------------------------------------------------------------
 */

int delete_at(int arr[], int *size, int index) {
    if (index < 0 || index >= *size) return 0; // 下标越界

    // 从前往后依次前移覆盖
    for (int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
    return 1;
}

int main(void) {
    int arr[] = {10, 20, 99, 30, 40};
    int size = 5;

    printf("删除前: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    delete_at(arr, &size, 2); // 删除下标 2 处的元素

    printf("删除下标 2 后: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

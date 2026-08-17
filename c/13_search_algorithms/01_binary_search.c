#include <stdio.h>

/**
 * 💡【知识点】经典查找算法 —— 二分查找 (Binary Search / 折半查找)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 前提条件：输入数组必须严格**升序有序**。
 *   2. 二分分治：维护区间 `[left, right]`，每次取中点 `mid = left + (right - left) / 2`。
 *      - 若 target == arr[mid]，直接命中返回下标。
 *      - 若 target < arr[mid]，目标在左半区，`right = mid - 1`。
 *      - 若 target > arr[mid]，目标在右半区，`left = mid + 1`。
 *   3. 时空复杂度：每次范围减半，时间复杂度 $O(\log N)$，空间复杂度 $O(1)$。
 * -----------------------------------------------------------------------------
 */

int binary_search(const int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        // 🔍【防溢出技巧】：避免 (left + right) 数值过大导致整型溢出
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // 命中返回下标
        } else if (arr[mid] < target) {
            left = mid + 1; // 搜寻右半区
        } else {
            right = mid - 1; // 搜寻左半区
        }
    }
    return -1; // 未找到
}

int main(void) {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("有序数组: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n\n");

    int targets[] = {23, 2, 91, 100};
    for (int i = 0; i < 4; i++) {
        int idx = binary_search(arr, size, targets[i]);
        if (idx != -1) {
            printf("🎯 查找 %2d: 成功，所在下标为 %d\n", targets[i], idx);
        } else {
            printf("❌ 查找 %2d: 不存在于数组中\n", targets[i]);
        }
    }
    return 0;
}

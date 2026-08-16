#include <stdio.h>

/**
 * 💡【知识点】顺序表/数组 —— 线性查找 (Linear Search)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 核心逻辑：从头到尾逐个扫描数组元素与目标 target 比对。匹配成功立即返回对应下标；
 *      遍历结束仍未找到则返回哨兵标志值 -1。
 *   2. 时空复杂度：最好 O(1)，最坏/平均 O(N)，空间复杂度 O(1)。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 查找算法实现 ====================

/**
 * @brief 线性顺序查找目标元素
 * @return 找到返回下标，未找到返回 -1
 */
int linear_search(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // 🔍 匹配命中，立即返回当前下标
        }
    }
    return -1; // 遍历完未找到
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    int arr[] = {15, 32, 48, 64, 80};
    int size = sizeof(arr) / sizeof(arr[0]);

    int target = 48;
    int index = linear_search(arr, size, target);

    if (index != -1) {
        printf("目标值 %d 查找成功，所在下标为: %d\n", target, index);
    } else {
        printf("未找到目标值 %d\n", target);
    }

    return 0;
}

#include <stdio.h>

/**
 * =============================================================================
 * 💡【知识点】经典查找算法 —— 二分查找 (Binary Search / 折半查找)
 * =============================================================================
 * 
 * 📌【1. 什么是二分查找？】
 *   二分查找是一种在「有序数组」中以对数级时间极速定位目标元素的分治算法。
 *   - 核心思想：每次将搜索区间一分为二，只取中间元素 (mid) 与目标值 (target) 比对。
 *   - 剪枝策略：
 *     - 若 `target == arr[mid]`：直接命中返回。
 *     - 若 `target < arr[mid]` ：目标必然在左半区，右边界收缩 `right = mid - 1`。
 *     - 若 `target > arr[mid]` ：目标必然在右半区，左边界收缩 `left = mid + 1`。
 * 
 * 📌【2. 搜索区间折半收缩图解 (以查找 target = 23 为例)】
 * 
 *   下标:    0    1    2    3    4    5    6    7    8    9
 *   数组:  [ 2,   5,   8,  12,  16,  23,  38,  56,  72,  91 ]
 *   
 *   第 1 轮: left=0, right=9 -> mid = (0+9)/2 = 4 (arr[4]=16 < 23) -> 目标在右边，left = 5
 *   第 2 轮: left=5, right=9 -> mid = (5+9)/2 = 7 (arr[7]=56 > 23) -> 目标在左边，right = 6
 *   第 3 轮: left=5, right=6 -> mid = (5+6)/2 = 5 (arr[5]=23 == 23) -> 🎯 命中目标！返回下标 5
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么中点计算必须写 `mid = left + (right - left) / 2`，而不能写 `(left + right) / 2`？
 *      👉 解答（经典工业级整型溢出 Bug，曾存在于早期 Java SDK 达数年之久）：
 *         - 在 32 位有符号整型下，最大值为 2,147,483,647。
 *         - 若 `left` 和 `right` 很大（如均为 15 亿），`left + right` 会直接超过 21 亿产生「整型正溢出变负数」！
 *         - 写成 `left + (right - left) / 2`，由于减法绝对不会超出范围，从而彻底杜绝了溢出隐患。
 * 
 *   ❓ Q2: 循环条件为什么是 `left <= right` 而不是 `left < right`？
 *      👉 解答：采用「双闭区间 [left, right]」设计。当 `left == right` 时，区间内仍然有唯一一个元素 `[left, left]`
 *         需要被检查，因此必须带上等号 `=`。
 * =============================================================================
 */

// ==================== 1. 二分查找算法实现 ====================

/**
 * @brief 在有序数组中二分查找目标值
 * 
 * @param arr    升序有序数组指针
 * @param size   数组元素个数
 * @param target 待查找的目标数值
 * @return int 找到返回下标 (0 ~ size-1)，未找到返回 -1
 * 
 * @note 时间复杂度: 最好 O(1)，最坏/平均 O(log N) —— 每次规模缩小一半
 * @note 空间复杂度: O(1) —— 原地迭代，无任何额外递归栈开销
 */
int binary_search(const int arr[], int size, int target) {
    if (arr == NULL || size <= 0) return -1;

    // 【步骤 1】初始化双闭搜索区间的左右端点 [left, right]
    int left = 0;
    int right = size - 1;

    // 【步骤 2】循环折半探测
    while (left <= right) {
        // 安全防溢出计算中点下标
        int mid = left + (right - left) / 2;

        // 【分支 1】中点值刚好命中目标
        if (arr[mid] == target) {
            return mid;
        }
        // 【分支 2】中点值偏小，说明目标在右半侧 -> 舍弃左半区
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        // 【分支 3】中点值偏大，说明目标在左半侧 -> 舍弃右半区
        else {
            right = mid - 1;
        }
    }

    // 【步骤 3】区间为空 (left > right)，说明目标值不存在于数组中
    return -1;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("==================== 二分查找算法 (Binary Search) 验证 ====================\n\n");
    printf("有序数组: [ ");
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], (i < size - 1) ? ", " : " ");
    }
    printf("] (共 %d 个元素)\n\n", size);

    int targets[] = {23, 2, 91, 100};
    for (int i = 0; i < 4; i++) {
        int idx = binary_search(arr, size, targets[i]);
        if (idx != -1) {
            printf("🎯 查找目标 %3d: 成功命中！所在下标为 [%d]\n", targets[i], idx);
        } else {
            printf("❌ 查找目标 %3d: 未找到 (返回值: %d)\n", targets[i], idx);
        }
    }

    return 0;
}

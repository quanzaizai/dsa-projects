#include <stdio.h>

/**
 * 💡【知识点】顺序表/数组 —— 元素删除 (Array Deletion)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 逻辑结构：删除下标 index 处的元素时，必须将 index 后面的所有元素
 *      **从前向后**依次向前搬移一位进行覆盖，最后将有效长度 size 减 1。
 *   2. 时空复杂度：平均时间复杂度 O(N)，空间复杂度 O(1)。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 删除算法实现 ====================

/**
 * @brief 删除顺序表指定下标处的元素
 * @param arr 数组指针
 * @param size 当前元素个数指针
 * @param index 待删除下标
 * @return 1 成功, 0 失败
 */
int delete_at(int arr[], int *size, int index) {
    // ⚠️【边界检查】：检查下标有效性
    if (index < 0 || index >= *size) {
        return 0;
    }

    // 🔍【核心前移】：从 index 开始，依次用后一个元素覆盖前一个元素
    for (int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    (*size)--; // 有效长度扣减
    return 1;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    int arr[] = {10, 20, 99, 30, 40};
    int size = 5;

    printf("删除前: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    delete_at(arr, &size, 2); // 删除下标 2 处的元素 (99)

    printf("删除下标 2 后: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

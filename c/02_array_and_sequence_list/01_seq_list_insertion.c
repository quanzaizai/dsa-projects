#include <stdio.h>

#define CAPACITY 10 // 顺序表最大容量

/**
 * 💡【知识点】顺序表/数组 —— 元素插入 (Array Insertion)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 逻辑结构：连续物理内存存储。在下标 index 处插入新值时，必须将 index 及其后面的所有元素
 *      **从后向前**依次向后搬移一位，腾出空位后写入新值。
 *   2. 时空复杂度：平均时间复杂度 O(N)（尾插 O(1)，头插 O(N)），空间复杂度 O(1)。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 插入算法实现 ====================

/**
 * @brief 在顺序表指定下标处插入元素
 * @param arr 数组指针
 * @param size 当前元素个数指针
 * @param capacity 最大容量
 * @param index 插入目标下标
 * @param value 待插入的新值
 * @return 1 成功, 0 失败
 */
int insert(int arr[], int *size, int capacity, int index, int value) {
    // ⚠️【边界检查】：容量已满或插入下标越界
    if (*size >= capacity || index < 0 || index > *size) {
        return 0;
    }

    // 🔍【核心后移】：从最后一个元素开始，从后向前依次后移一位
    for (int i = *size; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    arr[index] = value; // 填入新值
    (*size)++;          // 有效长度自增
    return 1;
}

// ==================== 2. 测试与验证入口 ====================

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

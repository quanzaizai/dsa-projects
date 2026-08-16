#include <stdio.h>

/**
 * 【知识点】时间复杂度 O(N) —— 线性时间复杂度
 * -----------------------------------------------------------------------------
 * 1. 核心思想：执行耗时与输入规模 N 成正比（单层循环遍历）。
 * 2. 关键考点：C 语言中数组传参会退化为指针，函数内无法求长度，必须额外传入 n。
 * -----------------------------------------------------------------------------
 */

// 单层循环累加：执行 n 次 -> 时间复杂度 O(N)，额外变量占常数空间 -> 空间复杂度 O(1)
int sumArray(int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

int main(void) {
    int nums[] = {10, 20, 30, 40, 50};
    int size = sizeof(nums) / sizeof(nums[0]); // 在定义作用域计算数组长度

    int result = sumArray(nums, size);
    printf("数组元素总和: %d\n", result);

    return 0;
}

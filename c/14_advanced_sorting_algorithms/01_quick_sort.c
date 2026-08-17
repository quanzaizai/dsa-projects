#include <stdio.h>

/**
 * =============================================================================
 * 💡【知识点】高级排序算法 —— 快速排序 (Quick Sort / 分治双向分区)
 * =============================================================================
 * 
 * 📌【1. 什么是快速排序？】
 *   由图灵奖得主 Tony Hoare 提出的分治排序算法，是现代工业界实际运行速度最快的通用排序之一。
 *   - 核心步骤：
 *     ① 挑选基准 (Pivot)：选定一个基准元素（本实现选用区间最右端元素 `arr[high]`）。
 *     ② 分区操作 (Partition)：一趟扫描，将所有 `<= Pivot` 的元素挪到左边，所有 `> Pivot` 的元素挪到右边。
 *     ③ 递归分治：对左右两个子区间分别递归执行快速排序，直到区间长度缩减为 1。
 * 
 * 📌【2. Lomuto 分区过程 (Partition) ASCII 图解】
 * 
 *   以数组 [10, 7, 8, 9, 1, 5] 为例，选取末尾 5 作为 Pivot:
 *   
 *   双指针: i 指向当前已处理的 `<= 5` 区域末尾 (初始为 low - 1)
 *          j 从 low 遍历到 high - 1 进行探测
 *          
 *   [ 10,  7,  8,  9,  1, (5) ]
 *                       ▲ Pivot
 *   当 j 扫描到元素 1 (1 <= 5) 时：
 *     i 自增 1，交换 arr[i] 与 arr[j] -> [ 1, 7, 8, 9, 10, (5) ]
 *   
 *   扫描完毕后，将 Pivot(5) 与 arr[i+1] 交换:
 *     [ 1, (5), 8, 9, 10, 7 ]  ===> 5 归位！左边 <= 5，右边 > 5！
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么快排在最坏情况下会退化到 O(N^2)？如何避免？
 *      👉 解答：若输入数组原本就是完全升序或降序的，每次选末尾作为 Pivot 会导致划分极度不平衡（一边为 0，一边为 N-1）。
 *         工业级优化方案：**三数取中法 (Median-of-three)** 或 **随机基准法 (Randomized Pivot)**。
 * =============================================================================
 */

// ==================== 1. 核心算法实现 ====================

static void swap(int *a, int *b) {
    int t = *a; 
    *a = *b; 
    *b = t;
}

/**
 * @brief Lomuto 单向双指针分区函数
 * 
 * @param arr  数组
 * @param low  当前子区间起始下标
 * @param high 当前子区间结束下标 (arr[high] 作为 Pivot)
 * @return int 基准值归位后的最终绝对下标 (Partition Index)
 * 
 * @note 时间复杂度: O(N) —— 线性遍历当前区间一次
 */
static int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选取末尾元素作为基准
    int i = low - 1;       // i 记录较小元素区域的最右边界

    // j 游标线性扫描整个区间
    for (int j = low; j < high; j++) {
        // 若当前元素小于等于基准值，将其并入较小区域
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // 将基准值交换到较小区域的后一位 (i + 1)，实现基准归位
    swap(&arr[i + 1], &arr[high]);

    return i + 1; // 返回基准值所在位置
}

/**
 * @brief 快速排序递归主函数
 * 
 * @param arr  数组指针
 * @param low  子区间起点下标
 * @param high 子区间终点下标
 * 
 * @note 时间复杂度: 平均 O(N log N)，最坏 O(N^2)
 * @note 空间复杂度: O(log N) (递归调用栈深度)
 */
void quick_sort(int arr[], int low, int high) {
    // 递归基：只有当区间至少包含 2 个元素时才继续划分
    if (low < high) {
        // 【步骤 1】分区并获取基准点
        int pi = partition(arr, low, high);

        // 【步骤 2】递归排序左半部分 (pi 的左侧)
        quick_sort(arr, low, pi - 1);

        // 【步骤 3】递归排序右半部分 (pi 的右侧)
        quick_sort(arr, pi + 1, high);
    }
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("==================== 快速排序 (Quick Sort) 验证 ====================\n\n");
    printf("待排数组: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    quick_sort(arr, 0, n - 1);

    printf("快排结果: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf(" (升序有序)\n");

    return 0;
}

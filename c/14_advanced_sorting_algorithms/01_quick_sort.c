#include <stdio.h>

/**
 * 💡【知识点】高级排序算法 —— 快速排序 (Quick Sort / 双向分区法)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 分治思想：选取一个基准值 (Pivot)，通过一趟分区将数组切分为两部分：
 *      左边所有元素 <= Pivot，右边所有元素 >= Pivot。随后对左右子区间递归执行快排。
 *   2. 时空复杂度：平均时间复杂度 $O(N \log N)$，最坏情况退化为 $O(N^2)$（如已有序未随机化），递归栈空间 $O(\log N)$。
 * -----------------------------------------------------------------------------
 */

static void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

static int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选取末尾为基准
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // 获取分区基准点
        quick_sort(arr, low, pi - 1);       // 递归左半区
        quick_sort(arr, pi + 1, high);      // 递归右半区
    }
}

int main(void) {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("快排前: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    quick_sort(arr, 0, n - 1);

    printf("快排后: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

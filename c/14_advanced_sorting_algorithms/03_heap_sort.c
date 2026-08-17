#include <stdio.h>

/**
 * 💡【知识点】高级排序算法 —— 堆排序 (Heap Sort / 原地堆化)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 算法步骤：
 *      ① 构建最大堆：从最后一个非叶子节点 `(n/2 - 1)` 开始向前遍历执行下沉调整。
 *      ② 原地排序：将堆顶（全局最大值）与当前末尾元素交换，堆有效大小减 1，再对堆顶执行下沉。
 *   2. 时空复杂度：时间复杂度严格为 $O(N \log N)$，原地排序空间复杂度 $O(1)$（不稳定）。
 * -----------------------------------------------------------------------------
 */

static void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

static void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    // 1. 原地构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 2. 依次提取堆顶并放到末尾
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0); // 对剩余堆维护平衡
    }
}

int main(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("堆排前: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    heap_sort(arr, n);

    printf("堆排后: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

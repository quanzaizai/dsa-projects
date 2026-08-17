#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】高级排序算法 —— 归并排序 (Merge Sort / 分治合并)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 分治模型：将数组从中点对半拆解为左右两半，递归排序子序列，最后执行双指针合并 (Merge)。
 *   2. 稳定性与复杂度：严格保证最坏与平均均为 $O(N \log N)$，稳定排序，需额外 $O(N)$ 辅助合并空间。
 * -----------------------------------------------------------------------------
 */

static void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main(void) {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("归并前: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    merge_sort(arr, 0, n - 1);

    printf("归并后: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

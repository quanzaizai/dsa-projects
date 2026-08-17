#include <stdio.h>
#include <stdbool.h>

#define HEAP_CAPACITY 64

/**
 * 💡【知识点】数据结构 —— 二叉堆 (最大堆 / Max Heap) 底层实现
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 堆的本质：基于完全二叉树的数组实现。每个父节点的值都大于等于其左右孩子节点的值。
 *   2. 数组索引映射（以 0 为根节点）：
 *      - 节点 i 的左孩子：`2 * i + 1`
 *      - 节点 i 的右孩子：`2 * i + 2`
 *      - 节点 i 的父节点：`(i - 1) / 2`
 *   3. 核心平衡调整算法：
 *      - **上浮调整 (Sift Up)**：插入新元素至数组末尾，若比父节点大则与其交换，逐步上浮 ($O(\log N)$)。
 *      - **下沉调整 (Sift Down)**：取出堆顶最大值后，将末尾元素移至堆顶，与较大孩子交换逐步下沉 ($O(\log N)$)。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 最大堆实现 ====================

typedef struct MaxHeap {
    int data[HEAP_CAPACITY];
    int size;
} MaxHeap;

void heap_init(MaxHeap *h) { if (h) h->size = 0; }

static void swap(int *a, int *b) {
    int temp = *a; *a = *b; *b = temp;
}

// 上浮操作 O(log N)
static void sift_up(MaxHeap *h, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (h->data[index] > h->data[parent]) {
            swap(&h->data[index], &h->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// 下沉操作 O(log N)
static void sift_down(MaxHeap *h, int index) {
    while (2 * index + 1 < h->size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < h->size && h->data[left] > h->data[largest]) largest = left;
        if (right < h->size && h->data[right] > h->data[largest]) largest = right;

        if (largest != index) {
            swap(&h->data[index], &h->data[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

// 插入新元素 O(log N)
bool heap_insert(MaxHeap *h, int val) {
    if (h->size >= HEAP_CAPACITY) return false;
    h->data[h->size] = val;
    sift_up(h, h->size);
    h->size++;
    return true;
}

// 提取堆顶最大值 O(log N)
bool heap_extract_max(MaxHeap *h, int *out_max) {
    if (h->size <= 0) return false;
    if (out_max) *out_max = h->data[0];

    h->data[0] = h->data[h->size - 1]; // 末尾覆盖堆顶
    h->size--;
    sift_down(h, 0); // 堆顶下沉维护平衡
    return true;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    MaxHeap heap;
    heap_init(&heap);

    printf("=== 最大堆 (Max Heap) 插入与提取测试 ===\n\n");
    int elements[] = {20, 15, 38, 45, 10, 50};
    int n = sizeof(elements) / sizeof(elements[0]);

    printf("依次插入元素: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", elements[i]);
        heap_insert(&heap, elements[i]);
    }
    printf("\n\n");

    printf("依次提取最大值 (按降序输出验证):\n");
    int max_val;
    while (heap_extract_max(&heap, &max_val)) {
        printf("🏆 提取最大值: %d (当前堆大小: %d)\n", max_val, heap.size);
    }

    return 0;
}

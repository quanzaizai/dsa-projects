#include <stdio.h>
#include <stdbool.h>

#define HEAP_CAPACITY 64

/**
 * =============================================================================
 * 💡【知识点】数据结构 —— 二叉堆 (最大堆 / Max Heap) 底层实现
 * =============================================================================
 * 
 * 📌【1. 什么是二叉堆与最大堆？】
 *   二叉堆是一棵「完全二叉树 (Complete Binary Tree)」，在物理上直接用「连续数组」紧凑存储。
 *   - 最大堆性质：任何一个父节点的值，都必须 **大于或等于 (>=)** 它的左右子节点的值。
 *   - 堆顶 (下标 0)：整个堆中数值最大的元素始终稳居堆顶！
 * 
 * 📌【2. 树形逻辑与数组物理下标映射模型】
 * 
 *            树形逻辑视图                          数组物理存储
 *                [50] (0)                下标:  0   1   2   3   4   5
 *              /          \              数值: |50 |45 |38 |20 |10 |15 |
 *           [45] (1)     [38] (2)
 *          /       \     /
 *        [20](3) [10](4)[15](5)
 * 
 *   👉 黄金下标计算公式（下标从 0 开始）：
 *      - 节点 i 的左孩子 (Left Child)  : `2 * i + 1`
 *      - 节点 i 的右孩子 (Right Child) : `2 * i + 2`
 *      - 节点 i 的父节点 (Parent)      : `(i - 1) / 2`
 * 
 * 📌【3. 核心平衡调整算法 (Q&A)】
 * 
 *   ❓ Q1: 什么是上浮调整 (Sift Up)？
 *      👉 新插入元素先放在数组末尾，若它比父节点大，就与父节点交换，一路向上“冒泡”，直到不大于父节点或到达堆顶。
 *         时间复杂度: O(log N)。
 * 
 *   ❓ Q2: 什么是下沉调整 (Sift Down)？
 *      👉 提取堆顶最大值后，将数组最后一个元素移至堆顶，然后与左右孩子中「较大的那个」比较并交换，
 *         一路向下“沉没”，直到不小于任何孩子或沉到底部。
 *         时间复杂度: O(log N)。
 * =============================================================================
 */

// ==================== 1. 最大堆结构与算法 ====================

typedef struct MaxHeap {
    int data[HEAP_CAPACITY]; // 存储完全二叉树的数组
    int size;                // 当前堆中的元素数量
} MaxHeap;

void heap_init(MaxHeap *h) { 
    if (h) h->size = 0; 
}

static void swap(int *a, int *b) {
    int temp = *a; 
    *a = *b; 
    *b = temp;
}

/**
 * @brief 上浮调整 (Sift Up) —— 维护插入后的最大堆性质
 * 
 * @param h     堆指针
 * @param index 待上浮的节点下标
 * @note 时间复杂度: O(log N) —— 最多向上走树的高度次
 */
static void sift_up(MaxHeap *h, int index) {
    // 只要当前节点还没到达堆顶 (index > 0)
    while (index > 0) {
        int parent = (index - 1) / 2; // 计算父节点下标

        // 若当前节点大于父节点，违反最大堆性质，必须交换
        if (h->data[index] > h->data[parent]) {
            swap(&h->data[index], &h->data[parent]);
            index = parent; // 游标上升到父节点位置，继续向上检查
        } else {
            break; // 已经满足最大堆性质，提前结束
        }
    }
}

/**
 * @brief 下沉调整 (Sift Down) —— 维护删除堆顶后的最大堆性质
 * 
 * @param h     堆指针
 * @param index 待下沉的节点下标
 * @note 时间复杂度: O(log N)
 */
static void sift_down(MaxHeap *h, int index) {
    // 只要当前节点至少还有一个左孩子（2*index + 1 < size）
    while (2 * index + 1 < h->size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index; // 记录父节点、左孩子、右孩子三者中的最大值下标

        // 寻找左孩子中是否有更大的
        if (left < h->size && h->data[left] > h->data[largest]) {
            largest = left;
        }

        // 寻找右孩子中是否有更大的
        if (right < h->size && h->data[right] > h->data[largest]) {
            largest = right;
        }

        // 若最大者不是当前节点，则与最大孩子交换并继续下沉
        if (largest != index) {
            swap(&h->data[index], &h->data[largest]);
            index = largest; // 游标下沉到被交换的孩子位置
        } else {
            break; // 已经比所有孩子都大，下沉到位
        }
    }
}

/**
 * @brief 向堆中插入新元素
 * 
 * @param h   堆指针
 * @param val 待插入的值
 * @return true 成功, false 堆满
 * @note 时间复杂度: O(log N)
 */
bool heap_insert(MaxHeap *h, int val) {
    if (h->size >= HEAP_CAPACITY) return false;

    // 【步骤 1】将新元素追加到完全二叉树的末尾
    h->data[h->size] = val;

    // 【步骤 2】对末尾新元素执行上浮调整
    sift_up(h, h->size);

    // 【步骤 3】有效元素自增
    h->size++;
    return true;
}

/**
 * @brief 提取并删除堆顶的最大值
 * 
 * @param h       堆指针
 * @param out_max 接收最大值的传出指针
 * @return true 成功, false 堆空
 * @note 时间复杂度: O(log N)
 */
bool heap_extract_max(MaxHeap *h, int *out_max) {
    if (h->size <= 0) return false;

    // 【步骤 1】保存堆顶最大值
    if (out_max) *out_max = h->data[0];

    // 【步骤 2】将数组最后一个元素搬移到堆顶
    h->data[0] = h->data[h->size - 1];
    h->size--;

    // 【步骤 3】对新的堆顶元素执行下沉调整
    sift_down(h, 0);

    return true;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    MaxHeap heap;
    heap_init(&heap);

    printf("==================== 最大堆 (Max Heap) 构建与验证 ====================\n\n");
    int elements[] = {20, 15, 38, 45, 10, 50};
    int n = sizeof(elements) / sizeof(elements[0]);

    printf("依次插入元素: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", elements[i]);
        heap_insert(&heap, elements[i]);
    }
    printf("\n\n");

    printf("依次提取堆顶最大值 (自动输出有序降序序列):\n");
    int max_val;
    while (heap_extract_max(&heap, &max_val)) {
        printf("🏆 提取最大值: %2d (剩余堆规模: %d)\n", max_val, heap.size);
    }

    return 0;
}

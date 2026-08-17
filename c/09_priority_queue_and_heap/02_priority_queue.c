// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

#define PQ_CAPACITY 64

/**
 * =============================================================================
 * 💡【知识点】数据结构 —— 基于二叉堆的优先队列 (Priority Queue)
 * =============================================================================
 * 
 * 📌【1. 什么是优先队列？】
 *   - 普通队列：严格按照 FIFO（先来先服务）。
 *   - 优先队列：每个元素附带一个「优先级 (Priority)」，出队时永远是「当前优先级最高」的元素优先出队，
 *     无论它是什么时候进来的！
 * 
 * 📌【2. 为什么优先队列的工业首选是二叉堆？】
 *   - 普通无序数组：插入 O(1)，但查找/提取最高优先级需要扫描全数组 O(N)。
 *   - 有序数组：提取最高优先级 O(1)，但插入新元素需要搬移数组 O(N)。
 *   - **二叉堆 (Binary Heap)**：插入与提取均达到极致均衡的 **O(log N)**！
 * 
 * 📌【3. 经典工业级应用场景】
 *   - 操作系统的 CPU 进程与硬件中断调度。
 *   - 图论算法中的 Dijkstra 最短路径、Prim 最小生成树。
 *   - 海量数据 Top-K 问题（前 100 个最高频词汇）。
 * =============================================================================
 */

typedef struct Task {
    int priority;    // 优先级数值：数值越大代表越紧急、越优先
    char name[32];   // 任务描述说明
} Task;

typedef struct PriorityQueue {
    Task tasks[PQ_CAPACITY];
    int size;
} PriorityQueue;

void pq_init(PriorityQueue *pq) { 
    if (pq) pq->size = 0; 
}

static void swap_task(Task *a, Task *b) {
    Task temp = *a; 
    *a = *b; 
    *b = temp;
}

/**
 * @brief 优先队列上浮调整 (根据 priority 比较)
 */
static void pq_sift_up(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->tasks[index].priority > pq->tasks[parent].priority) {
            swap_task(&pq->tasks[index], &pq->tasks[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

/**
 * @brief 优先队列下沉调整
 */
static void pq_sift_down(PriorityQueue *pq, int index) {
    while (2 * index + 1 < pq->size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int highest = index;

        if (left < pq->size && pq->tasks[left].priority > pq->tasks[highest].priority) {
            highest = left;
        }
        if (right < pq->size && pq->tasks[right].priority > pq->tasks[highest].priority) {
            highest = right;
        }

        if (highest != index) {
            swap_task(&pq->tasks[index], &pq->tasks[highest]);
            index = highest;
        } else {
            break;
        }
    }
}

/**
 * @brief 提交新任务入队
 * @note 时间复杂度: O(log N)
 */
bool pq_push(PriorityQueue *pq, int priority, const char *name) {
    if (pq->size >= PQ_CAPACITY) return false;

    pq->tasks[pq->size].priority = priority;
    snprintf(pq->tasks[pq->size].name, sizeof(pq->tasks[pq->size].name), "%s", name);
    
    pq_sift_up(pq, pq->size);
    pq->size++;
    return true;
}

/**
 * @brief 弹出并执行当前最高优先级任务
 * @note 时间复杂度: O(log N)
 */
bool pq_pop(PriorityQueue *pq, Task *out_task) {
    if (pq->size <= 0) return false;
    if (out_task) *out_task = pq->tasks[0];

    pq->tasks[0] = pq->tasks[pq->size - 1];
    pq->size--;
    pq_sift_down(pq, 0);

    return true;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    PriorityQueue pq;
    pq_init(&pq);

    printf("==================== 操作系统中断与任务调度模拟 (优先队列) ====================\n\n");
    pq_push(&pq, 1, "低优先级：后台日志转储同步");
    pq_push(&pq, 5, "高优先级：用户点击实时 UI 响应");
    pq_push(&pq, 10, "紧急级别：系统硬件中断与掉电保护");
    pq_push(&pq, 3, "中优先级：数据网络包接收处理");

    Task t;
    while (pq_pop(&pq, &t)) {
        printf("⚡ [优先调度执行] 优先级: %2d | 任务: %s\n", t.priority, t.name);
    }
    return 0;
}

#include <stdio.h>
#include <stdbool.h>

#define PQ_CAPACITY 64

/**
 * 💡【知识点】基于二叉堆的优先队列 (Priority Queue)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 优先队列特征：元素出队顺序由其**优先级 (Priority)** 决定，而非单纯的入队时间先后。
 *   2. 性能优势：基于二叉堆实现的优先队列，插入元素与提取最高优先级元素的时间复杂度均为高效的 $O(\log N)$。
 * -----------------------------------------------------------------------------
 */

typedef struct Task {
    int priority;    // 优先级数值越大，优先级越高
    char name[32];   // 任务描述
} Task;

typedef struct PriorityQueue {
    Task tasks[PQ_CAPACITY];
    int size;
} PriorityQueue;

void pq_init(PriorityQueue *pq) { if (pq) pq->size = 0; }

static void swap_task(Task *a, Task *b) {
    Task temp = *a; *a = *b; *b = temp;
}

static void pq_sift_up(PriorityQueue *pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->tasks[index].priority > pq->tasks[parent].priority) {
            swap_task(&pq->tasks[index], &pq->tasks[parent]);
            index = parent;
        } else break;
    }
}

static void pq_sift_down(PriorityQueue *pq, int index) {
    while (2 * index + 1 < pq->size) {
        int left = 2 * index + 1, right = 2 * index + 2;
        int highest = index;

        if (left < pq->size && pq->tasks[left].priority > pq->tasks[highest].priority) highest = left;
        if (right < pq->size && pq->tasks[right].priority > pq->tasks[highest].priority) highest = right;

        if (highest != index) {
            swap_task(&pq->tasks[index], &pq->tasks[highest]);
            index = highest;
        } else break;
    }
}

bool pq_push(PriorityQueue *pq, int priority, const char *name) {
    if (pq->size >= PQ_CAPACITY) return false;
    pq->tasks[pq->size].priority = priority;
    snprintf(pq->tasks[pq->size].name, sizeof(pq->tasks[pq->size].name), "%s", name);
    pq_sift_up(pq, pq->size);
    pq->size++;
    return true;
}

bool pq_pop(PriorityQueue *pq, Task *out_task) {
    if (pq->size <= 0) return false;
    if (out_task) *out_task = pq->tasks[0];
    pq->tasks[0] = pq->tasks[pq->size - 1];
    pq->size--;
    pq_sift_down(pq, 0);
    return true;
}

int main(void) {
    PriorityQueue pq;
    pq_init(&pq);

    printf("=== 操作系统任务调度模拟 (优先队列) ===\n\n");
    pq_push(&pq, 1, "低优先级：后台日志同步");
    pq_push(&pq, 5, "高优先级：用户点击实时响应");
    pq_push(&pq, 10, "紧急级别：系统硬件中断处理");
    pq_push(&pq, 3, "中优先级：数据网络包接收");

    Task t;
    while (pq_pop(&pq, &t)) {
        printf("⚡ [调度执行] 优先级: %2d | 任务: %s\n", t.priority, t.name);
    }
    return 0;
}

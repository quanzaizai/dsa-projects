#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * =============================================================================
 * 💡【知识点】数据结构 —— 双端队列 (Double-Ended Queue / Deque)
 * =============================================================================
 * 
 * 📌【1. 什么是双端队列？】
 *   双端队列结合了「栈 (LIFO)」与「队列 (FIFO)」的全部优势：
 *   - 允许在队列的「两端（头部 Front 和尾部 Rear）」自由进行插入与弹出。
 *   - 4 种核心操作：
 *     ① `push_front` (队头入)  ② `pop_front` (队头出)
 *     ③ `push_rear`  (队尾入)  ④ `pop_rear`  (队尾出)
 * 
 * 📌【2. 内存模型与操作图解】
 * 
 *        push_front ↘                          ↙ push_rear
 *        pop_front  ↙                          ↘ pop_rear
 *                +---------------------------------+
 *                | [Front] <===> [Node] <===> [Rear]|
 *                +---------------------------------+
 * 
 * 📌【3. 经典工业级应用场景 (Q&A)】
 * 
 *   ❓ Q1: 双端队列在实际工程和高频算法中有哪些杀手级应用？
 *      👉 解答：
 *         - **单调队列 / 滑动窗口最大值 (LeetCode 239)**：利用 Deque 两端弹出的特性维护单调性，实现 O(N) 窗口极值。
 *         - **工作窃取算法 (Work-Stealing Pool)**：Go 语言 Goroutine 调度器及 Java ForkJoinPool 中，
 *           每个工作线程从自己的 Deque 头部取任务，空闲线程从其他线程的 Deque 尾部“窃取”任务，极致减少锁竞争！
 * =============================================================================
 */

// ==================== 1. 双端队列结构与接口 ====================

typedef struct DequeNode {
    int data;
    struct DequeNode *prev;
    struct DequeNode *next;
} DequeNode;

typedef struct Deque {
    DequeNode *front; // 队头指针
    DequeNode *rear;  // 队尾指针
    int size;         // 元素总数
} Deque;

void deque_init(Deque *dq) {
    if (dq) {
        dq->front = dq->rear = NULL;
        dq->size = 0;
    }
}

bool deque_is_empty(const Deque *dq) {
    return (dq == NULL || dq->front == NULL);
}

/**
 * @brief 队头入队 (Push Front) —— O(1)
 */
void deque_push_front(Deque *dq, int val) {
    if (dq == NULL) return;

    DequeNode *n = (DequeNode *)malloc(sizeof(DequeNode));
    n->data = val;
    n->prev = NULL;
    n->next = dq->front;

    if (dq->front == NULL) {
        dq->front = dq->rear = n;
    } else {
        dq->front->prev = n;
        dq->front = n;
    }
    dq->size++;
}

/**
 * @brief 队尾入队 (Push Rear) —— O(1)
 */
void deque_push_rear(Deque *dq, int val) {
    if (dq == NULL) return;

    DequeNode *n = (DequeNode *)malloc(sizeof(DequeNode));
    n->data = val;
    n->next = NULL;
    n->prev = dq->rear;

    if (dq->rear == NULL) {
        dq->front = dq->rear = n;
    } else {
        dq->rear->next = n;
        dq->rear = n;
    }
    dq->size++;
}

/**
 * @brief 队头出队 (Pop Front) —— O(1)
 */
bool deque_pop_front(Deque *dq, int *out_val) {
    if (deque_is_empty(dq)) return false;

    DequeNode *temp = dq->front;
    if (out_val) *out_val = temp->data;

    dq->front = dq->front->next;
    if (dq->front == NULL) {
        dq->rear = NULL; // 队列变空，尾指针同步置空
    } else {
        dq->front->prev = NULL;
    }

    free(temp);
    dq->size--;
    return true;
}

/**
 * @brief 队尾出队 (Pop Rear) —— O(1)
 */
bool deque_pop_rear(Deque *dq, int *out_val) {
    if (deque_is_empty(dq)) return false;

    DequeNode *temp = dq->rear;
    if (out_val) *out_val = temp->data;

    dq->rear = dq->rear->prev;
    if (dq->rear == NULL) {
        dq->front = NULL; // 队列变空，头指针同步置空
    } else {
        dq->rear->next = NULL;
    }

    free(temp);
    dq->size--;
    return true;
}

/**
 * @brief 打印双端队列内容
 */
void deque_print(const Deque *dq) {
    printf("【双端队列】(Front -> Rear, size=%d): [头] ", dq->size);
    DequeNode *curr = dq->front;
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL) printf(" <-> ");
        curr = curr->next;
    }
    printf(" [尾]\n");
}

void deque_destroy(Deque *dq) {
    if (dq == NULL) return;
    DequeNode *curr = dq->front;
    while (curr != NULL) {
        DequeNode *next = curr->next;
        free(curr);
        curr = next;
    }
    dq->front = dq->rear = NULL;
    dq->size = 0;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    Deque dq;
    deque_init(&dq);

    printf("==================== 双端队列 4 种出入操作验证 ====================\n\n");

    // 混合入队测试
    deque_push_front(&dq, 20);
    deque_push_front(&dq, 10); // 10 插入最前面
    deque_push_rear(&dq, 30);  // 30 插入最后面
    deque_push_rear(&dq, 40);  // 40 插入最后面
    deque_print(&dq);

    // 混合出队测试
    int val;
    deque_pop_front(&dq, &val);
    printf("⬅️ 从队头弹出: %d\n", val);
    deque_pop_rear(&dq, &val);
    printf("➡️ 从队尾弹出: %d\n", val);
    deque_print(&dq);

    deque_destroy(&dq);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * 💡【知识点】双端队列 (Double-Ended Queue / Deque)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 结构特征：允许在队列的两端（头部 Front 和尾部 Rear）同时进行高效的插入与删除。
 *   2. 实现方案：基于双向链表 (Doubly Linked List)，所有 4 个核心操作均达到严格的 $O(1)$：
 *      - `push_front` (队头入队) / `pop_front` (队头出队)
 *      - `push_rear`  (队尾入队) / `pop_rear`  (队尾出队)
 *   3. 经典场景：滑动窗口最大值、任务工作窃取 (Work-Stealing) 调度算法。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 双端队列结构与接口 ====================

typedef struct DequeNode {
    int data;
    struct DequeNode *prev;
    struct DequeNode *next;
} DequeNode;

typedef struct Deque {
    DequeNode *front;
    DequeNode *rear;
    int size;
} Deque;

void deque_init(Deque *dq) {
    if (dq) {
        dq->front = dq->rear = NULL;
        dq->size = 0;
    }
}

bool deque_is_empty(const Deque *dq) {
    return dq == NULL || dq->front == NULL;
}

// 队头插入 O(1)
void deque_push_front(Deque *dq, int val) {
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

// 队尾插入 O(1)
void deque_push_rear(Deque *dq, int val) {
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

// 队头弹出 O(1)
bool deque_pop_front(Deque *dq, int *out_val) {
    if (deque_is_empty(dq)) return false;
    DequeNode *temp = dq->front;
    if (out_val) *out_val = temp->data;

    dq->front = dq->front->next;
    if (dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }
    free(temp);
    dq->size--;
    return true;
}

// 队尾弹出 O(1)
bool deque_pop_rear(Deque *dq, int *out_val) {
    if (deque_is_empty(dq)) return false;
    DequeNode *temp = dq->rear;
    if (out_val) *out_val = temp->data;

    dq->rear = dq->rear->prev;
    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }
    free(temp);
    dq->size--;
    return true;
}

void deque_print(const Deque *dq) {
    printf("【双端队列】(Front -> Rear): [头] ");
    DequeNode *curr = dq->front;
    while (curr) {
        printf("%d", curr->data);
        if (curr->next) printf(" <-> ");
        curr = curr->next;
    }
    printf(" [尾]\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    Deque dq;
    deque_init(&dq);

    printf("=== 双端队列灵活出入测试 ===\n");
    deque_push_front(&dq, 20);
    deque_push_front(&dq, 10); // 10 插入最前
    deque_push_rear(&dq, 30);  // 30 插入最后
    deque_push_rear(&dq, 40);  // 40 插入最后
    deque_print(&dq);

    int val;
    deque_pop_front(&dq, &val);
    printf("从队头弹出: %d\n", val);
    deque_pop_rear(&dq, &val);
    printf("从队尾弹出: %d\n", val);
    deque_print(&dq);

    return 0;
}

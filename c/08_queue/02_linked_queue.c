#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * 💡【知识点】数据结构 —— 链式队列 (Linked Queue)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 结构设计：基于单链表，维护 `front` (指向头节点) 和 `rear` (指向尾节点) 两个指针。
 *   2. 入队 (Enqueue)：在链表**尾部插入**新节点，更新 `rear` 指针 ($O(1)$)。
 *   3. 出队 (Dequeue)：在链表**头部删除**节点，更新 `front` 指针并 `free()` 内存 ($O(1)$)。
 *   4. 核心优势：动态扩容无容量上限，兼顾链表的灵活性与队列的严谨 FIFO 规则。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 结构定义与核心接口 ====================

typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

typedef struct LinkedQueue {
    QNode *front; // 队头指针
    QNode *rear;  // 队尾指针
    int size;
} LinkedQueue;

void linked_queue_init(LinkedQueue *q) {
    if (q) {
        q->front = q->rear = NULL;
        q->size = 0;
    }
}

bool linked_queue_is_empty(const LinkedQueue *q) {
    return q == NULL || q->front == NULL;
}

int linked_queue_size(const LinkedQueue *q) {
    return (q == NULL) ? 0 : q->size;
}

/**
 * @brief 入队 (Enqueue) —— 尾插法
 */
bool linked_queue_enqueue(LinkedQueue *q, int val) {
    if (q == NULL) return false;

    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    if (!newNode) return false;
    newNode->data = val;
    newNode->next = NULL;

    // 若原队列为空，新节点既是队头也是队尾
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode; // 原队尾连接新节点
        q->rear = newNode;       // 队尾指针后移
    }
    q->size++;

    printf("➡️ [Enqueue] %d 入队 | 当前长度: %d\n", val, q->size);
    return true;
}

/**
 * @brief 出队 (Dequeue) —— 头删法
 */
bool linked_queue_dequeue(LinkedQueue *q, int *out_val) {
    if (linked_queue_is_empty(q)) {
        printf("⚠️ [Dequeue 失败] 队列为空！\n");
        return false;
    }

    QNode *temp = q->front;
    if (out_val) *out_val = temp->data;

    q->front = q->front->next; // 队头指针后移
    // 若出队后队列变空，必须同步置空 rear
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp); // 释放内存
    q->size--;

    return true;
}

void linked_queue_destroy(LinkedQueue *q) {
    if (q == NULL) return;
    QNode *curr = q->front;
    while (curr) {
        QNode *next = curr->next;
        free(curr);
        curr = next;
    }
    q->front = q->rear = NULL;
    q->size = 0;
    printf("🧹 [销毁] 链式队列堆内存已完全释放\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    LinkedQueue q;
    linked_queue_init(&q);

    printf("=== 链式队列生命周期测试 ===\n\n");
    linked_queue_enqueue(&q, 100);
    linked_queue_enqueue(&q, 200);
    linked_queue_enqueue(&q, 300);

    int val;
    linked_queue_dequeue(&q, &val);
    printf("⬅️ [Dequeue] 弹出: %d\n", val);
    linked_queue_dequeue(&q, &val);
    printf("⬅️ [Dequeue] 弹出: %d\n", val);

    linked_queue_enqueue(&q, 400);

    linked_queue_destroy(&q);
    return 0;
}

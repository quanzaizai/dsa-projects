// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdlib.h>   // 标准通用工具库：提供 malloc(), free(), exit(), NULL 等堆内存动态分配与释放支持
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

/**
 * =============================================================================
 * 💡【知识点】数据结构 —— 链式队列 (Linked Queue)
 * =============================================================================
 * 
 * 📌【1. 什么是链式队列？】
 *   链式队列是用单链表实现的 FIFO (First In First Out，先进先出) 队列。
 *   - 队头指针 `front`：固定指向单链表的「首节点」，负责执行出队（头删法 O(1)）。
 *   - 队尾指针 `rear` ：固定指向单链表的「尾节点」，负责执行入队（尾插法 O(1)）。
 * 
 * 📌【2. 内存模型与入队/出队图解】
 * 
 *   [LinkedQueue 队列管理器]
 *   +-------------+------------+---------+
 *   | front(指针) | rear(指针) | size: 3 |
 *   +------+------+-----+------+---------+
 *          |            |
 *          v            +--------------------+
 *       +-------+------+       +-------+----+|       +-------+------+
 *       | 10  * | next | ----> | 20  * | next | ---> | 30  * | NULL |
 *       +-------+------+       +-------+------+       +-------+------+
 *        ▲ 队头 (Front)                                ▲ 队尾 (Rear)
 *        (负责 Dequeue 出队)                           (负责 Enqueue 入队)
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 当弹出队列中的「最后一个节点」时，需要特别注意什么？
 *      👉 解答（经典空指针同步细节）：
 *         - 出队操作执行 `front = front->next` 后，`front` 变成了 `NULL`。
 *         - 此时原最后一个节点的内存已经被 `free(temp)` 释放掉了！
 *         - 如果不对 `rear` 做处理，`rear` 就会变成指向已释放内存的「野指针」。
 *         - 因此必须检查：`if (q->front == NULL) q->rear = NULL;` 将 `rear` 也同步置空！
 * =============================================================================
 */

// ==================== 1. 结构定义与核心接口 ====================

typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

typedef struct LinkedQueue {
    QNode *front; // 队头指针：指向单链表第一个节点
    QNode *rear;  // 队尾指针：指向单链表最后一个节点
    int size;     // 有效元素计数
} LinkedQueue;

/**
 * @brief 初始化链式队列
 */
void linked_queue_init(LinkedQueue *q) {
    if (q) {
        q->front = q->rear = NULL;
        q->size = 0;
    }
}

/**
 * @brief 检查队列是否为空
 */
bool linked_queue_is_empty(const LinkedQueue *q) {
    return (q == NULL || q->front == NULL);
}

/**
 * @brief 获取队列元素个数
 */
int linked_queue_size(const LinkedQueue *q) {
    return (q == NULL) ? 0 : q->size;
}

/**
 * @brief 元素入队 (Enqueue) —— 尾插法 O(1)
 * 
 * @param q   队列指针
 * @param val 待入队数据
 * @return true 成功, false 堆内存不足
 */
bool linked_queue_enqueue(LinkedQueue *q, int val) {
    if (q == NULL) return false;

    // 【步骤 1】申请新节点
    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    if (!newNode) return false;
    newNode->data = val;
    newNode->next = NULL;

    // 【步骤 2】若原队列为空，新节点同时作为队头和队尾
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        // 原队尾节点连接新节点
        q->rear->next = newNode;
        // 队尾指针后移到新节点
        q->rear = newNode;
    }

    q->size++;
    printf("➡️ [Enqueue] 元素 %d 入队 | 当前队列长度: %d\n", val, q->size);
    return true;
}

/**
 * @brief 元素出队 (Dequeue) —— 头删法 O(1)
 * 
 * @param q       队列指针
 * @param out_val 接收弹出数据的指针
 * @return true 成功, false 队空失败
 */
bool linked_queue_dequeue(LinkedQueue *q, int *out_val) {
    // 【步骤 1】防下溢检查
    if (linked_queue_is_empty(q)) {
        printf("⚠️ [Dequeue 失败] 队列为空！\n");
        return false;
    }

    // 【步骤 2】暂存队头节点指针
    QNode *temp = q->front;
    if (out_val) {
        *out_val = temp->data;
    }

    // 【步骤 3】队头指针后移
    q->front = q->front->next;

    // 【步骤 4】⚠️ 关键细节：若出队后队列变空，必须把 rear 也同步置空！
    if (q->front == NULL) {
        q->rear = NULL;
    }

    // 【步骤 5】释放原队头内存
    free(temp);
    q->size--;

    return true;
}

/**
 * @brief 销毁链式队列并释放所有节点内存
 */
void linked_queue_destroy(LinkedQueue *q) {
    if (q == NULL) return;
    QNode *curr = q->front;
    while (curr != NULL) {
        QNode *next_node = curr->next;
        free(curr);
        curr = next_node;
    }
    q->front = q->rear = NULL;
    q->size = 0;
    printf("🧹 [销毁] 链式队列堆内存已完全释放\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    LinkedQueue q;
    linked_queue_init(&q);

    printf("==================== 链式队列全生命周期验证 ====================\n\n");
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

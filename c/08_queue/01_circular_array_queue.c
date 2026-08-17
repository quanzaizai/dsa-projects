#include <stdio.h>
#include <stdbool.h>

#define QUEUE_CAPACITY 6 // 队列数组容量（实际最多容纳 CAPACITY - 1 个元素）

/**
 * 💡【知识点】数据结构 —— 循环队列 (Circular Queue / 顺序队列)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. FIFO (先进先出)：元素从队尾 (Rear) 入队，从队头 (Front) 出队。
 *   2. 假溢出破局：普通数组队列出队后前端空间无法再使用（假溢出）。
 *      循环队列通过**取模运算 `% CAPACITY`** 将数组首尾相连成环形缓冲区。
 *   3. 判空与判满经典设计（牺牲一个数组存储单元）：
 *      - 队空条件：`front == rear`
 *      - 队满条件：`(rear + 1) % CAPACITY == front`
 *   4. 时空复杂度：入队、出队均为严苛的 $O(1)$，空间利用率极高。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 循环队列结构与接口 ====================

typedef struct CircularQueue {
    int data[QUEUE_CAPACITY];
    int front; // 队头指针（指向当前队头元素所在下标）
    int rear;  // 队尾指针（指向下一个元素即将插入的位置）
} CircularQueue;

void queue_init(CircularQueue *q) {
    if (q) {
        q->front = 0;
        q->rear = 0;
    }
}

bool queue_is_empty(const CircularQueue *q) {
    return q == NULL || q->front == q->rear;
}

bool queue_is_full(const CircularQueue *q) {
    return q != NULL && (q->rear + 1) % QUEUE_CAPACITY == q->front;
}

int queue_size(const CircularQueue *q) {
    if (q == NULL) return 0;
    return (q->rear - q->front + QUEUE_CAPACITY) % QUEUE_CAPACITY;
}

/**
 * @brief 入队 (Enqueue)
 */
bool queue_enqueue(CircularQueue *q, int val) {
    if (queue_is_full(q)) {
        printf("⚠️ [Enqueue 失败] 队列已满！无法插入 %d\n", val);
        return false;
    }

    q->data[q->rear] = val;
    // 🔍【环形前进】：取模运算绕回数组头部
    q->rear = (q->rear + 1) % QUEUE_CAPACITY;
    printf("➡️ [Enqueue 成功] %d 已入队 | 当前元素数: %d\n", val, queue_size(q));
    return true;
}

/**
 * @brief 出队 (Dequeue)
 */
bool queue_dequeue(CircularQueue *q, int *out_val) {
    if (queue_is_empty(q)) {
        printf("⚠️ [Dequeue 失败] 队列为空！\n");
        return false;
    }

    if (out_val) *out_val = q->data[q->front];
    // 🔍【环形前进】：队头指针取模后移
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    return true;
}

void queue_print(const CircularQueue *q) {
    if (queue_is_empty(q)) {
        printf("【队列状态】: [ 空队列 ]\n");
        return;
    }
    printf("【队列状态】(队头 -> 队尾): [头] ");
    int curr = q->front;
    while (curr != q->rear) {
        printf("%d", q->data[curr]);
        curr = (curr + 1) % QUEUE_CAPACITY;
        if (curr != q->rear) printf(" -> ");
    }
    printf(" [尾]\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    CircularQueue q;
    queue_init(&q);

    printf("==================== 1. 循环队列入队测试 ====================\n");
    queue_enqueue(&q, 10);
    queue_enqueue(&q, 20);
    queue_enqueue(&q, 30);
    queue_enqueue(&q, 40);
    queue_enqueue(&q, 50);
    queue_print(&q);

    // 满队测试 (容量 6 牺牲 1 位，最多放 5 个)
    printf("\n==================== 2. 队满防御测试 ====================\n");
    queue_enqueue(&q, 60);

    printf("\n==================== 3. 出队与环形复用测试 ====================\n");
    int val;
    queue_dequeue(&q, &val);
    printf("⬅️ [Dequeue] 弹出: %d\n", val);
    queue_dequeue(&q, &val);
    printf("⬅️ [Dequeue] 弹出: %d\n", val);
    queue_print(&q);

    printf("\n➡️ 再次入队验证环形空间复用:\n");
    queue_enqueue(&q, 99);
    queue_enqueue(&q, 100);
    queue_print(&q);

    return 0;
}

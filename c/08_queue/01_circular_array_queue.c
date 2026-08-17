#include <stdio.h>
#include <stdbool.h>

#define QUEUE_CAPACITY 6 // 队列底层数组物理长度（最多容纳 CAPACITY - 1 = 5 个元素）

/**
 * =============================================================================
 * 💡【知识点】数据结构 —— 循环队列 (Circular Queue / 环形缓冲区)
 * =============================================================================
 * 
 * 📌【1. 什么是循环队列？为什么要循环？】
 *   - 普通数组队列的致命缺陷（假溢出）：
 *     每次出队 `front++`，数组前端腾出的空间无法再被利用；当 `rear` 走到数组末尾时，
 *     哪怕前面全是空位，也无法再入队，这被称为「假溢出 (False Overflow)」。
 *   - 循环队列的解决方案：
 *     利用「取模运算 `% CAPACITY`」，让指针到达数组末尾后自动折返到下标 0，形成首尾相连的逻辑环形缓冲区！
 * 
 * 📌【2. 环形队列时钟模型与判空/判满原理图解】
 * 
 *            [0]
 *          /     \
 *       [5]       [1]     QUEUE_CAPACITY = 6 (牺牲 1 个单元区分满与空)
 *        |         |
 *       [4]       [2]
 *          \     /
 *            [3]
 * 
 *   - 判空 (Empty) : `front == rear`
 *   - 判满 (Full)  : `(rear + 1) % CAPACITY == front` (队尾的下一个位置就是队头)
 *   - 元素个数     : `(rear - front + CAPACITY) % CAPACITY`
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么要特意“牺牲”一个存储单元（容量为 6 却只能放 5 个元素）？
 *      👉 解答：
 *         - 如果不牺牲单元，当队列全满时，`rear` 转一圈追上了 `front`，此时 `front == rear`。
 *         - 而队列全空时，初始状态也是 `front == rear`！
 *         - 这导致无法仅凭指针位置区分是“全空”还是“全满”。
 *         - 牺牲 1 个单元后：全空是 `front == rear`，全满是 `(rear+1)%CAP == front`，界限泾渭分明。
 * =============================================================================
 */

// ==================== 1. 循环队列结构与接口 ====================

typedef struct CircularQueue {
    int data[QUEUE_CAPACITY]; // 存储数据的静态数组
    int front;                // 队头游标：指向当前队头元素所在的下标
    int rear;                 // 队尾游标：指向下一个元素即将写入的空槽位下标
} CircularQueue;

/**
 * @brief 初始化循环队列
 */
void queue_init(CircularQueue *q) {
    if (q) {
        q->front = 0;
        q->rear = 0;
    }
}

/**
 * @brief 判断队列是否为空
 */
bool queue_is_empty(const CircularQueue *q) {
    return q == NULL || q->front == q->rear;
}

/**
 * @brief 判断队列是否已满 (牺牲 1 单元判满法)
 */
bool queue_is_full(const CircularQueue *q) {
    return q != NULL && (q->rear + 1) % QUEUE_CAPACITY == q->front;
}

/**
 * @brief 计算当前队列中的有效元素个数
 */
int queue_size(const CircularQueue *q) {
    if (q == NULL) return 0;
    return (q->rear - q->front + QUEUE_CAPACITY) % QUEUE_CAPACITY;
}

/**
 * @brief 元素入队 (Enqueue)
 * 
 * @param q   队列指针
 * @param val 待入队数据
 * @return true 成功, false 队满失败
 * 
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
bool queue_enqueue(CircularQueue *q, int val) {
    // 【步骤 1】防上溢检查
    if (queue_is_full(q)) {
        printf("⚠️ [Enqueue 失败] 循环队列已满 (容量上限: %d)，无法压入 %d！\n", QUEUE_CAPACITY - 1, val);
        return false;
    }

    // 【步骤 2】在 rear 所指槽位写入数据
    q->data[q->rear] = val;

    // 【步骤 3】通过取模运算实现环形向前推进
    q->rear = (q->rear + 1) % QUEUE_CAPACITY;

    printf("➡️ [Enqueue 成功] 元素 %d 已入队 | 当前有效长度: %d\n", val, queue_size(q));
    return true;
}

/**
 * @brief 元素出队 (Dequeue)
 * 
 * @param q       队列指针
 * @param out_val 接收弹出数据的指针
 * @return true 成功, false 队空失败
 * 
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
bool queue_dequeue(CircularQueue *q, int *out_val) {
    // 【步骤 1】放下溢检查
    if (queue_is_empty(q)) {
        printf("⚠️ [Dequeue 失败] 队列为空，无法出队！\n");
        return false;
    }

    // 【步骤 2】取出队头元素
    if (out_val) {
        *out_val = q->data[q->front];
    }

    // 【步骤 3】队头指针环形后移
    q->front = (q->front + 1) % QUEUE_CAPACITY;

    return true;
}

/**
 * @brief 可视化打印环形队列从队头到队尾的内容
 */
void queue_print(const CircularQueue *q) {
    if (queue_is_empty(q)) {
        printf("【队列状态】: [ 空队列 ]\n");
        return;
    }

    printf("【队列状态】(队头 -> 队尾, size = %d): [队头] ", queue_size(q));
    int curr = q->front;
    while (curr != q->rear) {
        printf("%d", q->data[curr]);
        curr = (curr + 1) % QUEUE_CAPACITY; // 环形移动游标
        if (curr != q->rear) printf(" -> ");
    }
    printf(" [队尾]\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    CircularQueue q;
    queue_init(&q);

    printf("==================== 1. 连续入队测试 (至满载) ====================\n");
    queue_enqueue(&q, 10);
    queue_enqueue(&q, 20);
    queue_enqueue(&q, 30);
    queue_enqueue(&q, 40);
    queue_enqueue(&q, 50);
    queue_print(&q);

    // 满队测试 (物理长度为 6，但最多存 5 个)
    printf("\n==================== 2. 满队溢出防御测试 ====================\n");
    queue_enqueue(&q, 60);

    printf("\n==================== 3. 连续出队腾出空间 ====================\n");
    int val;
    queue_dequeue(&q, &val);
    printf("⬅️ [Dequeue] 弹出: %d\n", val);
    queue_dequeue(&q, &val);
    printf("⬅️ [Dequeue] 弹出: %d\n", val);
    queue_print(&q);

    printf("\n==================== 4. 再次入队验证空间环形复用 ====================\n");
    queue_enqueue(&q, 99);
    queue_enqueue(&q, 100);
    queue_print(&q);

    return 0;
}

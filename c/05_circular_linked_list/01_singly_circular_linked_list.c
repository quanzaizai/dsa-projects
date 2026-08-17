#include <stdio.h>
#include <stdlib.h>

/**
 * =============================================================================
 * 💡【知识点】单向循环链表 (Singly Circular Linked List) —— 环形闭环与 do-while 遍历
 * =============================================================================
 * 
 * 📌【1. 什么是单向循环链表？】
 *   单向循环链表是单链表的变体。它与普通单链表唯一的物理结构差异在于：
 *   - 普通单链表：尾节点的 `next` 指针指向 `NULL`。
 *   - 循环单链表：尾节点的 `next` 指针重新指向「头节点 (Head)」，形成首尾相连的闭合环。
 * 
 * 📌【2. 环形闭环结构 ASCII 图解】
 * 
 *          head
 *           |
 *           v
 *         +---+------+     +---+------+     +---+------+
 *         | 1 | next | --> | 2 | next | --> | 3 | next | ---+
 *         +---+------+     +---+------+     +---+------+    |
 *           ^                                               |
 *           |                                               |
 *           +-----------------------------------------------+
 *                           【尾节点 next 指回 head】
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么遍历循环链表通常使用 `do-while` 而不是 `while`？
 *      👉 解答：
 *         - 如果写 `while (curr != head)`，一开始初始化 `curr = head` 时，条件 `head != head` 直接为假，
 *           导致循环体一次都不会执行！
 *         - `do-while` 保证先进入循环体访问当前节点并移动一次（`curr = curr->next`），
 *           之后当 `curr` 绕了一整圈重新回到 `head` 时刚好终止循环。
 * 
 *   ❓ Q2: 循环链表如何安全释放全部内存？
 *      👉 解答：必须在遍历释放前打破环（如把尾节点的 next 置为 NULL），或者用计数/指针标记确保只转一圈，
 *         防止陷入死循环。
 * =============================================================================
 */

// ==================== 1. 结构与环形构建 ====================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = data;
    n->next = NULL;
    return n;
}

/**
 * @brief 安全释放单向循环链表
 */
void free_circular_list(Node *head) {
    if (head == NULL) return;

    Node *curr = head;
    Node *next_node = NULL;
    
    // 先打破环，将尾节点与 head 断开，退化为普通单链表后再逐一释放
    Node *tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = NULL; // 打破环形闭环！

    // 普通单链表释放
    while (curr != NULL) {
        next_node = curr->next;
        free(curr);
        curr = next_node;
    }
    printf("🧹 [清理完毕] 循环链表已破环并安全释放内存\n");
}

// ==================== 2. 测试与环形遍历 ====================

int main(void) {
    printf("==================== 单向循环链表遍历验证 ====================\n");

    // 【步骤 1】创建 3 个独立节点
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);

    // 【步骤 2】将尾节点的 next 指向头节点，完成闭环
    head->next->next->next = head;

    // 【步骤 3】使用 do-while 结构精准遍历一整圈
    printf("循环链表一整圈遍历结果: ");
    Node *curr = head;
    do {
        printf("[%d] -> ", curr->data);
        curr = curr->next; // 顺指针前进
    } while (curr != head); // 当指针重新对齐 head 时刚好整整绕了一圈！

    printf("(回到起点 head: %d)\n", head->data);

    // 释放资源
    free_circular_list(head);
    head = NULL;

    return 0;
}

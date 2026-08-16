#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】单向循环链表：结构闭环与 do-while 遍历
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 结构特征：尾节点的 next 指针不再指向 NULL，而是指向头节点 head，形成环状闭环。
 *   2. 遍历模式：使用 do-while 循环（先执行一步，直到 curr 重新等于 head 结束遍历）。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 结构与环形构建 ====================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

// ==================== 2. 测试与环形遍历 ====================

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = head; // 🔍 尾节点指向头节点闭环

    printf("循环链表一圈遍历: ");
    Node *curr = head;
    do {
        printf("%d -> ", curr->data);
        curr = curr->next;
    } while (curr != head);
    printf("(回到起点 head: %d)\n", head->data);

    return 0;
}

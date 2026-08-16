#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】单链表核心删除操作：按值删除 (Delete by Value)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 核心逻辑：删除节点需要定位待删节点 curr 和其前驱节点 prev。
 *   2. 指针重定向：`prev->next = curr->next;` 跨过待删节点完成解绑，随后 `free(curr)` 释放内存。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 链表删除算法 ====================

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

void delete_value(Node **head_ref, int key) {
    Node *curr = *head_ref, *prev = NULL;

    // 情况 1: 头节点恰好就是待删除的目标值
    if (curr != NULL && curr->data == key) {
        *head_ref = curr->next;
        free(curr);
        return;
    }

    // 情况 2: 遍历查找目标节点及其前驱节点
    while (curr != NULL && curr->data != key) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) return; // 链表中未找到目标值

    // 🔍【解绑跨越】：前驱跳过当前节点，连接后继节点
    prev->next = curr->next;
    free(curr);
}

void print_list(Node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    printf("删除前: ");
    print_list(head);

    delete_value(&head, 20); // 删除值为 20 的中间节点

    printf("删除 20 后: ");
    print_list(head);

    return 0;
}

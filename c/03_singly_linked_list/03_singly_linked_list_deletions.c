#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】单链表核心删除操作：头删与按值删除
 * -----------------------------------------------------------------------------
 * 1. 头删 O(1)：temp = head; head = head->next; free(temp);
 * 2. 按值删除 O(N)：找到目标节点的前驱 prev，执行 prev->next = curr->next; free(curr);
 * -----------------------------------------------------------------------------
 */

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
    if (curr != NULL && curr->data == key) {
        *head_ref = curr->next;
        free(curr);
        return;
    }
    while (curr != NULL && curr->data != key) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) return; // 未找到
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

int main(void) {
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    printf("删除前: ");
    print_list(head);

    delete_value(&head, 20); // 删除值为 20 的节点

    printf("删除 20 后: ");
    print_list(head);

    return 0;
}

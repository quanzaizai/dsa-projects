#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】单向循环链表：结构闭环与遍历
 * -----------------------------------------------------------------------------
 * 1. 结构特点：尾节点的 next 指针指向头节点 head，形成首尾相连的环。
 * 2. 遍历方式：使用 do-while 循环遍历一整圈。
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

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = head; // 尾部指向头部闭环

    printf("循环链表遍历一圈: ");
    Node *curr = head;
    do {
        printf("%d -> ", curr->data);
        curr = curr->next;
    } while (curr != head);
    printf("(回到了 head: %d)\n", head->data);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】单链表 (Singly Linked List)：创建、遍历与内存释放
 * -----------------------------------------------------------------------------
 * 1. 节点结构：包含数据域 (data) 和指针域 (next)。
 * 2. 内存回收：遍历链表时必须先保存下一个节点地址 (next)，再 free 当前节点。
 * -----------------------------------------------------------------------------
 */

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next; // 暂存下一节点
        free(curr);              // 释放当前节点
        curr = next;
    }
}

int main(void) {
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    printf("单链表: ");
    print_list(head);

    free_list(head);
    head = NULL;
    return 0;
}

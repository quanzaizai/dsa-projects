#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】双向链表插入操作
 * -----------------------------------------------------------------------------
 * 1. 黄金 4 步重连律：设置新节点的前后指针 -> 维护原节点与后继的前后指针。
 * -----------------------------------------------------------------------------
 */

typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

DNode* create_dnode(int data) {
    DNode *n = (DNode *)malloc(sizeof(DNode));
    n->data = data;
    n->prev = n->next = NULL;
    return n;
}

// 头部插入 O(1)
void insert_head(DNode **head_ref, int data) {
    DNode *newNode = create_dnode(data);
    newNode->next = *head_ref;
    if (*head_ref != NULL) {
        (*head_ref)->prev = newNode;
    }
    *head_ref = newNode;
}

void print_list(DNode *head) {
    while (head) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main(void) {
    DNode *head = NULL;
    insert_head(&head, 30);
    insert_head(&head, 20);
    insert_head(&head, 10);

    printf("双向链表头插结果: ");
    print_list(head);

    return 0;
}

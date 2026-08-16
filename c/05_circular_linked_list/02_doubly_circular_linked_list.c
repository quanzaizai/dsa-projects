#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】双向循环链表：双向闭环与 O(1) 首尾互访
 * -----------------------------------------------------------------------------
 * 1. 结构特征：head->prev 指向尾节点，tail->next 指向头节点。
 * 2. 优势：随时可以从头节点 O(1) 访问尾部。
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

int main(void) {
    DNode *head = create_dnode(10);
    DNode *tail = create_dnode(20);

    head->next = tail; tail->prev = head;
    tail->next = head; head->prev = tail; // 双向闭环

    printf("头节点: %d, 尾节点: %d\n", head->data, tail->data);
    printf("从头节点找尾节点 (head->prev): %d\n", head->prev->data);
    printf("从尾节点找头节点 (tail->next): %d\n", tail->next->data);

    return 0;
}

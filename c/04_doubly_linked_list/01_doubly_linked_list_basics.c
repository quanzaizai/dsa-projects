#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】双向链表 (Doubly Linked List)：双向指针与正反遍历
 * -----------------------------------------------------------------------------
 * 1. 结构特征：每个节点包含 prev (前驱) 和 next (后继) 两个指针。
 * 2. 优势：支持以 O(1) 访问前后相邻节点，可双向遍历。
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
    n->prev = NULL;
    n->next = NULL;
    return n;
}

int main(void) {
    DNode *n1 = create_dnode(10);
    DNode *n2 = create_dnode(20);
    DNode *n3 = create_dnode(30);

    // 建立双向连接
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;

    printf("正向遍历: ");
    DNode *curr = n1;
    while (curr) {
        printf("%d <-> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");

    return 0;
}

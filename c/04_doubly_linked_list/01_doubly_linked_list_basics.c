#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】双向链表 (Doubly Linked List)：双向指针与正反遍历
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 结构特征：每个节点包含 `prev` (指向前驱) 和 `next` (指向后继) 两个指针。
 *   2. 优势：支持 O(1) 直接访问前驱节点，可正向与逆向双向无缝遍历。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 结构体与初始化 ====================

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

// ==================== 2. 测试与双向验证 ====================

int main(void) {
    DNode *n1 = create_dnode(10);
    DNode *n2 = create_dnode(20);
    DNode *n3 = create_dnode(30);

    // 建立双向互联指针
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

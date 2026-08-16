#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】双向链表节点解绑与删除
 * -----------------------------------------------------------------------------
 * 1. O(1) 局部解绑：若已知节点指针 target，无需遍历即可通过 prev 和 next 完成断开并 free。
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

void delete_node(DNode **head_ref, DNode *del) {
    if (*head_ref == NULL || del == NULL) return;

    if (*head_ref == del) *head_ref = del->next;
    if (del->next != NULL) del->next->prev = del->prev;
    if (del->prev != NULL) del->prev->next = del->next;

    free(del);
}

void print_list(DNode *head) {
    while (head) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main(void) {
    DNode *head = create_dnode(10);
    DNode *n2 = create_dnode(20);
    head->next = n2; n2->prev = head;

    printf("删除前: ");
    print_list(head);

    delete_node(&head, n2);

    printf("删除 n2 后: ");
    print_list(head);

    return 0;
}

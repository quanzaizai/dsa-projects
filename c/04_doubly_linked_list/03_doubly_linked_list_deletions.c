#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】双向链表节点解绑与局部 O(1) 删除
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 局部 O(1) 解绑：若已知待删节点指针 target，无需像单链表那样从头遍历找前驱。
 *      直接操作 `target->prev->next = target->next` 和 `target->next->prev = target->prev`。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 解绑删除算法 ====================

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

    // 若待删除的是头节点
    if (*head_ref == del) *head_ref = del->next;
    // 维护后继节点的前驱指针
    if (del->next != NULL) del->next->prev = del->prev;
    // 维护前驱节点的后继指针
    if (del->prev != NULL) del->prev->next = del->next;

    free(del); // 释放内存
}

void print_list(DNode *head) {
    while (head) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    DNode *head = create_dnode(10);
    DNode *n2 = create_dnode(20);
    head->next = n2; n2->prev = head;

    printf("删除前: ");
    print_list(head);

    delete_node(&head, n2); // O(1) 直接解绑删除 n2

    printf("删除 n2 后: ");
    print_list(head);

    return 0;
}

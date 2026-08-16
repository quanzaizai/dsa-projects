#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】双向链表头部插入操作 (O(1))
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 黄金 4 步重连律：
 *      ① newNode->next = head
 *      ② newNode->prev = NULL
 *      ③ 原 head->prev = newNode
 *      ④ *head = newNode
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 头部插入算法 ====================

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

void insert_head(DNode **head_ref, int data) {
    DNode *newNode = create_dnode(data);
    newNode->next = *head_ref; // 新节点后继指向原头节点
    
    if (*head_ref != NULL) {
        (*head_ref)->prev = newNode; // 原头节点前驱指向新节点
    }
    *head_ref = newNode; // 头指针重定向
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
    DNode *head = NULL;
    insert_head(&head, 30);
    insert_head(&head, 20);
    insert_head(&head, 10);

    printf("双向链表头插构建结果: ");
    print_list(head);

    return 0;
}

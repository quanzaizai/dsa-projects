#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】双向循环链表：对称双向闭环与 O(1) 首尾互访
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 结构对称性：`head->prev` 直接指向尾节点 tail，`tail->next` 直接指向头节点 head。
 *   2. 核心优势：无需任何遍历，即可在 O(1) 常数时间内从头节点直接访问尾节点。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 结构定义 ====================

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

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    DNode *head = create_dnode(10);
    DNode *tail = create_dnode(20);

    // 构建双向循环闭环
    head->next = tail; tail->prev = head;
    tail->next = head; head->prev = tail;

    printf("头节点值: %d, 尾节点值: %d\n", head->data, tail->data);
    printf("🔍 从头节点 O(1) 直达尾节点 (head->prev): %d\n", head->prev->data);
    printf("🔍 从尾节点 O(1) 直达头节点 (tail->next): %d\n", tail->next->data);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】循环链表经典实战 —— 约瑟夫环问题 (Josephus Problem)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 问题模型：n 个人围坐成圈，从 1 报数到 m，报到 m 的人淘汰出局，随后下一个人重新从 1 报数，
 *      求最后幸存者的编号。
 *   2. 算法实现：使用单向循环链表模拟环形报数，报到 m 时解绑删除对应节点并 free，直到仅剩一个节点。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 约瑟夫环模拟算法 ====================

typedef struct Node {
    int id;
    struct Node *next;
} Node;

int josephus(int n, int m) {
    // 1. 构建包含 n 个人的单向循环链表
    Node *head = (Node *)malloc(sizeof(Node));
    head->id = 1;
    Node *prev = head;
    for (int i = 2; i <= n; i++) {
        Node *curr = (Node *)malloc(sizeof(Node));
        curr->id = i;
        prev->next = curr;
        prev = curr;
    }
    prev->next = head; // 尾首闭环

    // 2. 模拟报数淘汰出圈
    Node *curr = head;
    while (curr->next != curr) { // 只要环中不止 1 个人
        // 报数到第 m-1 个节点（即待淘汰节点的前驱）
        for (int i = 1; i < m - 1; i++) {
            curr = curr->next;
        }

        // 淘汰第 m 个节点
        Node *eliminated = curr->next;
        curr->next = eliminated->next; // 跨过淘汰节点
        free(eliminated);              // 释放出圈人员节点

        curr = curr->next; // 下一人从 1 重新报数
    }

    int winner = curr->id;
    free(curr); // 释放最后一人
    return winner;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    int n = 7, m = 3;
    printf("=== 约瑟夫环模拟 (n=%d 人, 报数到 m=%d 淘汰) ===\n", n, m);
    printf("最后幸存者的编号为: %d\n", josephus(n, m));
    return 0;
}

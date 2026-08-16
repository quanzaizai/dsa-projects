#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】约瑟夫环经典问题 (Josephus Problem)
 * -----------------------------------------------------------------------------
 * 1. 规则：n 个人围成一圈，从 1 报数到 m 的人出圈，求最后幸存者的编号。
 * 2. 算法模型：使用单向循环链表模拟报数出圈过程。
 * -----------------------------------------------------------------------------
 */

typedef struct Node {
    int id;
    struct Node *next;
} Node;

int josephus(int n, int m) {
    // 1. 构建 n 个节点的循环链表
    Node *head = (Node *)malloc(sizeof(Node));
    head->id = 1;
    Node *prev = head;
    for (int i = 2; i <= n; i++) {
        Node *curr = (Node *)malloc(sizeof(Node));
        curr->id = i;
        prev->next = curr;
        prev = curr;
    }
    prev->next = head; // 闭环

    // 2. 模拟报数淘汰
    Node *curr = head;
    while (curr->next != curr) {
        for (int i = 1; i < m - 1; i++) {
            curr = curr->next;
        }
        // 删除第 m 个节点
        Node *temp = curr->next;
        curr->next = temp->next;
        free(temp);
        curr = curr->next;
    }

    int winner = curr->id;
    free(curr);
    return winner;
}

int main(void) {
    int n = 7, m = 3;
    printf("%d 个人报数到 %d 淘汰，最后幸存者编号: %d\n", n, m, josephus(n, m));
    return 0;
}

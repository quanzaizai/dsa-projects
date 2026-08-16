#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】单链表 (Singly Linked List)：节点构建、遍历与内存回收
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 离散内存结构：每个节点由数据域 (data) 和指向下一个节点的指针域 (next) 组成。
 *   2. 内存回收要点：释放链表时必须**先暂存下一个节点的地址** (next_node)，然后再 free 当前节点，
 *      否则一旦释放当前节点，next 指针将失效变成野指针。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 节点结构与基础操作 ====================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 创建并初始化独立堆内存节点
Node* create_node(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 遍历打印整条链表
void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

// 释放整条单链表内存
void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next; // 🔍 关键技巧：先保存下一节点地址
        free(curr);              // 再安全释放当前节点
        curr = next;
    }
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    // 手动连接节点构建链表: 10 -> 20 -> 30 -> NULL
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    printf("单链表内容: ");
    print_list(head);

    // 内存安全回收闭环
    free_list(head);
    head = NULL;

    return 0;
}

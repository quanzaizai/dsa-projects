#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】单链表核心插入操作：头部插入 vs 尾部插入
 * -----------------------------------------------------------------------------
 * 📌【核心思想与本质】
 *   1. 头部插入 (O(1))：新节点指向原头节点，头指针重定向为新节点 (`newNode->next = *head; *head = newNode`)。
 *   2. 尾部插入 (O(N))：遍历至尾部节点，将原尾节点的 next 指向新节点。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 链表插入算法 ====================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

// 头部插入 O(1)（二级指针修改外部头指针）
void insert_head(Node **head_ref, int data) {
    Node *newNode = create_node(data);
    newNode->next = *head_ref; // 1. 新节点指向原头节点
    *head_ref = newNode;       // 2. 头指针指向新节点
}

// 尾部插入 O(N)
void insert_tail(Node **head_ref, int data) {
    Node *newNode = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    Node *curr = *head_ref;
    while (curr->next != NULL) {
        curr = curr->next; // 遍历定位至尾节点
    }
    curr->next = newNode;
}

void print_list(Node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    Node *head = NULL;

    insert_tail(&head, 20);
    insert_tail(&head, 30);
    insert_head(&head, 10); // 10 插入头部

    printf("插入后链表 (10 头插, 20/30 尾插): ");
    print_list(head);

    return 0;
}

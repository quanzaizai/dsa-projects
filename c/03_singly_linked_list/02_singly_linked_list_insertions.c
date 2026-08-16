#include <stdio.h>
#include <stdlib.h>

/**
 * 【知识点】单链表三大插入操作：头插、尾插与指定位置插入
 * -----------------------------------------------------------------------------
 * 1. 头插法 O(1)：newNode->next = head; head = newNode;
 * 2. 尾插法 O(N)：遍历至尾节点，tail->next = newNode;
 * -----------------------------------------------------------------------------
 */

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

// 头部插入 O(1)
void insert_head(Node **head_ref, int data) {
    Node *newNode = create_node(data);
    newNode->next = *head_ref;
    *head_ref = newNode;
}

// 尾部插入 O(N)
void insert_tail(Node **head_ref, int data) {
    Node *newNode = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    Node *curr = *head_ref;
    while (curr->next != NULL) curr = curr->next;
    curr->next = newNode;
}

void print_list(Node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main(void) {
    Node *head = NULL;

    insert_tail(&head, 20);
    insert_tail(&head, 30);
    insert_head(&head, 10); // 10 插入头部

    printf("插入后链表: ");
    print_list(head);

    return 0;
}

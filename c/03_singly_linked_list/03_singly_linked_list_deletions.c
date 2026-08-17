#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * =============================================================================
 * 💡【知识点】单链表核心删除操作 —— 按值删除 (Delete by Value)
 * =============================================================================
 * 
 * 📌【1. 删除机制与指针解绑原理】
 *   删除单链表中的某个节点 curr，关键是找到它的「前驱节点 prev」。
 *   通过让 `prev->next = curr->next` 跳过 curr 节点，再调用 `free(curr)` 释放其堆内存。
 * 
 * 📌【2. 删除中间节点过程 ASCII 图解】
 * 
 *   假设要删除值为 20 的节点:
 *   
 *         prev           curr (待删节点)      curr->next
 *           |              |                     |
 *           v              v                     v
 *       +-------+      +-------+             +-------+
 *       | 10  * | ---> | 20  * | ----------> | 30  * | ---> NULL
 *       +-------+      +-------+             +-------+
 *           |                                    ^
 *           |       【prev->next = curr->next】  |
 *           +------------------------------------+
 *           
 *   解绑后: free(curr)，释放 20 节点的内存。
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 删除操作有哪几种特殊边界情况需要单独处理？
 *      👉 解答：
 *         ① 空链表：直接退出，防止空指针解引用。
 *         ② 待删节点恰好是「头节点」：此时没有 prev 前驱，需要更新 `*head_ref = curr->next`。
 *         ③ 遍历到尾部仍未找到：不进行任何释放操作。
 * =============================================================================
 */

// ==================== 1. 链表删除算法 ====================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = data;
    n->next = NULL;
    return n;
}

/**
 * @brief 在单链表中查找并删除第一个值为 key 的节点
 * 
 * @param head_ref 外部头指针的地址
 * @param key      待删除的目标数据值
 * @return true 成功找到并删除, false 未找到目标值
 * 
 * @note 时间复杂度: 最好 O(1)（头节点命中），最坏/平均 O(N)
 * @note 空间复杂度: O(1)
 */
bool delete_value(Node **head_ref, int key) {
    if (head_ref == NULL || *head_ref == NULL) {
        return false;
    }

    Node *curr = *head_ref;
    Node *prev = NULL;

    // 【特殊情况 1】待删除的节点恰好是头节点
    if (curr->data == key) {
        *head_ref = curr->next; // 头指针直接后移一位
        free(curr);             // 释放原头节点
        return true;
    }

    // 【情况 2】遍历寻找目标值节点及其前驱节点 prev
    while (curr != NULL && curr->data != key) {
        prev = curr;       // prev 跟随前进
        curr = curr->next; // curr 前进
    }

    // 未找到目标值
    if (curr == NULL) {
        return false;
    }

    // 【情况 3】找到中间或尾部节点：指针越过 curr 完成解绑
    prev->next = curr->next;

    // 释放节点内存
    free(curr);

    return true;
}

void print_list(const Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head->next;
        free(head);
        head = temp;
    }
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    // 构造测试链表: 10 -> 20 -> 30 -> NULL
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    printf("==================== 单链表按值删除验证 ====================\n");
    printf("删除前: ");
    print_list(head);

    // 测试 1: 删除中间节点 20
    printf("\n【测试 1】删除中间节点 20...\n");
    delete_value(&head, 20);
    print_list(head);

    // 测试 2: 删除头节点 10
    printf("\n【测试 2】删除头节点 10...\n");
    delete_value(&head, 10);
    print_list(head);

    // 清理
    free_list(head);
    head = NULL;

    return 0;
}

#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】双向循环链表 (Doubly Circular Linked List) —— 完美的对称闭环与 O(1) 首尾互访
 * -----------------------------------------------------------------------------
 * 📌【概念与本质】
 *   双向循环链表是所有链表结构中最为完善、功能最强大的形态（Linux 内核核心数据结构 list_head 即以此为基石）：
 *   • 双向性：每个节点同时拥有 prev（前驱）和 next（后继）指针。
 *   • 闭环性：
 *     ① `head->prev == tail`（头节点的前驱直接指向尾节点！）
 *     ② `tail->next == head`（尾节点的后继直接指向头节点！）
 * 
 * 📌【最大的性能降维打击：O(1) 定位尾节点】
 *   • 在单向链表或单向循环链表中，要找到尾节点必须从头遍历 O(N) 步。
 *   • 在双向循环链表中，只需一行代码 `head->prev`，即可在 O(1) 常数时间内直接获取尾节点！
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)        : 双向节点定义 (data, prev, next)。
 *   2. createNode()         : 工厂函数 —— 单节点时前后指针均指向自身 (`prev=next=self`)。
 *   3. insertAtTail()       : O(1) 极速尾部追加（利用 head->prev 秒定位尾节点）。
 *   4. traverseForward()    : 顺时针（正向）遍历一整圈 (do-while)。
 *   5. traverseBackward()   : 逆时针（反向）遍历一整圈 (do-while)。
 *   6. freeDoublyCircular() : 破环与内存安全回收。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

typedef struct Node {
    int data;               // 数据域
    struct Node* prev;      // 前驱指针：头节点的 prev 指向尾节点
    struct Node* next;      // 后继指针：尾节点的 next 指向头节点
} Node;

// ==================== 2. 核心算法与操作实现 ====================

/**
 * @brief 工厂函数：创建单节点双向自环结构
 */
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = value;
    // 单节点时，前后指针都指回自己
    newNode->prev = newNode;
    newNode->next = newNode;
    return newNode;
}

/**
 * @brief 在双向循环链表尾部追加新节点 (O(1) 常数时间！)
 * @param headRef 二级指针
 * @param value 要追加的数据值
 * 
 * 🔍【O(1) 尾插法核心步骤】：
 *   因为是双向循环链表，当前尾节点 tail 实际上就是 `(*headRef)->prev`！
 *   完全不需要任何循环遍历，直接 4 步重新缝合：
 *     ① Node* tail = (*headRef)->prev;
 *     ② tail->next = newNode;          （原尾节点的后继连新节点）
 *     ③ newNode->prev = tail;          （新节点的前驱连原尾节点）
 *     ④ newNode->next = *headRef;      （新节点的后继连头节点）
 *     ⑤ (*headRef)->prev = newNode;    （头节点的前驱更新为新节点）
 */
void insertAtTail(Node** headRef, int value) {
    if (!headRef) return;

    Node* newNode = createNode(value);
    if (!newNode) return;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    // 核心精髓：一行代码 O(1) 拿到尾节点
    Node* head = *headRef;
    Node* tail = head->prev;

    // 4 步完成双向闭环重连
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
}

/**
 * @brief 顺时针正向遍历双向循环链表一整圈 (Head -> Tail)
 */
void traverseForward(const Node* head) {
    printf("正向顺时针遍历: ");
    if (!head) {
        printf("NULL\n");
        return;
    }

    const Node* cur = head;
    do {
        printf("%d", cur->data);
        if (cur->next != head) printf(" -> ");
        cur = cur->next;
    } while (cur != head);

    printf(" -> (回环到 head: %d)\n", head->data);
}

/**
 * @brief 逆时针反向遍历双向循环链表一整圈 (Tail -> Head)
 * 
 * 🔍【反向遍历逻辑】：
 *   直接从 `head->prev`（即尾节点）出发，沿 prev 方向回溯至 head！
 */
void traverseBackward(const Node* head) {
    printf("反向逆时针遍历: ");
    if (!head) {
        printf("NULL\n");
        return;
    }

    const Node* tail = head->prev; // 直接由 head->prev 获得尾节点
    const Node* cur = tail;
    do {
        printf("%d", cur->data);
        if (cur->prev != tail) printf(" <- ");
        cur = cur->prev;
    } while (cur != tail);

    printf(" <- (回环到 tail: %d)\n", tail->data);
}

/**
 * @brief 破环并释放双向循环链表内存
 */
void freeDoublyCircular(Node** headRef) {
    if (!headRef || !(*headRef)) return;

    Node* head = *headRef;
    Node* tail = head->prev;

    // 步骤 1：切断头尾闭环
    tail->next = NULL;
    head->prev = NULL;

    // 步骤 2：常规线性释放
    Node* cur = head;
    while (cur != NULL) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }

    *headRef = NULL;
}

// ==================== 3. 测试驱动入口 ====================

int main(void) {
    Node* head = NULL;

    printf("========== 1. 构建双向循环链表: 10 <-> 20 <-> 30 <-> 40 ==========\n");
    insertAtTail(&head, 10);
    insertAtTail(&head, 20);
    insertAtTail(&head, 30);
    insertAtTail(&head, 40);

    printf("\n========== 2. 验证 O(1) 尾节点直接获取 ==========\n");
    printf("头节点数值: %d | 由 head->prev 查得的尾节点数值: %d\n", head->data, head->prev->data);

    printf("\n========== 3. 双向环形遍历测试 ==========\n");
    traverseForward(head);
    traverseBackward(head);

    printf("\n========== 4. 安全内存释放 ==========\n");
    freeDoublyCircular(&head);
    printf("内存释放完成。\n");

    return 0;
}

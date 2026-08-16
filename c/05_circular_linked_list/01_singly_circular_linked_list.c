#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】单向循环链表 (Singly Circular Linked List) —— 结构闭环、插入与环形遍历
 * -----------------------------------------------------------------------------
 * 📌【概念与本质】
 *   单向循环链表是单链表的经典变体：
 *   • 普通单链表：尾节点的 next 指针指向 NULL，标志链表终结。
 *   • 单向循环链表：尾节点的 next 指针【重新指向头节点 head】，在逻辑上形成封闭的环状拓扑。
 *   • 单节点自环：当链表中仅有 1 个节点时，其自身的 next 指针指向自己 (`newNode->next = newNode`)。
 * 
 * 📌【遍历终止条件与 do-while 核心机制】
 *   • 为什么不能用 `while (cur != head)`？
 *     - 初始状态下 `cur` 正好等于 `head`，若使用 while 会在第一次判断时判定为假而直接跳出循环！
 *   • 正确解法：必须使用 `do { ... } while (cur != head);`，确保先执行访问首节点，再在环绕一圈回到起点时退出。
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)        : 单向循环链表节点定义。
 *   2. createNode()         : 节点工厂 —— 默认自成闭环 (`next = self`)。
 *   3. insertAtHead()       : 头部插入 —— 寻尾、连头、更新 head。
 *   4. insertAtTail()       : 尾部追加 —— 寻尾、连尾、新节点指回 head。
 *   5. traverse()           : do-while 环形安全遍历一整圈。
 *   6. freeCircularList()   : 破环释放 —— 先切断闭环再线性释放，防止死循环。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

typedef struct Node {
    int data;               // 数据域
    struct Node* next;      // 指针域：指向后继节点，尾节点指回 head
} Node;

// ==================== 2. 核心操作与算法实现 ====================

/**
 * @brief 工厂函数：创建一个自成闭环的孤立新节点
 * @param value 节点数据
 * @return Node* 分配成功的节点指针
 */
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "【错误】内存分配失败！\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = newNode; // 核心：单节点自身构成自环
    return newNode;
}

/**
 * @brief 在单向循环链表头部插入新节点 (O(N) 寻尾)
 * @param headRef 二级指针指向头节点指针
 * @param value 要插入的数据
 * 
 * 🔍【头插法重连逻辑剖析】：
 *   ① 若原链表为空 (*headRef == NULL)，新节点直接成为头节点并自环。
 *   ② 否则，先找到当前尾节点 tail（满足 tail->next == *headRef）。
 *   ③ 缝合双重指针：
 *      - newNode->next = *headRef; （新节点指向旧头节点）
 *      - tail->next = newNode;    （尾节点更新指向新头节点）
 *   ④ 更新头指针：*headRef = newNode;
 */
void insertAtHead(Node** headRef, int value) {
    if (!headRef) return;

    Node* newNode = createNode(value);
    if (!newNode) return;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    // 寻找到当前链表的末尾节点
    Node* tail = *headRef;
    while (tail->next != *headRef) {
        tail = tail->next;
    }

    newNode->next = *headRef; // 新节点指向原头节点
    tail->next = newNode;     // 尾节点指向新节点
    *headRef = newNode;       // 头指针更新为新节点
}

/**
 * @brief 在单向循环链表尾部追加新节点 (O(N))
 * @param headRef 二级指针指向头节点指针
 * @param value 要追加的数据
 * 
 * 🔍【尾插法重连逻辑剖析】：
 *   ① 若原链表为空，新节点自成环并作为头节点。
 *   ② 否则沿 next 遍历找到当前末尾节点 tail。
 *   ③ 重连指针：
 *      - tail->next = newNode; （原尾节点指向新节点）
 *      - newNode->next = *headRef; （新节点闭环指回表头）
 */
void insertAtTail(Node** headRef, int value) {
    if (!headRef) return;

    Node* newNode = createNode(value);
    if (!newNode) return;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    Node* tail = *headRef;
    while (tail->next != *headRef) {
        tail = tail->next;
    }

    tail->next = newNode;     // 原尾部指向新节点
    newNode->next = *headRef; // 新尾部指回表头完成闭环
}

/**
 * @brief 环形遍历单向循环链表刚好一整圈
 * @param head 头节点指针
 * 
 * 🔍【do-while 循环的不可替代性】：
 *   必须先无条件执行一次打印并推进指针，再在循环条件中检查 `cur != head`！
 */
void traverse(const Node* head) {
    printf("循环链表一整圈: ");
    if (!head) {
        printf("NULL (空链表)\n");
        return;
    }

    const Node* cur = head;
    do {
        printf("%d -> ", cur->data);
        cur = cur->next;
    } while (cur != head); // 当指针重新转回起点 head 时，精准停止

    printf("(回到起点 head: %d)\n", head->data);
}

/**
 * @brief 安全释放单向循环链表内存
 * @param headRef 二级指针
 * 
 * ⚠️【致命陷阱防范】：
 *   若直接使用单链表的 `while(cur)` 释放，由于环状结构永远不会遇到 NULL，会导致无限死循环！
 *   安全策略：先找到尾节点将环切断为普通单链表 (`tail->next = NULL`)，再逐个释放。
 */
void freeCircularList(Node** headRef) {
    if (!headRef || !(*headRef)) return;

    // 步骤 1：找到尾节点并破环
    Node* tail = *headRef;
    while (tail->next != *headRef) {
        tail = tail->next;
    }
    tail->next = NULL; // 破环：将循环链表解构为普通单链表

    // 步骤 2：常规线性释放
    Node* cur = *headRef;
    while (cur != NULL) {
        Node* nextNode = cur->next;
        free(cur);
        cur = nextNode;
    }

    *headRef = NULL;
}

// ==================== 3. 测试驱动入口 ====================

int main(void) {
    Node* head = NULL;

    printf("========== 1. 测试头部插入 insertAtHead (倒序插入 30, 20, 10) ==========\n");
    insertAtHead(&head, 30);
    insertAtHead(&head, 20);
    insertAtHead(&head, 10);
    traverse(head); // 期望: 10 -> 20 -> 30 -> (回到起点 10)

    printf("\n========== 2. 测试尾部插入 insertAtTail (追加 40, 50) ==========\n");
    insertAtTail(&head, 40);
    insertAtTail(&head, 50);
    traverse(head); // 期望: 10 -> 20 -> 30 -> 40 -> 50 -> (回到起点 10)

    printf("\n========== 3. 破环与安全内存释放 ==========\n");
    freeCircularList(&head);
    printf("释放完成，当前 head 地址: %p\n", (void*)head);

    return 0;
}

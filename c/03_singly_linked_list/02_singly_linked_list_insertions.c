#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】单链表 —— 三大插入操作 (Head, Tail, Middle Insertion)
 * -----------------------------------------------------------------------------
 * 📌【概念与本质】
 *   单链表的插入不需要像数组那样整体搬移后续数据，核心在于【指针重定向】。
 *   不同插入位置对应不同的指针链接策略和时间复杂度。
 * 
 * 📌【三大插入场景与复杂度对比】
 *   1. 头部插入 (insertAtHead) : O(1) —— 直接将新节点 next 指向旧头，成为新头。
 *   2. 尾部插入 (insertAtTail) : O(N) —— 单指针从 head 遍历到末尾节点后挂接。
 *   3. 中间插入 (insertAfter)  : O(1)* —— 在已知前驱节点后挂接（*若需查找前驱则需 O(N) 遍历）。
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)    : 节点类型封装 (data + next)。
 *   2. insertAtHead()   : 头部插入实现 (O(1))。
 *   3. insertAtTail()   : 尾部插入实现 (O(N) 寻尾挂接)。
 *   4. insertAfter()    : 指定前驱后插入 (核心：先连后继，再改前驱！)。
 *   5. printList()      : 遍历打印辅助。
 *   6. freeList()       : 堆内存安全释放。
 *   7. main()           : 驱动入口与多场景测试。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

typedef struct Node {
    int data;               // 数据域
    struct Node* next;      // 指针域
} Node;

// ==================== 2. 核心插入算法实现 ====================

/**
 * @brief 在链表头部插入新节点（头插法）
 * 
 * 🔍【核心逻辑剖析】：
 *   • 指针链接：新节点 newNode->next 直接指向当前 head。
 *   • 返回值：newNode 成为链表新的头节点，直接返回 newNode。
 *   • 时间复杂度: O(1)（无需遍历任何节点）。
 *   • 注意：连续头插生成的数据顺序与插入顺序相反（倒序效果）。
 */
Node* insertAtHead(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    newNode->data = value;
    
    newNode->next = head; // 步骤 1：新节点指向原头节点
    return newNode;       // 步骤 2：新节点升级为新的头节点返回
}

/**
 * @brief 在链表尾部插入新节点（尾插法）
 * 
 * 🔍【核心逻辑剖析】：
 *   • 空表特判：若 head 为 NULL，新节点即为唯一头节点，直接返回 newNode。
 *   • 寻尾遍历：使用 current 指针沿着 next 寻找末尾节点（判断依据：current->next == NULL）。
 *   • 挂接末尾：令末尾节点的 next 指向 newNode。
 *   • 时间复杂度: O(N)（需从头遍历至末尾）。
 */
Node* insertAtTail(Node* head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    newNode->data = value;
    newNode->next = NULL;

    // 特殊情况：空链表插入
    if (head == NULL) {
        return newNode;
    }

    // 寻尾循环：停留在最后一个有效节点上
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode; // 将新节点挂接在原尾部后面
    return head;
}

/**
 * @brief 在指定的前驱节点 prevNode 之后插入新节点（中间插入）
 * 
 * 🔍【核心逻辑剖析 —— 极其重要的指针链接次序！】：
 *   • 【步骤 ① 先连后继】：newNode->next = prevNode->next; 
 *     （必须先让新节点抓住后继节点，否则后续链条地址会丢失！）
 *   • 【步骤 ② 再改前驱】：prevNode->next = newNode;
 *     （将前驱节点的 next 改为指向新节点，完成缝合）
 *   • ⚠️ 致命错误反例：若先执行 prevNode->next = newNode，则 prevNode 原有的后继地址被覆盖丢失，
 *     后续整段链表将脱落发生内存泄漏！
 */
void insertAfter(Node* prevNode, int value) {
    if (prevNode == NULL) {
        printf("【插入失败】前驱节点不能为空！\n");
        return;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;
    newNode->data = value;

    // 核心两步曲（次序不可颠倒！）：
    newNode->next = prevNode->next; // 步骤 ①：新节点链接后继节点
    prevNode->next = newNode;       // 步骤 ②：前驱节点链接新节点
}

// ==================== 3. 辅助工具与内存管理 ====================

// 格式化打印链表
void printList(const char* tag, Node* head) {
    printf("%s: ", tag);
    Node* cur = head;
    while (cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// 释放链表堆空间
void freeList(Node* head) {
    Node* cur = head;
    while (cur != NULL) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
}

// ==================== 4. 测试与验证入口 ====================

int main(void) {
    Node* head = NULL;

    printf("================ 单链表插入操作演示 ================\n");

    // 1. 头插法测试：依次插入 30, 20, 10
    head = insertAtHead(head, 30);
    head = insertAtHead(head, 20);
    head = insertAtHead(head, 10);
    printList("1. 连续头插 (10, 20, 30)", head);

    // 2. 尾插法测试：在末尾追加 40
    head = insertAtTail(head, 40);
    printList("2. 尾部追加 (40)", head);

    // 3. 中间插入测试：在节点 20 (即 head->next) 后面插入 25
    insertAfter(head->next, 25);
    printList("3. 在 20 后插入 25", head);

    // 4. 释放内存闭环
    freeList(head);
    head = NULL;

    return 0;
}
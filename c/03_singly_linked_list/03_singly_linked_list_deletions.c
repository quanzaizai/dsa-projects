#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】单链表 —— 两大核心删除操作 (Delete Head & Delete by Value)
 * -----------------------------------------------------------------------------
 * 📌【概念与本质】
 *   单链表的删除操作核心在于：【跳过目标节点重连指针】 + 【及时 free 释放堆内存】。
 *   不同删除场景的核心逻辑：
 *     ① 删除头节点：修改 head 指向下一个节点，并释放旧头内存（O(1)）。
 *     ② 按值删除节点：找到目标节点的【前驱节点】，令前驱跨过目标直连后继，并释放目标内存（O(N)）。
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)      : 节点类型封装 (data + next)。
 *   2. deleteHead()       : 删除链表头节点 (O(1))。
 *   3. deleteByValue()    : 查找并删除首个值为 target 的节点 (O(N) 寻前驱)。
 *   4. printList()        : 遍历打印辅助。
 *   5. freeList()         : 堆内存安全释放。
 *   6. main()             : 链表构建、头删、值删及全生命周期验证。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

typedef struct Node {
    int data;               // 数据域
    struct Node* next;      // 指针域
} Node;

// ==================== 2. 核心删除算法实现 ====================

/**
 * @brief 删除单链表的头节点
 * 
 * 🔍【核心逻辑剖析】：
 *   • 空表特判：若 head == NULL，无节点可删，直接返回 NULL。
 *   • 安全释放三步曲：
 *     ① temp = head;          （暂存旧头节点的地址）
 *     ② head = head->next;    （将头指针后移，指向第二个节点）
 *     ③ free(temp);           （安全释放旧头节点占用的堆内存）
 *   • 时间复杂度: O(1)（常数时间，无任何循环遍历）。
 */
Node* deleteHead(Node* head) {
    if (head == NULL) return NULL;

    Node* temp = head;   // 1. 暂存旧头节点
    head = head->next;    // 2. 头指针后移
    free(temp);           // 3. 释放旧头节点堆内存
    return head;          // 4. 返回新的头节点
}

/**
 * @brief 查找并删除链表中第一个值为 target 的节点
 * 
 * 🔍【核心逻辑剖析 —— 为什么必须查找目标节点的“前驱节点”？】：
 *   • 单链表具有单向性：无法从当前节点反向找到前一个节点。
 *     若想删除某个节点，必须修改其【前驱节点 (current)】的 next 指针，使其绕过目标直接指向后继！
 *   • 核心步骤：
 *     1. 特判头节点：若 head->data == target，直接等价于调用 deleteHead(head)。
 *     2. 扫描查找前驱：遍历直到 current->next->data == target 或到达尾部。
 *     3. 跨越与释放：
 *        - temp = current->next;              （定位待删目标节点）
 *        - current->next = current->next->next;（前驱节点跨过目标直连后继）
 *        - free(temp);                        （释放目标节点的堆内存）
 *   • 时间复杂度: O(N)（最坏需遍历整条链表），空间复杂度 O(1)。
 */
Node* deleteByValue(Node* head, int target) {
    if (head == NULL) return NULL;

    // 情况 1：待删除的目标恰好是头节点
    if (head->data == target) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    // 情况 2：在后续节点中查找目标节点的前驱节点
    Node* current = head;
    while (current->next != NULL && current->next->data != target) {
        current = current->next; // 推进指针
    }

    // 若找到目标节点（current->next 不为 NULL）
    if (current->next != NULL) {
        Node* temp = current->next;          // 1. 锁定待删除的目标节点
        current->next = current->next->next; // 2. 前驱节点跨过目标，缝合后继
        free(temp);                          // 3. 释放目标节点内存
    } else {
        printf("【提示】链表中未找到值为 %d 的节点。\n", target);
    }

    return head;
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

// 释放链表全部堆空间
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
    // 1. 初始构建链表: 10 -> 20 -> 30 -> 40 -> NULL (头插法倒序构建)
    Node* head = NULL;
    int vals[] = {10, 20, 30, 40};
    for (int i = 3; i >= 0; i--) {
        Node* n = (Node*)malloc(sizeof(Node));
        n->data = vals[i];
        n->next = head;
        head = n;
    }

    printf("================ 单链表删除操作演示 ================\n");
    printList("1. 初始链表", head);

    // 2. 测试删除头节点 (删除 10)
    head = deleteHead(head);
    printList("2. 删除头节点 (10) 后", head);

    // 3. 测试按值删除中间节点 (删除 30)
    head = deleteByValue(head, 30);
    printList("3. 删除目标值 (30) 后", head);

    // 4. 安全释放剩余节点堆空间
    freeList(head);
    head = NULL;

    return 0;
}
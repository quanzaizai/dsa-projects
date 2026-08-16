#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】双向链表核心删除操作 —— 节点解绑、头删与按值删除
 * -----------------------------------------------------------------------------
 * 📌【概念与本质】
 *   双向链表相比单链表最具有压倒性优势的操作就是【删除节点】！
 *   • 单链表痛点：要删除某个已知节点 del，必须从头遍历寻找它的前驱节点 prevNode（O(N)），否则无法重连指针。
 *   • 双向链表解法：每个节点自身保存了 prev 指针。给定节点 del，直接通过 del->prev 和 del->next 
 *     即可在 O(1) 时间内完成前后节点的直接缝合与当前节点解绑！
 * 
 * 📌【删除任意节点 del 的通用 3 步法则】
 *   ① 若删除的是头节点 (*headRef == del)：将头指针后移 (*headRef = del->next)。
 *   ② 绕过前驱指针：若 del->prev != NULL，则 del->prev->next = del->next。
 *   ③ 绕过后继指针：若 del->next != NULL，则 del->next->prev = del->prev。
 *   ④ 释放空间：free(del)。
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)        : 双向节点定义。
 *   2. deleteNode()         : 核心函数 —— O(1) 物理删除任意指定节点指针 del。
 *   3. deleteHead()         : 便捷函数 —— 快速删除表头节点。
 *   4. deleteByValue()      : 综合函数 —— 查找包含目标数值的节点并执行删除。
 *   5. printDoublyList()    : 链表可视化打印。
 *   6. freeDoublyList()     : 内存安全销毁。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

typedef struct Node {
    int data;               // 数据域
    struct Node* prev;      // 前驱指针
    struct Node* next;      // 后继指针
} Node;

// ==================== 2. 核心删除算法实现 ====================

/**
 * @brief 节点创建辅助函数
 */
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief 尾插法辅助函数（用于快速构建测试链表）
 */
void append(Node** headRef, int value) {
    Node* newNode = createNode(value);
    if (!newNode) return;
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    Node* cur = *headRef;
    while (cur->next) cur = cur->next;
    cur->next = newNode;
    newNode->prev = cur;
}

/**
 * @brief 核心删除函数：直接删除指定的节点指针 del (O(1))
 * @param headRef 指向头指针的二级指针（若删除头节点需更新 *headRef）
 * @param del 指向待删除节点的指针
 * 
 * 🔍【删除解绑逻辑剖析】：
 *   假设原结构：prevNode <-> del <-> nextNode
 *   目标：让 prevNode 与 nextNode 互联，将 del 踢出链条并 free。
 * 
 *   情况 1：若 del 是头节点 (*headRef == del)
 *          -> 更新头指针：*headRef = del->next;
 *   情况 2：若 del 有前驱节点 (del->prev != NULL)
 *          -> 让前驱的 next 跳过 del，直接指向 del 的后继 (del->prev->next = del->next)。
 *   情况 3：若 del 有后继节点 (del->next != NULL)
 *          -> 让后继的 prev 跳过 del，直接指向 del 的前驱 (del->next->prev = del->prev)。
 *   最后：free(del) 归还堆内存。
 */
void deleteNode(Node** headRef, Node* del) {
    if (!headRef || !(*headRef) || !del) return;

    // 步骤 1：若删除的是头节点，更新头指针
    if (*headRef == del) {
        *headRef = del->next;
    }

    // 步骤 2：缝合前驱节点的 next 指向
    if (del->prev != NULL) {
        del->prev->next = del->next;
    }

    // 步骤 3：缝合后继节点的 prev 指向
    if (del->next != NULL) {
        del->next->prev = del->prev;
    }

    // 步骤 4：释放被剔除节点的内存空间
    free(del);
}

/**
 * @brief 快速删除双向链表头节点 (O(1))
 */
void deleteHead(Node** headRef) {
    if (!headRef || !(*headRef)) return;
    deleteNode(headRef, *headRef);
}

/**
 * @brief 按数值查找并删除首个匹配的节点 (O(N) 搜索 + O(1) 删除)
 * @param headRef 指向头指针的二级指针
 * @param target 要删除的目标数值
 * @return int 成功删除返回 1，未找到目标返回 0
 */
int deleteByValue(Node** headRef, int target) {
    if (!headRef || !(*headRef)) return 0;

    Node* cur = *headRef;
    // 遍历查找匹配节点
    while (cur != NULL && cur->data != target) {
        cur = cur->next;
    }

    // 未找到目标数值
    if (cur == NULL) {
        return 0;
    }

    // 调用通用删除函数
    deleteNode(headRef, cur);
    return 1;
}

// ==================== 3. 辅助函数与测试入口 ====================

/**
 * @brief 格式化打印链表现状
 */
void printDoublyList(const Node* head) {
    printf("当前链表: ");
    if (!head) {
        printf("NULL (空链表)\n");
        return;
    }
    const Node* cur = head;
    while (cur) {
        printf("[%d]", cur->data);
        if (cur->next) printf(" <-> ");
        cur = cur->next;
    }
    printf(" -> NULL\n");
}

/**
 * @brief 释放整表内存
 */
void freeDoublyList(Node** headRef) {
    if (!headRef || !(*headRef)) return;
    Node* cur = *headRef;
    while (cur) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    *headRef = NULL;
}

int main(void) {
    Node* head = NULL;

    printf("========== 1. 初始化双向链表: 10 <-> 20 <-> 30 <-> 40 <-> 50 ==========\n");
    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);
    append(&head, 50);
    printDoublyList(head);

    printf("\n========== 2. 测试删除头节点 (删除 10) ==========\n");
    deleteHead(&head);
    printDoublyList(head); // 期望: [20] <-> [30] <-> [40] <-> [50]

    printf("\n========== 3. 测试删除中间节点 (按值删除 30) ==========\n");
    if (deleteByValue(&head, 30)) {
        printf("成功删除数值 30！\n");
    }
    printDoublyList(head); // 期望: [20] <-> [40] <-> [50]

    printf("\n========== 4. 测试删除尾节点 (按值删除 50) ==========\n");
    if (deleteByValue(&head, 50)) {
        printf("成功删除数值 50！\n");
    }
    printDoublyList(head); // 期望: [20] <-> [40]

    printf("\n========== 5. 测试删除不存在的节点 (尝试删除 999) ==========\n");
    if (!deleteByValue(&head, 999)) {
        printf("未在链表中找到目标值 999，链表保持不变。\n");
    }
    printDoublyList(head);

    printf("\n========== 6. 销毁并释放链表 ==========\n");
    freeDoublyList(&head);
    printDoublyList(head);

    return 0;
}

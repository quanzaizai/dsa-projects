#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】双向链表三大插入操作 —— 头部插入、尾部插入与指定节点后插入
 * -----------------------------------------------------------------------------
 * 📌【概念与本质】
 *   在双向链表中插入新节点，核心在于【同时维护前驱与后继的双向连通性】。
 *   不同于单链表仅需修改 1~2 个指针，双向链表插入中间节点通常需要精确调整 4 个指针！
 * 
 * 📌【三大插入场景与复杂度】
 *   1. 头部插入 (Insert At Head) : O(1)
 *      - 新节点作为新表头，原表头的 prev 指向新节点，更新 head 指针。
 *   2. 尾部插入 (Insert At Tail) : O(N)（若维护 tail 指针则为 O(1)）
 *      - 寻至末尾，尾节点的 next 指向新节点，新节点的 prev 指向原尾节点。
 *   3. 指定节点后插入 (Insert After) : O(1)（给定目标节点指针时）
 *      - 必须严格遵循【先外后内、先连新节点两翼】的链接顺序，防止原有链条断裂！
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)        : 双向节点定义。
 *   2. createNode()         : 工厂函数创建独立节点。
 *   3. insertAtHead()       : 头部插入逻辑（需修改头指针，使用二级指针 Node**）。
 *   4. insertAtTail()       : 尾部追加逻辑。
 *   5. insertAfter()        : 中间/指定节点后插入（4 步黄金链接律）。
 *   6. printDoublyList()    : 打印双向链表现状。
 *   7. freeDoublyList()     : 内存安全释放。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

typedef struct Node {
    int data;               // 数据域
    struct Node* prev;      // 前驱指针
    struct Node* next;      // 后继指针
} Node;

// ==================== 2. 核心插入算法实现 ====================

/**
 * @brief 创建并初始化孤立节点
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
 * @brief 场景一：在双向链表头部插入新节点 (O(1))
 * @param headRef 指向头指针的二级指针（因为插入后头指针会改变）
 * @param value 插入的数据值
 * 
 * 🔍【头插法逻辑剖析】：
 *   ① 创建新节点 newNode。
 *   ② 若原链表非空 (*headRef != NULL)：
 *      - newNode->next = *headRef;   （新节点的 next 指向原头节点）
 *      - (*headRef)->prev = newNode; （原头节点的 prev 指向新节点）
 *   ③ *headRef = newNode;            （头指针移动，指向新节点）
 */
void insertAtHead(Node** headRef, int value) {
    if (!headRef) return;

    Node* newNode = createNode(value);
    if (!newNode) return;

    if (*headRef != NULL) {
        newNode->next = *headRef;
        (*headRef)->prev = newNode;
    }
    *headRef = newNode; // 新节点成为新的头节点
}

/**
 * @brief 场景二：在双向链表尾部追加新节点 (O(N))
 * @param headRef 指向头指针的二级指针
 * @param value 插入的数据值
 * 
 * 🔍【尾插法逻辑剖析】：
 *   ① 若原链表为空 (*headRef == NULL)，新节点直接作为头节点。
 *   ② 否则沿 next 遍历找到当前末尾节点 tail。
 *   ③ 绑定双向关系：
 *      - tail->next = newNode; （原尾节点指向新节点）
 *      - newNode->prev = tail; （新节点 prev 指向原尾节点）
 */
void insertAtTail(Node** headRef, int value) {
    if (!headRef) return;

    Node* newNode = createNode(value);
    if (!newNode) return;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    // 遍历寻找当前末尾节点
    Node* tail = *headRef;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = newNode; // 正向连接
    newNode->prev = tail; // 反向连接
}

/**
 * @brief 场景三：在指定的已知节点 prevNode 之后插入新节点 (O(1))
 * @param prevNode 目标前驱节点指针
 * @param value 插入的数据值
 * 
 * 🔍【4 步黄金链接律（核心必背）】：
 *   假设原有结构为：prevNode <-> nextNode
 *   现在要将 newNode 插入两者之间：
 *     ① newNode->next = prevNode->next; （步骤1：新节点右翼连接后继节点）
 *     ② newNode->prev = prevNode;       （步骤2：新节点左翼连接前驱节点）
 *     ③ if (prevNode->next != NULL) {
 *           prevNode->next->prev = newNode; （步骤3：后继节点的左翼反向指向新节点）
 *       }
 *     ④ prevNode->next = newNode;       （步骤4：前驱节点的右翼正向指向新节点）
 * 
 *   ⚠️【致命避坑】：步骤 1 必须在步骤 4 之前执行！否则若先执行 prevNode->next = newNode，
 *                 原后继节点 nextNode 的地址就会丢失，导致断链与内存泄漏！
 */
void insertAfter(Node* prevNode, int value) {
    if (!prevNode) {
        printf("【警告】目标前驱节点不能为空！\n");
        return;
    }

    Node* newNode = createNode(value);
    if (!newNode) return;

    // 步骤 1 & 2：先设置新节点自身的前后指针（先连外围两翼）
    newNode->next = prevNode->next;
    newNode->prev = prevNode;

    // 步骤 3：若原后继节点存在，将其 prev 指向新节点
    if (prevNode->next != NULL) {
        prevNode->next->prev = newNode;
    }

    // 步骤 4：前驱节点的 next 指向新节点
    prevNode->next = newNode;
}

// ==================== 3. 辅助函数与测试入口 ====================

/**
 * @brief 格式化打印双向链表状态
 */
void printDoublyList(const Node* head) {
    printf("当前链表: ");
    if (!head) {
        printf("NULL\n");
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
 * @brief 释放双向链表内存
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

    printf("========== 1. 测试头部插入 insertAtHead ==========\n");
    insertAtHead(&head, 20); // 链表: [20]
    insertAtHead(&head, 10); // 链表: [10] <-> [20]
    printDoublyList(head);

    printf("\n========== 2. 测试尾部插入 insertAtTail ==========\n");
    insertAtTail(&head, 40); // 链表: [10] <-> [20] <-> [40]
    insertAtTail(&head, 50); // 链表: [10] <-> [20] <-> [40] <-> [50]
    printDoublyList(head);

    printf("\n========== 3. 测试中间指定节点后插入 insertAfter ==========\n");
    // 寻找值为 20 的节点，并在其后插入 30
    Node* target = head;
    while (target && target->data != 20) {
        target = target->next;
    }
    if (target) {
        printf("在节点 [%d] 之后插入数值 30:\n", target->data);
        insertAfter(target, 30); // 期望: [10] <-> [20] <-> [30] <-> [40] <-> [50]
        printDoublyList(head);
    }

    printf("\n========== 4. 释放内存 ==========\n");
    freeDoublyList(&head);
    printf("链表已成功销毁。\n");

    return 0;
}

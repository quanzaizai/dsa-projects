#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】双向链表 (Doubly Linked List) —— 节点结构、构建与双向遍历
 * -----------------------------------------------------------------------------
 * 📌【概念与本质】
 *   双向链表是对单链表的重大扩展，每个节点由三部分组成：
 *     ① 数据域 (data) : 存储具体业务数据。
 *     ② 前驱指针 (prev) : 指向直接前驱节点（前一个节点）。
 *     ③ 后继指针 (next) : 指向直接后继节点（后一个节点）。
 * 
 * 📌【双向链表 vs 单链表 核心对比】
 *   • 遍历能力：单链表只能沿 next 单向移动；双向链表既可沿 next 正向遍历，也可沿 prev 反向回溯。
 *   • 空间开销：在 64 位系统下，双向链表每个节点多出一个 8 字节的 prev 指针（以空间换时间与操作灵活性）。
 *   • 删除效率：双向链表删除已知节点不需要像单链表那样专门遍历寻找前驱节点，可直接自定位解绑。
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)        : 数据结构定义 —— 包含 prev、data、next。
 *   2. createNode()         : 节点工厂函数 —— 独立分配并初始化节点。
 *   3. createDoublyList()   : 高效建表 —— 维护 tail 指针以 O(N) 尾插法构建双向关系。
 *   4. traverseForward()    : 正向遍历 —— 沿 next 指向从 head 移动至 NULL。
 *   5. traverseBackward()   : 反向遍历 —— 先寻尾节点 tail，再沿 prev 反向回溯至 head。
 *   6. freeDoublyList()     : 内存安全 —— 逐个释放堆内存，杜绝内存泄漏。
 *   7. main()               : 驱动入口 —— 演示完整生命周期与双向遍历输出。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

// 定义双向链表节点结构体
typedef struct Node {
    int data;               // 数据域：存储整数数据
    struct Node* prev;      // 前驱指针域：指向前一个节点（首节点为 NULL）
    struct Node* next;      // 后继指针域：指向后一个节点（尾节点为 NULL）
} Node;

// ==================== 2. 核心算法与操作实现 ====================

/**
 * @brief 节点工厂函数：创建并初始化一个孤立的双向链表新节点
 * @param value 要存入节点的数据值
 * @return Node* 成功返回分配的节点指针，内存不足返回 NULL
 */
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "【错误】堆内存分配失败！\n");
        return NULL;
    }
    newNode->data = value;
    newNode->prev = NULL; // 初始前驱指针置空
    newNode->next = NULL; // 初始后继指针置空
    return newNode;
}

/**
 * @brief 构建包含 1 到 n 顺序连续数值的双向链表
 * 
 * 🔍【核心双向链接逻辑】：
 *   每次追加新节点 newNode 时，必须同时完成双向指针的绑定：
 *     ① tail->next = newNode; （正向连通：原尾节点的 next 指向新节点）
 *     ② newNode->prev = tail; （反向连通：新节点的 prev 指向原尾节点）
 *     ③ tail = newNode;       （更新尾指针：将 tail 移动到最新末尾节点）
 */
Node* createDoublyList(int n) {
    if (n <= 0) return NULL;

    // 步骤 1：创建首节点
    Node* head = createNode(1);
    if (!head) return NULL;

    Node* tail = head; // 尾指针追踪链表末端

    // 步骤 2：循环追加 2 到 n
    for (int i = 2; i <= n; i++) {
        Node* newNode = createNode(i);
        if (!newNode) {
            // 若某次分配失败，释放已创建链表
            // (此处暂略快速异常处理，实际项目中可回滚)
            break;
        }

        // 双向双向缝合
        tail->next = newNode; // 正向链接
        newNode->prev = tail; // 反向链接
        tail = newNode;       // 尾指针后移
    }

    return head;
}

/**
 * @brief 正向遍历双向链表 (Forward Traversal)
 * @param head 链表头指针
 */
void traverseForward(const Node* head) {
    printf("正向遍历 (Head -> Tail): ");
    if (!head) {
        printf("【空链表】\n");
        return;
    }

    const Node* cur = head;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" <-> ");
        }
        cur = cur->next; // 沿 next 指针向前推进
    }
    printf(" -> NULL\n");
}

/**
 * @brief 反向遍历双向链表 (Backward Traversal)
 * @param head 链表头指针
 * 
 * 🔍【反向遍历逻辑剖析】：
 *   ① 先沿 next 遍历走到最后一个有效节点（即 tail，其满足 tail->next == NULL）。
 *   ② 再从 tail 开始，沿 prev 指针依次倒序访问，直到 cur == NULL。
 */
void traverseBackward(const Node* head) {
    printf("反向遍历 (Tail -> Head): ");
    if (!head) {
        printf("【空链表】\n");
        return;
    }

    // 第一步：走到尾节点
    const Node* cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    // 第二步：从尾节点沿 prev 指针回溯至表头
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->prev != NULL) {
            printf(" <-> ");
        }
        cur = cur->prev; // 沿 prev 指针回溯
    }
    printf(" -> NULL\n");
}

/**
 * @brief 安全释放双向链表的所有节点内存
 * @param headRef 指向头指针的二级指针，释放后自动将 *headRef 置为 NULL
 */
void freeDoublyList(Node** headRef) {
    if (!headRef || !(*headRef)) return;

    Node* current = *headRef;
    while (current != NULL) {
        Node* nextNode = current->next; // 暂存后继地址，防止销毁后迷路
        free(current);                  // 释放当前节点堆空间
        current = nextNode;             // 推进到下一个节点
    }

    *headRef = NULL; // 彻底切断野指针
}

// ==================== 3. 驱动测试入口 ====================

int main(void) {
    printf("========== 1. 创建包含 5 个节点的双向链表 ==========\n");
    Node* list = createDoublyList(5);

    printf("\n========== 2. 双向遍历测试 ==========\n");
    traverseForward(list);
    traverseBackward(list);

    printf("\n========== 3. 内存释放与销毁 ==========\n");
    freeDoublyList(&list);
    printf("链表释放完毕，当前 head 地址: %p\n", (void*)list);

    return 0;
}

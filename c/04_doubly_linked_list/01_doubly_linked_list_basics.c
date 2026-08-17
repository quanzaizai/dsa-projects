#include <stdio.h>
#include <stdlib.h>

/**
 * =============================================================================
 * 💡【知识点】双向链表 (Doubly Linked List) —— 双向指针模型与正反向双向遍历
 * =============================================================================
 * 
 * 📌【1. 双向链表的结构与特征】
 *   双向链表在单链表的基础上，为每个节点增设了一个前驱指针 `prev`。
 *   - `prev` (Previous)：指向物理逻辑上的上一个前驱节点（首节点的 prev 为 NULL）。
 *   - `data` (Data)    ：存储数据。
 *   - `next` (Next)    ：指向物理逻辑上的下一个后继节点（尾节点的 next 为 NULL）。
 * 
 * 📌【2. 内存模型与正反遍历图解】
 * 
 *          head
 *           |
 *           v
 *         +------+------+------+     +------+------+------+     +------+------+------+
 *   NULL <| prev |  10  | next |<===>| prev |  20  | next |<===>| prev |  30  | next |> NULL
 *         +------+------+------+     +------+------+------+     +------+------+------+
 *                节点 1                     节点 2                     节点 3 (tail)
 * 
 *   - 正向遍历 (Forward) ：从 head 出发，顺着 `next` 指针向右走: 10 -> 20 -> 30
 *   - 反向遍历 (Backward)：从 tail 出发，顺着 `prev` 指针向左走: 30 -> 20 -> 10
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 既然单链表也能存数据，为什么还要耗费内存使用双向链表？
 *      👉 解答：
 *         - 单链表找前驱节点需要 O(N) 遍历，导致很多操作（如已知节点指针时的删除、在某节点前插入）性能受限。
 *         - 双向链表让每个节点都拥有直达前后邻居的“超链接”，删除已知节点只需 O(1) 常数时间！
 *         - 经典工业应用：操作系统内核进程调度队列、LRU 页面置换算法缓存池、浏览器的“前进/后退”栈结构。
 * =============================================================================
 */

// ==================== 1. 结构体与初始化 ====================

/**
 * @brief 双向链表节点结构体
 */
typedef struct DNode {
    int data;            // 数据域
    struct DNode *prev;  // 前驱指针：指向前一个节点
    struct DNode *next;  // 后继指针：指向后一个节点
} DNode;

/**
 * @brief 在堆上动态创建双向链表节点
 * 
 * @param data 装填的数据
 * @return DNode* 新节点地址
 * 
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
DNode* create_dnode(int data) {
    DNode *n = (DNode *)malloc(sizeof(DNode));
    if (!n) {
        printf("⚠️ [创建失败] 堆内存不足！\n");
        return NULL;
    }
    n->data = data;
    n->prev = NULL; // 初始时前后指针均悬空置 NULL
    n->next = NULL;
    return n;
}

/**
 * @brief 释放双向链表
 */
void free_dlist(DNode *head) {
    DNode *curr = head;
    while (curr != NULL) {
        DNode *next_node = curr->next;
        free(curr);
        curr = next_node;
    }
}

// ==================== 2. 测试与双向验证 ====================

int main(void) {
    printf("==================== 双向链表基础与双向遍历验证 ====================\n");

    // 【步骤 1】创建 3 个独立节点
    DNode *n1 = create_dnode(10);
    DNode *n2 = create_dnode(20);
    DNode *n3 = create_dnode(30);

    // 【步骤 2】手动构建双向互联指针关系
    // n1 与 n2 互联
    n1->next = n2;
    n2->prev = n1;

    // n2 与 n3 互联
    n2->next = n3;
    n3->prev = n2;

    // 【步骤 3】正向遍历 (顺着 next 指针)
    printf("▶️ 正向遍历 (Head -> Tail): ");
    DNode *curr = n1;
    DNode *tail = NULL;
    while (curr != NULL) {
        printf("[%d] <-> ", curr->data);
        if (curr->next == NULL) tail = curr; // 记录尾节点供逆向使用
        curr = curr->next;
    }
    printf("NULL\n");

    // 【步骤 4】反向遍历 (顺着 prev 指针)
    printf("◀️ 反向遍历 (Tail -> Head): ");
    curr = tail;
    while (curr != NULL) {
        printf("[%d] <-> ", curr->data);
        curr = curr->prev;
    }
    printf("NULL\n");

    // 安全回收
    free_dlist(n1);
    n1 = NULL;

    return 0;
}

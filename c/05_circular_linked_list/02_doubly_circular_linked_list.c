// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdlib.h>   // 标准通用工具库：提供 malloc(), free(), exit(), NULL 等堆内存动态分配与释放支持

/**
 * =============================================================================
 * 💡【知识点】双向循环链表 (Doubly Circular Linked List) —— 对称双向闭环与 O(1) 首尾互访
 * =============================================================================
 * 
 * 📌【1. 什么是双向循环链表？】
 *   双向循环链表是链表结构的“集大成者”。
 *   - 头节点的 `prev` 直接指向「尾节点 tail」；
 *   - 尾节点的 `next` 直接指向「头节点 head」；
 *   - 整个结构完美对称，既能顺时针前进，也能逆时针后退。
 * 
 * 📌【2. 双向闭环对称模型 ASCII 图解】
 * 
 *            +-------------------------------------------------+
 *            |             【head->prev 直达 tail】            |
 *            |                                                 v
 *            |         +-------+-------+-------+       +-------+-------+-------+
 *            +-------> | prev  | head  | next  |<=====>| prev  | tail  | next  | ------+
 *                      |       |  10   |       |       |       |  20   |       |       |
 *                      +-------+-------+-------+       +-------+-------+-------+       |
 *                                  ^                               |                   |
 *                                  |   【tail->next 直达 head】    |                   |
 *                                  +-------------------------------+-------------------+
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 双向循环链表最强大的杀手级特性是什么？
 *      👉 解答：
 *         - **O(1) 尾部直达**：普通单链表找尾节点需要 O(N)，而双向循环链表只需一条语句 `head->prev` 即可瞬间定位尾部！
 *         - **O(1) 尾部插入与删除**：无需额外维护 tail 指针，利用 `head->prev` 即可在常数时间内完成尾插和尾删。
 *         - Linux 内核标准 `struct list_head` 数据结构正是基于这种双向循环链表设计！
 * =============================================================================
 */

// ==================== 1. 结构定义 ====================

typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

DNode* create_dnode(int data) {
    DNode *n = (DNode *)malloc(sizeof(DNode));
    if (!n) return NULL;
    n->data = data;
    n->prev = n->next = NULL;
    return n;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    printf("==================== 双向循环链表对称性验证 ====================\n");

    // 【步骤 1】创建头尾两个节点
    DNode *head = create_dnode(10);
    DNode *tail = create_dnode(20);

    // 【步骤 2】构建双向循环互联关系
    // 节点间正反向连接
    head->next = tail;
    tail->prev = head;

    // 首尾闭环跨接
    tail->next = head; // 尾节点的 next 连回 head
    head->prev = tail; // 头节点的 prev 连至 tail

    // 【步骤 3】验证 O(1) 首尾瞬时互访
    printf("头节点存储值: %d\n", head->data);
    printf("尾节点存储值: %d\n", tail->data);
    printf("🔍 从 head 出发通过 head->prev 直接在 O(1) 访问尾节点: %d\n", head->prev->data);
    printf("🔍 从 tail 出发通过 tail->next 直接在 O(1) 访问头节点: %d\n", tail->next->data);

    // 释放资源（破环后释放）
    head->prev = NULL;
    tail->next = NULL;
    free(head);
    free(tail);

    return 0;
}

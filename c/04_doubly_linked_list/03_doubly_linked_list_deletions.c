// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdlib.h>   // 标准通用工具库：提供 malloc(), free(), exit(), NULL 等堆内存动态分配与释放支持

/**
 * =============================================================================
 * 💡【知识点】双向链表节点解绑与局部 O(1) 快速删除
 * =============================================================================
 * 
 * 📌【1. 双向链表 O(1) 解绑的奥秘】
 *   在单链表中，删除节点必须从头遍历查找前驱 `prev`（O(N)）。
 *   而在双向链表中，已知待删节点指针 `del`，其前驱就是 `del->prev`，后继就是 `del->next`。
 *   只需直接修改前后邻居的指针，即可在 O(1) 常数时间内让 del 从链条中脱离！
 * 
 * 📌【2. 节点脱钩解绑 ASCII 图解】
 * 
 *   假设要删除中间的节点 del:
 *   
 *         del->prev                del (待删)               del->next
 *         +-------+               +-------+               +-------+
 *   ... < |  10   | next -------> |  20   | next -------> |  30   | > ...
 *         |       | <------- prev |       | <------- prev |       |
 *         +-------+               +-------+               +-------+
 *             |                                               ^
 *             |   【del->prev->next = del->next】             |
 *             +-----------------------------------------------+
 *             |                                               |
 *             |   【del->next->prev = del->prev】             |
 *             + <---------------------------------------------+
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么分别要对 `del->next != NULL` 和 `del->prev != NULL` 做条件判断？
 *      👉 解答：
 *         - 若 del 是「尾节点」：`del->next == NULL`，此时没有后继节点，不需要也不可以访问 `del->next->prev`。
 *         - 若 del 是「头节点」：`del->prev == NULL`，此时没有前驱节点，需要更新头指针 `*head_ref = del->next`。
 * =============================================================================
 */

// ==================== 1. 解绑删除算法 ====================

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

/**
 * @brief 在双向链表中删除指定的节点 del
 * 
 * @param head_ref 外部头指针地址
 * @param del      待删除节点的内存指针
 * 
 * @note 时间复杂度: O(1) —— 原地指针跨越，无需任何遍历
 * @note 空间复杂度: O(1)
 */
void delete_node(DNode **head_ref, DNode *del) {
    // 【步骤 1】防御性空指针检查
    if (head_ref == NULL || *head_ref == NULL || del == NULL) {
        return;
    }

    // 【步骤 2】特殊情况：若待删除的恰好是头节点
    if (*head_ref == del) {
        *head_ref = del->next; // 头指针直接后移
    }

    // 【步骤 3】维护后继节点的前驱指针（跳过 del 节点）
    if (del->next != NULL) {
        del->next->prev = del->prev;
    }

    // 【步骤 4】维护前驱节点的后继指针（跳过 del 节点）
    if (del->prev != NULL) {
        del->prev->next = del->next;
    }

    // 【步骤 5】显式释放节点内存
    free(del);
}

void print_list(const DNode *head) {
    while (head != NULL) {
        printf("[%d] <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_dlist(DNode *head) {
    while (head != NULL) {
        DNode *temp = head->next;
        free(head);
        head = temp;
    }
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    printf("==================== 双向链表 O(1) 快速删除验证 ====================\n");

    // 构造链表: 10 <-> 20 <-> 30
    DNode *head = create_dnode(10);
    DNode *n2 = create_dnode(20);
    DNode *n3 = create_dnode(30);

    head->next = n2; n2->prev = head;
    n2->next = n3;   n3->prev = n2;

    printf("删除前: ");
    print_list(head);

    // 测试 1: 直接传入节点指针删除中间节点 n2 (20) -> O(1)
    printf("\n【测试 1】直接通过指针 O(1) 删除节点 20...\n");
    delete_node(&head, n2);
    print_list(head);

    // 测试 2: 删除头节点 (10)
    printf("\n【测试 2】删除头节点 10...\n");
    delete_node(&head, head);
    print_list(head);

    free_dlist(head);
    head = NULL;

    return 0;
}

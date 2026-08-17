// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdlib.h>   // 标准通用工具库：提供 malloc(), free(), exit(), NULL 等堆内存动态分配与释放支持
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

/**
 * =============================================================================
 * 💡【知识点】双向链表头部插入 (Doubly Linked List Head Insertion)
 * =============================================================================
 * 
 * 📌【1. 头插法核心原理】
 *   在双向链表头部插入新节点 newNode 时，需要同时维护 4 根指针的指向，缺一不可：
 *   ① `newNode->next` 指向原头节点 `*head_ref`
 *   ② `newNode->prev` 置为 `NULL`（因为它是新的首节点）
 *   ③ 如果原头节点非空，原头节点的 `(*head_ref)->prev` 反向指向 `newNode`
 *   ④ 外部头指针 `*head_ref` 重定向为 `newNode`
 * 
 * 📌【2. 头插法指针重连 ASCII 图解】
 * 
 *   原有链表: *head_ref -> [Node A] <===> [Node B] -> NULL
 *   
 *   步骤 1: 申请 [newNode: 10]，其 prev = NULL
 *   步骤 2: newNode->next = *head_ref;
 *          [newNode: 10] -------> [Node A] <===> [Node B] -> NULL
 *                                    |
 *   步骤 3: (*head_ref)->prev = newNode;
 *          [newNode: 10] <======> [Node A] <===> [Node B] -> NULL
 *                ^
 *                |
 *   步骤 4: *head_ref = newNode; (更新外部头指针)
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么要特别判断 `if (*head_ref != NULL)`？
 *      👉 解答：如果链表原本是「空链表（*head_ref == NULL）」，此时如果直接执行 `(*head_ref)->prev = newNode`，
 *         就会引发严重的「空指针解引用」导致程序段错误崩溃！
 * =============================================================================
 */

// ==================== 1. 头部插入算法 ====================

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
 * @brief 在双向链表头部插入新节点 (头插法)
 * 
 * @param head_ref 外部头指针变量的地址 (二级指针)
 * @param data     待插入的数据
 * @return true 成功, false 内存不足
 * 
 * @note 时间复杂度: O(1) —— 常数次指针操作
 * @note 空间复杂度: O(1)
 */
bool insert_head(DNode **head_ref, int data) {
    if (head_ref == NULL) return false;

    // 【步骤 1】创建新节点
    DNode *newNode = create_dnode(data);
    if (!newNode) return false;

    // 【步骤 2】新节点的 next 指向原头节点
    newNode->next = *head_ref;
    newNode->prev = NULL; // 作为新的头节点，其前驱必定是 NULL

    // 【步骤 3】若原链表非空，原头节点的前驱必须反向勾住新节点
    if (*head_ref != NULL) {
        (*head_ref)->prev = newNode;
    }

    // 【步骤 4】头指针正式转移至新节点
    *head_ref = newNode;

    return true;
}

/**
 * @brief 打印双向链表
 */
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
    DNode *head = NULL; // 初始为空链表

    printf("==================== 双向链表头插法验证 ====================\n");
    printf("依次头插: 30, 20, 10...\n");

    insert_head(&head, 30);
    insert_head(&head, 20);
    insert_head(&head, 10);

    printf("最终构建结果: ");
    print_list(head);

    free_dlist(head);
    head = NULL;

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * =============================================================================
 * 💡【知识点】单链表核心插入操作 —— 头部插入 (Head) vs 尾部插入 (Tail)
 * =============================================================================
 * 
 * 📌【1. 插入机制与指针搭桥原理】
 *   - 头部插入 (头插法):
 *     新节点的 next 指向原头节点，随后将头指针更新为新节点。
 *     时间复杂度: O(1)
 *   - 尾部插入 (尾插法):
 *     找到链表的最后一个节点（其 next 为 NULL），将其 next 指向新节点。
 *     时间复杂度: O(N)（若维护 tail 尾指针则可降为 O(1)）
 * 
 * 📌【2. 头插法过程 ASCII 图解】
 * 
 *   原有链表:  *head_ref -> [Node A] -> [Node B] -> NULL
 *   
 *   步骤 1: 创建新节点 [newNode: 10]
 *   步骤 2: newNode->next = *head_ref;
 *          [newNode: 10] ---> [Node A] -> [Node B] -> NULL
 *          
 *   步骤 3: *head_ref = newNode;
 *          *head_ref
 *              |
 *              v
 *          [newNode: 10] ---> [Node A] -> [Node B] -> NULL (新头节点诞生！)
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么函数参数要用「二级指针 `Node **head_ref`」？
 *      👉 解答（C 语言值传递陷阱）：
 *         - 在 C 语言中，函数参数传递都是「值拷贝」。
 *         - 如果只传 `Node *head`，在函数内修改 `head = newNode` 只是修改了函数内部的形参拷贝，
 *           `main` 函数里的 `head` 变量依然是原来的值！
 *         - 传入 `Node **head_ref`（头指针变量的地址），通过 `*head_ref = newNode` 才能真正改变外部的头指针。
 * =============================================================================
 */

// ==================== 1. 链表插入算法 ====================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return NULL;
    n->data = data;
    n->next = NULL;
    return n;
}

/**
 * @brief 单链表头部插入 (头插法)
 * 
 * @param head_ref 外部头指针变量的地址（二级指针）
 * @param data     待插入的数据
 * @return true 成功, false 内存不足
 * 
 * @note 时间复杂度: O(1) —— 无论链表多长，均只需常数次指针赋值
 * @note 空间复杂度: O(1)
 */
bool insert_head(Node **head_ref, int data) {
    if (head_ref == NULL) return false;

    // 【步骤 1】创建新节点
    Node *newNode = create_node(data);
    if (!newNode) return false;

    // 【步骤 2】新节点指向原有的首节点
    newNode->next = *head_ref;

    // 【步骤 3】修改外部头指针，指向新节点
    *head_ref = newNode;

    return true;
}

/**
 * @brief 单链表尾部插入 (尾插法)
 * 
 * @param head_ref 外部头指针变量的地址
 * @param data     待插入的数据
 * @return true 成功, false 失败
 * 
 * @note 时间复杂度: O(N) —— 需要从头遍历到链表末尾
 * @note 空间复杂度: O(1)
 */
bool insert_tail(Node **head_ref, int data) {
    if (head_ref == NULL) return false;

    // 【步骤 1】创建新节点
    Node *newNode = create_node(data);
    if (!newNode) return false;

    // 【步骤 2】特殊情况：若链表当前为空，新节点直接作为头节点
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return true;
    }

    // 【步骤 3】非空链表：遍历寻找尾节点 (其 next 为 NULL 的节点)
    Node *curr = *head_ref;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    // 【步骤 4】原尾节点的 next 连接新节点
    curr->next = newNode;

    return true;
}

/**
 * @brief 打印链表内容
 */
void print_list(const Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

/**
 * @brief 释放整条链表
 */
void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head->next;
        free(head);
        head = temp;
    }
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    Node *head = NULL; // 初始空链表

    printf("==================== 单链表插入操作验证 ====================\n");

    // 1. 尾插法测试 (保持输入先后顺序)
    printf("1. 依次尾插 20, 30...\n");
    insert_tail(&head, 20);
    insert_tail(&head, 30);
    print_list(head);

    // 2. 头插法测试 (新元素置于最前)
    printf("\n2. 头插 10...\n");
    insert_head(&head, 10);
    print_list(head);

    // 释放资源
    free_list(head);
    head = NULL;

    return 0;
}

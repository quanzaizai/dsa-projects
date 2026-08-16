#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】单链表 (Singly Linked List) —— 构建、遍历与内存回收闭环
 * -----------------------------------------------------------------------------
 * 📌【概念与本质】
 *   单链表是一种物理存储单元上【非连续、离散分布】的线性结构。
 *   每个节点（Node）包含两大核心部分：
 *     ① 数据域 (data) : 存放节点承载的具体业务数据。
 *     ② 指针域 (next) : 存放指向后继节点的内存地址（指针自引用）。
 * 
 * 📌【链表 vs 数组 核心差异】
 *   • 连续性与扩容：数组需要整块连续空间，扩容成本极高；链表节点离散，按需 malloc 申请，天生支持无限动态扩容。
 *   • 访问与增删：数组支持 O(1) 下标随机访问；链表访问需从 head 逐个遍历（O(N)），但节点增删只需调整指针指向。
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)  : 数据结构定义 —— 封装数据域与指针域。
 *   2. createList()   : 核心构建 —— 利用 tail 指针实现 O(N) 尾插法高效建表。
 *   3. traverse()     : 核心遍历 —— 沿 next 指针链条逐个读取并格式化输出。
 *   4. freeList()     : 内存安全 —— 暂存 next 指针，逐节点释放堆空间（防野指针）。
 *   5. main()         : 驱动入口 —— 贯穿建表、遍历与释放全生命周期。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

// 定义单链表节点结构体
typedef struct Node {
    int data;               // 数据域：存储整型数值
    struct Node* next;      // 指针域：指向下一个节点的地址（自引用指针）
} Node;

// ==================== 2. 核心算法与操作实现 ====================

/**
 * @brief 动态创建一个包含 1 到 n 顺序数值的单链表
 * 
 * 🔍【核心构建逻辑剖析（尾插法）】：
 *   • 为什么引入 tail 尾指针？
 *     - 若无 tail，每次追加新节点都必须从 head 从头遍历到尾（单次 O(N)），总建表复杂度将恶化为 O(N^2)！
 *     - 维护 tail 指针可将每次尾插降为 O(1) 常数时间，总建表复杂度优化为 O(N)。
 *   • 尾插链接两步曲：
 *     ① tail->next = newNode; （将当前尾节点的 next 指向新分配的节点）
 *     ② tail = newNode;       （将 tail 指针后移，始终锚定在最新末尾节点）
 */
Node* createList(int n) {
    if (n <= 0) return NULL;

    // 步骤 1：创建首节点（头节点）
    Node* head = (Node*)malloc(sizeof(Node));
    if (!head) return NULL; // 内存不足保护
    head->data = 1;
    head->next = NULL;

    // 步骤 2：使用 tail 指针追踪当前链表的末尾
    Node* tail = head;

    // 步骤 3：循环追加后续新节点 (2 到 n)
    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) break;
        newNode->data = i;
        newNode->next = NULL;

        tail->next = newNode; // 步骤 ①：挂接新节点
        tail = newNode;       // 步骤 ②：更新尾指针
    }
    return head; // 返回头节点指针作为链表的唯一访问入口
}

/**
 * @brief 顺序遍历并打印单链表所有节点
 * 
 * 🔍【核心遍历逻辑剖析】：
 *   • 迭代推进：current = current->next 沿指针链条单向推进。
 *   • 终止条件：当 current == NULL 时，表示已到达链表末尾，退出循环。
 *   • 时空复杂度：时间复杂度 O(N)，空间复杂度 O(1)。
 */
void traverse(Node* head) {
    Node* current = head;
    printf("链表内容: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next; // 推进到下一个节点
    }
    printf("NULL\n");
}

/**
 * @brief 逐节点安全释放链表占用的堆内存
 * 
 * 🔍【核心安全释放剖析（致命陷阱防御）】：
 *   • 常见错误写法：free(current); current = current->next;（严重 Bug！）
 *     - 一旦 free(current)，该内存已被系统收回，再去访问 current->next 属于非法读取（Use-After-Free 野指针）。
 *   • 正确标准姿势：
 *     ① 暂存后继：Node* nextNode = current->next;
 *     ② 释放当前：free(current);
 *     ③ 推进指针：current = nextNode;
 */
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* nextNode = current->next; // 1. 先暂存下一个节点地址
        free(current);                  // 2. 安全释放当前节点
        current = nextNode;             // 3. 推进到暂存的下一个节点
    }
}

// ==================== 3. 测试与验证入口 ====================

int main(void) {
    int n = 5;
    
    printf("================ 单链表完整生命周期测试 ================\n");

    // 1. 动态建表 (1 -> 2 -> 3 -> 4 -> 5 -> NULL)
    printf("--> 动态创建包含 %d 个节点的单链表...\n", n);
    Node* head = createList(n);

    // 2. 顺序遍历
    traverse(head);

    // 3. 释放堆内存闭环
    printf("--> 深度释放链表堆空间，防止内存泄漏...\n");
    freeList(head);
    head = NULL; // 置空指针，杜绝悬空指针

    printf("【测试完成】链表已成功构建、遍历并安全销毁！\n");
    return 0;
}
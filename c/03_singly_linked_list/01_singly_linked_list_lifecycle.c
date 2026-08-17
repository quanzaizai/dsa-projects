#include <stdio.h>
#include <stdlib.h>

/**
 * =============================================================================
 * 💡【知识点】单链表 (Singly Linked List) —— 节点生命周期、遍历与安全回收
 * =============================================================================
 * 
 * 📌【1. 单链表的物理与逻辑结构】
 *   单链表是由一组在物理内存中「任意/离散分布」的节点通过指针链接而成的线性表。
 *   - 每个节点包含两个部分：
 *     ① 数据域 (data) ：存储具体业务数据。
 *     ② 指针域 (next) ：存储下一个节点的物理内存地址（最后一个节点指向 NULL）。
 * 
 * 📌【2. 单链表内存模型图解】
 * 
 *   head 指针
 *     |
 *     v
 *   +---------+------+       +---------+------+       +---------+------+
 *   | data:10 | next | ----> | data:20 | next | ----> | data:30 | NULL |
 *   +---------+------+       +---------+------+       +---------+------+
 *   (堆地址:0x1000)          (堆地址:0x2050)          (堆地址:0x1080)
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么单链表不支持数组那样的 `arr[i]` 随机访问？
 *      👉 解答：数组在内存中是连续的，可以通过 `基地址 + i * 元素大小` 一步计算出物理地址（O(1)）。
 *         而单链表节点散落在堆区各处，只能从 `head` 开始顺着 `next` 指针一路向后“顺藤摸瓜”，
 *         访问第 k 个节点必须遍历 k 次，时间复杂度为 O(k)。
 * 
 *   ❓ Q2: 为什么释放链表时必须用 `next = curr->next` 暂存？
 *      👉 解答（经典内存越界陷阱 Use-After-Free）：
 *         - 如果先执行 `free(curr)`，当前节点占用的内存就被系统收回了！
 *         - 此时如果再去读取 `curr->next`，就属于读取非法内存（未定义行为），可能导致数据错乱或程序崩溃。
 *         - 正确姿势：先用 `next` 变量把后继地址记在小本本上，再放心 `free(curr)`。
 * =============================================================================
 */

// ==================== 1. 节点定义与基础操作 ====================

/**
 * @brief 单链表节点结构体定义
 */
typedef struct Node {
    int data;               // 数据域
    struct Node *next;      // 指针域：指向后继节点
} Node;

/**
 * @brief 在堆上动态创建一个新节点
 * 
 * @param data 节点装填的数据
 * @return Node* 指向新节点的指针；若内存分配失败返回 NULL
 * 
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
Node* create_node(int data) {
    // 【步骤 1】向堆区申请节点所需内存
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    // 【步骤 2】防御性检查
    if (newNode == NULL) {
        printf("⚠️ [创建失败] 堆内存分配失败！\n");
        return NULL;
    }

    // 【步骤 3】初始化数据域与指针域
    newNode->data = data;
    newNode->next = NULL; // 新生节点默认不指向任何后继

    return newNode;
}

/**
 * @brief 遍历打印整条单链表
 * 
 * @param head 链表的头指针
 * @note 时间复杂度: O(N) | 空间复杂度: O(1)
 */
void print_list(const Node *head) {
    const Node *curr = head; // 游标指针，从头节点出发

    printf("链表内容: ");
    while (curr != NULL) {
        printf("[%d] -> ", curr->data);
        curr = curr->next; // 游标移动到下一个节点
    }
    printf("NULL (尾端)\n");
}

/**
 * @brief 安全销毁整条链表，释放全部堆内存
 * 
 * @param head 链表头指针
 * @note 时间复杂度: O(N) | 空间复杂度: O(1)
 */
void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        // 【关键步骤 1】先暂存下一个节点的指针，防止释放后断链
        Node *next_node = curr->next;

        // 【关键步骤 2】安全释放当前节点
        free(curr);

        // 【关键步骤 3】游标指向下一个待释放节点
        curr = next_node;
    }
    printf("🧹 [清理完毕] 单链表所有节点已安全释放\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    printf("==================== 单链表生命周期验证 ====================\n");

    // 【手动连接节点构建测试链表】: 10 -> 20 -> 30 -> NULL
    Node *head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);

    // 遍历展示
    print_list(head);

    // 闭环释放全部堆内存
    free_list(head);
    head = NULL; // 防御性置空，杜绝野指针

    return 0;
}

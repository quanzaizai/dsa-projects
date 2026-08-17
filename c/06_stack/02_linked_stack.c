// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdlib.h>   // 标准通用工具库：提供 malloc(), free(), exit(), NULL 等堆内存动态分配与释放支持
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

/**
 * =============================================================================
 * 💡【知识点】数据结构 —— 链式栈 (Linked-List-based Stack)
 * =============================================================================
 * 
 * 📌【1. 什么是链式栈？】
 *   链式栈就是用「单链表」实现的栈。它遵循 LIFO (Last In First Out，后进先出) 原则。
 *   - 栈顶 (Top)   ：固定对准单链表的「头节点 (Head)」。
 *   - 栈底 (Bottom)：固定对准单链表的「尾节点 (Tail)」，其 next 指向 NULL。
 * 
 * 📌【2. 内存模型图解 (Memory Layout)】
 * 
 *   [LinkedStack 栈管理结构]
 *   +-------------+---------+
 *   |  top (指针)  | size: 3 |
 *   +------+------+---------+
 *          |
 *          v
 *     +---------+------+       +---------+------+       +---------+------+
 *     | data:30 | next | ----> | data:20 | next | ----> | data:10 | next | ----> NULL
 *     +---------+------+       +---------+------+       +---------+------+
 *       ▲ 栈顶 (Top)                                      ▲ 栈底 (Bottom)
 * 
 * 📌【3. 深度思考与高频疑难解答 (Q&A)】
 * 
 *   ❓ Q1: 为什么一定要用「单链表头部」做栈顶，而不是「尾部」？
 *      👉 解答：
 *         - 头部做栈顶：入栈（头插）、出栈（头删）都只需要操作头指针，时间复杂度为严格的 O(1)。
 *         - 尾部做栈顶：入栈（尾插）若有尾指针也可以 O(1)，但「出栈（尾删）」必须找到尾节点的前驱节点！
 *           在单链表中找前驱必须从头到尾遍历整条链表，出栈时间退化为 O(N)！
 *           （除非使用双向链表，但每个节点会额外浪费一个 prev 指针空间，得不偿失）。
 * 
 *   ❓ Q2: 为什么函数的出栈不用 `int pop()`，而用 `bool pop(..., int *out_val)`？
 *      👉 解答：
 *         - 如果设计为 `int pop()`，当栈为空时返回什么呢？返回 -1 还是 0？
 *         - 如果栈里正好存的就是 -1 或 0，调用者就无法区分「是取出了数据 -1」还是「栈空出错了」。
 *         - 采用 `bool` 返回状态（成功/失败），用指针传出数据，是工业级 C 语言开发的经典防御性规范。
 * 
 *   ❓ Q3: 顺序栈 vs 链式栈，怎么选？
 *      👉 对比：
 *         - 顺序栈：内存连续，CPU 缓存命中率极高，无额外指针开销；但容量固定（可能栈满溢出）。
 *         - 链式栈：动态按需分配堆内存，理论上永不栈满；但每个节点多耗费一个指针空间（64位下为8字节），
 *                  且频繁 malloc/free 存在少许内存碎片和系统调用开销。
 * =============================================================================
 */

// ==================== 1. 数据结构定义 ====================

/**
 * @brief 链表节点结构体
 */
typedef struct StackNode {
    int data;               // 节点存储的数据
    struct StackNode *next; // 指向下一个节点的指针（下方栈元素）
} StackNode;

/**
 * @brief 链式栈管理结构体
 */
typedef struct LinkedStack {
    StackNode *top;         // 栈顶指针：指向链表的第一个有效节点
    int size;               // 元素计数器：记录当前栈中元素的总数
} LinkedStack;

// ==================== 2. 核心操作接口实现 ====================

/**
 * @brief 初始化链式栈
 * @param s 待初始化的栈管理结构指针
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
void linked_stack_init(LinkedStack *s) {
    if (s == NULL) return;
    s->top = NULL; // 初始时没有任何节点，栈顶指针悬空置 NULL
    s->size = 0;   // 初始元素计数为 0
}

/**
 * @brief 判断链式栈是否为空
 * @param s 栈指针
 * @return true 栈为空, false 栈非空
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
bool linked_stack_is_empty(const LinkedStack *s) {
    // 栈指针为空 或 栈顶指针为 NULL，均视为空栈
    return (s == NULL || s->top == NULL);
}

/**
 * @brief 获取链式栈当前的元素个数
 * @param s 栈指针
 * @return 栈内有效元素总数
 * @note 时间复杂度: O(1)（直接读取计数器，无需遍历链表）
 */
int linked_stack_size(const LinkedStack *s) {
    return (s == NULL) ? 0 : s->size;
}

/**
 * @brief 入栈操作 (Push) —— 单链表头插法
 * 
 * 🎨【入栈过程 ASCII 图解】：
 *   假设原有栈: top -> [A] -> NULL，要压入新节点 [newNode: B]
 *   
 *   步骤 1: 开辟新节点并在堆上填入数据
 *          [newNode: B] (next 暂时未定)
 *          
 *   步骤 2: 将新节点的 next 指向当前栈顶 (newNode->next = s->top)
 *          [newNode: B] ---> [A] ---> NULL
 *                            ▲
 *                            |
 *                         s->top
 *                         
 *   步骤 3: 更新栈顶指针指向新节点 (s->top = newNode)
 *          [newNode: B] ---> [A] ---> NULL
 *               ▲
 *               |
 *            s->top (新栈顶诞生！)
 * 
 * @param s 栈指针
 * @param value 待入栈的数据
 * @return true 入栈成功, false 内存耗尽分配失败
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
bool linked_stack_push(LinkedStack *s, int value) {
    // 防御性检查：传入的栈管理指针不能为空
    if (s == NULL) return false;

    // 【步骤 1】向操作系统堆区申请一个新节点的内存空间
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("⚠️ [Push 失败] 系统堆内存不足，malloc 分配失败！\n");
        return false;
    }

    // 【步骤 2】装填数据
    newNode->data = value;

    // 【步骤 3】核心指针连接：新节点的 next 指向当前栈顶所指的节点
    newNode->next = s->top;

    // 【步骤 4】栈顶指针移动：让 s->top 指向刚刚插入的新节点
    s->top = newNode;

    // 【步骤 5】维护元素计数
    s->size++;

    printf("⬆️ [Push 成功] 元素 %d 已入栈 | 当前栈深度: %d\n", value, s->size);
    return true;
}

/**
 * @brief 出栈操作 (Pop) —— 单链表头删法
 * 
 * 🎨【出栈过程 ASCII 图解】：
 *   假设原有栈: top -> [B] -> [A] -> NULL，需要弹出 [B]
 *   
 *   步骤 1: 用临时指针 temp 锁定当前栈顶节点
 *          temp = s->top (锁定节点 B)
 *          
 *   步骤 2: 栈顶指针后移到下一个节点 (s->top = s->top->next)
 *          [B] (被 temp 抓着)
 *          
 *          s->top ---> [A] ---> NULL
 *          
 *   步骤 3: 释放 temp 节点的内存 (free(temp))，防止内存泄漏！
 *          [A] ---> NULL (现在 A 成为了新的栈顶)
 *           ▲
 *         s->top
 * 
 * @param s 栈指针
 * @param out_val 用于接收弹出数据的指针（传出参数）
 * @return true 出栈成功, false 栈空失败
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
bool linked_stack_pop(LinkedStack *s, int *out_val) {
    // 【步骤 1】防御性检查：栈空时无法弹出元素（防止下溢）
    if (linked_stack_is_empty(s)) {
        printf("⚠️ [Pop 失败] 栈为空，无法执行出栈！\n");
        return false;
    }

    // 【步骤 2】暂存待删除的原栈顶节点指针（后续用于 free）
    StackNode *temp = s->top;

    // 【步骤 3】如果调用者提供了接收指针，将数据传出
    if (out_val != NULL) {
        *out_val = temp->data;
    }

    // 【步骤 4】核心指针移动：栈顶指针越过当前节点，指向其下一个节点
    s->top = s->top->next;

    // 【步骤 5】维护元素计数
    s->size--;

    // 【步骤 6】⚠️ 关键细节：显式释放原栈顶节点内存，彻底杜绝内存泄漏！
    free(temp);
    temp = NULL; // 良好的防御性习惯：避免野指针

    return true;
}

/**
 * @brief 查看栈顶元素 (Peek)
 * @param s 栈指针
 * @param out_val 用于接收栈顶数据的指针
 * @return true 成功获取, false 栈空或参数非法
 * @note 仅窥视栈顶数据，不改变栈顶指针，不释放任何内存
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
bool linked_stack_peek(const LinkedStack *s, int *out_val) {
    if (linked_stack_is_empty(s) || out_val == NULL) {
        return false;
    }
    // 直接读取栈顶节点的数据
    *out_val = s->top->data;
    return true;
}

/**
 * @brief 销毁栈并释放所有节点的堆内存（防止内存泄漏）
 * 
 * 🎨【循环释放原理】：
 *   每次循环时：
 *     1. 暂存当前节点的 next 指针：next = curr->next
 *     2. 释放当前节点：free(curr)
 *     3. 移动到下一个节点：curr = next
 *   ⚠️ 警示：切不可直接 free(curr) 后再去访问 curr->next，那属于非法内存访问 (Use-After-Free)！
 * 
 * @param s 待销毁的栈指针
 * @note 时间复杂度: O(N) | 空间复杂度: O(1)
 */
void linked_stack_destroy(LinkedStack *s) {
    if (s == NULL) return;

    StackNode *curr = s->top;
    while (curr != NULL) {
        // 先把下一个节点的地址记下来
        StackNode *next = curr->next;
        // 安全释放当前节点
        free(curr);
        // 指针前进
        curr = next;
    }

    // 栈管理结构归零，防止野指针
    s->top = NULL;
    s->size = 0;
    printf("🧹 [清理完毕] 链式栈已安全释放全部堆内存节点\n");
}

/**
 * @brief 可视化打印链式栈当前的所有元素
 * @param s 栈指针
 * @note 从栈顶顺着 next 指针一路打印到栈底
 */
void linked_stack_print(const LinkedStack *s) {
    if (linked_stack_is_empty(s)) {
        printf("【栈状态】: [ 空栈 ] (size = 0)\n");
        return;
    }

    printf("【栈状态】(当前 size = %d): [栈顶] ", s->size);
    StackNode *curr = s->top;
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL) {
            printf(" -> ");
        }
        curr = curr->next;
    }
    printf(" [栈底]\n");
}

// ==================== 3. 测试与验证入口 ====================

int main(void) {
    // 声明栈变量并初始化
    LinkedStack stack;
    linked_stack_init(&stack);

    printf("==================== 1. 动态入栈测试 (Push) ====================\n");
    linked_stack_push(&stack, 100);
    linked_stack_push(&stack, 200);
    linked_stack_push(&stack, 300);
    linked_stack_print(&stack);

    printf("\n==================== 2. 栈顶窥视测试 (Peek) ====================\n");
    int top_val;
    if (linked_stack_peek(&stack, &top_val)) {
        printf("🔍 [Peek] 当前栈顶元素为: %d (元素并未出栈，size 仍为 %d)\n", top_val, linked_stack_size(&stack));
    }

    printf("\n==================== 3. 出栈与内存释放测试 (Pop) ====================\n");
    int popped_val;
    linked_stack_pop(&stack, &popped_val);
    printf("⬇️ [Pop 成功] 弹出元素: %d\n", popped_val);
    linked_stack_print(&stack);

    linked_stack_pop(&stack, &popped_val);
    printf("⬇️ [Pop 成功] 弹出元素: %d\n", popped_val);
    linked_stack_print(&stack);

    printf("\n==================== 4. 栈销毁与安全清理 (Destroy) ====================\n");
    linked_stack_destroy(&stack);
    linked_stack_print(&stack);

    printf("\n==================== 5. 空栈出栈防御测试 (Underflow) ====================\n");
    linked_stack_pop(&stack, &popped_val);

    return 0;
}

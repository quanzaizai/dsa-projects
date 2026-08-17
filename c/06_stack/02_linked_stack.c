#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * 💡【知识点】数据结构 —— 链式栈 (Linked-List-based Stack)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 动态链表结构：以单链表的**头部**作为栈顶 (Top)。
 *   2. 入栈 (Push) 机制：采用**头插法**，新节点 next 指向原栈顶，栈顶指针重定向为新节点 (O(1))。
 *   3. 出栈 (Pop) 机制：暂存原栈顶节点指针，栈顶指针后移 (`top = top->next`)，并安全 `free()` 释放原栈顶 (O(1))。
 *   4. 核心优势：突破数组固定容量限制，按需动态分配堆内存，理论上永不发生栈满溢出（只要系统内存充足）。
 *   5. 内存管理：生命周期结束时，必须显式调用 `free_stack` 遍历释放全部节点，杜绝内存泄漏。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构与核心接口 ====================

// 链表节点结构
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// 链式栈控制结构体
typedef struct LinkedStack {
    StackNode *top; // 指向链表头节点（即栈顶）
    int size;       // 记录栈中有效元素数量
} LinkedStack;

/**
 * @brief 初始化链式栈
 */
void linked_stack_init(LinkedStack *s) {
    if (s != NULL) {
        s->top = NULL;
        s->size = 0;
    }
}

/**
 * @brief 检查链式栈是否为空
 */
bool linked_stack_is_empty(const LinkedStack *s) {
    return s == NULL || s->top == NULL;
}

/**
 * @brief 获取链式栈元素个数
 */
int linked_stack_size(const LinkedStack *s) {
    return (s == NULL) ? 0 : s->size;
}

/**
 * @brief 入栈操作 (Push) —— 头插法
 * @param s 栈指针
 * @param value 待入栈元素
 * @return true 成功, false 内存分配失败
 */
bool linked_stack_push(LinkedStack *s, int value) {
    if (s == NULL) return false;

    // 1. 动态开辟新节点内存
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("⚠️ [Push 失败] 堆内存分配失败！\n");
        return false;
    }

    newNode->data = value;
    // 🔍【核心头插】：新节点的 next 指向当前栈顶
    newNode->next = s->top;
    // 栈顶指针重定向为新节点
    s->top = newNode;
    s->size++;

    printf("⬆️ [Push 成功] 元素 %d 已入栈 | 当前栈深度: %d\n", value, s->size);
    return true;
}

/**
 * @brief 出栈操作 (Pop) —— 头删法
 * @param s 栈指针
 * @param out_val 接收弹出数据的指针
 * @return true 成功, false 栈空失败
 */
bool linked_stack_pop(LinkedStack *s, int *out_val) {
    if (linked_stack_is_empty(s)) {
        printf("⚠️ [Pop 失败] 栈为空，无法出栈！\n");
        return false;
    }

    // 🔍【核心头删】：
    // 1. 暂存待释放的原栈顶节点
    StackNode *temp = s->top;
    if (out_val != NULL) {
        *out_val = temp->data;
    }

    // 2. 栈顶指针后移
    s->top = s->top->next;
    s->size--;

    // 3. ⚠️【关键细节】：显式释放原栈顶节点内存，防止内存泄漏
    free(temp);

    return true;
}

/**
 * @brief 查看栈顶元素 (Peek)
 */
bool linked_stack_peek(const LinkedStack *s, int *out_val) {
    if (linked_stack_is_empty(s) || out_val == NULL) {
        return false;
    }
    *out_val = s->top->data;
    return true;
}

/**
 * @brief 销毁栈并释放所有节点内存（闭环回收）
 */
void linked_stack_destroy(LinkedStack *s) {
    if (s == NULL) return;

    StackNode *curr = s->top;
    while (curr != NULL) {
        StackNode *next = curr->next;
        free(curr); // 释放当前节点
        curr = next;
    }
    s->top = NULL;
    s->size = 0;
    printf("🧹 [清理完毕] 链式栈已安全释放全部堆内存节点\n");
}

/**
 * @brief 打印当前链式栈内元素
 */
void linked_stack_print(const LinkedStack *s) {
    if (linked_stack_is_empty(s)) {
        printf("【栈状态】: [ 空栈 ]\n");
        return;
    }

    printf("【栈状态】(从栈顶到栈底): [顶] ");
    StackNode *curr = s->top;
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL) printf(" -> ");
        curr = curr->next;
    }
    printf(" [底]\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    LinkedStack stack;
    linked_stack_init(&stack);

    printf("==================== 1. 动态入栈测试 ====================\n");
    linked_stack_push(&stack, 100);
    linked_stack_push(&stack, 200);
    linked_stack_push(&stack, 300);
    linked_stack_print(&stack);

    int top_val;
    if (linked_stack_peek(&stack, &top_val)) {
        printf("\n🔍 [Peek] 栈顶元素: %d\n", top_val);
    }

    printf("\n==================== 2. 出栈与内存释放测试 ====================\n");
    int val;
    linked_stack_pop(&stack, &val);
    printf("⬇️ [Pop 成功] 弹出: %d\n", val);
    linked_stack_print(&stack);

    printf("\n==================== 3. 销毁栈释放堆内存 ====================\n");
    linked_stack_destroy(&stack);
    linked_stack_print(&stack);

    return 0;
}

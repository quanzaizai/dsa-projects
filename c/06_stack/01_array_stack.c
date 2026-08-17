// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

#define MAX_CAPACITY 5 // 栈的最大物理容量

/**
 * =============================================================================
 * 💡【知识点】数据结构 —— 顺序栈 (Array-based Stack)
 * =============================================================================
 * 
 * 📌【1. 什么是顺序栈？】
 *   顺序栈是用「连续数组」实现的受限线性表。
 *   - LIFO (Last In First Out，后进先出)：所有插入 (Push) 和删除 (Pop) 操作均限制在同一端（栈顶 Top）进行。
 *   - 栈底 (Bottom)：固定在数组下标 0 处。
 *   - 栈顶 (Top)   ：由游标指针 `top` 动态指示。
 * 
 * 📌【2. 内存模型与入栈/出栈操作图解】
 * 
 *   [初始空栈] top = -1
 *   下标:    0     1     2     3     4
 *   数组:  |  _  |  _  |  _  |  _  |  _  |   (top = -1)
 *   
 *   [入栈 Push 10, 20, 30] -> 先 ++top，再写入 items[top] = val
 *   下标:    0     1     2     3     4
 *   数组:  | 10  | 20  | 30  |  _  |  _  |   (top = 2, size = 3)
 *          [栈底]        [栈顶]
 *          
 *   [出栈 Pop 30] -> 先读取 items[top]，再 top--
 *   下标:    0     1     2     3     4
 *   数组:  | 10  | 20  | (30)|  _  |  _  |   (top = 1, size = 2)
 *          [栈底]  [栈顶]
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 栈顶指针 `top` 为什么初始值设为 `-1` 而不是 `0`？
 *      👉 解答（两种经典设计流派）：
 *         - 方案 A（本项目采用）：`top = -1` 指向「当前栈顶元素」。
 *           - 判空：`top == -1`
 *           - 判满：`top == MAX_CAPACITY - 1`
 *           - 元素个数：`top + 1`
 *           - 入栈：`items[++top] = val`
 *         - 方案 B：`top = 0` 指向「下一个待插入的空位」。
 *           - 判空：`top == 0`
 *           - 判满：`top == MAX_CAPACITY`
 *           - 元素个数：`top`
 *           - 入栈：`items[top++] = val`
 * 
 *   ❓ Q2: 什么是栈上溢 (Overflow) 与栈下溢 (Underflow)？
 *      👉 解答：
 *         - 栈上溢 (Stack Overflow) ：栈已经满了 (`top == MAX-1`)，还强行 Push，导致数组越界。
 *         - 栈下溢 (Stack Underflow)：栈已经是空的 (`top == -1`)，还强行 Pop，导致读取非法内存。
 * =============================================================================
 */

// ==================== 1. 数据结构定义与核心接口 ====================

typedef struct ArrayStack {
    int items[MAX_CAPACITY]; // 存储栈元素的静态数组
    int top;                 // 栈顶游标：指向当前栈顶元素的下标
} ArrayStack;

/**
 * @brief 初始化栈
 * @param s 栈指针
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
void stack_init(ArrayStack *s) {
    if (s != NULL) {
        s->top = -1; // 初始时没有任何元素，置为 -1 表示空栈
    }
}

/**
 * @brief 检查栈是否为空
 * @param s 栈指针
 * @return true 栈空, false 非空
 */
bool stack_is_empty(const ArrayStack *s) {
    return (s == NULL || s->top == -1);
}

/**
 * @brief 检查栈是否已满
 * @param s 栈指针
 * @return true 栈满, false 未满
 */
bool stack_is_full(const ArrayStack *s) {
    return (s != NULL && s->top == MAX_CAPACITY - 1);
}

/**
 * @brief 获取当前栈内元素个数
 */
int stack_size(const ArrayStack *s) {
    return (s == NULL) ? 0 : s->top + 1;
}

/**
 * @brief 入栈操作 (Push)
 * 
 * @param s     栈指针
 * @param value 待入栈数据
 * @return true 成功, false 栈满失败 (上溢防御)
 * 
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
bool stack_push(ArrayStack *s, int value) {
    // 【步骤 1】防上溢检查：栈满时拒绝压入
    if (stack_is_full(s)) {
        printf("⚠️ [Push 失败] 栈已满 (容量: %d)，无法压入元素 %d！\n", MAX_CAPACITY, value);
        return false;
    }

    // 【步骤 2】先将 top 指针自增 1，再把新元素存入该槽位
    s->items[++(s->top)] = value;

    printf("⬆️ [Push 成功] 元素 %d 已入栈 | 当前栈深度: %d\n", value, stack_size(s));
    return true;
}

/**
 * @brief 出栈操作 (Pop)
 * 
 * @param s       栈指针
 * @param out_val 用于接收弹出数据的指针 (传出参数)
 * @return true 成功, false 栈空失败 (下溢防御)
 * 
 * @note 时间复杂度: O(1) | 空间复杂度: O(1)
 */
bool stack_pop(ArrayStack *s, int *out_val) {
    // 【步骤 1】放下溢检查：栈空时拒绝弹出
    if (stack_is_empty(s)) {
        printf("⚠️ [Pop 失败] 栈为空，无元素可弹出！\n");
        return false;
    }

    // 【步骤 2】先取出栈顶数据，再将 top 指针自减 1
    if (out_val != NULL) {
        *out_val = s->items[(s->top)--];
    } else {
        (s->top)--;
    }

    return true;
}

/**
 * @brief 查看栈顶元素 (Peek / Top)
 * @note 仅窥视数据，不改变 top 指针，不改变栈状态
 */
bool stack_peek(const ArrayStack *s, int *out_val) {
    if (stack_is_empty(s) || out_val == NULL) {
        return false;
    }
    *out_val = s->items[s->top];
    return true;
}

/**
 * @brief 可视化打印栈内元素
 */
void stack_print(const ArrayStack *s) {
    if (stack_is_empty(s)) {
        printf("【栈状态】: [ 空栈 ] (size = 0)\n");
        return;
    }

    printf("【栈状态】(从栈底到栈顶): [栈底] ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d", s->items[i]);
        if (i < s->top) printf(" -> ");
    }
    printf(" [栈顶]\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    ArrayStack my_stack;
    stack_init(&my_stack);

    printf("==================== 1. 顺序栈压栈测试 (Push 至满) ====================\n");
    stack_push(&my_stack, 10);
    stack_push(&my_stack, 20);
    stack_push(&my_stack, 30);
    stack_push(&my_stack, 40);
    stack_push(&my_stack, 50);
    stack_print(&my_stack);

    // 测试满栈溢出防御
    printf("\n==================== 2. 栈满上溢防御测试 ====================\n");
    stack_push(&my_stack, 60);

    // 查看栈顶
    int top_val;
    if (stack_peek(&my_stack, &top_val)) {
        printf("\n🔍 [Peek] 当前栈顶元素为: %d (并未出栈)\n", top_val);
    }

    printf("\n==================== 3. 连续出栈测试 (验证 LIFO 特性) ====================\n");
    int popped;
    while (!stack_is_empty(&my_stack)) {
        stack_pop(&my_stack, &popped);
        printf("⬇️ [Pop 成功] 弹出元素: %d | 剩余深度: %d\n", popped, stack_size(&my_stack));
    }
    stack_print(&my_stack);

    // 测试空栈下溢防御
    printf("\n==================== 4. 栈空下溢防御测试 ====================\n");
    stack_pop(&my_stack, &popped);

    return 0;
}

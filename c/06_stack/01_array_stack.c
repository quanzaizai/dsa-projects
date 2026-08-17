#include <stdio.h>
#include <stdbool.h>

#define MAX_CAPACITY 5 // 栈的最大容量

/**
 * 💡【知识点】数据结构 —— 顺序栈 (Array-based Stack)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. LIFO (后进先出)：所有插入 (Push) 与弹出 (Pop) 操作均限制在数组同一端（栈顶 Top）进行。
 *   2. 栈顶指针 (top)：
 *      - 初始时 top = -1（表示空栈）。
 *      - 入栈时：先 ++top，再写入数据 items[top] = val。
 *      - 出栈时：先读取数据 items[top]，再 top--。
 *   3. 时空复杂度：入栈、出栈、查看栈顶均为严格的 O(1) 常数时间复杂度，额外空间 O(1)。
 *   4. 优缺点：内存连续、访问速度极快、CPU 缓存友好；但容量固定，可能发生栈溢出 (Stack Overflow)。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义与核心接口 ====================

typedef struct ArrayStack {
    int items[MAX_CAPACITY]; // 存储栈元素的静态数组
    int top;                 // 栈顶指针（存储当前栈顶元素的下标）
} ArrayStack;

/**
 * @brief 初始化栈（将 top 置为 -1）
 */
void stack_init(ArrayStack *s) {
    if (s != NULL) {
        s->top = -1;
    }
}

/**
 * @brief 检查栈是否为空
 * @return true 栈空, false 非空
 */
bool stack_is_empty(const ArrayStack *s) {
    return s == NULL || s->top == -1;
}

/**
 * @brief 检查栈是否已满
 * @return true 栈满, false 未满
 */
bool stack_is_full(const ArrayStack *s) {
    return s != NULL && s->top == MAX_CAPACITY - 1;
}

/**
 * @brief 获取当前栈内元素个数
 */
int stack_size(const ArrayStack *s) {
    return (s == NULL) ? 0 : s->top + 1;
}

/**
 * @brief 入栈操作 (Push)
 * @param s 栈指针
 * @param value 待入栈数据
 * @return true 入栈成功, false 栈满失败
 */
bool stack_push(ArrayStack *s, int value) {
    // ⚠️【防御性检查】：入栈前必须检查是否栈满，防止数组越界
    if (stack_is_full(s)) {
        printf("⚠️ [Push 失败] 栈已满 (容量: %d)，无法压入元素 %d！\n", MAX_CAPACITY, value);
        return false;
    }

    // 🔍【核心逻辑】：先将栈顶指针加 1，再把新元素存入该位置
    s->items[++(s->top)] = value;
    printf("⬆️ [Push 成功] 元素 %d 已入栈 | 当前栈深度: %d\n", value, stack_size(s));
    return true;
}

/**
 * @brief 出栈操作 (Pop)
 * @param s 栈指针
 * @param out_val 用于接收弹出元素的指针
 * @return true 出栈成功, false 栈空失败
 */
bool stack_pop(ArrayStack *s, int *out_val) {
    // ⚠️【防御性检查】：出栈前必须检查是否栈空，防止下溢 (Stack Underflow)
    if (stack_is_empty(s)) {
        printf("⚠️ [Pop 失败] 栈为空，无元素可弹出！\n");
        return false;
    }

    // 🔍【核心逻辑】：先取出栈顶元素，再将栈顶指针减 1
    if (out_val != NULL) {
        *out_val = s->items[(s->top)--];
    } else {
        (s->top)--;
    }
    return true;
}

/**
 * @brief 查看栈顶元素 (Peek / Top)
 * @note 仅读取栈顶数据，不移动 top 指针，不修改栈结构
 */
bool stack_peek(const ArrayStack *s, int *out_val) {
    if (stack_is_empty(s) || out_val == NULL) {
        return false;
    }
    *out_val = s->items[s->top];
    return true;
}

/**
 * @brief 格式化可视化打印当前栈内状态
 */
void stack_print(const ArrayStack *s) {
    if (stack_is_empty(s)) {
        printf("【栈状态】: [ 空栈 ]\n");
        return;
    }

    printf("【栈状态】(从栈底到栈顶): [底] ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d", s->items[i]);
        if (i < s->top) printf(" -> ");
    }
    printf(" [顶]\n");
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    ArrayStack my_stack;
    stack_init(&my_stack);

    printf("==================== 1. 连续入栈测试 (压栈至满) ====================\n");
    stack_push(&my_stack, 10);
    stack_push(&my_stack, 20);
    stack_push(&my_stack, 30);
    stack_push(&my_stack, 40);
    stack_push(&my_stack, 50);
    stack_print(&my_stack);

    // 尝试满栈溢出压入
    printf("\n==================== 2. 栈满溢出防御测试 ====================\n");
    stack_push(&my_stack, 60);

    // 查看栈顶
    int top_val;
    if (stack_peek(&my_stack, &top_val)) {
        printf("\n🔍 [Peek] 当前栈顶元素为: %d (并未出栈)\n", top_val);
    }

    printf("\n==================== 3. 连续出栈测试 (验证 LIFO 后进先出) ====================\n");
    int popped;
    while (!stack_is_empty(&my_stack)) {
        stack_pop(&my_stack, &popped);
        printf("⬇️ [Pop 成功] 弹出元素: %d | 剩余深度: %d\n", popped, stack_size(&my_stack));
    }
    stack_print(&my_stack);

    // 尝试空栈下溢弹出
    printf("\n==================== 4. 栈空下溢防御测试 ====================\n");
    stack_pop(&my_stack, &popped);

    return 0;
}

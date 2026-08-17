#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define STACK_CAPACITY 64

/**
 * 💡【知识点】栈经典应用 —— 逆波兰表达式 / 后缀表达式求值 (Postfix Evaluation)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 逆波兰表达式规则：操作数在前，运算符在后（如 "2 3 +" 等价于 2 + 3）。无需括号即可精确表达运算优先级。
 *   2. 算法核心步骤：
 *      - 从左向右遍历后缀表达式。
 *      - 遇到操作数（数字）：将其压入数值栈。
 *      - 遇到运算符（+, -, *, /）：连续弹出栈顶的两个操作数（⚠️ 注意：先弹出的为右操作数 b，后弹出的为左操作数 a），
 *        执行 `a op b` 计算后，将计算结果重新压入栈中。
 *      - 表达式遍历结束后，栈顶元素即为最终计算结果。
 *   3. 时空复杂度：时间复杂度 O(N)（单趟线性扫描），空间复杂度 O(N)（辅助操作数栈）。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 整型计算辅助栈 ====================

typedef struct NumStack {
    int items[STACK_CAPACITY];
    int top;
} NumStack;

static void num_stack_init(NumStack *s) { s->top = -1; }
static bool num_stack_is_empty(const NumStack *s) { return s->top == -1; }

static bool num_stack_push(NumStack *s, int val) {
    if (s->top >= STACK_CAPACITY - 1) return false;
    s->items[++(s->top)] = val;
    return true;
}

static bool num_stack_pop(NumStack *s, int *out_val) {
    if (num_stack_is_empty(s)) return false;
    if (out_val) *out_val = s->items[(s->top)--];
    return true;
}

// ==================== 2. 后缀表达式求值算法 ====================

/**
 * @brief 计算以空格分隔的后缀表达式
 * @param expr 字符串（如 "5 3 + 8 2 - *" -> (5+3) * (8-2) = 48）
 * @param out_result 存储计算结果
 * @return true 计算成功, false 表达式非法
 */
bool evaluate_postfix(const char *expr, int *out_result) {
    if (expr == NULL || out_result == NULL) return false;

    NumStack stack;
    num_stack_init(&stack);

    int i = 0;
    while (expr[i] != '\0') {
        // 过滤空格
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // 1. 解析多位数字
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            num_stack_push(&stack, num);
        }
        // 2. 解析运算符
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            char op = expr[i];
            int b, a; // ⚠️ 先弹出的为右操作数 b，后弹出的为左操作数 a
            if (!num_stack_pop(&stack, &b) || !num_stack_pop(&stack, &a)) {
                printf("⚠️ 错误：表达式缺少操作数！\n");
                return false;
            }

            int res = 0;
            switch (op) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("⚠️ 错误：除数为 0！\n");
                        return false;
                    }
                    res = a / b; 
                    break;
            }
            num_stack_push(&stack, res); // 结果压回栈
            i++;
        } else {
            i++; // 忽略其他未知字符
        }
    }

    return num_stack_pop(&stack, out_result);
}

// ==================== 3. 测试与验证入口 ====================

int main(void) {
    printf("=== 逆波兰 / 后缀表达式计算器 ===\n\n");

    const char *expr1 = "5 3 + 8 2 - *"; // (5 + 3) * (8 - 2) = 8 * 6 = 48
    int result1;
    if (evaluate_postfix(expr1, &result1)) {
        printf("表达式: \"%s\"\n-> 计算结果: %d\n\n", expr1, result1);
    }

    const char *expr2 = "15 7 1 1 + - / 3 * 2 1 1 + + -"; // 5
    int result2;
    if (evaluate_postfix(expr2, &result2)) {
        printf("表达式: \"%s\"\n-> 计算结果: %d\n\n", expr2, result2);
    }

    return 0;
}

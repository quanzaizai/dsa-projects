#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define STACK_CAPACITY 64

/**
 * 💡【知识点】中缀表达式转后缀表达式 (Shunting-Yard 调度场算法)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 运算符优先级映射：`*`, `/` 优先级 (2) > `+`, `-` 优先级 (1)。
 *   2. 调度规则：
 *      - 遇到数字：直接追加输出到后缀表达式末尾。
 *      - 遇到左括号 `(`：直接压入运算符栈。
 *      - 遇到右括号 `)`：不断弹出栈顶运算符追加到输出，直至遇到 `(` 并将其弹出丢弃。
 *      - 遇到普通运算符：只要栈顶运算符的优先级 >= 当前运算符，就不断弹出栈顶追加到输出，最后将当前运算符压栈。
 *   3. 终验步骤：输入遍历结束后，将栈中残留的所有运算符依次弹出并追加到输出。
 * -----------------------------------------------------------------------------
 */

// 获取运算符优先级
static int get_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// ==================== 1. 核心转换算法 ====================

/**
 * @brief 将中缀表达式转换为后缀表达式
 * @param infix 输入中缀表达式（如 "a+b*(c-d)"）
 * @param postfix 输出后缀缓冲区
 */
void infix_to_postfix(const char *infix, char *postfix) {
    char op_stack[STACK_CAPACITY];
    int top = -1;
    int k = 0; // 输出索引

    int len = strlen(infix);
    for (int i = 0; i < len; i++) {
        char ch = infix[i];

        if (isspace(ch)) continue;

        // 1. 操作数（字母或数字）：直接输出
        if (isalnum(ch)) {
            postfix[k++] = ch;
            postfix[k++] = ' '; // 加空格分隔
        }
        // 2. 左括号：无条件压栈
        else if (ch == '(') {
            op_stack[++top] = ch;
        }
        // 3. 右括号：弹出直至遇到左括号
        else if (ch == ')') {
            while (top >= 0 && op_stack[top] != '(') {
                postfix[k++] = op_stack[top--];
                postfix[k++] = ' ';
            }
            if (top >= 0 && op_stack[top] == '(') {
                top--; // 弹出并丢弃 '('
            }
        }
        // 4. 普通四则运算符
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (top >= 0 && op_stack[top] != '(' &&
                   get_precedence(op_stack[top]) >= get_precedence(ch)) {
                postfix[k++] = op_stack[top--];
                postfix[k++] = ' ';
            }
            op_stack[++top] = ch; // 当前运算符压栈
        }
    }

    // 5. 将栈中残留运算符全部出栈
    while (top >= 0) {
        postfix[k++] = op_stack[top--];
        postfix[k++] = ' ';
    }

    if (k > 0 && postfix[k - 1] == ' ') k--; // 抹去末尾多余空格
    postfix[k] = '\0';
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    char postfix[128];

    const char *expr1 = "A + B * C";
    infix_to_postfix(expr1, postfix);
    printf("中缀: %-20s -> 后缀: %s\n", expr1, postfix);

    const char *expr2 = "(A + B) * (C - D)";
    infix_to_postfix(expr2, postfix);
    printf("中缀: %-20s -> 后缀: %s\n", expr2, postfix);

    const char *expr3 = "3 + 5 * (2 - 8)";
    infix_to_postfix(expr3, postfix);
    printf("中缀: %-20s -> 后缀: %s\n", expr3, postfix);

    return 0;
}

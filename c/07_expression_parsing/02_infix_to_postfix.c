// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持
#include <ctype.h>    // 字符分类与转换库：提供 isdigit(), isalpha(), isspace() 等字符类型判断函数
#include <string.h>   // 字符串与内存操作库：提供 strlen(), strcpy(), strcmp(), memset() 等内存/文本处理函数

#define STACK_CAPACITY 64

/**
 * =============================================================================
 * 💡【知识点】中缀表达式转后缀表达式 (Dijkstra's Shunting-Yard 调度场算法)
 * =============================================================================
 * 
 * 📌【1. 什么是调度场算法？】
 *   由图灵奖得主 Edsger Dijkstra 提出。就像火车站的编组站道岔调度车厢一样：
 *   - 数字车厢（操作数）：无需等待，直接开向输出轨道（追加到后缀表达式）。
 *   - 符号车厢（运算符）：进入侧线编组栈，根据优先级排队等候调度。
 * 
 * 📌【2. 优先级判定与调度规则】
 * 
 *   运算符优先级表:
 *     优先级 2 :  *  /  (乘除优先)
 *     优先级 1 :  +  -  (加减次之)
 *     优先级 0 :  (     (括号作为隔离边界)
 * 
 *   核心调度规则:
 *   ① 遇到数字：直接追加输出。
 *   ② 遇到左括号 '('：无条件压入符号栈。
 *   ③ 遇到右括号 ')'：不断弹出栈顶符号输出，直到遇到对应的 '(' 为止（括号本身被抛弃，不进入后缀表达式）。
 *   ④ 遇到普通运算符：只要「栈顶运算符优先级 >= 当前运算符优先级」，就不断弹出栈顶输出（先来且优先级高的先执行！），
 *      直到栈空或栈顶优先级更低，最后把当前运算符压栈。
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 遇到右括号时，为什么左括号 '(' 只弹出却不输出到后缀表达式中？
 *      👉 解答：后缀表达式的精髓就是「完全去除所有括号」，运算符的位置本身已经隐式且确定地决定了运算先后次序。
 * =============================================================================
 */

static int get_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// ==================== 1. 核心转换算法 ====================

/**
 * @brief 将中缀表达式转换为后缀表达式
 * 
 * @param infix   输入中缀表达式（如 "(A + B) * (C - D)"）
 * @param postfix 输出后缀表达式缓冲区
 * 
 * @note 时间复杂度: O(N) —— 单趟线性遍历
 * @note 空间复杂度: O(N) —— 运算符辅助栈
 */
void infix_to_postfix(const char *infix, char *postfix) {
    if (infix == NULL || postfix == NULL) return;

    char op_stack[STACK_CAPACITY];
    int top = -1;
    int k = 0; // 后缀缓冲区写入游标

    int len = (int)strlen(infix);
    for (int i = 0; i < len; i++) {
        char ch = infix[i];

        if (isspace(ch)) continue;

        // 【规则 1】操作数（字母或数字）：直接输出
        if (isalnum(ch)) {
            postfix[k++] = ch;
            postfix[k++] = ' '; // 加空格清晰分隔各 Token
        }
        // 【规则 2】左括号：无条件压入符号栈
        else if (ch == '(') {
            op_stack[++top] = ch;
        }
        // 【规则 3】右括号：弹出符号直到遇到左括号 '('
        else if (ch == ')') {
            while (top >= 0 && op_stack[top] != '(') {
                postfix[k++] = op_stack[top--];
                postfix[k++] = ' ';
            }
            if (top >= 0 && op_stack[top] == '(') {
                top--; // 将 '(' 弹出栈并丢弃，不输出
            }
        }
        // 【规则 4】普通四则运算符：比对优先级并调度
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // 只要栈顶运算符优先级更高或相等，栈顶就应该先出栈输出
            while (top >= 0 && op_stack[top] != '(' &&
                   get_precedence(op_stack[top]) >= get_precedence(ch)) {
                postfix[k++] = op_stack[top--];
                postfix[k++] = ' ';
            }
            // 当前运算符压栈
            op_stack[++top] = ch;
        }
    }

    // 【规则 5】扫描结束：将符号栈中残留的所有运算符全部弹出输出
    while (top >= 0) {
        postfix[k++] = op_stack[top--];
        postfix[k++] = ' ';
    }

    if (k > 0 && postfix[k - 1] == ' ') k--; // 抹去末尾多余空格
    postfix[k] = '\0'; // 规范字符串结尾符
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    char postfix[128];

    printf("==================== 调度场算法 (中缀转后缀) 验证 ====================\n\n");

    const char *expr1 = "A + B * C";
    infix_to_postfix(expr1, postfix);
    printf("中缀: %-25s -> 后缀: %s\n", expr1, postfix);

    const char *expr2 = "(A + B) * (C - D)";
    infix_to_postfix(expr2, postfix);
    printf("中缀: %-25s -> 后缀: %s\n", expr2, postfix);

    const char *expr3 = "3 + 5 * (2 - 8)";
    infix_to_postfix(expr3, postfix);
    printf("中缀: %-25s -> 后缀: %s\n", expr3, postfix);

    return 0;
}

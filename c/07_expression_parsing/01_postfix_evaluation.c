#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define STACK_CAPACITY 64

/**
 * =============================================================================
 * 💡【知识点】栈经典实战 —— 逆波兰表达式 / 后缀表达式求值 (Postfix Evaluation)
 * =============================================================================
 * 
 * 📌【1. 什么是逆波兰 / 后缀表达式？】
 *   - 中缀表达式 (如 `(5 + 3) * 2`)：运算符在中间，严重依赖括号和优先级规则，人类易读但计算机极难解析。
 *   - 后缀表达式 (如 `5 3 + 2 *`)：运算符紧跟在操作数后面，**完全不需要任何括号**即可无歧义地表达运算顺序！
 * 
 * 📌【2. 算法核心执行流程与操作数左右顺序图解】
 * 
 *   遇到运算符时，连续弹出两个数字：
 *   
 *         |          |
 *         |    b     |  <--- ⚠️【第 1 个弹出的为「右操作数」b】
 *         +----------+
 *         |    a     |  <--- ⚠️【第 2 个弹出的为「左操作数」a】
 *         +----------+
 *           [数值栈]
 *           
 *   执行计算: 【 a  op  b 】（对于减法 a - b 和除法 a / b，顺序一旦搞反结果全错！）
 *   计算完毕后，将结果 res 重新压入栈顶。
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么先出栈的是右操作数？
 *      👉 解答：以 `8 2 -` 为例，8 先入栈，2 后入栈（2 位于 8 的上方）。出栈时 2 先出来，
 *         因此先出栈的是减号右边的减数 (b=2)，后出栈的是被减数 (a=8)，实际执行 `8 - 2 = 6`。
 * 
 *   ❓ Q2: 为什么后缀表达式是编译原理中堆栈虚拟机的基石？
 *      👉 解答：Java JVM 字节码（如 `iadd`, `imul`）和 Python 字节码的底层计算引擎，
 *         本质上都是基于后缀表达式的栈式计算模型。
 * =============================================================================
 */

// ==================== 1. 整型计算辅助栈 ====================

typedef struct NumStack {
    int items[STACK_CAPACITY];
    int top;
} NumStack;

static void num_stack_init(NumStack *s) { 
    s->top = -1; 
}

static bool num_stack_is_empty(const NumStack *s) { 
    return s->top == -1; 
}

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
 * 
 * @param expr       字符串（如 "5 3 + 8 2 - *"）
 * @param out_result 存储计算最终结果的传出指针
 * @return true 运算成功, false 表达式非法或除以零
 * 
 * @note 时间复杂度: O(N) —— 线性扫描表达式一次
 * @note 空间复杂度: O(N) —— 辅助数值栈深度与操作数数量成正比
 */
bool evaluate_postfix(const char *expr, int *out_result) {
    if (expr == NULL || out_result == NULL) return false;

    NumStack stack;
    num_stack_init(&stack);

    int i = 0;
    while (expr[i] != '\0') {
        // 【步骤 1】跳过空白字符
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // 【步骤 2】解析多位整数并压栈
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            num_stack_push(&stack, num);
        }
        // 【步骤 3】解析四则运算符并执行双操作数出栈计算
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            char op = expr[i];
            int b, a; 

            // ⚠️ 关键细节：先弹出的是右操作数 b，后弹出的是左操作数 a
            if (!num_stack_pop(&stack, &b) || !num_stack_pop(&stack, &a)) {
                printf("⚠️ [求值错误] 缺少足够的双操作数！\n");
                return false;
            }

            int res = 0;
            switch (op) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("⚠️ [除零错误] 除数不能为 0！\n");
                        return false;
                    }
                    res = a / b; 
                    break;
            }

            // 计算结果重新入栈供后续运算消费
            num_stack_push(&stack, res);
            i++;
        } else {
            i++; // 忽略其他未知字符
        }
    }

    // 【步骤 4】最终栈内应只残留唯一的最终结果
    return num_stack_pop(&stack, out_result);
}

// ==================== 3. 测试与验证入口 ====================

int main(void) {
    printf("==================== 逆波兰 / 后缀表达式计算器 ====================\n\n");

    // 测试 1: (5 + 3) * (8 - 2) = 8 * 6 = 48
    const char *expr1 = "5 3 + 8 2 - *";
    int result1;
    if (evaluate_postfix(expr1, &result1)) {
        printf("表达式: \"%-25s\" -> 计算结果: %d\n", expr1, result1);
    }

    // 测试 2: 复杂嵌套表达式
    const char *expr2 = "15 7 1 1 + - / 3 * 2 1 1 + + -";
    int result2;
    if (evaluate_postfix(expr2, &result2)) {
        printf("表达式: \"%-25s\" -> 计算结果: %d\n", expr2, result2);
    }

    return 0;
}

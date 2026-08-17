#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STACK_CAPACITY 128

/**
 * 💡【知识点】栈实战经典算法 —— 有效括号匹配 (Valid Parentheses / LeetCode 20)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 匹配原理：
 *      - 扫描字符串，遇到左括号 ('(', '[', '{') 时，将其压入栈中。
 *      - 遇到右括号 (')', ']', '}') 时：
 *        ① 若当前栈为空，说明右括号多余，直接判定**不匹配**。
 *        ② 若栈非空，弹出栈顶左括号，检查是否与当前右括号成对匹配。若不成对，判定**不匹配**。
 *      - 扫描结束后，若栈为空，说明所有括号完全配对；若栈仍有残留左括号，判定**不匹配**。
 *   2. 时空复杂度：时间复杂度 O(N)（线性扫描字符串一次），空间复杂度 O(N)（最坏情况下栈深达 N）。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 字符专用辅助栈 ====================

typedef struct CharStack {
    char items[STACK_CAPACITY];
    int top;
} CharStack;

static void char_stack_init(CharStack *s) { s->top = -1; }
static bool char_stack_is_empty(const CharStack *s) { return s->top == -1; }

static bool char_stack_push(CharStack *s, char c) {
    if (s->top >= STACK_CAPACITY - 1) return false;
    s->items[++(s->top)] = c;
    return true;
}

static bool char_stack_pop(CharStack *s, char *out_c) {
    if (char_stack_is_empty(s)) return false;
    if (out_c) *out_c = s->items[(s->top)--];
    return true;
}

// 辅助函数：判断两字符是否成对匹配
static bool is_pair(char left, char right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}

// ==================== 2. 核心括号匹配算法 ====================

/**
 * @brief 校验括号字符串是否有效
 * @param s 输入字符串（包含各类括号）
 * @return true 匹配有效, false 无效
 */
bool is_valid_parentheses(const char *str) {
    if (str == NULL) return true;

    CharStack stack;
    char_stack_init(&stack);

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        char ch = str[i];

        // 1. 遇到左括号，入栈
        if (ch == '(' || ch == '[' || ch == '{') {
            char_stack_push(&stack, ch);
        }
        // 2. 遇到右括号，弹出栈顶比对
        else if (ch == ')' || ch == ']' || ch == '}') {
            char top_char;
            // ⚠️ 栈为空却遇到了右括号，说明没有左括号与之对应
            if (!char_stack_pop(&stack, &top_char)) {
                return false;
            }
            // 检查成对性
            if (!is_pair(top_char, ch)) {
                return false;
            }
        }
        // 非括号字符忽略跳过
    }

    // 🔍【最终检查】：所有字符扫描完毕后，栈必须刚好为空才算完美匹配
    return char_stack_is_empty(&stack);
}

// ==================== 3. 测试与验证入口 ====================

void test_case(const char *expr) {
    bool valid = is_valid_parentheses(expr);
    printf("表达式: %-20s -> 验证结果: %s\n", 
           expr, 
           valid ? "✅ 有效匹配 (Valid)" : "❌ 格式非法 (Invalid)");
}

int main(void) {
    printf("=== 有效括号匹配算法验证 (LeetCode 20) ===\n\n");

    // 正确用例测试
    test_case("()");
    test_case("()[]{}");
    test_case("{[()]}");
    test_case("int main() { int a[5]; }");

    printf("\n----------------------------------------\n\n");

    // 错误用例测试
    test_case("(]");          // 类型不匹配
    test_case("([)]");        // 交叉闭合错误
    test_case("(((");         // 缺少闭合右括号
    test_case("]");           // 单独右括号开头
    test_case("{[()]}}");     // 右括号多余

    return 0;
}

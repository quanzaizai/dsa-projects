#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STACK_CAPACITY 128

/**
 * =============================================================================
 * 💡【知识点】栈经典应用 —— 有效括号匹配 (Valid Parentheses / LeetCode 20)
 * =============================================================================
 * 
 * 📌【1. 为什么用「栈」解决括号匹配？】
 *   括号的嵌套具有天然的「后出现先闭合」特性：
 *   - 最内层的左括号必须最先找到对应的右括号闭合。
 *   - 这种“最后进入、最先配对”的逻辑与「栈 (LIFO)」的机制完美契合！
 * 
 * 📌【2. 算法匹配流程图解】
 * 
 *   以字符串 "{ [ ( ) ] }" 为例：
 *   
 *   扫描到 '{' -> 入栈: [ '{' ]
 *   扫描到 '[' -> 入栈: [ '{', '[' ]
 *   扫描到 '(' -> 入栈: [ '{', '[', '(' ]
 *   扫描到 ')' -> 弹出栈顶 '(', 与 ')' 成功配对！剩余: [ '{', '[' ]
 *   扫描到 ']' -> 弹出栈顶 '[', 与 ']' 成功配对！剩余: [ '{' ]
 *   扫描到 '}' -> 弹出栈顶 '{', 与 '}' 成功配对！剩余: [ 空 ]
 *   遍历结束 -> 栈恰好为空 -> 判定为【✅ 有效合法】
 * 
 * 📌【3. 三种经典非法情况分析 (Q&A)】
 * 
 *   ❓ 情况 1（类型不匹配）: 如 "(]"
 *      👉 扫描到 ']' 时，弹出栈顶 '('，发现两者的括号类型不属于同一门派 -> 立即判错！
 *      
 *   ❓ 情况 2（右括号多余）: 如 "())"
 *      👉 扫描到第 2 个 ')' 时，栈已经空了，无法弹出任何左括号与之配对 -> 立即判错！
 *      
 *   ❓ 情况 3（左括号多余）: 如 "(()"
 *      👉 全部字符扫描结束，栈中依然残留有多余的 '(' 未被闭合 -> 最终判错！
 * =============================================================================
 */

// ==================== 1. 字符专用辅助栈 ====================

typedef struct CharStack {
    char items[STACK_CAPACITY];
    int top;
} CharStack;

static void char_stack_init(CharStack *s) { 
    s->top = -1; 
}

static bool char_stack_is_empty(const CharStack *s) { 
    return s->top == -1; 
}

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

/**
 * @brief 辅助判断左右两个括号是否成对匹配
 */
static bool is_pair(char left, char right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}

// ==================== 2. 核心括号匹配算法 ====================

/**
 * @brief 校验输入的字符串中的括号是否完全成对有效
 * 
 * @param str 待校验的表达式字符串
 * @return true 括号完全合法匹配, false 格式非法
 * 
 * @note 时间复杂度: O(N) —— 线性遍历字符串一次
 * @note 空间复杂度: O(N) —— 最坏情况下所有字符均为左括号入栈
 */
bool is_valid_parentheses(const char *str) {
    if (str == NULL) return true;

    CharStack stack;
    char_stack_init(&stack);

    int len = (int)strlen(str);
    for (int i = 0; i < len; i++) {
        char ch = str[i];

        // 【分支 1】遇到左括号：压入栈中等待未来的右括号来消解
        if (ch == '(' || ch == '[' || ch == '{') {
            char_stack_push(&stack, ch);
        }
        // 【分支 2】遇到右括号：必须有最近的左括号与之配对
        else if (ch == ')' || ch == ']' || ch == '}') {
            char top_char;
            // ⚠️ 检查 A：栈为空却来了右括号（右括号多余）
            if (!char_stack_pop(&stack, &top_char)) {
                return false;
            }
            // ⚠️ 检查 B：类型不匹配（如 '(' 遇到了 ']'）
            if (!is_pair(top_char, ch)) {
                return false;
            }
        }
        // 其他非括号字符（如数字、空格）直接忽略
    }

    // 【最终检查】扫描结束后，栈必须刚好为空（若非空说明左括号多余）
    return char_stack_is_empty(&stack);
}

// ==================== 3. 测试与验证入口 ====================

void test_case(const char *expr) {
    bool valid = is_valid_parentheses(expr);
    printf("表达式: %-30s -> 判定: %s\n", 
           expr, 
           valid ? "✅ 合法 (Valid)" : "❌ 非法 (Invalid)");
}

int main(void) {
    printf("==================== 括号匹配状态机验证 (LeetCode 20) ====================\n\n");

    printf("--- 1. 正确用例测试 ---\n");
    test_case("()");
    test_case("()[]{}");
    test_case("{[()]}");
    test_case("int main() { int a[5]; }");

    printf("\n--- 2. 经典错误用例测试 ---\n");
    test_case("(]");          // 类型不匹配
    test_case("([)]");        // 交叉闭合错误
    test_case("(((");         // 缺少闭合右括号 (栈残留)
    test_case("]");           // 单独右括号 (栈空下溢)
    test_case("{[()]}}");     // 右括号多余

    return 0;
}

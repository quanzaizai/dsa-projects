#include <stdio.h>
#include <stdlib.h>

/**
 * =============================================================================
 * 💡【知识点】循环链表经典算法 —— 约瑟夫环仿真 (Josephus Problem)
 * =============================================================================
 * 
 * 📌【1. 经典问题背景】
 *   - 场景：有 N 个人编号 1 ~ N 围坐成一圈。
 *   - 规则：从第 1 个人开始报数，数到第 M 的人被淘汰出局；
 *           由淘汰者的下一位重新从 1 开始报数，如此反复循环；
 *           求最后幸存者的编号。
 * 
 * 📌【2. 算法模拟过程图解 (以 N=7, M=3 为例)】
 * 
 *   初始环:  (1) -> (2) -> (3) -> (4) -> (5) -> (6) -> (7) --+
 *             ^                                               |
 *             +-----------------------------------------------+
 *   
 *   第一轮报数 (M=3):
 *     1报1, 2报2, 3报3 (3号淘汰！)
 *     解绑并 free 节点 3: (2)->next = (4)
 *     下一人 4 号重新从 1 报数...
 *     
 *   终止条件: 循环链表中只剩下 1 个节点时，即 `curr->next == curr`。
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么要移动 `m-1` 步？
 *      👉 解答：在单链表中要删除第 M 个节点，必须让游标指针停留在第 `M-1` 个节点（即待删节点的前驱节点）上，
 *         这样才能执行 `curr->next = curr->next->next` 跨过待淘汰人员并完成 `free`。
 * 
 *   ❓ Q2: 模拟法 vs 数学递推公式解法？
 *      👉 对比：
 *         - 循环链表模拟法：直观真实，时空复杂度 O(N * M)，能清晰打印每一轮出圈顺序。
 *         - 数学公式法：$f(N) = (f(N-1) + M) \pmod N$，时间复杂度 O(N)，适合直接计算最终结果。
 * =============================================================================
 */

// ==================== 1. 约瑟夫环模拟算法 ====================

typedef struct Node {
    int id;             // 人员编号 (1 ~ n)
    struct Node *next;  // 顺时针指向下一个人
} Node;

/**
 * @brief 使用单向循环链表模拟约瑟夫环淘汰全过程
 * 
 * @param n 总人数
 * @param m 淘汰报数阈值
 * @return int 最终幸存者的编号
 * 
 * @note 时间复杂度: O(N * M)
 * @note 空间复杂度: O(N) —— 在堆上构建 N 个节点的环形链表
 */
int josephus_simulation(int n, int m) {
    if (n <= 0 || m <= 0) return -1;
    if (n == 1) return 1;

    // 【步骤 1】在堆上构建包含 1 ~ N 的单向循环链表
    Node *head = (Node *)malloc(sizeof(Node));
    head->id = 1;
    head->next = NULL;

    Node *prev = head;
    for (int i = 2; i <= n; i++) {
        Node *curr = (Node *)malloc(sizeof(Node));
        curr->id = i;
        curr->next = NULL;
        prev->next = curr;
        prev = curr;
    }
    prev->next = head; // 首尾相接完成闭环！

    // 【步骤 2】模拟逐轮报数与淘汰过程
    Node *curr = head;
    int round = 1;

    // 只要链表中不止 1 个人（当只剩 1 个人时，它的 next 指向自己 `curr->next == curr`）
    while (curr->next != curr) {
        // 让 curr 停在待淘汰节点的前一个节点（移动 m-2 步）
        for (int count = 1; count < m - 1; count++) {
            curr = curr->next;
        }

        // 待淘汰的目标节点是 curr 的下一个
        Node *eliminated = curr->next;
        printf("第 %2d 轮: 淘汰编号 [%d] 号人员\n", round++, eliminated->id);

        // 指针跨过淘汰节点
        curr->next = eliminated->next;

        // 释放出局人员的节点内存
        free(eliminated);

        // 指针后移，下一个人重新从 1 开始报数
        curr = curr->next;
    }

    // 【步骤 3】获取最后唯一幸存者编号
    int winner = curr->id;

    // 释放最后一个幸存者节点，确保完全无内存泄漏
    free(curr);

    return winner;
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    int n = 7, m = 3;

    printf("==================== 约瑟夫环仿真模拟 (N=%d, M=%d) ====================\n", n, m);
    int survivor = josephus_simulation(n, m);
    printf("\n🏆 最终幸存者的编号为: [%d]\n", survivor);

    return 0;
}

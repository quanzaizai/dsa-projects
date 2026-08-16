#include <stdio.h>
#include <stdlib.h> // 提供 malloc, free, NULL

/**
 * 💡【知识点】循环链表经典算法实战 —— 约瑟夫环问题 (Josephus Problem)
 * -----------------------------------------------------------------------------
 * 📌【问题背景与数学模型】
 *   罗马历史学家约瑟夫斯记载的著名生存博弈问题：
 *   • 规则：设有 n 个人围坐成一个圆圈（编号依次为 1 到 n），从编号 1 的人开始按顺时针方向报数。
 *          每数到第 m 个人时，该人立即被淘汰出圈；接着从他的下一个人重新从 1 开始报数。
 *          如此反复循环，直至圈中只剩下最后 1 位幸存者。
 * 
 * 📌【为什么循环链表是约瑟夫环的“天选数据结构”？】
 *   • 数组解法的痛点：每次淘汰一人都需要做繁琐的下标取模 (`index % remaining`) 并将后续元素向前平移搬移（O(N) 搬移成本）。
 *   • 循环链表降维解法：首尾天生相连，指针沿着 next 自然打转；淘汰一人仅需修改前驱指针（O(1) 解绑），完全符合物理现实！
 * 
 * 📌【架构与模块分工】
 *   1. Node (结构体)        : 循环链表节点（存储每个人的编号 ID）。
 *   2. createJosephusRing() : 初始化包含 1 ~ n 个人的单向循环链表。
 *   3. solveJosephus()      : 核心模拟引擎 —— 报数、出圈打印、解绑释放、判定最后幸存者。
 *   4. main()               : 驱动入口 —— 验证经典样例 (n=7, m=3) 与其他参数。
 * -----------------------------------------------------------------------------
 */

// ==================== 1. 数据结构定义 ====================

typedef struct Node {
    int id;                 // 玩家/人员编号 (1 ~ n)
    struct Node* next;      // 指向下一位玩家
} Node;

// ==================== 2. 约瑟夫环核心算法实现 ====================

/**
 * @brief 构建包含 1 到 n 编号的单向循环链表
 * @param n 总人数
 * @return Node* 返回编号为 1 的头节点指针
 */
Node* createJosephusRing(int n) {
    if (n <= 0) return NULL;

    // 步骤 1：创建第 1 个人并自环
    Node* head = (Node*)malloc(sizeof(Node));
    if (!head) return NULL;
    head->id = 1;
    head->next = head;

    // 步骤 2：依次追加第 2 到 n 个人
    Node* tail = head;
    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) break;
        newNode->id = i;
        
        newNode->next = head; // 新节点指回表头
        tail->next = newNode; // 原尾部指向新节点
        tail = newNode;       // tail 移动到最新末尾
    }

    return head;
}

/**
 * @brief 模拟约瑟夫环报数与淘汰全过程
 * @param n 总人数
 * @param m 淘汰报数阈值（数到 m 出圈）
 * 
 * 🔍【核心指针移动与淘汰解绑机制】：
 *   ① 维护双指针：
 *      - `cur`  : 当前正在报数的人（初始为 head）。
 *      - `prev` : `cur` 的前驱节点（初始需定位在整个环的尾节点）。
 *   ② 报数前进：每轮只需向前移动 (m - 1) 步，`cur` 正好停在要被淘汰的人身上。
 *   ③ 淘汰解绑：
 *      - prev->next = cur->next; （前驱跳过 cur，直接连向下一位）
 *      - free(cur);              （释放被淘汰人员内存）
 *      - cur = prev->next;       （从下一位重新开始报数）
 *   ④ 终止条件：`cur->next == cur`（环中仅剩 1 个自环节点，即为最终幸存者！）。
 */
void solveJosephus(int n, int m) {
    if (n <= 0 || m <= 0) {
        printf("【参数错误】总人数与报数值必须为正整数！\n");
        return;
    }

    // 步骤 1：构建 1~n 环形链表
    Node* head = createJosephusRing(n);
    if (!head) return;

    // 步骤 2：将 prev 指针唯一定位到尾节点
    Node* prev = head;
    while (prev->next != head) {
        prev = prev->next;
    }

    Node* cur = head;
    printf("===== 约瑟夫环模拟 (总人数 n=%d, 报数淘汰 m=%d) =====\n", n, m);
    printf("淘汰顺序流水线: ");

    int round = 1;
    // 只要还没有只剩 1 个人 (cur->next != cur)，就持续循环
    while (cur->next != cur) {
        // 报数前进 m-1 次
        for (int count = 1; count < m; count++) {
            prev = cur;
            cur = cur->next;
        }

        // 此时 cur 即为数到 m 的被淘汰者
        printf("[第%d轮: %d号] -> ", round++, cur->id);

        // 核心解绑：将 cur 踢出循环链表
        prev->next = cur->next;
        free(cur);

        // 从下一位幸存者继续开始下一轮报数
        cur = prev->next;
    }

    // 输出唯一留存的胜利者
    printf("\n🏆【最终唯一幸存者】: 编号 %d 号！\n\n", cur->id);

    // 释放最后一个幸存者节点
    free(cur);
}

// ==================== 3. 测试驱动入口 ====================

int main(void) {
    // 案例 1：菜鸟教程经典样例 (7 个人，数到 3 淘汰)
    // 淘汰顺序: 3 -> 6 -> 2 -> 7 -> 5 -> 1，最终幸存者为 4 号
    solveJosephus(7, 3);

    // 案例 2：经典小规模博弈 (5 个人，数到 2 淘汰)
    // 淘汰顺序: 2 -> 4 -> 1 -> 5，最终幸存者为 3 号
    solveJosephus(5, 2);

    return 0;
}

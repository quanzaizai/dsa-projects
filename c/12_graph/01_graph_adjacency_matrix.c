// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

#define MAX_VERTICES 5 // 最大顶点数量

/**
 * =============================================================================
 * 💡【知识点】图的表示与遍历 —— 邻接矩阵 (Adjacency Matrix) 与 BFS / DFS
 * =============================================================================
 * 
 * 📌【1. 什么是邻接矩阵？】
 *   邻接矩阵是一个二维数组 `matrix[u][v]`：
 *   - 若顶点 u 与顶点 v 之间有直接边相连，则 `matrix[u][v] = 1`（带权图中存权值）。
 *   - 若无边相连，则为 0（或无穷大 INF）。
 *   - 无向图的邻接矩阵沿主对角线完全对称 (`matrix[u][v] == matrix[v][u]`)。
 * 
 * 📌【2. 图的两种核心遍历机制图解】
 * 
 *   测试图结构:
 *          [0]
 *         /   \
 *       [1]   [2]
 *       /       \
 *     [3]       [4]
 * 
 *   ① 深度优先遍历 (DFS - 递归回溯 / 类似于二叉树的前序遍历)：
 *      - 策略：不撞南墙不回头。沿着一条路径一直探索到底，遇到死胡同或已访问节点时才回溯。
 *      - 路径：0 -> 1 -> 3 -> 回溯到 0 -> 2 -> 4
 *      
 *   ② 广度优先遍历 (BFS - 队列层序 / 水波辐射扩散)：
 *      - 策略：先访问起点，再访问起点的所有直接邻居，最后访问邻居的邻居。
 *      - 路径：0 -> 1, 2 (第一层) -> 3, 4 (第二层)
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么图的遍历必须维护一个 `visited` 布尔数组？
 *      👉 解答：树是不存在环的无向无环连通图，而**图允许存在环路**！
 *         如果没有 `visited` 数组记录每个顶点是否已被访问过，遍历过程就会在环路中无限打转，导致死循环或栈溢出崩溃。
 * =============================================================================
 */

typedef struct Graph {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} Graph;

void graph_init(Graph *g, int n) {
    g->num_vertices = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

/**
 * @brief 添加一条无向边 (双向连通)
 */
void add_edge(Graph *g, int u, int v) {
    if (u >= 0 && u < g->num_vertices && v >= 0 && v < g->num_vertices) {
        g->matrix[u][v] = 1;
        g->matrix[v][u] = 1; // 无向图对称置 1
    }
}

/**
 * @brief 深度优先遍历 (DFS) —— 递归回溯实现
 * @note 时间复杂度: O(V^2) (邻接矩阵遍历所有出边) | 空间复杂度: O(V)
 */
void dfs(const Graph *g, int vertex, bool visited[]) {
    // 【步骤 1】标记当前顶点已被访问
    visited[vertex] = true;
    printf("[%d] ", vertex);

    // 【步骤 2】顺次检查所有相连的邻接顶点
    for (int i = 0; i < g->num_vertices; i++) {
        // 若有边相连且未被访问过，递归深入探索
        if (g->matrix[vertex][i] == 1 && !visited[i]) {
            dfs(g, i, visited);
        }
    }
}

/**
 * @brief 广度优先遍历 (BFS) —— 辅助队列层序扩展实现
 * @note 时间复杂度: O(V^2) | 空间复杂度: O(V)
 */
void bfs(const Graph *g, int start) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // 【步骤 1】起点入队并标记已访问
    visited[start] = true;
    queue[rear++] = start;

    // 【步骤 2】队列不为空时循环扩散
    while (front < rear) {
        int u = queue[front++]; // 队头出队
        printf("[%d] ", u);

        // 将 u 的所有未访问邻居全部入队
        for (int v = 0; v < g->num_vertices; v++) {
            if (g->matrix[u][v] == 1 && !visited[v]) {
                visited[v] = true; // ⚠️ 入队时立刻标记 visited，防止重复入队！
                queue[rear++] = v;
            }
        }
    }
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    Graph g;
    graph_init(&g, 5);

    // 构建测试连通图
    add_edge(&g, 0, 1);
    add_edge(&g, 0, 2);
    add_edge(&g, 1, 3);
    add_edge(&g, 2, 4);

    printf("==================== 图的遍历算法验证 (邻接矩阵) ====================\n\n");

    printf("▶️ 深度优先遍历 (DFS, 从 0 出发): ");
    bool visited[MAX_VERTICES] = {false};
    dfs(&g, 0, visited);
    printf("\n");

    printf("🌊 广度优先遍历 (BFS, 从 0 出发): ");
    bfs(&g, 0);
    printf("\n");

    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 5          // 图的顶点总数
#define INF INT_MAX  // 定义无穷大距离

/**
 * =============================================================================
 * 💡【知识点】单源最短路径 —— 迪杰斯特拉算法 (Dijkstra's Algorithm)
 * =============================================================================
 * 
 * 📌【1. 迪杰斯特拉算法的核心思想】
 *   - 目标：计算从指定「源点 (Source)」到图中「所有其他顶点」的最短距离。
 *   - 策略：**贪心选择 + 动态松弛 (Greedy + Relaxation)**。
 *     ① 维护一个集合 S，记录已经确定最短路径的顶点。
 *     ② 每次从尚未确定的顶点中，贪心挑选一个「当前到源点距离最短」的顶点 u 加入 S。
 *     ③ 以 u 为中转站，尝试刷新所有从 u 出发能够到达的邻居 v 的最短距离（松弛操作）。
 * 
 * 📌【2. 核心松弛操作 (Relaxation) 图解】
 * 
 *           [ 源点 src ]
 *             /      \
 *     dist[u]/        \ dist[v] (原记录距离)
 *           v          v
 *         [ u ] =====> [ v ]
 *               weight
 *               
 *   👉 核心判定条件：
 *      `if (dist[u] + weight(u, v) < dist[v]) { dist[v] = dist[u] + weight(u, v); }`
 *      （意为：经过中转站 u 绕过去，比原先直达或已知的路径更近！）
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么 Dijkstra 算法绝对不能处理「含有负权边」的图？
 *      👉 解答：Dijkstra 算法基于贪心原则——它假设“当前选出的距离最短点 u，其最短距离已经板上钉钉，未来不可能变得更短”。
 *         如果存在负权边，未来可能会通过绕经一条负权边让经过 u 的总距离进一步变小，导致贪心假设彻底崩塌！
 *         （含有负权边的图必须使用 Bellman-Ford 算法或 SPFA 算法）。
 * =============================================================================
 */

// 辅助函数：在尚未确定最短路径的顶点中，寻找 dist 最小的顶点下标
static int min_distance(const int dist[], const bool visited[]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

/**
 * @brief 执行单源最短路径计算
 * 
 * @param graph 带权有向/无向图的邻接矩阵表示
 * @param src   起始源点编号
 * 
 * @note 时间复杂度: O(V^2) (邻接矩阵版) | 空间复杂度: O(V)
 */
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // 记录源点到各顶点的最短估计距离
    bool visited[V];   // 记录顶点是否已被确定最短路径

    // 【步骤 1】初始化距离数组（除源点自身距离为 0 外，其余全设为无穷大 INF）
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[src] = 0;

    // 【步骤 2】主循环：迭代 V-1 次，逐个确定所有顶点的最短路径
    for (int count = 0; count < V - 1; count++) {
        // 贪心挑选当前距离最小的未锁定顶点 u
        int u = min_distance(dist, visited);
        if (u == -1) break; // 剩余未访问顶点均不可达

        visited[u] = true; // 锁定顶点 u 的最短距离！

        // 【步骤 3】以 u 为跳板，对 u 的所有未访问邻居 v 执行松弛操作
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INF) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v]; // 成功松弛，刷新更短路径！
                }
            }
        }
    }

    // 【步骤 3】格式化输出结果
    printf("=== 从源点 [%d] 出发到达各顶点的最短路径 ===\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            printf("目标顶点 [%d]: ❌ 不可达 (INF)\n", i);
        } else {
            printf("目标顶点 [%d]: 最短距离 = %2d\n", i, dist[i]);
        }
    }
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    // 构建 5 个顶点的带权图
    int graph[V][V] = {
        {0, 10,  3,  0,  0},
        {0,  0,  1,  2,  0},
        {0,  4,  0,  8,  2},
        {0,  0,  0,  0,  7},
        {0,  0,  0,  9,  0}
    };

    printf("==================== 迪杰斯特拉 (Dijkstra) 算法验证 ====================\n\n");
    dijkstra(graph, 0);

    return 0;
}

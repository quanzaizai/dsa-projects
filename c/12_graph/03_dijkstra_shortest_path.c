#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 5
#define INF INT_MAX

/**
 * 💡【知识点】单源最短路径 —— 迪杰斯特拉算法 (Dijkstra Algorithm)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 贪心策略：维护已确定最短距离的点集 S。每次从尚未确定的点中挑选距离源点最近的点 u，
 *      以 u 为中继点对所有相连的邻居节点 v 执行**松弛操作 (Relaxation)**：
 *      `if (dist[u] + weight < dist[v]) dist[v] = dist[u] + weight;`
 *   2. 时空复杂度：邻接矩阵版时间复杂度为 $O(V^2)$。
 * -----------------------------------------------------------------------------
 */

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

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = min_distance(dist, visited);
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v]; // 🔍 松弛操作
            }
        }
    }

    printf("=== 从源点 %d 出发的最短距离 ===\n", src);
    for (int i = 0; i < V; i++) {
        printf("目标顶点 %d: 最短路径 = %d\n", i, dist[i]);
    }
}

int main(void) {
    int graph[V][V] = {
        {0, 10,  3,  0,  0},
        {0,  0,  1,  2,  0},
        {0,  4,  0,  8,  2},
        {0,  0,  0,  0,  7},
        {0,  0,  0,  9,  0}
    };
    dijkstra(graph, 0);
    return 0;
}

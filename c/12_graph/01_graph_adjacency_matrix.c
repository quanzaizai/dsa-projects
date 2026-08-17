#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 5

/**
 * 💡【知识点】图的表示与遍历 —— 邻接矩阵 (Adjacency Matrix) 与 BFS / DFS
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 邻接矩阵：二维数组 `matrix[u][v] = 1` 表示顶点 u 与顶点 v 之间存在边。
 *   2. **深度优先遍历 (DFS)**：利用递归回溯，沿着一条路径探索到底，再回溯尝试其他分支。
 *   3. **广度优先遍历 (BFS)**：利用辅助队列，按层级向外辐射扩散遍历相连邻居。
 * -----------------------------------------------------------------------------
 */

typedef struct Graph {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} Graph;

void graph_init(Graph *g, int n) {
    g->num_vertices = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g->matrix[i][j] = 0;
}

void add_edge(Graph *g, int u, int v) {
    g->matrix[u][v] = 1;
    g->matrix[v][u] = 1; // 无向图双向连接
}

// 深度优先遍历 (DFS)
void dfs(const Graph *g, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < g->num_vertices; i++) {
        if (g->matrix[vertex][i] == 1 && !visited[i]) {
            dfs(g, i, visited);
        }
    }
}

// 广度优先遍历 (BFS)
void bfs(const Graph *g, int start) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        printf("%d ", u);

        for (int v = 0; v < g->num_vertices; v++) {
            if (g->matrix[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
        }
    }
}

int main(void) {
    Graph g;
    graph_init(&g, 5);

    add_edge(&g, 0, 1);
    add_edge(&g, 0, 2);
    add_edge(&g, 1, 3);
    add_edge(&g, 2, 4);

    printf("图的 DFS 遍历 (从 0 出发): ");
    bool visited[5] = {false};
    dfs(&g, 0, visited);
    printf("\n");

    printf("图的 BFS 遍历 (从 0 出发): ");
    bfs(&g, 0);
    printf("\n");

    return 0;
}

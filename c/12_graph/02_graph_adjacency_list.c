#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】图的链式表示 —— 邻接表 (Adjacency List)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 稀疏图优化：邻接矩阵空间为 $O(V^2)$。邻接表为每个顶点维护一个相连边的链表，空间仅需 $O(V + E)$。
 * -----------------------------------------------------------------------------
 */

typedef struct AdjNode {
    int dest;
    struct AdjNode *next;
} AdjNode;

typedef struct GraphList {
    int num_vertices;
    AdjNode **heads;
} GraphList;

GraphList* create_graph_list(int n) {
    GraphList *g = (GraphList *)malloc(sizeof(GraphList));
    g->num_vertices = n;
    g->heads = (AdjNode **)malloc(n * sizeof(AdjNode *));
    for (int i = 0; i < n; i++) g->heads[i] = NULL;
    return g;
}

void add_list_edge(GraphList *g, int src, int dest) {
    AdjNode *n = (AdjNode *)malloc(sizeof(AdjNode));
    n->dest = dest;
    n->next = g->heads[src];
    g->heads[src] = n;
}

void print_graph_list(const GraphList *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("顶点 %d: ", i);
        AdjNode *curr = g->heads[i];
        while (curr) {
            printf("-> %d ", curr->dest);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main(void) {
    GraphList *g = create_graph_list(4);
    add_list_edge(g, 0, 1);
    add_list_edge(g, 0, 2);
    add_list_edge(g, 1, 2);
    add_list_edge(g, 2, 3);

    printf("=== 邻接表结构 ===\n");
    print_graph_list(g);
    return 0;
}

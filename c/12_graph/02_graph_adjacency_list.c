#include <stdio.h>
#include <stdlib.h>

/**
 * =============================================================================
 * 💡【知识点】图的链式表示 —— 邻接表 (Adjacency List) 与稀疏图空间优化
 * =============================================================================
 * 
 * 📌【1. 什么是邻接表？】
 *   邻接表是「数组 + 单链表」的结合体：
 *   - 数组：长度为 V（顶点总数），每个槽位 `heads[i]` 代表顶点 i。
 *   - 单链表：挂在 `heads[i]` 下面的链表，记录了所有从顶点 i 可以直接到达的目标顶点。
 * 
 * 📌【2. 邻接表结构模型图解】
 * 
 *   [顶点数组]
 *   顶点 [0] ---> [dest: 2] ---> [dest: 1] ---> NULL  (0 连接了 1, 2)
 *   顶点 [1] ---> [dest: 2] ---> NULL                 (1 连接了 2)
 *   顶点 [2] ---> [dest: 3] ---> NULL                 (2 连接了 3)
 *   顶点 [3] ---> NULL                                (3 无出边)
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 邻接矩阵 vs 邻接表，该怎么选？
 *      👉 对比选型：
 *         - **稠密图 (Dense Graph，边数接近 $V^2$)**：选「邻接矩阵」，空间利用率高，判断任意两点是否有边直接 $O(1)$。
 *         - **稀疏图 (Sparse Graph，边数远小于 $V^2$)**：绝大多数实际工程网络（如社交好友、互联网网页链接）都是稀疏图。
 *           邻接矩阵会有海量 0 浪费空间 ($O(V^2)$)，而邻接表仅需 $O(V + E)$，极致节省内存！
 * =============================================================================
 */

// ==================== 1. 结构体与核心接口 ====================

typedef struct AdjNode {
    int dest;               // 目标顶点编号
    struct AdjNode *next;   // 指向下一条邻接边
} AdjNode;

typedef struct GraphList {
    int num_vertices;       // 顶点总数 V
    AdjNode **heads;        // 指针数组：每个元素是指向邻接链表头部的指针
} GraphList;

/**
 * @brief 创建并初始化邻接表
 */
GraphList* create_graph_list(int n) {
    GraphList *g = (GraphList *)malloc(sizeof(GraphList));
    g->num_vertices = n;
    
    // 动态开辟包含 n 个链表头指针的数组
    g->heads = (AdjNode **)malloc((size_t)n * sizeof(AdjNode *));
    for (int i = 0; i < n; i++) {
        g->heads[i] = NULL;
    }
    return g;
}

/**
 * @brief 添加一条有向边 (src -> dest) —— 头插法 O(1)
 */
void add_list_edge(GraphList *g, int src, int dest) {
    if (g == NULL || src < 0 || src >= g->num_vertices || dest < 0 || dest >= g->num_vertices) {
        return;
    }

    // 创建新边节点
    AdjNode *n = (AdjNode *)malloc(sizeof(AdjNode));
    n->dest = dest;

    // 头插法挂载到 src 的链表头部
    n->next = g->heads[src];
    g->heads[src] = n;
}

/**
 * @brief 打印邻接表结构
 */
void print_graph_list(const GraphList *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("顶点 [%d] 的出边邻居: ", i);
        AdjNode *curr = g->heads[i];
        while (curr != NULL) {
            printf("-> [%d] ", curr->dest);
            curr = curr->next;
        }
        printf("-> NULL\n");
    }
}

/**
 * @brief 释放邻接表的所有动态内存
 */
void free_graph_list(GraphList *g) {
    if (g == NULL) return;
    for (int i = 0; i < g->num_vertices; i++) {
        AdjNode *curr = g->heads[i];
        while (curr != NULL) {
            AdjNode *next_node = curr->next;
            free(curr);
            curr = next_node;
        }
    }
    free(g->heads);
    free(g);
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    GraphList *g = create_graph_list(4);

    // 构建有向边关系
    add_list_edge(g, 0, 1);
    add_list_edge(g, 0, 2);
    add_list_edge(g, 1, 2);
    add_list_edge(g, 2, 3);

    printf("==================== 邻接表结构与稀疏图表达 ====================\n\n");
    print_graph_list(g);

    free_graph_list(g);
    g = NULL;

    return 0;
}

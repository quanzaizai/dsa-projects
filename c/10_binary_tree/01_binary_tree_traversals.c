#include <stdio.h>
#include <stdlib.h>

/**
 * 💡【知识点】二叉树体系 —— 构建与四大遍历方式 (Traversals)
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. 遍历递归模型：
 *      - **前序遍历 (Pre-order)**：根 -> 左 -> 右 (常用于树的复制与序列化)
 *      - **中序遍历 (In-order)**：左 -> 根 -> 右 (二叉搜索树中序遍历结果严格有序！)
 *      - **后序遍历 (Post-order)**：左 -> 右 -> 根 (常用于先释放孩子再释放根的内存回收)
 *   2. 时空复杂度：每种遍历访问每个节点恰好 1 次 -> 时间复杂度 $O(N)$，递归调用栈空间 $O(H)$ (H 为树高)。
 * -----------------------------------------------------------------------------
 */

// 二叉树节点
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* create_tree_node(int val) {
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

// 1. 前序遍历 (根 -> 左 -> 右)
void pre_order(const TreeNode *root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    pre_order(root->left);
    pre_order(root->right);
}

// 2. 中序遍历 (左 -> 根 -> 右)
void in_order(const TreeNode *root) {
    if (root == NULL) return;
    in_order(root->left);
    printf("%d ", root->val);
    in_order(root->right);
}

// 3. 后序遍历 (左 -> 右 -> 根)
void post_order(const TreeNode *root) {
    if (root == NULL) return;
    post_order(root->left);
    post_order(root->right);
    printf("%d ", root->val);
}

// 后序释放树内存闭环
void free_tree(TreeNode *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    /*
             1
           /   \
          2     3
         / \   /
        4   5 6
    */
    TreeNode *root = create_tree_node(1);
    root->left = create_tree_node(2);
    root->right = create_tree_node(3);
    root->left->left = create_tree_node(4);
    root->left->right = create_tree_node(5);
    root->right->left = create_tree_node(6);

    printf("前序遍历 (根->左->右): ");
    pre_order(root);
    printf("\n");

    printf("中序遍历 (左->根->右): ");
    in_order(root);
    printf("\n");

    printf("后序遍历 (左->右->根): ");
    post_order(root);
    printf("\n");

    free_tree(root);
    return 0;
}

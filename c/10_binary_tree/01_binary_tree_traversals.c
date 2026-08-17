// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdlib.h>   // 标准通用工具库：提供 malloc(), free(), exit(), NULL 等堆内存动态分配与释放支持

/**
 * =============================================================================
 * 💡【知识点】二叉树 (Binary Tree) —— 构建与三大深度优先遍历 (DFS)
 * =============================================================================
 * 
 * 📌【1. 二叉树的递归本质】
 *   二叉树由一个根节点以及两棵互不相交的「左子树」和「右子树」构成。
 *   - 无论树多大多深，任何子树本身也完全符合二叉树的定义（天然具备递归自相似性）。
 * 
 * 📌【2. 树形结构与三大遍历路径图解】
 * 
 *                 [1] (根)
 *               /     \
 *             [2]     [3]
 *            /   \    /
 *          [4]   [5] [6]
 * 
 *   ① 前序遍历 (Pre-order, 根->左->右)  : 1 -> 2 -> 4 -> 5 -> 3 -> 6
 *      - 特点：根节点总是最先被访问。常用于：树的复制、快速序列化存档。
 *      
 *   ② 中序遍历 (In-order,  左->根->右)  : 4 -> 2 -> 5 -> 1 -> 6 -> 3
 *      - 特点：根节点在左右子树中间。常用于：二叉搜索树（BST 中序遍历严格单调递增！）。
 *      
 *   ③ 后序遍历 (Post-order, 左->右->根) : 4 -> 5 -> 2 -> 6 -> 3 -> 1
 *      - 特点：根节点最后被访问。常用于：自底向上计算树高、释放整棵树的内存（先释放孩子再释放父亲！）。
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么释放树的内存必须用「后序遍历 (Post-order)」？
 *      👉 解答：如果用前序遍历，先 `free(root)` 释放了根节点，那么 `root->left` 和 `root->right` 指针
 *         就变成了野指针，子树节点的地址丢失，引发严重的内存泄漏！
 *         后序遍历先确保左右子树都完全安全释放完毕，最后再销毁根节点自身。
 * =============================================================================
 */

// ==================== 1. 结构体与核心接口 ====================

typedef struct TreeNode {
    int val;                 // 节点存储的数值
    struct TreeNode *left;   // 指向左孩子节点的指针
    struct TreeNode *right;  // 指向右孩子节点的指针
} TreeNode;

/**
 * @brief 在堆上动态创建二叉树节点
 */
TreeNode* create_tree_node(int val) {
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    if (!n) return NULL;
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

/**
 * @brief 1. 前序遍历 (Pre-order: 根 -> 左 -> 右)
 * @note 时间复杂度: O(N) | 空间复杂度: O(H) (H 为树的高度，即递归调用栈深度)
 */
void pre_order(const TreeNode *root) {
    if (root == NULL) return; // 递归基 (Base Case)
    
    printf("%d ", root->val); // 【1】访问根
    pre_order(root->left);    // 【2】递归遍历左子树
    pre_order(root->right);   // 【3】递归遍历右子树
}

/**
 * @brief 2. 中序遍历 (In-order: 左 -> 根 -> 右)
 * @note 时间复杂度: O(N) | 空间复杂度: O(H)
 */
void in_order(const TreeNode *root) {
    if (root == NULL) return;
    
    in_order(root->left);     // 【1】递归遍历左子树
    printf("%d ", root->val); // 【2】访问根
    in_order(root->right);    // 【3】递归遍历右子树
}

/**
 * @brief 3. 后序遍历 (Post-order: 左 -> 右 -> 根)
 * @note 时间复杂度: O(N) | 空间复杂度: O(H)
 */
void post_order(const TreeNode *root) {
    if (root == NULL) return;
    
    post_order(root->left);   // 【1】递归遍历左子树
    post_order(root->right);  // 【2】递归遍历右子树
    printf("%d ", root->val); // 【3】访问根
}

/**
 * @brief 递归安全释放整棵二叉树内存（后序遍历思想）
 */
void free_tree(TreeNode *root) {
    if (root == NULL) return;
    // 先递归释放左右子树
    free_tree(root->left);
    free_tree(root->right);
    // 最后释放根节点自身
    free(root);
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    printf("==================== 二叉树构建与三大遍历验证 ====================\n\n");

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

    // 内存安全闭环回收
    free_tree(root);
    root = NULL;
    printf("\n🧹 整棵二叉树已安全后序递归销毁\n");

    return 0;
}

// ==================== 0. 标准库头文件引入与作用解析 ====================
#include <stdio.h>    // 标准输入输出库：提供 printf(), puts() 等控制台格式化输出函数
#include <stdlib.h>   // 标准通用工具库：提供 malloc(), free(), exit(), NULL 等堆内存动态分配与释放支持
#include <stdbool.h>  // C99 标准布尔库：提供 bool, true, false 逻辑判定类型支持

/**
 * =============================================================================
 * 💡【知识点】二叉搜索树 (Binary Search Tree / BST) —— 增删查改与中序单调性
 * =============================================================================
 * 
 * 📌【1. 什么是二叉搜索树 (BST)？】
 *   BST 是一棵满足以下严格性质的二叉树：
 *   - 对于任意节点 X：
 *     - 若其左子树不为空，则**左子树上所有节点的值均严格小于** X 的值。
 *     - 若其右子树不为空，则**右子树上所有节点的值均严格大于** X 的值。
 *     - 左右子树本身也各自是一棵二叉搜索树。
 *   - 核心性质：**对 BST 进行「中序遍历」，输出序列必定是严格单调递增的！**
 * 
 * 📌【2. BST 节点删除的三大核心分支图解 (最难知识点)】
 * 
 *   分支 ①（叶子节点）：无任何子节点，直接 `free` 并返回 NULL。
 *   分支 ②（单孩子节点）：只有一个左孩子或右孩子，让唯一孩子直接“顶替”父节点位置。
 *   分支 ③（双孩子节点）：
 *          [30] (待删除)
 *         /    \
 *       [20]   [40]
 *             /    \
 *           [35]   [50]  (寻找右子树的最小值 -> 后继节点 In-order Successor [35])
 *           
 *       步骤：
 *       1. 找到右子树中最小的节点（35）。
 *       2. 用 35 覆盖原待删节点 30 的数值。
 *       3. 转而在右子树中递归删除那个已经被利用完的 35（退化为分支 ① 或 ②）。
 * 
 * 📌【3. 深度思考与高频 Q&A】
 * 
 *   ❓ Q1: 为什么删除双孩子节点要找「右子树的最小值」？
 *      👉 解答：右子树的最小值（即中序遍历中紧跟在其后的节点）比原节点大，但比右子树其他所有节点都小，
 *         把它提拔上来做新的根节点，可以完美维持 BST 的整体秩序！
 * =============================================================================
 */

// ==================== 1. BST 核心算法实现 ====================

typedef struct BSTNode {
    int val;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/**
 * @brief 向 BST 中递归插入新节点
 * @note 时间复杂度: 平均 O(log N)，最坏 O(N) (退化为链表)
 */
BSTNode* bst_insert(BSTNode *root, int val) {
    // 递归基：找到插入空位
    if (root == NULL) {
        BSTNode *n = (BSTNode *)malloc(sizeof(BSTNode));
        n->val = val;
        n->left = n->right = NULL;
        return n;
    }

    // 二分决策路由
    if (val < root->val) {
        root->left = bst_insert(root->left, val); // 较小值往左插
    } else if (val > root->val) {
        root->right = bst_insert(root->right, val); // 较大值往右插
    }
    // 若 val == root->val，BST 默认不允许重复值，直接忽略

    return root;
}

/**
 * @brief 在 BST 中查找目标值
 * @note 时间复杂度: 平均 O(log N)，最坏 O(N)
 */
bool bst_search(const BSTNode *root, int target) {
    if (root == NULL) return false;
    if (root->val == target) return true; // 命中目标

    if (target < root->val) {
        return bst_search(root->left, target); // 往左子树搜
    } else {
        return bst_search(root->right, target); // 往右子树搜
    }
}

/**
 * @brief 辅助函数：寻找子树中的最小值节点 (一路向左到底)
 */
static BSTNode* find_min(BSTNode *root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

/**
 * @brief 从 BST 中删除值为 key 的节点
 * @return 删除完成后的新子树根节点指针
 * @note 时间复杂度: 平均 O(log N)，最坏 O(N)
 */
BSTNode* bst_delete(BSTNode *root, int key) {
    if (root == NULL) return NULL;

    // 【1. 递归定位待删除节点】
    if (key < root->val) {
        root->left = bst_delete(root->left, key);
    } else if (key > root->val) {
        root->right = bst_delete(root->right, key);
    } else {
        // 【2. 命中目标！开始执行 3 种情况的删除】

        // 情况 A: 只有右孩子或为叶子节点
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp; // 右孩子上位
        }
        // 情况 B: 只有左孩子
        else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp; // 左孩子上位
        }

        // 情况 C: 拥有左右两个孩子（最复杂情况）
        // 找到右子树的最小值（后继节点）
        BSTNode *min_node = find_min(root->right);

        // 用后继节点的数值覆盖当前节点
        root->val = min_node->val;

        // 在右子树中递归删除那个后继节点
        root->right = bst_delete(root->right, min_node->val);
    }

    return root;
}

/**
 * @brief 中序遍历打印 BST (验证单调有序性)
 */
void bst_inorder(const BSTNode *root) {
    if (!root) return;
    bst_inorder(root->left);
    printf("%d ", root->val);
    bst_inorder(root->right);
}

void bst_free(BSTNode *root) {
    if (!root) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

// ==================== 2. 测试与验证入口 ====================

int main(void) {
    BSTNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    
    printf("==================== 二叉搜索树 (BST) 核心算法验证 ====================\n\n");
    for (int i = 0; i < 7; i++) {
        root = bst_insert(root, values[i]);
    }

    printf("BST 中序遍历 (自动升序排序): ");
    bst_inorder(root);
    printf("\n\n");

    // 查找测试
    printf("🔍 查找元素 40: %s\n", bst_search(root, 40) ? "✅ 存在" : "❌ 不存在");
    printf("🔍 查找元素 99: %s\n", bst_search(root, 99) ? "✅ 存在" : "❌ 不存在");

    // 删除双孩子节点测试
    printf("\n🗑️ 删除节点 30 (含左右双孩子的核心分支测试)...\n");
    root = bst_delete(root, 30);
    printf("删除后中序遍历结果: ");
    bst_inorder(root);
    printf(" (依然保持严格有序！)\n");

    bst_free(root);
    root = NULL;

    return 0;
}

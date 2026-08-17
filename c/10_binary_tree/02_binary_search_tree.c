#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * 💡【知识点】二叉搜索树 (Binary Search Tree / BST) 增删查改
 * -----------------------------------------------------------------------------
 * 📌【核心思想与底层原理】
 *   1. BST 性质：对于任意节点，其左子树所有节点值 < 根节点值 < 右子树所有节点值。
 *   2. 查找与插入：利用二分决策，比当前节点小往左走，比当前节点大往右走 ($O(\log N)$)。
 *   3. 删除节点 3 种情况：
 *      ① 叶子节点：直接 free 并置空。
 *      ② 单孩子节点：孩子直接接替自身位置。
 *      ③ 双孩子节点：找到右子树的最小值（后继节点）覆盖自身，然后递归删除该后继节点。
 * -----------------------------------------------------------------------------
 */

typedef struct BSTNode {
    int val;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode* bst_insert(BSTNode *root, int val) {
    if (root == NULL) {
        BSTNode *n = (BSTNode *)malloc(sizeof(BSTNode));
        n->val = val;
        n->left = n->right = NULL;
        return n;
    }
    if (val < root->val) root->left = bst_insert(root->left, val);
    else if (val > root->val) root->right = bst_insert(root->right, val);
    return root;
}

bool bst_search(const BSTNode *root, int target) {
    if (root == NULL) return false;
    if (root->val == target) return true;
    if (target < root->val) return bst_search(root->left, target);
    return bst_search(root->right, target);
}

static BSTNode* find_min(BSTNode *root) {
    while (root && root->left != NULL) root = root->left;
    return root;
}

BSTNode* bst_delete(BSTNode *root, int key) {
    if (root == NULL) return NULL;

    if (key < root->val) root->left = bst_delete(root->left, key);
    else if (key > root->val) root->right = bst_delete(root->right, key);
    else {
        // 找到了待删除节点
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }
        // 双孩子情况：找右子树最小值
        BSTNode *min_node = find_min(root->right);
        root->val = min_node->val;
        root->right = bst_delete(root->right, min_node->val);
    }
    return root;
}

void bst_inorder(const BSTNode *root) {
    if (!root) return;
    bst_inorder(root->left);
    printf("%d ", root->val);
    bst_inorder(root->right);
}

int main(void) {
    BSTNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) root = bst_insert(root, values[i]);

    printf("BST 中序遍历 (自动有序): ");
    bst_inorder(root);
    printf("\n");

    printf("查找 40: %s\n", bst_search(root, 40) ? "✅ 存在" : "❌ 不存在");
    printf("查找 99: %s\n", bst_search(root, 99) ? "✅ 存在" : "❌ 不存在");

    printf("删除节点 30 (双孩子节点)...\n");
    root = bst_delete(root, 30);
    printf("删除后中序遍历: ");
    bst_inorder(root);
    printf("\n");

    return 0;
}

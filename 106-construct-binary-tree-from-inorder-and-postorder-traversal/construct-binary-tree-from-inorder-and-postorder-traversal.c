/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static struct TreeNode* buildHelper(
    int* postorder, int* postIdx,
    int inStart, int inEnd,
    int* inMap
) {
    if (inStart > inEnd) return NULL;

    // The last remaining element in postorder is the current subtree's root
    int rootVal = postorder[(*postIdx)--];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootVal;

    // O(1) lookup for root's split position in inorder
    int mid = inMap[rootVal + 3000];

    // CRITICAL: Build RIGHT subtree first because postorder pops Left -> Right -> Root in reverse
    root->right = buildHelper(postorder, postIdx, mid + 1, inEnd, inMap);
    root->left = buildHelper(postorder, postIdx, inStart, mid - 1, inMap);

    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    if (inorderSize == 0 || postorderSize == 0) return NULL;

    // Node values are guaranteed in [-3000, 3000]
    int inMap[6001];
    for (int i = 0; i < inorderSize; i++) {
        inMap[inorder[i] + 3000] = i;
    }

    int postIdx = postorderSize - 1;
    return buildHelper(postorder, &postIdx, 0, inorderSize - 1, inMap);
}
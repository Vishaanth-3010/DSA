#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* buildHelper(int* preorder, int* preorderIdx, int* inorder, int inStart, int inEnd) {
    // Base case: no elements left in this inorder range
    if (inStart > inEnd) {
        return NULL;
    }

    // 1. Pick the current root from preorder and advance the index
    int rootVal = preorder[(*preorderIdx)++];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootVal;

    // 2. Find the root's split index in the inorder array
    int inRootIdx = inStart;
    while (inRootIdx <= inEnd && inorder[inRootIdx] != rootVal) {
        inRootIdx++;
    }

    // 3. Recursively build left subtree first (matching preorder's Root -> Left -> Right order)
    root->left = buildHelper(preorder, preorderIdx, inorder, inStart, inRootIdx - 1);
    root->right = buildHelper(preorder, preorderIdx, inorder, inRootIdx + 1, inEnd);

    return root;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    int preorderIdx = 0;
    return buildHelper(preorder, &preorderIdx, inorder, 0, inorderSize - 1);
}
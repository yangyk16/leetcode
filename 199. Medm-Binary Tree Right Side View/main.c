/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int depth;
int maxdep;
int gflag;
void recurrent(struct TreeNode* root) {
    if(root && ++depth > maxdep)
        maxdep = depth;
    if(root->left) {
        recurrent(root->left);
    }
    if(root->right)
        recurrent(root->right);
    depth--;
}

int *ret;
void rec(struct TreeNode* root) {
    if(root && ++depth > maxdep) {
        maxdep = depth;
        ret[depth-1] = root->val;
    }
    if(root->right) {
        rec(root->right);
    }
    if(root->left)
        rec(root->left);
    depth--;
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    int lflag = 0;
    if(!root) {
        *returnSize = 0;
        return 0;
    }
    depth = 0;
    maxdep = 0;
    recurrent(root);
    ret = malloc(sizeof(int)*maxdep);
    //printf("%d\n",ret);
    maxdep = 0;
    depth = 0;
    rec(root);
    *returnSize = maxdep;
    return ret;
}
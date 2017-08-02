/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxsum;
typedef struct disnode{
    int lval;
    int rval;
    struct disnode *left;
    struct disnode *right;
} node_t;

node_t *headroot;
void recurrent(struct TreeNode* root, node_t* nroot) {
    int retl,retr,ret;
    static int flag = 0;
    if(root->left) {
        int tmp;
        node_t* nchild = malloc(sizeof(node_t));
        nroot->left = nchild;
        nchild->left = nchild->right = 0;
        recurrent(root->left, nchild);
        if(nchild->lval > nchild->rval)
            tmp = nchild->lval;
        else
            tmp = nchild->rval;
        if(tmp > 0)
            nroot->lval = tmp + root->val;
        else
            nroot->lval = root->val;
    } else {
        nroot->lval = root->val;
    }
    if(root->right) {
        int tmp;
        node_t* nchild = malloc(sizeof(node_t));
        nroot->right = nchild;
        nchild->left = nchild->right = 0;
        recurrent(root->right, nchild);
        if(nchild->lval > nchild->rval)
            tmp = nchild->lval;
        else
            tmp = nchild->rval;
        if(tmp > 0)
            nroot->rval = tmp + root->val;
        else
            nroot->rval = root->val;
    } else {
        nroot->rval = root->val;
    }
}

void recursion(node_t *root, struct TreeNode* nroot) {
    int retl, retr, ret;
    int tmp;
    if(root->left) {
        recursion(root->left, nroot->left);
    }
    if(root->right) {
        recursion(root->right, nroot->right);
    }
    if(root->lval > 0 && root->rval > 0) {
        tmp = root->lval + root->rval - nroot->val;
    } else {
        if(root->lval > root->rval)
            tmp = root->lval;
        else
            tmp = root->rval;
    }
    if(tmp>maxsum)
        maxsum = tmp;
    free(root);
}
int maxPathSum(struct TreeNode* root) {
    maxsum = -2147483648;
    node_t* nroot = malloc(sizeof(node_t));
    nroot->left = nroot->right = 0;
    recurrent(root, nroot);
    //printf("recurrent1\n");
    recursion(nroot, root);
    //printf("recurrent2\n");
    return maxsum;
}
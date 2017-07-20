/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode* root, int sum) {
    static int cursum = 0;
    bool ret = false;
    if(root == NULL)
        return false;
    cursum += root->val;
    if(root->left == NULL && root->right == NULL) {
        if(cursum == sum) {
            cursum -= root->val;
            return true;
        } else {
            cursum -= root->val;
            return false;
        }
    }
    if(root->left)
        ret = hasPathSum(root->left, sum);
    if(ret) {
        cursum -= root->val;
        return ret;
    }
    if(root->right)
        ret = hasPathSum(root->right, sum);
    if(ret) {
        cursum -= root->val;
        return ret;
    }
    cursum -=root->val;
    return false;
}

//先序遍历，全局变量保存所有路径val之和，在leaf结算。成功则return true并一路返回，失败return false并继续计算。
*注意：即使return true也要清理全局变量cursum，否则连续调用时上次调用结果残留导致出错。
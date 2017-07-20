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

//���������ȫ�ֱ�����������·��val֮�ͣ���leaf���㡣�ɹ���return true��һ·���أ�ʧ��return false���������㡣
*ע�⣺��ʹreturn trueҲҪ����ȫ�ֱ���cursum��������������ʱ�ϴε��ý���������³���
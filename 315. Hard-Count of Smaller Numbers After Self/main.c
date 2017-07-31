/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define debug
typedef struct node node_t;
struct node{
    int val;
    int vl;
    int vm;
    int vr;
    node_t *l;
    node_t *m;
    node_t *r;
};

node_t* root;
int insnum;
int insert(int val, node_t* cur) {
    int tmpret;
    if(val < cur->val) {
        if(cur->l == 0) {
            root[insnum].val = val;
            root[insnum].vl = 0;
            cur->vl++;
            cur->l = &root[insnum++];
            debug("1val=%d,vl=%d,vm=%d,vr=%d\n",val,cur->vl,cur->vm,cur->vr);
            return 0;
        } else {
            debug("2val=%d,vl=%d,vm=%d,vr=%d\n",val,cur->vl,cur->vm,cur->vr);
            tmpret = insert(val, cur->l);
            cur->vl++;
            return tmpret;
        }
    }
    else if(val == cur->val) {
        if(cur->m == 0) {
            root[insnum].val = val;
            root[insnum].vm = 0;
            cur->m = &root[insnum++];
            cur->vm++;
            debug("3val=%d,vl=%d,vm=%d,vr=%d\n",val,cur->vl,cur->vm,cur->vr);
            return cur->vl;
        } else {
            cur->vm++;
            debug("4val=%d,vl=%d,vm=%d,vr=%d\n",val,cur->vl,cur->vm,cur->vr);
            return insert(val, cur->m) + cur->vl;
        }
    }
    else {
        if(cur->r == 0) {
            root[insnum].val = val;
            root[insnum].vr = 0;
            cur->r = &root[insnum++];
            cur->vr++;
            debug("5val=%d,vl=%d,vm=%d,vr=%d\n",val,cur->vl,cur->vm,cur->vr);
            return cur->vl + cur->vm + 1;
        } else {
            cur->vr++;
            debug("6val=%d,cval=%d,vl=%d,vm=%d,vr=%d\n",val,cur->val,cur->vl,cur->vm,cur->vr);
            return insert(val, cur->r) + cur->vl + cur->vm + 1;
        }
    }
}
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* ret = malloc(sizeof(int) * numsSize);
    int i;
    if(numsSize == 0) {
        *returnSize = 0;
        return 0;
    }
    root = malloc(sizeof(node_t) * numsSize);
    memset(root, 0, sizeof(node_t) * numsSize);
    root[0].l = root[0].m = root[0].r = 0;
    root[0].vl = root[0].vm = root[0].vr = 0;
    root[0].val = nums[numsSize-1];
    insnum = 1;
    ret[numsSize-1] = 0;
    for(i=numsSize-2;i>=0;i--) {
        ret[i] = insert(nums[i], root);
        //debug("%d ",ret[i]);
    }
    *returnSize = numsSize;
    return ret;
}
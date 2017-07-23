/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct chain {
    struct chain* next;
    int* num;
} chain_t;

int* gnums;
chain_t* curchain;
int count;
int gnumsSize;
void recurrent(int index, int depth, int sum, chain_t* pchain) {
    int i;
    int csum;
    for(i=index+1;i<=gnumsSize-depth;i++) {
        pchain->num[depth-1]=gnums[i];
        csum = sum + gnums[i];
        if(csum == 0 && depth == 1) {
            chain_t* chainptr = malloc(sizeof(chain_t));
            chainptr->num = malloc(sizeof(int)*3);
            chainptr->next = NULL;
            curchain->next = chainptr;
            curchain = chainptr;
            memcpy(chainptr->num, pchain->num, sizeof(int)*3);
            count++;
        }
        printf("depth=%d,sum=%d,i=%d,pchain=%d,%d,%d\n",depth,csum,i,pchain->num[0],pchain->num[1],pchain->num[2]);
        if(depth>1) {
            recurrent(i, depth-1, csum, pchain);
        }
    }
}

int** threeSum(int* nums, int numsSize, int* returnSize) {
    chain_t head, chainc;
    int **ret;
    int i;
    gnums = nums;
    gnumsSize = numsSize;
    count = 0;
    curchain = &head;
    memset(&chainc,0,sizeof(chain_t));
    chainc.num = malloc(sizeof(int)*3);
    recurrent(-1,3,0,&chainc);
    *returnSize = count;
    printf("count=%d\n",count);
    if(count == 0)
        return 0;
    ret = malloc(count * sizeof(int*));
    for(i=0,curchain=head.next;i<count;i++) {
        ret[i] = curchain->num;
        curchain = curchain->next;
    }
    return ret;
}
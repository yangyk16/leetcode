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
int maxnum;

void slowsort(int* s, int n){
    int i,j;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++) {
            if(s[i]>s[j]) {
                int t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
        }
}
void sort(int **s, int l, int r, int key)  
{  
    int i, j, x[3];  
    if (l < r)  
    {  
        i = l;  
        j = r;  
        //x = s[i][key];  
        x[0]=s[i][0];
        x[1]=s[i][1];
        x[2]=s[i][2];
        while (i < j)  
        {  
            while(i < j && s[j][key] > x[key])   
                j--;
            if(i < j) {
                //s[i++][key] = s[j][key];
                s[i][0] = s[j][0];
                s[i][1] = s[j][1];
                s[i++][2] = s[j][2];
            } 
            while(i < j && s[i][key] < x[key])
                i++;
            if(i < j) {
                s[j][0] = s[i][0];
                s[j][1] = s[i][1];
                s[j--][2] = s[i][2];
                //s[j--][key] = s[i][key];  
            }
        }  
        //s[i][key] = x;  
        s[i][0]=x[0];
        s[i][1]=x[1];
        s[i][2]=x[2];
        sort(s, l, i-1, key);
        sort(s, i+1, r, key);  
    }  
}

int findn(int arr[], int num, int sz)//二分查找函数
{
    int mid = 0;//折半后数字的下标
    int left = 0;//左下标
    int right = sz - 1;//右下标
    while (left < right)//判断当左下标小于右下标条件满足
    {
        if(right-left<=1) {
            if(num == arr[right])
                return right;
            if(num == arr[left])
                return left;
            return -1;
        }
        mid = (left + right)/2;//找出折半后数字下标(尽量不要用此方法)
        if (num <arr[mid])
            right = mid;
        else if (num > arr[mid])
            left = mid;
        else
            return mid;//找到目标数字并返回数组下标
    }
    if(sz == 1 && arr[0] == num)
        return 0;
    return -1;//左下标大于右下标没找到
}

void filter(int* s, int *num) {
    int n = *num;
    int *sbak = malloc(*num * sizeof(int));
    int i;
    int j = 0;
    int sflag;
    int repeat;
    for(i=0;i<n-1;i++) {
        sflag = 0;
        repeat = 0;
        while(s[i]==s[i+1] && i<n-1) {
            sflag = 1;
            i++;
            repeat++;
        }
        //printf("index=%d,r=%d\n",i,repeat);
        if(sflag) {
            int ret = findn(s, -2*s[i-1], n);
            if((ret >= 0 && s[i-1] != 0) || (s[i-1] == 0 && repeat >=2)) {
                chain_t* chainptr = malloc(sizeof(chain_t));
                chainptr->num = malloc(sizeof(int)*3);
                chainptr->next = NULL;
                curchain->next = chainptr;
                curchain = chainptr;
                if(s[i-1] < 0) {
                    chainptr->num[0] = chainptr->num[1] = s[i-1];
                    chainptr->num[2] = -2 * s[i-1];
                } else {
                    chainptr->num[0] = -2 * s[i-1];
                    chainptr->num[1] = chainptr->num[2] = s[i-1];
                }
                count++;                
            }
        }
        //printf("filter\n");
        sbak[j++] = s[i];
    }
    if(!sflag || sflag && i==n-1)
        sbak[j++] = s[i];
    memcpy(s, sbak, sizeof(int) * j);
    *num = j;
}

void recurrent(int index, int depth, int sum, chain_t* pchain) {
    int i;
    int csum;
    for(i=index+1;i<=gnumsSize-depth;i++) {
        pchain->num[depth-1]=gnums[i];
        csum = sum + gnums[i];
        if((csum > 0) && (gnums[i] > 0))
            return;
        if((depth == 3) && (csum < 0) && (csum + maxnum * 2 < 0))
            continue;
        if(depth == 2) {
            if(findn(gnums+i+1, -csum, gnumsSize - i - 1) >= 0) {
                pchain->num[0] = -csum;
                chain_t* chainptr = malloc(sizeof(chain_t));
                chainptr->num = malloc(sizeof(int)*3);
                chainptr->next = NULL;
                curchain->next = chainptr;
                curchain = chainptr;
                memcpy(chainptr->num, pchain->num, sizeof(int)*3);
                count++;               
            } else
                continue;
        } 
        //printf("depth=%d,sum=%d,i=%d,pchain=%d,%d,%d\n",depth,csum,i,pchain->num[0],pchain->num[1],pchain->num[2]);
        if(depth>2) {
            recurrent(i, depth-1, csum, pchain);
        }
    }
}

int** threeSum(int* nums, int numsSize, int* returnSize) {
    chain_t *head, chainc;
    int **ret;
    int i;
    gnums = nums;
    gnumsSize = numsSize;
    count = 0;
    memset(&chainc,0,sizeof(chain_t));
    chainc.num = malloc(sizeof(int)*3);
    head = malloc(sizeof(chain_t));
    head->num = malloc(sizeof(int)*3);
    curchain = head;
    slowsort(nums, numsSize);
    /*for(i=0;i<gnumsSize;i++) {
        printf("%d ",nums[i]);
    }
    printf("\n");*/
    filter(nums, &gnumsSize);
    maxnum = nums[gnumsSize-1];
    printf("max=%d\n",maxnum);
    /*for(i=0;i<gnumsSize;i++) {
        printf("%d ",nums[i]);
    }
    printf("\n");*/
    //printf("size=%d\n",gnumsSize);
    recurrent(-1,3,0,&chainc);
    *returnSize = count;
    printf("count=%d\n",count);
    if(count == 0)
        return 0;
    ret = malloc(count * sizeof(int*));
    for(i=0,curchain=head->next;i<count;i++) {
        ret[i] = curchain->num;
        curchain = curchain->next;
        {
            int t;
            if(ret[i][0]>ret[i][1])
                {t=ret[i][0];ret[i][0]=ret[i][1];ret[i][1]=t;}
            if(ret[i][1]>ret[i][2])
                {t=ret[i][1];ret[i][1]=ret[i][2];ret[i][2]=t;}
            if(ret[i][0]>ret[i][1])
                {t=ret[i][0];ret[i][0]=ret[i][1];ret[i][1]=t;}
        }
    }
    //no same num ensure answer uniq. needn't remove extra answer and sort.
    *returnSize = count;
    return ret;
}
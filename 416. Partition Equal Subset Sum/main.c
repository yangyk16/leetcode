int* array;
int count;
int exps;
int rec(int sizen, int dep, int sum) {
    int i;
    bool ret;
    for(i=sizen;i<count;i++) {
        if(sum+array[i]==exps)
            return 0;
        if(sum+array[i]>exps)
            continue;
        if(dep) {
            ret = rec(i+1, dep-1, sum+array[i]);
            if(!ret)
                return ret;
        }
    }
    return 2;
}
bool canPartition(int* nums, int numsSize) {
    int sum = 0;
    int i,j;
    int ret;
    array = nums;
    count = numsSize;
    for(i=0;i<numsSize-1;i++)
        for(j=i+1;j<numsSize;j++)
            if(array[i]<array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
    for(i=0; i<numsSize; i++)
        sum += nums[i];
    if(sum & 1)
        return false;
    exps = sum/2;
    if(array[0] > exps)
        return false;
    ret = rec(0, numsSize/2, 0);
    if(!ret)
        return true;
    return false;
}
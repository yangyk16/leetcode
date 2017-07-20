bool rec(int* nums, int sizen, int sizem, int dep, int sum, int exp) {
    int i;
    bool ret;
    for(i=sizen;i<sizem;i++) {
        if(sum+nums[i]==exp)
            return true;
        if(dep) {
            ret = rec(nums, i+1, sizem, dep-1, sum+nums[i], exp);
            if(ret)
                return ret;
        }
    }
    return false;
}
bool canPartition(int* nums, int numsSize) {
    int sum = 0;
    int i;
    bool ret;
    for(i=0; i<numsSize; i++)
        sum += nums[i];
    if(sum & 1)
        return false;
    ret = rec(nums, 0, numsSize, numsSize/2, 0, sum/2);
    if(ret)
        return ret;
    return false;
}
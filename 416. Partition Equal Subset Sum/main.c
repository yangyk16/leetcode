bool rec(int* nums, int sizen, int sizem, int sum, int exp) {
    int i;
    bool ret;
    for(i=0;i<=sizen-sizem;i++) {
        if(sizem == 1)
            if(sum+nums[i]==exp)
                return true;
            else
                continue;
        ret = rec(nums+i+1, sizen-1, sizem-1, sum+nums[i], exp);
        if(ret)
            return ret;
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
    for(i=1; i<=numsSize/2; i++) {
        ret = rec(nums, numsSize, i, 0, sum/2);
        if(ret)
            return ret;
    }
    return false;
}



//code efficient of recurrent is low. maybe use DP
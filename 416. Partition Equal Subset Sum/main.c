bool canPartition(int* nums, int numsSize) {
    volatile int* array = malloc(pow(2,numsSize)*4);
    int i,j;
    int sum=0;
    for(i=0;i<numsSize;i++)
        sum+=nums[i];
    if(sum&1)
        return false;
    else
        sum/=2;
    for(i=0;i<pow(2,numsSize);i++)
        array[i]=0;
    for(i=0;i<numsSize;i++) {
        int jmax = pow(2, i);
        for(j=0;j<jmax;j++) {
            array[j+jmax-1]=array[j]+nums[i];
            if(array[j+jmax-1] == sum)
                return true;
        }
    }
    return false;
}
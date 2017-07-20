int flaged = 0;
int *flag;
int *curchain;
int *distable;
int maxdis=0;

void cir(int* nums, int pos){
    int beginpos = pos;
    int tmpdis = 0;
    int i = pos;
    //printf("%d,",pos);
    do{
        //printf("%d ",i);
        flag[i]=1;
        tmpdis++;
        flaged++;
        i=nums[i];
    } while(i!=beginpos);
    //printf("\n");
    //printf("%d\n",flaged);
    if(tmpdis>maxdis)
        maxdis=tmpdis;
}
int arrayNesting(int* nums, int numsSize) {
    int** dismat = malloc(numsSize * 8);
    int i,j;
    flag = malloc(numsSize * 4);
    curchain = malloc(numsSize * 4);
    distable = malloc(numsSize * 4);
    maxdis = 0;
    flaged = 0;
    for(i=0;i<numsSize;i++)
        flag[i]=curchain[i]=distable[i]=0;
    for(i=0;i<numsSize;i++) {
        if(!flag[i]) {
            cir(nums, i);
            //printf("flagd=%d\n",flaged);
        }
    }
    return maxdis;
    free(flag);
    free(curchain);
    free(distable);
}
int maxCoins(int* nums, int numsSize) {
    int i,j,k;
    int **opt;
    int *numt = malloc(sizeof(int) * (numsSize+2));
    opt = malloc(sizeof(int*) * (numsSize+2));
    for(i=0;i<=numsSize+1;i++)
        opt[i] = malloc(sizeof(int) * (numsSize+2));
    for(i=1;i<=numsSize+1;i++)
        opt[i][i-1] = 0;
    memcpy(numt+1, nums, numsSize*sizeof(int));
    numt[0] = numt[numsSize+1] = 1;
    for(i=1;i<=numsSize;i++)
        for(j=1;j<=numsSize-i+1;j++) {
            int maxs = 0;
            int curs;
            int e = j + i - 1;
            for(k=0;k<i;k++) {
                curs = opt[j][j+k-1] + numt[j-1] * numt[j+k] * numt[e+1] + opt[j+k+1][e];
                if(curs>maxs)
                    maxs = curs;
            }
            opt[j][e] = maxs;
        }
    return opt[1][numsSize];
}
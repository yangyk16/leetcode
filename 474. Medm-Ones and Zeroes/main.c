int *marray, *narray;
int *summ, *sumn;
int max;
int allm, alln;
int globalsize;
int recurrent(int index, int mused, int nused, int choose) {
    int ret1 = 0, ret2 = 0;
    //printf("index=%d,mused=%d,nused=%d,choose=%d\n",index,mused,nused,choose);
    if(index == globalsize)
        return choose;
    if(marray[index] + mused > allm)
        return choose;
    if(mused + summ[index] <= allm && nused + sumn[index] <= alln)
        return choose + globalsize - index;
    if(marray[index] + mused <= allm && narray[index] + nused <= alln) {
        ret1 = recurrent(index+1, mused+marray[index], nused+narray[index], choose+1);
        ret2 = recurrent(index+1, mused, nused, choose);
        return ret1>ret2?ret1:ret2;
    } else
        return recurrent(index+1, mused, nused, choose);
}

void sort(int* array1, int* array2, int size)
{
    int i,j;
    for(i=0;i<size-1;i++)
        for(j=i+1;j<size;j++){
            if(array1[i]>array1[j]) {
                int temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
                temp = array2[i];
                array2[i] = array2[j];
                array2[j] = temp;
            }
        }
}

int findMaxForm(char** strs, int strsSize, int m, int n) {
    int i,j,ret;
    marray = malloc(strsSize * sizeof(int));
    narray = malloc(strsSize * sizeof(int));
    summ = malloc(strsSize * sizeof(int));
    sumn = malloc(strsSize * sizeof(int));
    allm = m;
    alln = n;
    globalsize = strsSize;
    for(i=0;i<strsSize;i++)
        marray[i] = narray[i] = summ[i] = sumn[i] = 0;
    for(i=0;i<strsSize;i++)
        for(j=0;strs[i][j];j++) {
            if(strs[i][j] == '1')
                narray[i]++;
            else
                marray[i]++;
        }
    sort(marray, narray, strsSize);
    summ[strsSize-1] = marray[strsSize-1];
    sumn[strsSize-1] = narray[strsSize-1];
    for(i=strsSize-2;i>=0;i--) {
        summ[i] = summ[i+1] + marray[i];
        sumn[i] = sumn[i+1] + narray[i];
    }
    ret = recurrent(0, 0, 0, 0);
    return ret;
}

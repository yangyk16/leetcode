int firstUniqChar(char* s) {
    int num[255] = {0};
    int fpos[255] = {-1};
    int i,j=0,min;
    int strlen = 0;
    //for(i=0;i<255;i++)
    //    num[i]=fpos[i]=0;
    i=0;
    while(s[i]) {
        num[s[i]]++;
        if(num[s[i]] == 1)
            fpos[s[i]] = i;
        i++;
    }
    if(s[0]==0)return -1;
    min = i;
    for(i=0;i<255;i++) {
        if(num[i] == 1) {
            j=1;
            if(fpos[i]<min)
                min = fpos[i];
        }
    }
    if(j)
        return min;
    else
        return -1;
}
bool repeatedSubstringPattern(char* s) {
    int len = strlen(s);
    int i,j,k;
    for(i=2;i<len+1;i++) {
        if(len % i == 0) {
            j = len / i;
            for(k=0;k<len;k+=j) {
                if(memcmp(s,s+k,j))
                    goto ci;
            }
            return true;
        }
ci:
        i;
    }
    return false;
}
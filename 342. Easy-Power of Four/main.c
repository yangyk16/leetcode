bool isPowerOfFour(int num) {
    int k = num;
    while(k) {
        if(k & 3)
            if(k==1)
                return true;
            else
                return false;
        k>>=2;
    }
    return false;
}
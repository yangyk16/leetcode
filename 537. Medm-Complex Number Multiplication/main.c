char* complexNumberMultiply(char* a, char* b) {
    static char res[100]={0};
    int ra,rb,ca,cb;
    int resr,resc;
    int i;
    ra=atoi(a);
    rb=atoi(b);
    for(i=0;a[i]!='+';)
        i++;
    ca=atoi(a+i+1);
    for(i=0;b[i]!='+';)
        i++;
    cb=atoi(b+i+1);
    printf("%d,%d,%d,%d",ra,rb,ca,cb);
    resr = ra*rb - ca*cb;
    resc = ca*rb + cb*ra;
    sprintf(res,"%d+%di",resr,resc);
    return res;
}
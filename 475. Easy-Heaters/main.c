int findmax(int a, int b) {
    if(a>=b)
        return a;
    else
        return b;
}

int findmin(int a, int b) {
    if(a<=b)
        return a;
    else
        return b;
}
int findmid(int* houses, int heat_1, int heat_2, int index1, int index2, int* getk) {
    int k;
    float aim = (heat_1 + heat_2) / 2.0;
    int ret;
    //printf("aim=%f  ",aim);
    for(k=index1; k<index2; k++){
        if(houses[k]<=aim && houses[k+1]>=aim) {
            if(houses[k] >= heat_1 && houses[k+1] <= heat_2) {
                ret = findmax(abs(houses[k]-heat_1),abs(houses[k+1]-heat_2));
                //if(ret == abs(houses[k]-heat_1)) {
                    *getk = k + 1;
                //} else
                //    *getk = k + 2;
                //printf("1,%d\n",ret);
                return ret;
            } else if(houses[k] >= heat_1 && houses[k+1] >= heat_2) {
                *getk = k;
                ret = findmin(abs(houses[k]-heat_1),abs(houses[k]-heat_2));
                //printf("2,%d\n",ret);
                return ret;                
            } else if(houses[k] <= heat_1 && houses[k+1] <= heat_2) {
                *getk = k + 1;
                ret = findmin(abs(houses[k+1]-heat_1),abs(houses[k+1]-heat_2));
                //printf("3,%d\n",ret);
                return ret;
            } else {
                *getk = k;
                ret = 0;
                //printf("4,%d\n",ret);
                return ret;
            }
        }
    }
    //printf("\n");
    *getk = k;
    return 0;
}

void quick_sort(int s[], int l, int r)  
{  
    int i, j, x;  
    if (l < r)  
    {  
        i = l;  
        j = r;  
        x = s[i];  
        while (i < j)  
        {  
            while(i < j && s[j] > x)   
                j--; /* 从右向左找第一个小于x的数 */  
            if(i < j)   
                s[i++] = s[j];  
      
  
            while(i < j && s[i] < x)   
                i++; /* 从左向右找第一个大于x的数 */  
            if(i < j)   
                s[j--] = s[i];  
  
        }  
        s[i] = x;  
        quick_sort(s, l, i-1); /* 递归调用 */  
        quick_sort(s, i+1, r);  
    }  
}  

int findRadius(int* houses, int housesSize, int* heaters, int heatersSize) {
    int i,j,k=0;
    int min=0;
    int tmpr;
    int min1,min2;
    int lightbegin,lightend;
    if(housesSize == 1) {
        return findmin(abs(heaters[0]-houses[0]),abs(heaters[heatersSize-1]-houses[0]));
    }
    if(heatersSize == 1) {
        return findmax(abs(heaters[0]-houses[0]),abs(heaters[0]-houses[housesSize-1]));
    }
    quick_sort(houses, 0, housesSize-1);
    quick_sort(heaters, 0, heatersSize-1);
    int mindisfromlighttohouse0, mindisfromlighttohouseN;
    int indexmindis0 = 0, indexmindisN = heatersSize-1;
    mindisfromlighttohouse0 = abs(heaters[0]-houses[0]);
    mindisfromlighttohouseN = abs(heaters[heatersSize-1]-houses[housesSize-1]);
    for(i=0;i<heatersSize;i++) {
        if(abs(heaters[i]-houses[0]) <= mindisfromlighttohouse0) {
            mindisfromlighttohouse0 = abs(heaters[i]-houses[0]);
            indexmindis0 = i;
        } else
            break;
    }
    for(i=heatersSize-1;i>=0;i--) {
        if(abs(heaters[i]-houses[housesSize-1]) <= mindisfromlighttohouseN) {
            mindisfromlighttohouseN = abs(heaters[i]-houses[housesSize-1]);
            indexmindisN = i;
        } else
            break;
    }    
    /*for(i=0;i<housesSize;i++)
        printf("%d ",houses[i]);
    printf("\n");
    for(i=0;i<heatersSize;i++)
        printf("%d ",heaters[i]);
    printf("\n");*/
    min1 = findmin(abs(houses[0]-heaters[indexmindis0]),abs(houses[0]-heaters[indexmindisN]));
    min2 = findmin(abs(houses[housesSize-1]-heaters[indexmindis0]),abs(houses[housesSize-1]-heaters[indexmindisN]));
    min = findmax(min1,min2);
    //printf("b=%d,e=%d\n",indexmindis0,indexmindisN);
    //printf("b=%d,e=%d\n",heaters[indexmindis0],heaters[indexmindisN]);
    //printf("begmin=%d\n",min);
    for(i=indexmindis0;i<indexmindisN;i++) {
        tmpr = findmid(houses,heaters[i], heaters[i+1],k,housesSize-1,&k);
        if(tmpr>min)
            min = tmpr;
    }
    return min;
}
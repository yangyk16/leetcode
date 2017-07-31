int **flag, **total, **gmatrix;
int nrow, ncol;
int totalmax;
int recurrent(int row, int col) {
    if(flag[row][col] == 1)
        return total[row][col];
    else {
        int l = 1, r = 1, u = 1, d = 1;
        int max1 = 0, max2 = 0, max;
        if(row>0) {
            if(gmatrix[row-1][col] > gmatrix[row][col]) {
                u = recurrent(row-1, col) + 1;
            } else 
                u = 1;
        }
        if(row < nrow-1) {
            if(gmatrix[row+1][col] > gmatrix[row][col]) {
                d = recurrent(row+1, col) + 1;
            } else 
                d = 1;  
        }
        if(col>0) {
            if(gmatrix[row][col-1] > gmatrix[row][col]) {
                l = recurrent(row, col-1) + 1;
            } else 
                l = 1;  
        }
        if(col<ncol-1) {
            if(gmatrix[row][col+1] > gmatrix[row][col]) {
                r = recurrent(row, col+1) + 1;
            } else 
                r = 1;
        }
        max1 = l>r?l:r;
        max2 = u>d?u:d;
        max = max1>max2?max1:max2;
        flag[row][col] = 1;
        total[row][col] = max;
        if(max > totalmax)
            totalmax = max;
        //printf("r=%d,c=%d,max=%d\n",row,col,max);
        return max;
    }
}
int longestIncreasingPath(int** matrix, int matrixRowSize, int matrixColSize) {
    int i,j;
    int longest = 1;
    nrow = matrixRowSize;
    ncol = matrixColSize;
    flag = malloc(sizeof(int*) * matrixRowSize);
    total = malloc(sizeof(int*) * matrixRowSize);
    totalmax = 0;
    gmatrix = matrix;
    for(i=0;i<matrixRowSize;i++) {
        flag[i] = malloc(sizeof(int) * matrixColSize);
        total[i] = malloc(sizeof(int) * matrixColSize);
    }
    for(i=0;i<matrixRowSize;i++)
        for(j=0;j<matrixColSize;j++) {
            flag[i][j] = 0; 
            total[i][j] = 0;
        }
    for(i=0;i<matrixRowSize;i++)
        for(j=0;j<matrixColSize;j++) {
            if(flag[i][j] == 0) {
                recurrent(i,j);
                //printf("i=%d,j=%d\n",i,j);
            }
                
        }
    return totalmax;
}
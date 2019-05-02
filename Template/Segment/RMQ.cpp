/*
 * 预处理 O(nlogn)
 * dp[i][j]:从a[i]开始2^j个数的最小值
 * 数组下标从1开始，注意-1 +1 <=等细节
 */
void init(){
    for(int i=1;i<=n;i++){
        dp[i][0]=a[i];
    }
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i+(1<<(j-1))-1<=n;i++){
            dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
        }
    }
}
/*
 * 查询[l,r]最大值
 */
int rmq(int l,int r){
    int k=0;
    //保证刚好[l,l+2^k]和[r-2^k,r]重叠
    while((1<<(k+1))<=r-l+1){
        k++;
    }
    return max(dp[l][k],dp[r-(1<<k)+1][k]);
}
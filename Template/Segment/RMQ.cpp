/*
 * 预处理 O(nlogn)
 * dp[i][j]:从a[i]开始2^j个数的最小值
 */
void RMQ_init(int n){
    for(int i=0;i<n;i++){
        dp[i][0]=a[i];
    }
    for(int j=1;(1<<j)<=n;j++){
	for(int i=0;i+(1<<j)-1<n;i++){
	    //两段重叠部分小区间
	    dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
	}
    }
}
/*
 * 查询[l,r]最小值，最大值同理
 */
int RMQ(int l,int r){
    int k=0;
    //保证刚好[l,l+2^k]和[r-2^k,r]重叠
    while((1<<(k+1))<=r-l+1){
        k++;
    }
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
}

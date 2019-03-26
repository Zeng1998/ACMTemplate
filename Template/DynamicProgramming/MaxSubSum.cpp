/*
 * 求最大连续子序列和
 * 定义dp[i]表示前ｉ个值的最大连续和，dp[i]=max(dp[i-1]+a[i],a[i])
 */
void maxSum(int a[],int n){
    //根据题目具体要求赋初值
    int ans=-2147483647;
    int cur=0;
    for(int i=0;i<n;i++){
        cur=max(cur+a[i],a[i]);
	ans=max(ans,cur);
    }
    return ans;
}

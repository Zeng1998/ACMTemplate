/*
 * 经典石头归并问题(2合1)
 * dp[i][j]: 区间[i..j]合并成1堆的最小代价
 */ 
int solve(){
    //初始化
    memset(dp,INF,sizeof(dp));
    for(int i=1;i<=n;i++){
        dp[i][i]=0;
    }
    //最外层一定是枚举区间长度，从小区间更新到大区间
    for(int len=2;len<=n;len++){
        //枚举左端点，计算右端点
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            //枚举区间分割点
            for(int m=l;m<r;m++){
                //状态转移
                dp[l][r]=min(dp[l][r],dp[l][m]+dp[m+1][r]+pre[r]-pre[l-1]);
            }
        }
    }
    return dp[1][n];
}
/*
 * 拓展到k合1的情况(Leetcode1000)
 * dp2[i][j][k]: 区间[i..j]合并成k堆的最小代价
 */ 
int ksolve(int K){
    memset(dp2,INF,sizeof(dp2));
    for(int i=1;i<=n;i++){
        dp2[i][i][1]=0;
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            for(int m=l;m<r;m++){
                for(int k=2;k<=len;k++){
                    dp2[l][r][k]=min(dp2[l][r][k],dp2[l][m][k-1]+dp2[m+1][r][1]);
                }
            }
            dp2[l][r][1]=dp2[l][r][K]+pre[r]-pre[l-1];
        }
    }
    return dp2[1][n][1];
}
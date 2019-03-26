/*
 * 编辑距离/莱温斯坦距离
 * 两个字符串，三种操作(替换/插入/删除一个字符)，求使两个字符串相同的最小操作数
 * dp[i][j]: 表示str1前i个字符和str2前j个字符的最小编辑距离
 * dp[i][0]=dp[0][i]=i;
 * dp[i][j]=dp[i-1][j-1]                               (str1[i-1]==str2[j-1])
 *         =min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1  (otherwise)
 */ 
void LD(char str1[],char str2[]){
    int n=strlen(str1);
    int m=strlen(str2);
    for(int i=0;i<=n;i++){
        dp[i][0]=i;
    }
    for(int i=0;i<=m;i++){
        dp[0][i]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(str1[i-1]==str2[j-1]){
                dp[i][j]=dp[i-1][j-1];
            }else{
                dp[i][j]=min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
            }
        }
    }
}

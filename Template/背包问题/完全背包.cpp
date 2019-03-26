/*
    完全背包问题：每种物品有无限个
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=1010;
//物品n种
int n=5;
//物品的体积(从1开始)
int V[MAXN]={-10001,2,3,2,5,4};
//物品的重量
int W[MAXN]={-10001,3,4,2,3,2};
//背包容量
int C=6;
int dp[MAXN][MAXN];
int dp_2[MAXN];
int main(void){
    //二维数组表示
    //dp[i][j]表示把前i个物品装到背包的最大重量
    for(int i=1;i<=n;i++){
        for(int j=1;j<=C;j++){
            if(j>=V[i]){
                //这里是dp[i][j-V[i]]+W[i]，和01背包的区别
                dp[i][j]=max(dp[i-1][j],dp[i][j-V[i]]+W[i]);
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=C;j++){
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }
    printf("最大重量：%d\n",dp[5][C]);
    return 0;
}

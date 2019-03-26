/*
    01背包问题：每种物品只有一个，只存在选或不选
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
int W[MAXN]={-10001,3,5,2,3,2};
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
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-V[i]]+W[i]);
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
    /*          容量: 1->C 
 面对第i个物品    0 3 3 3 3 3
                0 3 5 5 8 8
                0 3 5 5 8 8
                0 3 5 5 8 8
                0 3 5 5 8 8 
    */

    //一维数组表示（滚动数组）
    for(int i=1;i<=n;i++){
        for(int j=C;j>=V[i];j--){
            dp_2[j]=max(dp_2[j],dp_2[j-V[i]]+W[i]);
            //省略
            /*
            else{
                dp_2[j]=dp_2[j];
            }
            */
        }
    }
    for(int i=1;i<=C;i++){
        printf("%d ",dp_2[i]);
    }
    printf("\n");
    printf("最大重量：%d\n",dp_2[C]);
    /*
        0 3 5 5 8 8
    */
    return 0;
}

/*
    多重背包问题：每种物品既不是只有一个，也不是无限个，而是有限个数目
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=1010;
//物品n种
int n=5;
//物品的体积(从1开始)
int V[MAXN]={-10001,2,3,2,5,1};
//物品的重量
int W[MAXN]={-10001,3,5,2,3,2};
//物品的数量
int N[MAXN]={-10001,2,3,4,2,5};
//背包容量
int C=11;
int dp[MAXN][MAXN];
int main(void){
    //二维数组表示
    //dp[i][j]表示把前i个物品装到背包j体积的最大重量
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=C;j++){
    //         //默认先不适用i物品
    //         dp[i][j]=dp[i-1][j];
    //         for(int k=1;k<=N[i];k++){
    //             //目前可用背包体积j已经不足放k个i物品
    //             if(V[i]*k>j){
    //                 break;
    //             }
    //             dp[i][j]=max(dp[i][j],dp[i-1][j-V[i]*k]+W[i]*k);
    //         }
    //     }
    // }
	//二进制优化
	int cnt=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<N[i];j*=2){
			V[cnt]=j*V[i];
			W[cnt]=j*V[i];
			cnt++;
			N[i]--;
		}
		//最后一项补齐
		if(N[i]>0){
			V[cnt]=N[i]*V[i];
			W[cnt]=N[i]*W[i];
			cnt++;
		}
	}
	//然后转化为01背包
    for(int i=1;i<=n;i++){
        for(int j=1;j<=C;j++){
            printf("%d ",dp[i][j]);
        }
        printf("\n");
    }
    printf("最大重量：%d\n",dp[5][C]);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+50;
struct SAM{
    //后缀自动机
    //dp[u]表示以u为起点的路径总数
    ll dp[N*2];
    void dfs(int u){
        dp[u]=u==0?0:1ll;
        for(int i=0;i<26;i++){
            int v=next[u][i];
            if(v){
                if(!dp[v]){
                    dfs(v);
                }
                dp[u]+=dp[v];
            }
        }
    }
    ll solve(){
        dfs(0);
        return dp[0];
    }
}ac;
int n;
char s[N];
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d",&n);
    scanf("%s",s);
    ac.init();
    for(int i=0;i<n;i++){
        ac.add(s[i]);
    }
    ll ans=ac.solve();
    printf("%lld\n",ans);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
struct node{
    ll cnt;
    ll sum;
    ll powsum;
}dp[30][10][10];
int a[30];
ll pw[30];
void init(){
    pw[0]=1;
    for(int i=1;i<30;i++){
        pw[i]=(pw[i-1]*10)%MOD;
    }
    for(int i=0;i<30;i++){
        for(int j=0;j<10;j++){
            for(int k=0;k<10;k++){
                dp[i][j][k]=node{-1,0,0};
            }
        }
    }
}
node dfs(int pos,int summod,int valmod,bool limit){
    if(pos<0){
        node tmp;
        tmp.cnt=(summod!=0 && valmod!=0);
        //只有计数才能在这里返回，其他两个值要在回溯的时候计算
        //换句话说，递归边界只是为了判断是否存在这个合法的数
        tmp.sum=tmp.powsum=0;
        return tmp;
    }
    if(!limit && dp[pos][summod][valmod].cnt!=-1){
        return dp[pos][summod][valmod];
    }
    int up=limit?a[pos]:9;
    node ans;
    ans.cnt=ans.sum=ans.powsum=0;
    for(int i=0;i<=up;i++){
        if(i==7){
            continue;
        }
        node tmp=dfs(pos-1,(summod+i)%7,(valmod*10+i)%7,limit&&(i==up));

        //普通数位dp计数
        ans.cnt=(ans.cnt+tmp.cnt)%MOD;
        //sum计算
        //比如递归到最后一位是3 4两个符合的数位，当前位是第1位，数位为2
        //回溯计算就是3+4=7 -->3+4+23+24=54
        //也就是加上pw[1]=10乘以i=2乘以递归边界计数tmp.cnt=2
        ans.sum=(ans.sum+tmp.sum+((pw[pos]*i)%MOD*tmp.cnt)%MOD)%MOD;
        //powsum计算
        //同上 3^2+4^2=25 --> 3^2+4^2+23^2+24^2
        //也就是加上(20+3)^2+(20+4)^2=20^2+20^2+3^2+4^2+2*10*(3+4)
        ans.powsum=((ans.powsum+tmp.powsum)%MOD+((((tmp.cnt*pw[pos])
        %MOD*pw[pos])%MOD*i*i)%MOD)+(((tmp.sum*pw[pos])%MOD*2*i)%MOD))%MOD;
    }
    if(!limit){
        dp[pos][summod][valmod]=ans;
    }
    return ans;
}
ll solve(ll x){
    int k=0;
    while(x){
        a[k++]=x%10;
        x/=10;
    }
    return dfs(k-1,0,0,true).powsum;
}
int t;
ll l,r;
int main(void){
    init();
    scanf("%d",&t);
    while(t--){
        scanf("%lld%lld",&l,&r);
        ll ansr=solve(r)%MOD;
        ll ansl=solve(l-1)%MOD;
        printf("%lld\n",(ansr-ansl+MOD)%MOD);
    }
    return 0;
}
/**
 * 数列分块4：区间更新，区间求和
 */ 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e4+50;
ll a[N];
int bel[N];
//add是单点累加标记 w是块累加标记 add时也要更新w 
ll add[N],w[N];
int n,o,l,r;
ll c;
ll mod;
int block;
void update(int l,int r,ll c){
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++){
            a[i]+=c;
            w[bel[l]]+=c;
        }
    }else{
        for(int i=l;i<=bel[l]*block;i++){
            a[i]+=c;
            w[bel[l]]+=c;
        }
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            a[i]+=c;
            w[bel[r]]+=c;
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            add[i]+=c;
            w[i]+=c*block;
        }
    }
}
ll query(int l,int r){
    ll ans=0;
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++){
            ans+=(a[i]+add[bel[l]])%mod;
        }
    }else{
        for(int i=l;i<=bel[l]*block;i++){
            ans+=(a[i]+add[bel[l]])%mod;
        }
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            ans+=(a[i]+add[bel[r]])%mod;
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            ans+=w[i]%mod;
        }
    }
    return ans%mod;
}
int main(void){
    scanf("%d",&n);
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        bel[i]=(i-1)/block+1;
        //初始化每一块的和
        w[bel[i]]+=a[i];
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%lld",&o,&l,&r,&c);
        if(o==0){
            update(l,r,c);
        }else{
            mod=c+1;
            int ans=query(l,r);
            printf("%lld\n",ans%mod);
        }
    }
    return 0;
}
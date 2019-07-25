/**
 * 数列分块7：区间乘法，加法，单点查询
 */ 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+50;
const int mod=1e4+7;
ll a[N],bel[N];
//标记
ll add[N],mul[N];
int n,block;
int o,l,r,c;
void Add(int l,int r,int w){
    if(bel[l]==bel[r]){
        //同一块的，先加上标记
        for(int i=(bel[l]-1)*block+1;i<=bel[l]*block;i++){
            a[i]=(a[i]*mul[bel[l]]+add[bel[l]])%mod;
        }
        add[bel[l]]=0;
        mul[bel[l]]=1;
        //再暴力更新
        for(int i=l;i<=r;i++){
            a[i]=(a[i]+w)%mod;
        }
    }else{
        //左边部分块，标记
        for(int i=(bel[l]-1)*block+1;i<=bel[l]*block;i++){
            a[i]=(a[i]*mul[bel[l]]+add[bel[l]])%mod;
        }
        add[bel[l]]=0;
        mul[bel[l]]=1;
        //暴力
        for(int i=l;i<=bel[l]*block;i++){
            a[i]=(a[i]+w)%mod;
        }
        //右边部分块
        for(int i=(bel[r]-1)*block+1;i<=bel[r]*block;i++){
            a[i]=(a[i]*mul[bel[r]]+add[bel[r]])%mod;
        }
        add[bel[r]]=0;
        mul[bel[r]]=1;
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            a[i]=(a[i]+w)%mod;
        }
        //中间整块
        for(int i=bel[l]+1;i<bel[r];i++){
            add[i]=(add[i]+w)%mod;
        }
    }
}
void Mul(int l,int r,int w){
    if(bel[l]==bel[r]){
        //同一块的，先加上标记
        for(int i=(bel[l]-1)*block+1;i<=bel[l]*block;i++){
            a[i]=(a[i]*mul[bel[l]]+add[bel[l]])%mod;
        }
        add[bel[l]]=0;
        mul[bel[l]]=1;
        //再暴力更新
        for(int i=l;i<=r;i++){
            a[i]=(a[i]*w)%mod;
        }
    }else{
        //左边部分块，标记
        for(int i=(bel[l]-1)*block+1;i<=bel[l]*block;i++){
            a[i]=(a[i]*mul[bel[l]]+add[bel[l]])%mod;
        }
        add[bel[l]]=0;
        mul[bel[l]]=1;
        //暴力
        for(int i=l;i<=bel[l]*block;i++){
            a[i]=(a[i]*w)%mod;
        }
        //右边部分块
        for(int i=(bel[r]-1)*block+1;i<=bel[r]*block;i++){
            a[i]=(a[i]*mul[bel[r]]+add[bel[r]])%mod;
        }
        add[bel[r]]=0;
        mul[bel[r]]=1;
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            a[i]=(a[i]*w)%mod;
        }
        //中间整块
        for(int i=bel[l]+1;i<bel[r];i++){
            add[i]=(add[i]*w)%mod;
            mul[i]=(mul[i]*w)%mod;
        }
    }
}
int main(void){
    scanf("%d",&n);
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        bel[i]=(i-1)/block+1;
        mul[i]=1;
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&o,&l,&r,&c);
        if(o==0){
            Add(l,r,c);
        }else if(o==1){
            Mul(l,r,c);
        }else{
            printf("%d\n",(a[r]*mul[bel[r]]+add[bel[r]])%mod);
        }
    }
    return 0;
}
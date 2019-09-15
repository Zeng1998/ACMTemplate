#include <bits/stdc++.h>
using namespace std;
#define ls i<<1
#define rs i<<1|1
#define mid (l+r)/2
typedef long long ll;
const ll mod=1e9+9;
const int N=3e5+50;
int n,m,o,l,r;
ll a[N];
ll sum[N*4];
//维护区间前两个位置的系数
int la[N*4],lb[N*4];
ll f[N];
//计算f[k]
ll calc(ll a,ll b,int k){
    if(k==1){
        return a;
    }else if(k==2){
        return b;
    }else{
        return (a*f[k-2]%mod+b*f[k-1]%mod)%mod;
    }
}
//计算f[i]前缀和
ll get(ll a,ll b,int k){
    if(k==1){
        return a;
    }else if(k==2){
        return (a+b)%mod;
    }else{
        //f[i]前缀和等于h[k+2]-h[2]
        return (calc(a,b,k+2)-b+mod)%mod;
    }
}
void pushup(int i){
    sum[i]=(sum[ls]+sum[rs])%mod;
}
void build(int i,int l,int r){
    la[i]=0;
    lb[i]=0;
    if(l==r){
        sum[i]=a[l];
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(i);
}
void pushdown(int i,int l,int r){
    if(la[i]){
        //左儿子的前两项等同于父节点前两项
        la[ls]=(la[ls]+la[i])%mod;
        lb[ls]=(lb[ls]+lb[i])%mod;
        sum[ls]=(sum[ls]+get(la[i],lb[i],mid-l+1))%mod;
        //右儿子不等，计算右儿子的前两项
        ll ta=calc(la[i],lb[i],mid-l+1+1);
        ll tb=calc(la[i],lb[i],mid-l+1+2);
        la[rs]=(la[rs]+ta)%mod;
        lb[rs]=(lb[rs]+tb)%mod;
        sum[rs]=(sum[rs]+get(ta,tb,r-mid))%mod;
        la[i]=0;
        lb[i]=0;
    }
}
void update(int i,int l,int r,int ql,int qr){
    if(ql<=l && qr>=r){
        //线段树节点区间(不是更新区间)f序列前两项
        ll ta=f[l-ql+1];
        ll tb=f[l-ql+2];
        la[i]=(la[i]+ta)%mod;
        lb[i]=(lb[i]+tb)%mod;
        sum[i]=(sum[i]+get(ta,tb,r-l+1))%mod;
        return;
    }
    pushdown(i,l,r);
    if(ql<=mid){
        update(ls,l,mid,ql,qr);
    }
    if(qr>mid){
        update(rs,mid+1,r,ql,qr);
    }
    pushup(i);
}
ll query(int i,int l,int r,int ql,int qr){
    if(ql<=l && qr>=r){
        return sum[i]%mod;
    }
    ll ans=0;
    pushdown(i,l,r);
    if(ql<=mid){
        ans=(ans+query(ls,l,mid,ql,qr))%mod;
    }
    if(qr>mid){
        ans=(ans+query(rs,mid+1,r,ql,qr))%mod;
    }
    return ans%mod;
}
int main(void){
    // freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    //先预处理出1 1开头的斐波那契数列，对于任意斐波那契数列，记录前两项，就能O(1)推出第k项，而第k项减1就是第k-2项的前缀和
    f[1]=1ll;
    f[2]=1ll;
    for(int i=3;i<=n+2;i++){
        f[i]=(f[i-1]+f[i-2])%mod;
    }
    build(1,1,n);
    while(m--){
        scanf("%d%d%d",&o,&l,&r);
        if(o==1){
            update(1,1,n,l,r);
        }else{
            printf("%lld\n",query(1,1,n,l,r));
        }
    }
    return 0;
}

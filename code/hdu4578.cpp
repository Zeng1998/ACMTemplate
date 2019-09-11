#include <bits/stdc++.h>
using namespace std;
#define ls i<<1
#define rs i<<1|1
#define mid (l+r)/2
typedef long long ll;
const int N=1e5+50;
const ll mod=10007;
ll st[N*4],ad[N*4],mu[N*4],sum[N*4][4];
int n,m,o,x,y,c;
void pushup(int i){
    for(int j=1;j<=3;j++){
        sum[i][j]=(sum[ls][j]+sum[rs][j])%mod;
    }
}
void build(int i,int l,int r){
    st[i]=ad[i]=0;
    mu[i]=1ll;
    if(l==r){
        for(int j=1;j<=3;j++){
            sum[i][j]=0;
        }
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(i);
}
void funSet(int i,int l,int r,ll v){
    ad[i]=0;
    mu[i]=1;
    st[i]=v;
    sum[i][3]=(v*v%mod*v%mod*(r-l+1))%mod;
    sum[i][2]=(v*v%mod*(r-l+1))%mod;
    sum[i][1]=(v*(r-l+1))%mod;
}
void funMul(int i,int l,int r,ll v){
    ad[i]=(ad[i]*v)%mod;
    mu[i]=(mu[i]*v)%mod;
    sum[i][3]=(sum[i][3]*v%mod*v%mod*v)%mod;
    sum[i][2]=(sum[i][2]*v%mod*v)%mod;
    sum[i][1]=(sum[i][1]*v)%mod;
}
void funAdd(int i,int l,int r,ll v){
    ad[i]=(ad[i]+v)%mod;
    sum[i][3]=(sum[i][3]+v*v%mod*v%mod*(r-l+1)%mod
              +3ll*sum[i][2]%mod*v%mod+3ll*sum[i][1]%mod*v%mod*v%mod)%mod;
    sum[i][2]=(sum[i][2]+v*v%mod*(r-l+1)%mod+2ll*sum[i][1]%mod*v%mod)%mod;
    sum[i][1]=(sum[i][1]+v*(r-l+1))%mod;
}
void pushdown(int i,int l,int r){
    if(st[i]){
        funSet(ls,l,mid,st[i]);
        funSet(rs,mid+1,r,st[i]);
        st[i]=0;
    }
    if(mu[i]!=1){
        funMul(ls,l,mid,mu[i]);
        funMul(rs,mid+1,r,mu[i]);
        mu[i]=1;
    }
    if(ad[i]){
        funAdd(ls,l,mid,ad[i]);
        funAdd(rs,mid+1,r,ad[i]);
        ad[i]=0;
    }
}
void update(int i,int l,int r,int ql,int qr,int o,ll v){
    if(ql<=l && qr>=r){
        v%=mod;
        if(o==1){
            funAdd(i,l,r,v);
        }else if(o==2){
            funMul(i,l,r,v);
        }else if(o==3){
            funSet(i,l,r,v);
        }
        return;
    }
    pushdown(i,l,r);
    if(ql<=mid){
        update(ls,l,mid,ql,qr,o,v);
    }
    if(qr>mid){
        update(rs,mid+1,r,ql,qr,o,v);
    }
    pushup(i);
}
ll query(int i,int l,int r,int ql,int qr,int p){
    if(ql<=l && qr>=r){
        return sum[i][p]%mod;
    }
    pushdown(i,l,r);
    ll ans=0;
    if(ql<=mid){
        ans=(ans+query(ls,l,mid,ql,qr,p))%mod;
    }
    if(qr>mid){
        ans=(ans+query(rs,mid+1,r,ql,qr,p))%mod;
    }
    return ans%mod;
}
int main(){
    while(~scanf("%d%d",&n,&m) && n+m){
        build(1,1,n);
        for(int i=0;i<m;i++){
            scanf("%d%d%d%d",&o,&x,&y,&c);
            if(o==4){
                ll ans=query(1,1,n,x,y,c);
                printf("%lld\n",ans%mod);
            }else{
                update(1,1,n,x,y,o,ll(c));
            }
        }
    }
    return 0;
}

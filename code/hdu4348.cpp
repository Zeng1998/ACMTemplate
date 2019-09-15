#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+50;
int n,m,tr[N],tim,l,r,t;
char q[5];
ll a[N],v;
struct HJT{
#define mid (l+r)/2
    int tot,ls[N*50],rs[N*50];
    ll sum[N*50],lz[N*50];
    void init(){
        tot=0;
    }
    //普通线段树的操作是update递归到下一层之前先把lz标记下放
    //而标记永久化是不下放，而是等pushup回溯再加上当前层的lz
    void pushup(int i,int l,int r){
        sum[i]=sum[ls[i]]+sum[rs[i]]+lz[i]*(r-l+1);
    }
    void build(int &rt,int l,int r){
        rt=++tot;
        ls[rt]=rs[rt]=lz[rt]=0;
        if(l==r){
            sum[rt]=a[l];
            return;
        }
        build(ls[rt],l,mid);
        build(rs[rt],mid+1,r);
        pushup(rt,l,r);
    }
    void update(int &rt,int pre,int l,int r,int ql,int qr,ll v){
        rt=++tot;
        ls[rt]=ls[pre];
        rs[rt]=rs[pre];
        lz[rt]=lz[pre];
        sum[rt]=sum[pre];
        if(ql<=l && qr>=r){
            lz[rt]+=v;
            sum[rt]+=v*(r-l+1);
            return;
        }
        if(ql<=mid){
            update(ls[rt],ls[pre],l,mid,ql,qr,v);
        }
        if(qr>mid){
            update(rs[rt],rs[pre],mid+1,r,ql,qr,v);
        }
        pushup(rt,l,r);
    }
    ll query(int rt,int l,int r,int ql,int qr,ll add){
        if(ql<=l && qr>=r){
            //标记永久化
            return sum[rt]+(r-l+1)*add;
        }
        ll ans=0;
        if(ql<=mid){
            ans+=query(ls[rt],l,mid,ql,qr,add+lz[rt]);
        }
        if(qr>mid){
            ans+=query(rs[rt],mid+1,r,ql,qr,add+lz[rt]);
        }
        return ans;
    }
}ac;
int main(){
    // freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    ac.init();
    tim=0;
    ac.build(tr[0],1,n);
    while(m--){
        scanf("%s",q);
        if(q[0]=='C'){
            scanf("%d%d%lld",&l,&r,&v);
            tim++;
            ac.update(tr[tim],tr[tim-1],1,n,l,r,v);
        }else if(q[0]=='H'){
            scanf("%d%d%d",&l,&r,&t);
            printf("%lld\n",ac.query(tr[t],1,n,l,r,0));
        }else if(q[0]=='Q'){
            scanf("%d%d",&l,&r);
            printf("%lld\n",ac.query(tr[tim],1,n,l,r,0));
        }else if(q[0]=='B'){
            scanf("%d",&tim);
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N=2e5+150;
int n,m,a[N],b[N];
int o,l,r,xi,yi;
int x[N],y[N];
int c1,c2;
int tr[N*150];
struct HJT{
#define mid (l+r)/2
    int tot,sum[N*150],ls[N*150],rs[N*150];
    void update(int& rt,int l,int r,int v,int add){
        //因为b数组有0值，在查询时0不算
        if(!v){
            return;
        }
        if(!rt){
            rt=++tot;
        }
        sum[rt]+=add;
        if(l<r){
            if(v<=mid){
                update(ls[rt],l,mid,v,add);
            }else{
                update(rs[rt],mid+1,r,v,add);
            }
        }
    }
    //区间[l,r]值域在[1,k]的个数
    int query(int l,int r,int k){
        if(k==0){
            return 0;
        }
        if(r<=k){
            int ans=0;
            for(int i=1;i<=c1;i++){
                ans-=sum[x[i]];
            }
            for(int i=1;i<=c2;i++){
                ans+=sum[y[i]];
            }
            return ans;
        }
        if(k<=mid){
            for(int i=1;i<=c1;i++){
                x[i]=ls[x[i]];
            }
            for(int i=1;i<=c2;i++){
                y[i]=ls[y[i]];
            }
            return query(l,mid,k);
        }else{
            int ans=0;
            for(int i=1;i<=c1;i++){
                ans-=sum[ls[x[i]]];
            }
            for(int i=1;i<=c2;i++){
                ans+=sum[ls[y[i]]];
            }
            for(int i=1;i<=c1;i++){
                x[i]=rs[x[i]];
            }
            for(int i=1;i<=c2;i++){
                y[i]=rs[y[i]];
            }
            return ans+query(mid+1,r,k);
        }
    }
}ac;
struct BIT{
    int lowbit(int x){
        return x&(-x);
    }
    //修改权值线段树的bit前缀和(非连续)
    void modify(int i,int x){
        int k=b[i];
        while(i<=n){
            ac.update(tr[i],1,n,k,x);
            i+=lowbit(i);
        }
    }
    //预处理权值线段树的查询路径
    int query(int l,int r,int xi,int yi){
        c1=c2=0;
        for(int i=(l-1);i;i-=lowbit(i)){
            x[++c1]=tr[i];
        }
        for(int i=r;i;i-=lowbit(i)){
            y[++c2]=tr[i];
        }
        int R=ac.query(1,n,yi);
        c1=c2=0;
        for(int i=(l-1);i;i-=lowbit(i)){
            x[++c1]=tr[i];
        }
        for(int i=r;i;i-=lowbit(i)){
            y[++c2]=tr[i];
        }
        int L=ac.query(1,n,xi-1);
        return R-L;
    }
}bit;
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=(a[i]==a[i-1])?0:a[i];
    }
    for(int i=1;i<=n;i++){
        bit.modify(i,1);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&o,&l,&r);
        if(o==1){
            bit.modify(l,-1);
            bit.modify(l+1,-1);
            a[l]=r;
            b[l]=(a[l]==a[l-1])?0:a[l];
            b[l+1]=(a[l+1]==a[l])?0:a[l+1];
            bit.modify(l,1);
            bit.modify(l+1,1);
        }else{
            scanf("%d%d",&xi,&yi);
            int ans=bit.query(l+1,r,xi,yi);
            if(a[l]>=xi && a[l]<=yi){
                ans++;
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
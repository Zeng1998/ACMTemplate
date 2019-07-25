#include <bits/stdc++.h>
using namespace std;
#define mid (l+r)/2
const int N=2e5+50;
int n,q,a[N],l,r,k,b[N];
//空间开大，40倍
int tot,tr[N*40],sum[N*40],lr[N*40],rr[N*40];
int build(int l,int r){
    int rt=++tot;
    if(l==r){
        return rt;
    }
    lr[rt]=build(l,mid);
    rr[rt]=build(mid+1,r);
    return rt;
}
int update(int pre,int l,int r,int p,int v){
    int rt=++tot;
    //修改一个子节点，另一个连pre
    lr[rt]=lr[pre];
    rr[rt]=rr[pre];
    sum[rt]=sum[pre]+v;
    if(l<r){
        if(p<=mid){
            lr[rt]=update(lr[pre],l,mid,p,v);
        }else{
            rr[rt]=update(rr[pre],mid+1,r,p,v);
        }
    }
    return rt;
}
//查询区间[u,v]第k大/小，l,r是线段的范围
int query(int u,int v,int l,int r,int k){
    if(l>=r){
        return l;
    }
    //左子树大小(左子树对应区间数的个数)
    int le=sum[lr[v]]-sum[lr[u]];
    if(k<=le){
        return query(lr[u],lr[v],l,mid,k);
    }else{
        return query(rr[u],rr[v],mid+1,r,k-le);
    }
}
int main(void){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    //离散化
    sort(b+1,b+1+n);
    int m=unique(b+1,b+1+n)-b-1;
    tr[0]=build(1,m);
    for(int i=1;i<=n;i++){
        int k=lower_bound(b+1,b+1+m,a[i])-b;
        tr[i]=update(tr[i-1],1,m,k,1);
    }
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&l,&r,&k);
        int ans=query(tr[l-1],tr[r],1,m,k);
        printf("%d\n",b[ans]);
    }
    return 0;
}

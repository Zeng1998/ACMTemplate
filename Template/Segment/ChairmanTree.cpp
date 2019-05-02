#include <bits/stdc++.h>
using namespace std;
const int N=1e6+50;
//记录多少个根
int cnt;
//左右子树根的编号(不再是i<<1和i<<1|1)
int lr[4*N],rr[4*N];
//(权值线段树)sum[rt]表示根为rt的树值为[1,m]的数有多少个
int sum[4*N];
//建树，返回根节点编号
int build(int l,int r){
    int rt=++cnt;
    sum[rt]=0;
    if(l<r){
        int mid=(l+r)/2;
        lr[rt]=build(l,mid);
        rr[rt]=build(mid+1,r);
    }
    return rt;
}
//插入一个节点(一颗新树)
//pre: 上一个线段树的根
//l,r: 线段树区间范围
//x: 插入的值
int update(int pre,int l,int r,int x){
    int rt=++cnt;
    lr[rt]=lr[pre]; 
    rr[rt]=rr[pre];
    //比上一时刻的树多了一个数x，所以sum+1
    sum[rt]=sum[pre]+1;
    //递归下去，只修改一条链
    if(l<r){
        int mid=(l+r)/2;
        if(x<=mid){
            lr[rt]=update(lr[pre], l, mid, x);
        }else{
            rr[rt]=update(rr[pre], mid+1, r, x);
        }
    }
    return rt;
}
//查询区间[u,v]第k大/小，注意这里l,r是根线段的范围
int query(int u,int v,int l,int r,int k){
    //递归边界
    if(l>=r){
        return l;
    }
    int x=sum[lr[v]]-sum[lr[u]];
    int mid=(l+r)/2;
    //同全局第k大/小，注意两颗线段树要同时走左子树或右子树，保证结构相同才能前缀和
    if(k<=x){
        return query(lr[u], lr[v], l, mid, k);
    }else{
        return query(rr[u], rr[v], mid+1, r, k-x);
    }
}
int n,q,l,r,k;
int a[N],b[N],tr[N];
int main(void){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    int m=unique(b+1,b+1+n)-b-1;
    //tr[i]保存每个时刻线段树的根，tr[0]为空树
    tr[0]=build(1,m);
    for(int i=1;i<=n;i++){
        int t=lower_bound(b+1,b+1+m,a[i])-b;
        tr[i]=update(tr[i-1],1,m,t);
    }
    while(q--){
        scanf("%d%d%d",&l,&r,&k);
        //前缀和的思想，查询两颗树之间的第k大
        int t=query(tr[l-1],tr[r],1,m,k);
        printf("%d\n",b[t]);
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define lson i<<1
#define rson i<<1|1
#define mid (l+r)/2
const int N=1e5+50;
vector<int> g[N];
int ans;
int a[N],b[N],n,m,u,v;
//动态开点权值线段树
int cnt,sum[N*40],ls[N*40],rs[N*40];
//两个线段树，维护节点对应(值域)区间的lis/lds最大值
//比如节点[1,4]维护的就是1的某个子孙节点到1，2的某个子孙节点到2...4的某个子孙节点到4这4个lis/lds中的最大值
int lis[N*40],lds[N*40];
int rt[N];
//now: 当前节点
//l,r: 权值线段树范围
//x: 要插入的值
//a: 本题中区别维护的是LIS还是LDS
//c: 要插入的这个权值对应的权值(lis/lds长度)
//不同于主席树，权值线段树合并是每个根节点rt[i]一个完全的线段树，然后再合并
void insert(int &now,int l,int r,int x,int c,int *a){
    //动态开点
    if(!now){
        now=++cnt;
    }
    //lis/lds即维护最大值
    a[now]=max(a[now],c);
    if(l==r){
        return;
    }
    if(x<=mid){
        insert(ls[now],l,mid,x,c,a);
    }else{
        insert(rs[now],mid+1,r,x,c,a);
    }
}
//权值线段树合并
int merge(int a,int b){
    if(!a){
        return b;
    }
    if(!b){
        return a;
    }
    lis[a]=max(lis[a],lis[b]);
    lds[a]=max(lds[a],lds[b]);
    //更新全局答案
    ans=max(ans,max(lis[ls[a]]+lds[rs[b]],lds[rs[a]]+lis[ls[b]]));
    ls[a]=merge(ls[a],ls[b]); rs[a]=merge(rs[a],rs[b]);
    return a;
}
//权值线段树查询最值(lis或lds)
//查询now(rt[v])对应权值线段树权值为[ql,qr]之间的a数组最大值
//即查询以v(u的子节点)结尾，所对应子树权值为[ql,qr]之间的lis或lds，和u的权值结合成一个新的lis或lds
int query(int now,int l,int r,int ql,int qr,int *a){
    //因为是动态开点，递归到不存在的节点直接返回
    if(!now){
        return 0;
    }
    if(ql<=l && qr>=r){
        return a[now];
    }
    if(qr<=mid){
        return query(ls[now],l,mid,ql,qr,a);
    }
    if(ql>mid){
        return query(rs[now],mid+1,r,ql,qr,a);
    }
    return max(query(ls[now],l,mid,ql,mid,a),query(rs[now],mid+1,r,mid+1,qr,a));
}
void dfs(int u,int f){
    int mlis=0,mlds=0;
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i];
        if(v==f){
            continue;
        }
        dfs(v,u);
        //对于u，先递归查询每个子链，再依次合并
        //这里就是查询从v的子孙节点到v路径上值域为[1,a[u]-1]的lis长度
        int ilis=query(rt[v],1,m,1,a[u]-1,lis);
        //同理
        int ilds=query(rt[v],1,m,a[u]+1,m,lds);
        //合并权值线段树
        rt[u]=merge(rt[u],rt[v]);
        //更新全局答案
        ans=max(ans,max(ilis+mlds,ilds+mlis)+1);
        //更新u节点暂时的值(从u的子孙节点到u路径上，以u结尾)
        mlis=max(mlis,ilis);
        mlds=max(mlds,ilds);
    }
    //节点u对应的一颗权值线段树，从u的某个子孙节点到u路径上某个值域区间的lis/lds长度
    insert(rt[u],1,m,a[u],mlis+1,lis);
    insert(rt[u],1,m,a[u],mlds+1,lds);
}
int main(void){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    m=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+m,a[i])-b;
    }
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    printf("%d\n",ans);
    return 0;
}

/**
 * 权值线段树可以求全局第k大，而主席树就是可持久化权值线段树，
 * 因此可以求区间第k大，以及由此延伸出的各种应用
 * 1. 静态区间第k大
 * 2. 区间内在某个范围数的个数
 * 3. 区间内不同数的个数
 */
#include <bits/stdc++.h>
using namespace std;
#define mid (l+r)/2
const int N=1e6+50;
//记录多少个根，每棵树根的编号
int cnt,tr[N];
//左右子树根的编号(不再是i<<1和i<<1|1)
int lr[40*N],rr[40*N];
//普通权值线段树sum[i]保存的就是值在[le[i],ri[i]]之间的数的个数
//同理,主席树保存到就是值在[le[i],ri[i]]之间数的个数,但是由于静态主席树每棵树的结构都是一样的
int sum[40*N];
//建树，返回根节点编号
int build(int l,int r){
    int rt=++cnt;
    sum[rt]=0;
    if(l==r){
        return rt;
    }
    lr[rt]=build(l,mid);
    rr[rt]=build(mid+1,r);
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
        if(x<=mid){
            lr[rt]=update(lr[pre], l, mid, x);
        }else{
            rr[rt]=update(rr[pre], mid+1, r, x);
        }
    }
    return rt;
}
//查询区间[u,v]第k大/小，注意这里l,r是线段的范围
int query(int u,int v,int l,int r,int k){
    //递归边界
    if(l>=r){
        return l;
    }
    //相减就是左子树大小(左子树对应区间数的个数)
    int x=sum[lr[v]]-sum[lr[u]];
    //同全局第k大/小，注意两颗线段树要同时走左子树或右子树，保证结构相同才能前缀和
    if(k<=x){
        return query(lr[u], lr[v], l, mid, k);
    }else{
        return query(rr[u], rr[v], mid+1, r, k-x);
    }
}
//查询主席树区间[u,v]在线段树区间[l,r]值在区间[x,y]的个数
int query(int u,int v,int l,int r,int x,int y){
    if(x>y){
        return 0;
    }
    //整个区间的数都满足条件
    if(x<=l && r<=y){
        return sum[v]-sum[u];
    }
    int ans=0;
    if(x<=mid){
        ans+=query(lr[u],lr[v],l,mid,x,y);
    }
    if(y>mid){
        ans+=query(rr[u],rr[v],mid+1,r,x,y);
    }
    return ans;
}

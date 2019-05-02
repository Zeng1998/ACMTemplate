/*
 * 莫队是一种基于分块思想的离线算法，用于解决区间问题，适用范围如下：
 * 0. 只有询问没有修改。
 * 1. 允许离线。
 * 2. 在已知[l,r]答案的情况下可以O(1)得到[l,r−1],[l,r+1],[l−1,r],[l+1,r]的答案。
 * 
 * 有n个不同颜色的袜子，多个询问在区间[l,r]里随机抽两个袜子，同一颜色的概率是多少
 * 对区间长度为n的询问来说，答案为(sum(ai^2)-n)/n*(n-1)，其中ai为颜色i在区间内的个数
 * 分母n*(n-1)表示抽的所有可能情况(第一只有n种选择，第二只有n-1种)
 * 分子同理为sum(ai*(ai-1))=sum(ai^2)-sum(ai)=sum(ai^2)-n
 */ 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e4+50;
int pw(int x){
    return x*x;
}
int n,m;
int be[N];
ll a[N],sum[N];
struct Q{
    int id,l,r;
    ll zi,mu;
}q[N];
bool cmp1(Q a,Q b){
    //左端点同块按右端点排序，否则按左端点排序
    return be[a.l]==be[b.l]?a.l<b.l:a.r<b.r;
}
bool cmp2(Q a,Q b){
    return a.id<b.id;
}
int ans;
//查询的答案就是(sum(ai^2)-n)/(n(n-1))
void fun(int i,int x){
    //更新分子sum(ai^2)部分
    ans-=pw(sum[a[i]]);
    sum[a[i]]+=x;
    ans+=pw(sum[a[i]]);
}
int main(void){
    scanf("%d%d",&n,&m);
    int unit=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        //分块
        be[i]=i/unit+1;
    }
    for(int i=0;i<m;i++){
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].id=i;
    }
    //对查询的区间预处理排序
    sort(q,q+m,cmp1);
    //上一次查询的区间
    int l=1,r=0;
    for(int i=0;i<m;i++){
        //左端点移动到当前查询区间左端点，同时更新答案
        while(l<q[i].l){
            fun(l,-1);
            l++;
        }
        //以下同理，但要注意边界问题l l-1 r+1 r
        while(l>q[i].l){
            fun(l-1,1);
            l--;
        }
        while(r<q[i].r){
            fun(r+1,1);
            r++;
        }
        while(r>q[i].r){
            fun(r,-1);
            r--;
        }
        //统计答案
        ll len=(q[i].r-q[i].l+1)*1LL;
        q[i].zi=ans-len;
        q[i].mu=len*(len-1);
        ll g=__gcd(q[i].zi,q[i].mu);
        q[i].zi/=g;
        q[i].mu/=g;
    }
    sort(q,q+m,cmp2);
    for(int i=0;i<m;i++){
        printf("%lld/%lld\n",q[i].zi,q[i].mu);
    }
    return 0;
}
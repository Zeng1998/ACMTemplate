#include <bits/stdc++.h>
using namespace std;
const int N=2e5+50;
int n,m,nx,a[N];
//用bit维护权值线段树，因此查询区间[l,r]不再是直接查询tr[l-1]到tr[r]
//因为bit维护的前缀和是不连续的前缀和，所以要先预处理出查询路径
int x[N],y[N];
int c1,c2;
struct Orz{
    vector<int> a;
    void init(){
        a.clear();
    }
    int siz(){
        return a.size();
    }
    void add(int x){
        a.push_back(x);
    }
    void work(){
        sort(a.begin(),a.end());
        a.erase(unique(a.begin(),a.end()),a.end());
    }
    int idx(int v){
        return lower_bound(a.begin(),a.end(),v)-a.begin()+1;
    }
    int val(int i){
        return a[i-1];
    }
}orz;
int tr[N*100];
struct HJT{
#define mid (l+r)/2
    int tot,sum[N*100],ls[N*100],rs[N*100];
    //动态开点权值线段树
    void update(int& rt,int l,int r,int v,int add){
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
    //查询区间第k大
    int query(int l,int r,int k){
        if(l>=r){
            return l;
        }
        //普通的主席树是直接前缀和做差求区间sum
        //这里要根据bit预处理出来的子树路径计算sum
        int ans=0;
        for(int i=1;i<=c1;i++){
            ans-=sum[ls[x[i]]];
        }
        for(int i=1;i<=c2;i++){
            ans+=sum[ls[y[i]]];
        }
        if(k<=ans){
            for(int i=1;i<=c1;i++){
                x[i]=ls[x[i]];
            }
            for(int i=1;i<=c2;i++){
                y[i]=ls[y[i]];
            }
            return query(l,mid,k);
        }else{
            for(int i=1;i<=c1;i++){
                x[i]=rs[x[i]];
            }
            for(int i=1;i<=c2;i++){
                y[i]=rs[y[i]];
            }
            return query(mid+1,r,k-ans);
        }
    }
}ac;
struct BIT{
    int lowbit(int x){
        return x&(-x);
    }
    //修改权值线段树的bit前缀和(非连续)
    void modify(int i,int x){
        int k=orz.idx(a[i]);
        while(i<=n){
            ac.update(tr[i],1,nx,k,x);
            i+=lowbit(i);
        }
    }
    //预处理权值线段树的查询路径
    int query(int l,int r,int k){
        c1=c2=0;
        for(int i=(l-1);i;i-=lowbit(i)){
            x[++c1]=tr[i];
        }
        for(int i=r;i;i-=lowbit(i)){
            y[++c2]=tr[i];
        }
        return ac.query(1,nx,k);
    }
}bit;
struct Query{
    int o,l,r,k;
}q[N];
char op[5];
int main(){
    scanf("%d%d",&n,&m);
    orz.init();
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        orz.add(a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%s",op);
        scanf("%d%d",&q[i].l,&q[i].r);
        if(op[0]=='Q'){
            q[i].o=1;
            scanf("%d",&q[i].k);
        }else{
            orz.add(q[i].r);
        }
    }
    orz.work();
    nx=orz.siz();
    for(int i=1;i<=n;i++){
        bit.modify(i,1);
    }
    for(int i=1;i<=m;i++){
        if(q[i].o==1){
            printf("%d\n",orz.val(bit.query(q[i].l,q[i].r,q[i].k)));
        }else{
            bit.modify(q[i].l,-1);
            a[q[i].l]=q[i].r;
            bit.modify(q[i].l,1);
        }
    }
    return 0;
}
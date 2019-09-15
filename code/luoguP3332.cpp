#include <bits/stdc++.h>
using namespace std;
#define mid (l+r)/2
const int N=1e5+50;
typedef long long ll;
int n,m,ns;
struct Q{
    int o,a,b;
    ll c;
}q[N];
struct Orz{
    //离散化
}orz;
//内层的普通线段树，维护外层值域区间为[L,R]的数在位置区间[l,r]的个数
struct ST{
    int tot,ls[N*200],rs[N*200];;
    ll sum[N*200],lz[N*200];
    void update(int &i,int l,int r,int ql,int qr,int v){
        if(!i){
            i=++tot;
        }
        //标记永久化
        sum[i]+=min(qr,r)-max(ql,l)+1;
        if(ql<=l && qr>=r){
            lz[i]+=v;
            return;
        }
        if(ql<=mid){
            update(ls[i],l,mid,ql,qr,v);
        }
        if(qr>mid){
            update(rs[i],mid+1,r,ql,qr,v);
        }
    }
    ll query(int i,int l,int r,int ql,int qr,int add=0){
        if(!i){
            //有上面带下来的标记，不能返回0
            return (min(qr,r)-max(ql,l)+1)*add;
        }
        if(ql<=l && qr>=r){
            return sum[i]+add*(r-l+1);
        }
        ll ans=0;
        if(ql<=mid){
            ans+=query(ls[i],l,mid,ql,qr,add+lz[i]);
        }
        if(qr>mid){
            ans+=query(rs[i],mid+1,r,ql,qr,add+lz[i]);
        }
        return ans;
    }
}st;
//外层的权值线段树
struct VST{
#define ls i<<1
#define rs i<<1|1
    int tr[N*4];
    //当前vst值域范围为[l,r]，更新值v对应的线段树区间[ql,qr]，即加上v这个数
    void update(int i,int l,int r,int ql,int qr,int v){
        //该值域区间[l,r]所对应的线段树的区间[ql,qr]所维护的数字个数加1
        st.update(tr[i],1,n,ql,qr,1);
        if(l==r){
            return;
        }
        if(v<=mid){
            update(ls,l,mid,ql,qr,v);
        }else{
            update(rs,mid+1,r,ql,qr,v);
        }
    }
    //查询区间[ql,qr]值域[l,r]的第k大!
    int query(int i,int l,int r,int ql,int qr,ll k){
        if(l==r){
            return l;
        }
        //区间[ql,qr]左边值域对应数的个数
        ll sum=st.query(tr[rs],1,n,ql,qr);
        if(k<=sum){
            return query(rs,mid+1,r,ql,qr,k);
        }else{
            return query(ls,l,mid,ql,qr,k-sum);
        }
    }
}vst;
int main(){
//    freopen("in.txt","r",stdin);
   scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
       scanf("%d%d%d%lld",&q[i].o,&q[i].a,&q[i].b,&q[i].c);
        if(q[i].o==1){
            orz.add(q[i].c);
        }
    }
    orz.work();
    ns=orz.siz();
    for(int i=1;i<=m;i++){
        if(q[i].o==1){
            q[i].c=orz.idx(q[i].c);
        }
    }
    for(int i=1;i<=m;i++){
        if(q[i].o==1){
            vst.update(1,1,ns,q[i].a,q[i].b,q[i].c);
        }else{
            printf("%lld\n",orz.val(vst.query(1,1,ns,q[i].a,q[i].b,q[i].c)));
        }
    }
    return 0;
}

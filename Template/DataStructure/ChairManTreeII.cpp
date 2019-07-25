#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mid (l+r)/2
const int N=60005;
int a[N], b[N];
int tr[N], lr[N<<5], rr[N<<5], c[N<<5];
int ctr[N];
int m,cnt,T,n,q;
char s[10];
struct que{
    int l,r,k;
    bool Q;
}Q[10005];
int build(int l,int r){
    int rt=++cnt;
    c[rt]=0;
    if(l==r){
        return rt;
    }
    lr[rt]=build(l,mid);
    rr[rt]=build(mid+1,r);
    return rt;
}
int update(int pre,int l,int r,int p,int v){
    int rt=++cnt;
    lr[rt]=lr[pre];
    rr[rt]=rr[pre];
    c[rt]=c[pre]+v;
    if(l<r){
        if(p<=mid){
            lr[rt]=update(lr[pre],l,mid,p,v);
        }else{
            rr[rt]=update(rr[pre],mid+1,r,p,v);
        }
    }
    return rt;
}
int lowbit(int x){
    return x&(-x);
}
void add(int i, int p, int v){
    while(i<=n){
        //比如修改第一个值 实际上就只有序号为1 2 4的根修改了
        ctr[i]=update(ctr[i],1,m,p,v);
        i+=lowbit(i);
    }
}
//查询
int use[N];
int sum(int i){
    int ans=0;
    while(i>0){
        //i是根序号 use[i]是根标号
        //因为是跟前缀和有关，所以往左子树搜
        ans+=c[lr[use[i]]];
        i-=lowbit(i);
    }
    return ans;
}
//根的标号和根的序号不同，bit中使用的是根的序号也就是加入的顺序
//而主席树查询用的是根的标号，也就是节点标号
//u,v: 根的标号  lrr,rrr: 根的序号
int query(int u,int v,int lrr,int rrr,int l,int r,int k){
    if(l>=r){
        return l;
    }
    //左子树大小，比静态主席树多了sum(rrr)-sum(lrr)
    //因为加了bit，此时的c[lr[v]]-c[lr[u]]已经不再是左子树大小
    //需要加上bit对这段区间的查询值sum(rrr)-sum(lrr)
    int tmp=sum(rrr)-sum(lrr)+c[lr[v]]-c[lr[u]];
    if(tmp>=k){
        //记录bit查询跳转时候使用的节点，即查询路径
        for(int i=lrr;i>0;i-=lowbit(i)){
            use[i]=lr[use[i]];
        }
        for(int i=rrr;i>0;i-=lowbit(i)){
            use[i]=lr[use[i]];
        }
        //递归查询
        return query(lr[u],lr[v],lrr,rrr,l,mid,k);
    }else{
        for(int i=lrr;i;i-=lowbit(i)){
            use[i]=rr[use[i]];
        }
        for(int i=rrr;i;i-=lowbit(i)){
            use[i]=rr[use[i]];
        }
        return query(rr[u],rr[v],lrr,rrr,mid+1,r,k-tmp);
    }
}
int main(){
    
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&q);
        cnt=0;
        m=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            b[m++]=a[i];
        }
        for(int i=0;i<q;i++){
            scanf("%s",s);
            if(s[0]=='Q'){
                scanf("%d%d%d", &Q[i].l, &Q[i].r, &Q[i].k);
                Q[i].Q=true;
            }
            else{
                scanf("%d%d", &Q[i].l, &Q[i].r);
                Q[i].Q=false;
                b[m++]=Q[i].r;
            }
        }
        //离散化建树
        sort(b,b+m);
        m=unique(b+1,b+1+m)-b;
        tr[0]=build(1,m);
        for(int i=1;i<=n;i++){
            int k=lower_bound(b,b+m,a[i])-b;
            tr[i]=update(tr[i-1],1,m,k,1);
        }
        //初始化树状数组
        for(int i=1;i<=n;i++){
            ctr[i]=tr[0];
        }
        for(int i=0;i<q;i++){
            if(Q[i].Q){
                for(int j=Q[i].l-1;j;j-=lowbit(j))
                    use[j]=ctr[j];
                for(int j=Q[i].r;j;j-=lowbit(j))
                    use[j]=ctr[j];
                //普通主席树查询操作，离散化映射
                printf("%d\n", b[query(tr[Q[i].l-1],tr[Q[i].r],Q[i].l-1,Q[i].r,1,m,Q[i].k)]);
            }else{
                //将a[que[i].l]修改为que[i].r 离散化后即将kl修改为kr
                int kl=lower_bound(b, b+m, a[Q[i].l])-b;
                int kr=lower_bound(b, b+m, Q[i].r)-b;
                //树状数组单点修改
                //普通树状数组的数组下标i改成了主席树的根，同样是修改的位置
                add(Q[i].l,kl,-1);
                add(Q[i].l,kr,1);
                //原数组也修改
                a[Q[i].l]=Q[i].r;
            }
        }
    }
    return 0;
}
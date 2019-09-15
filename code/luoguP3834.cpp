#include <bits/stdc++.h>
using namespace std;
//值域有负数的情况，用位运算除法
#define mid ((l+r)>>1)
const int N=1e6+50;
const int INF=1e9+7;
int n,m,a[N],l,r,k,ans[N];
struct Q{
    int id,l,r,k;
}q[N],L[N],R[N];
struct BIT{
    //树状数组
}bit;
//整体二分 [ql,qr]是询问范围 [l,r]是值域范围
void solve(int ql,int qr,int l,int r){
    if(ql>qr){
        return;
    }
    if(l==r){
        for(int i=ql;i<=qr;i++){
            //询问
            if(q[i].id){
                ans[q[i].id]=l;
            }
        }
        return;
    }
    int cl=0,cr=0;
    for(int i=ql;i<=qr;i++){
        if(!q[i].id){
            //插入
            if(q[i].k<=mid){
                L[++cl]=q[i];
                bit.add(q[i].l,1);
            }else{
                R[++cr]=q[i];
            }
        }else{
            //询问
            int t=bit.sum(q[i].r)-bit.sum(q[i].l-1);
            if(q[i].k<=t){
                L[++cl]=q[i];
            }else{
                q[i].k-=t;
                R[++cr]=q[i];
            }
        }
    }
    for(int i=1;i<=cl;i++){
        q[ql-1+i]=L[i];
        if(!L[i].id){
            bit.add(L[i].l,-1);
        }
    }
    for(int i=1;i<=cr;i++){
        q[ql-1+cl+i]=R[i];
    }
    solve(ql,ql+cl-1,l,mid);
    solve(ql+cl,qr,mid+1,r);
}
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        q[i]=Q{0,i,i,a[i]};
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&l,&r,&k);
        q[n+i]=Q{i,l,r,k};
    }
    solve(1,n+m,-INF,INF);
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}

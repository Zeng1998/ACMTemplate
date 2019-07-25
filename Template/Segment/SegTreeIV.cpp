/**
 * hdu1540 区间合并，查询某个点向左向右最大延伸区间
 */ 
#include <bits/stdc++.h>
using namespace std;
#define lson i<<1
#define rson i<<1|1
#define mid (l+r)/2
const int N=50050;
int lm[4*N],rm[4*N],mx[4*N];
void pushup(int i,int l,int r){
    lm[i]=lm[lson];
    rm[i]=rm[rson];
    if(lm[lson]==mid-l+1){
        lm[i]+=lm[rson];
    }
    if(rm[rson]==r-mid){
        rm[i]+=rm[lson];
    }
    mx[i]=max(max(mx[lson],mx[rson]),rm[lson]+lm[rson]);
}
//单点更新省略 void update(int i,int l,int r,int p,int c){}
int query(int i,int l,int r,int p){
    if(l==r && l==p){
        return mx[i];
    }
    if(p<=mid){
        return query(lson,l,mid,p);
    }else{
        return query(rson,mid+1,r,p);
    }
}
//查询1到x的右边区间
int queryR(int i,int l,int r,int ql,int qr){
    if(ql<=l && qr>=r){
        return rm[i];
    }
    int la=0,ra=0;
    if(ql<=mid){
        la=queryR(lson,l,mid,ql,min(mid,qr));
    }
    if(qr>mid){
        ra=queryR(rson,mid+1,r,mid+1,qr);
        if(ra==qr-mid){
            return la+ra;
        }else{
            return ra;
        }
    }else{
        return la;
    }
}
//查询x到n的左边区间
int queryL(int i,int l,int r,int ql,int qr){
    if(ql<=l && qr>=r){
        return lm[i];
    }
    int la=0,ra=0;
    if(qr>mid){
        ra=queryL(rson,mid+1,r,max(ql,mid+1),qr);
    }
    if(ql<=mid){
        la=queryL(lson,l,mid,ql,mid);
        if(la==mid-ql+1){
            return ra+la;
        }else{
            return la;
        }
    }else{
        return ra;
    }
}
int n,m,x;
char q[10];
stack<int> sta;
int main(void){
    while(~scanf("%d%d",&n,&m)){
        build(1,1,n);
        while(m--){
            scanf("%s",q);
            if(q[0]=='D'){
                scanf("%d",&x);
                sta.push(x);
                update(1,1,n,x,0);
            }else if(q[0]=='Q'){
                scanf("%d",&x);
                int ri=queryR(1,1,n,1,x);
                int le=queryL(1,1,n,x,n);
                int mm=query(1,1,n,x);
                printf("%d\n",ri+le-mm);
            }else if(q[0]=='R'){
                int las=sta.top();
                sta.pop();
                update(1,1,n,las,1);
            }
        }
    }
    return 0;
}
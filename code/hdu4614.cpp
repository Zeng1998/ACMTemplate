#include <bits/stdc++.h>
using namespace std;
#define ls i<<1
#define rs i<<1|1
#define mid (l+r)/2
const int N=5e4+50;
int sum[N*4],lz[N*4];
void pushup(int i){
    sum[i]=sum[ls]+sum[rs];
}
void build(int i,int l,int r){
    lz[i]=-1;
    if(l==r){
        sum[i]=1;
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(i);
}
void fun(int i,int l,int r,int v){
    lz[i]=v;
    sum[i]=(r-l+1)*v;
}
void pushdown(int i,int l,int r){
    if(lz[i]!=-1){
        fun(ls,l,mid,lz[i]);
        fun(rs,mid+1,r,lz[i]);
        lz[i]=-1;
    }
}
void update(int i,int l,int r,int ql,int qr,int v){
    if(ql<=l && qr>=r){
        fun(i,l,r,v);
        return;
    }
    pushdown(i,l,r);
    if(ql<=mid){
        update(ls,l,mid,ql,qr,v);
    }
    if(qr>mid){
        update(rs,mid+1,r,ql,qr,v);
    }
    pushup(i);
}
int query(int i,int l,int r,int ql,int qr){
    if(ql<=l && qr>=r){
        return sum[i];
    }
    pushdown(i,l,r);
    int ans=0;
    if(ql<=mid){
        ans+=query(ls,l,mid,ql,qr);
    }
    if(qr>mid){
        ans+=query(rs,mid+1,r,ql,qr);
    }
    return ans;
}
int T,n,m,o,l,r;
//二分从l找到第一个sum为1(空花瓶)的位置
int findL(int l){
    int L=l,R=n;
    int ans=0;
    while(L<=R){
        int md=(L+R)/2;
        if(query(1,1,n,l,md)>=1){
            ans=md;
            R=md-1;
        }else{
            L=md+1;
        }
    }
    return ans;
}
//二分从l找到第一个r使得sum(l...r)=num(从l放下连续num朵花)
int findR(int l,int num){
    int L=l,R=n;
    int ans=0;
    while(L<=R){
        int md=(L+R)/2;
        if(query(1,1,n,l,md)>=num){
            ans=md;
            R=md-1;
        }else{
            L=md+1;
        }
    }
    //不够放，从右边二分找到最后一个空花瓶
    if(!ans){
        int LL=n,RR=l;
        while(LL>=RR){
            int md=(LL+RR)/2;
            if(query(1,1,n,md,n)>=1){
                ans=md;
                RR=md+1;
            }else{
                LL=md-1;
            }
        }
    }
    return ans;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        build(1,1,n);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&o,&l,&r);
            if(o==1){
                l++;
                int L=findL(l);
                if(L==0){
                    printf("Can not put any one.\n");
                    continue;
                }
                int R=findR(L,r);
                printf("%d %d\n",L-1,R-1);
                update(1,1,n,L,R,0);
            }else if(o==2){
                l++;
                r++;
                printf("%d\n",r-l+1-query(1,1,n,l,r));
                update(1,1,n,l,r,1);
            }
        }
        printf("\n");
    }
    return 0;
}

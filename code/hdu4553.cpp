#include <bits/stdc++.h>
using namespace std;
#define ls i<<1
#define rs i<<1|1
#define mid (l+r)/2
const int N=1e5+50;
//不同线段树的区间覆盖问题，1表示空闲时间，ds占用时间只会影响ds线段树的空闲时间
//ns请求时间可以查询ds线段树，即全局空闲时间，再查询ns线段树，即被ds占用的时间
int lm[2][N*4],rm[2][N*4],mx[2][N*4],lz[2][N*4];
void pushup(int j,int i,int l,int r){
    mx[j][i]=max(max(mx[j][ls],mx[j][rs]),rm[j][ls]+lm[j][rs]);
    lm[j][i]=lm[j][ls];
    if(lm[j][i]==mid-l+1){
        lm[j][i]+=lm[j][rs];
    }
    rm[j][i]=rm[j][rs];
    if(rm[j][i]==r-mid){
        rm[j][i]+=rm[j][ls];
    }
}
void fun(int j,int i,int l,int r,int v){
    lz[j][i]=v;
    lm[j][i]=rm[j][i]=mx[j][i]=(r-l+1)*v;
}
void pushdown(int j,int i,int l,int r){
    if(lz[j][i]!=-1){
        fun(j,ls,l,mid,lz[j][i]);
        fun(j,rs,mid+1,r,lz[j][i]);
        lz[j][i]=-1;
    }
}
void build(int i,int l,int r){
    for(int j=0;j<2;j++){
        lz[j][i]=-1;
        lm[j][i]=rm[j][i]=mx[j][i]=(r-l+1);
    }
    if(l==r){
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
}
void update(int j,int i,int l,int r,int ql,int qr,int v){
    if(ql<=l && qr>=r){
        fun(j,i,l,r,v);
        return;
    }
    pushdown(j,i,l,r);
    if(ql<=mid){
        update(j,ls,l,mid,ql,qr,v);
    }
    if(qr>mid){
        update(j,rs,mid+1,r,ql,qr,v);
    }
    pushup(j,i,l,r);
}
int query(int j,int i,int l,int r,int num){
    if(l==r){
        return l;
    }
    pushdown(j,i,l,r);
    if(mx[j][ls]>=num){
        return query(j,ls,l,mid,num);
    }else{
        if(rm[j][ls]+lm[j][rs]>=num){
            return mid-rm[j][ls]+1;
        }else{
            return query(j,rs,mid+1,r,num);
        }
    }
}
int T,n,m,q,r;
char s[10];
int main(){
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        scanf("%d%d",&n,&m);
        printf("Case %d:\n",cas);
        build(1,1,n);
        for(int i=1;i<=m;i++){
            scanf("%s%d",s,&q);
            if(s[0]=='D'){
                if(mx[1][1]<q){
                    printf("fly with yourself\n");
                }else{
                    int ans=query(1,1,1,n,q);
                    //只减少ds空闲时间
                    update(1,1,1,n,ans,ans+q-1,0);
                    printf("%d,let's fly\n",ans);
                }
            }else if(s[0]=='N'){
                if(mx[1][1]<q && mx[0][1]<q){
                    printf("wait for me\n");
                }else{
                    int p;
                    if(mx[1][1]>=q){
                        //ds空闲时间足够，直接用
                        p=query(1,1,1,n,q);
                    }else{
                        //否则，用ns空闲时间，会覆盖一部分的ds时间
                        p=query(0,1,1,n,q);
                    }
                    //减少ds和ns空闲时间
                    update(0,1,1,n,p,p+q-1,0);
                    update(1,1,1,n,p,p+q-1,0);
                    printf("%d,don't put my gezi\n",p);
                }
            }else if(s[0]=='S'){
                scanf("%d",&r);
                update(0,1,1,n,q,r,1);
                update(1,1,1,n,q,r,1);
                printf("I am the hope of chinese chengxuyuan!!\n");
            }
        }
    }
    return 0;
}

/**
 * 数列分块1：区间更新，单点查询
 */ 
#include <bits/stdc++.h>
using namespace std;
const int N=5e4+50;
int a[N],bel[N],add[N];
int n,o,l,r,c;
int block;
void update(int l,int r,int c){
    //在一个区间内，暴力修改
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++){
            a[i]+=c;
        }
    }else{
        //修改两边
        for(int i=l;i<=bel[l]*block;i++){
            a[i]+=c;
        }
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            a[i]+=c;
        }
        //修改整个区间
        for(int i=bel[l]+1;i<bel[r];i++){
            add[i]+=c;
        }
    }
}
int main(void){
    scanf("%d",&n);
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        bel[i]=(i-1)/block+1;
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&o,&l,&r,&c);
        if(o==0){
            update(l,r,c);
        }else{
            printf("%d\n",a[r]+add[bel[r]]);
        }
    }
    return 0;
}
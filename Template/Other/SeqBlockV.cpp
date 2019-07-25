/**
 * 数列分块5：区间开方，区间求和
 */  
#include <bits/stdc++.h>
using namespace std;
const int N=5e4+50;
int a[N],bel[N],mx[N],w[N];
int n,block,o,l,r,c;
//区间开方更新
void update(int l,int r){
    if(bel[l]==bel[r]){
        if(mx[bel[l]]!=0 && mx[bel[l]]!=1){
            for(int i=l;i<=r;i++){
                int t=a[i]-(int)sqrt(a[i]);
                w[bel[l]]-=t;
                a[i]-=t;
            }
            //更新区间最大值,因为开方的部分区间会影响到整个区间的最大值
            //要记得从0开始，不能从原来的mx[bel[l]]开始
            mx[bel[l]]=0;
            for(int i=(bel[l]-1)*block+1;i<=bel[l]*block;i++){
                mx[bel[l]]=max(mx[bel[l]],a[i]);
            }
        }
    }else{
        if(mx[bel[l]]!=0 && mx[bel[l]]!=1){
            for(int i=l;i<=bel[l]*block;i++){
                int t=a[i]-(int)sqrt(a[i]);
                w[bel[l]]-=t;
                a[i]-=t;
            }
            mx[bel[l]]=0;
            for(int i=(bel[l]-1)*block+1;i<=bel[l]*block;i++){
                mx[bel[l]]=max(mx[bel[l]],a[i]);
            }
        }
        if(mx[bel[r]]!=0 && mx[bel[r]]!=1){
            for(int i=(bel[r]-1)*block+1;i<=r;i++){
                int t=a[i]-(int)sqrt(a[i]);
                w[bel[r]]-=t;
                a[i]-=t;
            }
            mx[bel[r]]=0;
            for(int i=(bel[r]-1)*block+1;i<=bel[r]*block;i++){
                mx[bel[r]]=max(mx[bel[r]],a[i]);
            }
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            if(mx[i]!=0 && mx[i]!=1){
                mx[i]=0;
                for(int j=(i-1)*block+1;j<=i*block;j++){
                    int t=a[j]-(int)sqrt(a[j]);
                    w[i]-=t;
                    a[j]-=t;
                    mx[i]=max(mx[i],a[j]);
                }
            }
        }
    }
}
int query(int l,int r){
    int ans=0;
    if(bel[l]==bel[r]){
        if(mx[bel[l]]!=0){
            for(int i=l;i<=r;i++){
                ans+=a[i];
            }
        }
    }else{
        for(int i=l;i<=bel[l]*block;i++){
            if(mx[bel[l]]!=0){
                ans+=a[i];
            }
        }
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            if(mx[bel[r]]!=0){
                ans+=a[i];
            }
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            ans+=w[i];
        }
    }
    return ans;
}
int main(void){
    scanf("%d",&n);
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        bel[i]=(i-1)/block+1;
        w[bel[i]]+=a[i];
        mx[bel[i]]=max(mx[bel[i]],a[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&o,&l,&r,&c);
        if(o==0){
            update(l,r);
        }else{
            printf("%d\n",query(l,r));
        }
    }
    return 0;
}
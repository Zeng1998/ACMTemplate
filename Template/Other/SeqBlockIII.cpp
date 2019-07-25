/**
 * 数列分块3：区间更新，查询区间里x的前驱
 */ 
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int a[N],b[N],add[N],bel[N];
int n,o,l,r,c;
int block;
void bsort(int x){
    int l=(x-1)*block+1;
    int r=min(l+block-1,n);
    for(int i=l;i<=r;i++){
        b[i]=a[i];
    }
    sort(b+l,b+r+1);
}
void update(int l,int r,int c){
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++){
            a[i]+=c;
        }
        bsort(bel[l]);
    }else{
        for(int i=l;i<=bel[l]*block;i++){
            a[i]+=c;
        }
        bsort(bel[l]);
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            a[i]+=c;
        }
        bsort(bel[r]);
        for(int i=bel[l]+1;i<bel[r];i++){
            add[i]+=c;
        }
    }
}
//在x块找到最接近c的最大数
int cal(int x,int c){
    int l=(x-1)*block+1;
    int r=min(l+block-1,n);
    int ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(b[mid]+add[x]<c){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return b[ans]+add[x];
}
int query(int l,int r,int c){
    int ans=-1;
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++){
            int t=a[i]+add[bel[l]];
            if(t<c && t>ans){
                ans=t;
            }
        }
    }else{
        for(int i=l;i<=bel[l]*block;i++){
            int t=a[i]+add[bel[l]];
            if(t<c && t>ans){
                ans=t;
            }
        }
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            int t=a[i]+add[bel[r]];
            if(t<c && t>ans){
                ans=t;
            }
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            int t=cal(i,c);
            if(t<c && t>ans){
                ans=t;
            }
        }
    }
    return ans;
}
int main(void){
    //b[0]设置为-1，这样找a[0]的前驱就不会找到0而是找到-1(实际上是找不到)
    b[0]=-1;
    scanf("%d",&n);
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        bel[i]=(i-1)/block+1;
    }
    int cnt=(n-1)/block+1;
    for(int i=1;i<=cnt;i++){
        bsort(i);
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&o,&l,&r,&c);
        if(o==0){
            update(l,r,c);
        }else{
            printf("%d\n",query(l,r,c));
        }
    }
    return 0;
}
/**
 * 数列分块2：区间更新，查询区间小于x的个数
 */ 
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int a[N],b[N],bel[N],add[N];
int block;
int n;
int o,l,r,c;
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
//块内具有单调性
//二分查找第x个块小于c的个数
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
    return ans?(ans-(x-1)*block):0;
}
//查询[l,r]中小于c的数的个数
int query(int l,int r,int c){
    int ans=0;
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++){
            if(a[i]+add[bel[l]]<c){
                ans++;
            }
        }
    }else{
        for(int i=l;i<=bel[l]*block;i++){
            if(a[i]+add[bel[l]]<c){
                ans++;
            }
        }
        for(int i=(bel[r]-1)*block+1;i<=r;i++){
            if(a[i]+add[bel[r]]<c){
                ans++;
            }
        }
        for(int i=bel[l]+1;i<bel[r];i++){
            ans+=cal(i,c);
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
    }
    int cnt=(n-1)/block+1;
    //每一块进行排序预处理
    for(int i=1;i<=cnt;i++){
        bsort(i);
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&o,&l,&r,&c);
        if(o==0){
            update(l,r,c);
        }else{
            printf("%d\n",query(l,r,c*c));
        }
    }
    return 0;
}
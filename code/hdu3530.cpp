#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int n,m,k,a[N];
int mxq[N],mnq[N];
int main(void){
    // freopen("in.txt","r",stdin);
    while(~scanf("%d%d%d",&n,&m,&k)){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        int l=1;
        int l1=1,r1=0;
        int l2=1,r2=0;
        int ans=0;
        for(int r=1;r<=n;r++){
            //删除队尾元素 入队
            while(l1<=r1 && a[r]>a[mxq[r1]]){
                r1--;
            }
            mxq[++r1]=r;
            while(l2<=r2 && a[r]<a[mnq[r2]]){
                r2--;
            }
            mnq[++r2]=r;
            //队首元素只能用来维护max和min的最大差值
            while(l<=r && l1<=r1 && l2<=r2 && a[mxq[l1]]-a[mnq[l2]]>k){
                l++;
                while(l1<=r1 && mxq[l1]<l){
                    l1++;
                }
                while(l2<=r2 && mnq[l2]<l){
                    l2++;
                }
            }
            if(l1<=r1 && l2<=r2 && a[mxq[l1]]-a[mnq[l2]]>=m){
                ans=max(ans,r-l+1);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
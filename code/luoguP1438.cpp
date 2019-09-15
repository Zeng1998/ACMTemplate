#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+50;
ll a[N];
int n,m,o,l,r,k,d,p;
struct ST{
    //线段树，区间修改，区间查询
}ac;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    ac.build(1,1,n);
    while(m--){
        scanf("%d",&o);
        if(o==1){
            scanf("%d%d%d%d",&l,&r,&k,&d);
            //维护差分数组，最后查询求前缀和就是单点的累加值
            //第一项加k
            ac.update(1,1,n,l,l,k);
            if(l<r){
                //等差数列，中间每一项相差d
                ac.update(1,1,n,l+1,r,d);
            }
            if(r<n){
                //差分数组的区间修改，类比a[l]++ a[r+1]--
                ac.update(1,1,n,r+1,r+1,-(k+(r-l)*d));
            }
        }else if(o==2){
            scanf("%d",&p);
            printf("%lld\n",a[p]+ac.query(1,1,n,1,p));
        }
    }
    return 0;
}

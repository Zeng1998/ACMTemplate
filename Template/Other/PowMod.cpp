/**
 * 给出正整数x和n个正整数ai，求x^ai % p
 * x^ai=(x^(ai % s))*(x^ai/s)^s
 * 先预处理出x的0-S-1次幂，即x^(ai % s)
 * 再预处理x的s次的0-S-1次幂 即x^s^(ai/s)
 */ 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e6+50;
const ll mod=998244352;
int n;
ll x,a[N];
ll p[N],sp[N];
int main(void){
    scanf("%lld%d",&x,&n);
    ll s=sqrt(mod+0.5)+1;
    p[0]=1;
    for(int i=1;i<=s;i++){
        p[i]=p[i-1]*x%mod;
    }
    sp[0]=1;
    for(int i=1;i<=s;i++){
        sp[i]=sp[i-1]*p[s]%mod;
    }
    for(int i=0;i<n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=0;i<n;i++){
        printf("%lld ",sp[a[i]/s]*p[a[i]%s]%mod);
    }
    printf("\n");
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t;
ll a,b,l,r,c;
ll Pow(ll a,ll n){
    ll ans=1;
    while(n){
        if(n%2){
            ans=ans*a%b;
        }
        a=a*a%b;
        n/=2;
    }
    return ans;
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%lld%lld%lld%lld",&a,&b,&l,&r);
        int i=l;
        c=a*Pow(10,l-1);
        while(i++<=r){
            c%=b;
            c*=10;
            printf("%lld",c/b);
        }
        printf("\n");
    }
}
/*
 * 快速幂取模: 求a^n%mod
 */ 
ll PowMod(ll a,ll n,ll mod){
    ll ans=1;
    a%=mod;
    while(n){
        if(n%2){
            ans=(ans*a)%mod;
        }
        a=a*a%mod;
        n/=2;
    }
    return ans;
}
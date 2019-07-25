//快速乘法取模 
ll qmul_mod(ll a,ll b,ll mod){
    ll ans=0;
    while(b){
        if((b%=mod)&1){
            ans+=a%=mod;
        }
        b>>=1;
        a<<=1;
    }
    return ans%mod;
}
//O(1)快速乘取模
 ll ksc(ll x,ll y,ll mod){
    return (x*y-(ll)((long double)x/mod*y)*mod+mod)%mod;     
}
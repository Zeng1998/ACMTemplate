/*
 * 欧拉降幂: 解决A^B%C(B特别大)
 * 1. 欧拉降幂: 要求A和C互质，A^B%C=A^(B%phi(C))
 * 2. 广义欧拉降幂: A^B%C=A^(B%phi(C)+phi(C)) 
 */ 
ll solve(ll a,char *s,ll c){
    int n=strlen(s);
    ll b=0;
    ll mod=getPhi(c);
    for(int i=0;i<n;i++){
        b=(b+s[i]-'0')%mod;
    }
    b=(b+mod)%mod;
    return PowMod(a,b,c);
}
/*
 * exgcd求逆元 当且仅当gcd(a,m)=1时才存在逆元
 * 原理: ax=1(mod m) => ax+km=1 (mod m) 
 */ 
ll inv(ll a,ll m){
    ll x,y;
    ll d=exgcd(a,m,x,y);
    return d==1?(x+m)%m:-1;
}
/*
 * 费马小定理求逆元 当a<p且p为素数
 */ 
ll inv(ll a,ll p){
    return PowMod(a,p-2,p);
}
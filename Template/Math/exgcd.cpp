#define Mod(a,b) ((a)%(b)+(b))%(b)
/*
 * exgcd: 给定ax+by=gcd(a,b) 已知a,b求x,y且|x|+|y|最小
 */
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll d=exgcd(b,a%b,x,y);
    ll t=x;
    x=y;
    y=t-a/b*y;
    return d;
}
/*
 * 解ax+by=c: 求非负整数解
 * x,y: 最小非负整数解
 * dx,dy: X=x+k*dx Y=y-k*dy为方程通解
 * 无解返回false
 */ 
bool solve(ll a,ll b,ll c,ll &x,ll &y,ll &dx,ll &dy){
    //无非负整数解
    if(a==0 && b==0){
        return false;
    }
    ll x0,y0;
    ll d=exgcd(a,b,x0,y0);
    //c不整除gcd(a,b)，无解
    if(c%d!=0){
        return false;
    }
    //注意a和b要反过来
    dx=b/d;
    dy=a/d;
    //取最小正数解
    x=Mod(x0*c/d,dx);
    y=(c-a*x)/b;
    return true;
}
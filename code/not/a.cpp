//minamoto
#include<iostream>
#include<cstdio>
#define ll long long
#define inf 0x3f3f3f3f
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);
}
const int N=20005,mod=3;
int head[N],Next[N<<1],edge[N<<1],ver[N<<1];ll ans=0;
int sz[N],son[N],sum[4],vis[N];
int size,mx,rt,n,tot;
inline void add(int u,int v,int e){
    ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;
    ver[++tot]=u,Next[tot]=head[v],head[v]=tot,edge[tot]=e;
}
void getrt(int u,int fa){
    sz[u]=1,son[u]=0;
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(vis[v]||v==fa) continue;
        getrt(v,u);
        sz[u]+=sz[v];
        cmax(son[u],sz[v]);
    }
    cmax(son[u],size-sz[u]);
    if(son[u]<mx) mx=son[u],rt=u;
}
void query(int u,int fa,int d){
    ++sum[d%mod];
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(vis[v]||v==fa) continue;
        query(v,u,(d+edge[i])%mod);
    }
}
ll solve(int rt,int d){
    sum[0]=sum[1]=sum[2]=0;
    query(rt,0,d);
    ll res=1ll*sum[1]*sum[2]*2+1ll*sum[0]*sum[0];
    return res;
}
void divide(int u){
    ans+=solve(u,0);
    vis[u]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(vis[v]) continue;
        ans-=solve(v,edge[i]);
        mx=inf,rt=0,size=sz[v];
        getrt(v,0);
        divide(rt);
    }
}
inline ll gcd(ll a,ll b){
    while(b^=a^=b^=a%=b);
    return a;
}
int main(){
    n=read();
    for(int i=1;i<n;++i){
        int u=read(),v=read(),e=read();
        add(u,v,e%3);
    }
    mx=inf,size=n,ans=0,rt=0;
    getrt(1,0),divide(rt);
    ll p=n*n,GCD=gcd(ans,p);
    print(ans/GCD),sr[++C]='/',print(p/GCD);
    Ot();
    return 0;
}

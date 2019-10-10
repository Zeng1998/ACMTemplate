//minamoto
//这棵树上的点的度数都不超过20，
#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
#define N 100005
#define inf 0x3f3f3f3f
#define rint register int
using namespace std;
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
inline void print(ll x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
struct G{
    int head[N],Next[N<<1],edge[N<<1],ver[N<<1],tot;
    G(){tot=0;memset(head,0,sizeof(head));}
    inline void add(int u,int v,int e){
        ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;
    }
}T1,T2;
int n,q,st[N<<1][18],logn[N<<1],bin[25],tp;
ll sum,ans,d[N],dis1[N],dis2[N],sumv[N];
int dfn[N],num;
void dfs1(int u,int fa){
    st[dfn[u]=++num][0]=d[u];
    for(int i=T1.head[u];i;i=T1.Next[i]){
        int v=T1.ver[i];
        if(v==fa) continue;
        d[v]=d[u]+T1.edge[i],dfs1(v,u),st[++num][0]=d[u];
    }
}
inline ll LCA(int a,int b){
    if(dfn[a]>dfn[b]) a^=b^=a^=b;
    int k=logn[dfn[b]-dfn[a]+1];
    return min(st[dfn[a]][k],st[dfn[b]-bin[k]+1][k])<<1;
}
inline ll dis(int a,int b){return d[a]+d[b]-LCA(a,b);}
int sz[N],son[N],size,rt,fa[N];bool vis[N];
void dfs2(int u,int fa){
    sz[u]=1,son[u]=0;
    for(int i=T1.head[u];i;i=T1.Next[i]){
        int v=T1.ver[i];
        if(vis[v]||v==fa) continue;
        dfs2(v,u),sz[u]+=sz[v],cmax(son[u],sz[v]);
    }
    cmax(son[u],size-sz[u]);
    if(son[u]<son[rt]) rt=u;
}
void dfs3(int u){
    vis[u]=true;
    for(int i=T1.head[u];i;i=T1.Next[i]){
        int v=T1.ver[i];
        if(vis[v]) continue;
        rt=0,size=sz[v],son[0]=n+1;
        dfs2(v,0),T2.add(u,rt,v),fa[rt]=u,dfs3(rt);
    }
}
inline void update(int u,int val){
    sumv[u]+=val;
    for(int p=u;fa[p];p=fa[p]){
        ll dist=dis(fa[p],u)*val;
        dis1[fa[p]]+=dist;
        dis2[p]+=dist;
        sumv[fa[p]]+=val;
    }
}
inline ll calc(int u){
    ll ans=dis1[u];
    for(int p=u;fa[p];p=fa[p]){
        ll dist=dis(fa[p],u);
        ans+=dis1[fa[p]]-dis2[p];
        ans+=dist*(sumv[fa[p]]-sumv[p]);
    }
    return ans;
}
ll query(int u){
    ll ans=calc(u);
    for(int i=T2.head[u];i;i=T2.Next[i]){
        ll tmp=calc(T2.edge[i]);
        if(tmp<ans) return query(T2.ver[i]);
    }
    return ans;
}
void init(){
    n=read(),q=read();
    bin[0]=1,logn[0]=-1;
    for(rint i=1;i<=20;++i) bin[i]=bin[i-1]<<1;
    while(bin[tp+1]<=(n<<1)) ++tp;
    for(rint i=1;i<=(n<<1);++i) logn[i]=logn[i>>1]+1;
    for(rint i=1;i<n;++i){
        rint u=read(),v=read(),e=read();
        T1.add(u,v,e),T1.add(v,u,e);
    }
    dfs1(1,0),rt=0,son[0]=n+1,size=n,dfs2(1,0);
    for(rint j=1;j<=tp;++j)
    for(rint i=1;i+bin[j]-1<=(n<<1);++i)
    st[i][j]=min(st[i][j-1],st[i+bin[j-1]][j-1]);
}
int main(){
    init();
    int LastOrder=rt;dfs3(rt);
    while(q--){
        int x=read(),y=read();update(x,y);
        print(query(LastOrder));
    }
    Ot();
    return 0;
}

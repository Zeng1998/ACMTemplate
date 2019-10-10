#include <cstdio>
#include <cstring>
#include <ctime>
#include <set>
#include <queue>
using namespace std;
#define N 100010
#define inf 0x3fffffff
#define Vt Vater[rt]
int n,e,adj[N];
struct edge{int zhong,next;}s[N<<1];
inline void add(int qi,int zhong)
    {s[++e].zhong=zhong;s[e].next=adj[qi];adj[qi]=e;}
int Vater[N],size[N],root,totsize,maxs[N];
bool state[N],vis[N];
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
struct heap
{
    priority_queue<int>q1,q2;
    inline void push(int x){q1.push(x);}
    inline void erase(int x){q2.push(x);}
    inline int top()
    {
        while(q2.size()&&q1.top()==q2.top())q1.pop(),q2.pop();
        return q1.top();
    }
    inline void pop()
    {
        while(q2.size()&&q1.top()==q2.top())q1.pop(),q2.pop();
        q1.pop();
    }
    inline int top2()
    {
        int val=top();pop();
        int ret=top();push(val);
        return ret;
    }
    inline int size()
    {
        return q1.size()-q2.size();
    }
}h1[N],h2[N],h3;
inline void dfs1(int rt,int fa)
{
    size[rt]=1,maxs[rt]=0;
    for(int i=adj[rt];i;i=s[i].next)
        if(s[i].zhong!=fa&&!vis[s[i].zhong])
            dfs1(s[i].zhong,rt),size[rt]+=size[s[i].zhong],
            maxs[rt]=max(maxs[rt],size[s[i].zhong]);
    maxs[rt]=max(maxs[rt],totsize-maxs[rt]);
    if(maxs[rt]<maxs[root])root=rt;
}
int f[N][18],bin[25],tp,deep[N];
inline void pre(int rt,int fa)
{
    f[rt][0]=fa;deep[rt]=deep[fa]+1;
    for(int i=1;bin[i]+1<=deep[rt];++i)f[rt][i]=f[f[rt][i-1]][i-1];
    for(int i=adj[rt];i;i=s[i].next)
        if(s[i].zhong!=fa)pre(s[i].zhong,rt);
}
inline int LCA(int a,int b)
{
    if(deep[a]<deep[b])a^=b,b^=a,a^=b;
    int i,cha=deep[a]-deep[b];
    for(i=tp;~i;--i)if(cha&bin[i])a=f[a][i];
    if(a==b)return a;
    for(i=tp;~i;--i)
        if(f[a][i]!=f[b][i])a=f[a][i],b=f[b][i];
    return f[a][0];
}
inline int dis(int a,int b)
    {return deep[a]+deep[b]-(deep[LCA(a,b)]<<1);}
inline void dfs3(int rt,int fa,int Vatty)
{
    h1[root].push(dis(rt,Vatty));
    for(int i=adj[rt];i;i=s[i].next)
        if(!vis[s[i].zhong]&&s[i].zhong!=fa)
            dfs3(s[i].zhong,rt,Vatty);
}
inline void dfs2(int rt,int fa)
{
    Vt=fa,vis[rt]=1,h2[rt].push(0);
    int siz=totsize;
    for(int i=adj[rt];i;i=s[i].next)
        if(!vis[s[i].zhong])
        {
            if(size[s[i].zhong]>size[rt])
                totsize=siz-size[rt];
            else 
                totsize=size[s[i].zhong];
            root=0,dfs1(s[i].zhong,0),dfs3(root,0,rt);
            h2[rt].push(h1[root].top()),dfs2(root,rt);
        }
    if(h2[rt].size()>1)h3.push(h2[rt].top()+h2[rt].top2());
}
inline void turnoff(int who)
{
    int val,tmp;
    if(h2[who].size()>1)h3.erase(h2[who].top()+h2[who].top2());
    h2[who].push(0);
    if(h2[who].size()>1)h3.push(h2[who].top()+h2[who].top2());
    //queue empty() 后依然有数
    for(int rt=who;Vt;rt=Vt)
    {
        if(h2[Vt].size()>1)h3.erase(h2[Vt].top()+h2[Vt].top2());
        if(h1[rt].size())h2[Vt].erase(h1[rt].top());
        h1[rt].push(dis(who,Vt));
        h2[Vt].push(h1[rt].top());
        if(h2[Vt].size()>1)h3.push(h2[Vt].top()+h2[Vt].top2());
    }
}
inline void turnon(int who)
{
    int val,tmp;
    if(h2[who].size()>1)h3.erase(h2[who].top()+h2[who].top2());
    h2[who].erase(0);
    if(h2[who].size()>1)h3.push(h2[who].top()+h2[who].top2());
    //queue empty()后依然有数
    for(int rt=who;Vt;rt=Vt)
    {
        if(h2[Vt].size()>1)h3.erase(h2[Vt].top()+h2[Vt].top2());
        h2[Vt].erase(h1[rt].top());
        h1[rt].erase(dis(who,Vt));
        if(h1[rt].size())h2[Vt].push(h1[rt].top());
        if(h2[Vt].size()>1)h3.push(h2[Vt].top()+h2[Vt].top2());
    }
}
char B[1<<15],X=0,*S=B,*T=B;
#define getc ( S==T&&( T=(S=B)+fread(B,1,1<<15,stdin),S==T )?0:*S++ )
inline int read()
{
    int x=0;while(X<'0'||X>'9')X=getc;
    while(X>='0'&&X<='9')x=10*x+(X^48),X=getc;
    return x;
}
inline void readc(){X=getc;while(X<'A'||X>'Z')X=getc;}
int main()
{
    n=read();
    register int i,j,q,a,b,cnt=n;
    for(bin[0]=i=1;i<=20;++i)bin[i]=bin[i-1]<<1;
    while(bin[tp+1]<=n)++tp;
    for(i=1;i<n;++i)
        a=read(),b=read(),add(a,b),add(b,a);
    pre(1,0);
    maxs[0]=inf,root=0,totsize=n,dfs1(1,0),dfs2(root,0);
    q=read();
    while(q--)
    {
        readc();
        if(X=='C')
        {
            i=read();
            if(state[i])++cnt,turnoff(i);
            else --cnt,turnon(i);
            state[i]^=1;
        }
        else
        {
            if(cnt<2)printf("%d\n",cnt-1);
            else printf("%d\n",h3.top());
        }
    }
}

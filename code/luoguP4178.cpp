//点分治求距离小于等于k的点对数
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const int N=1e5+50;
int n,u,v,w,tot,root;ll k;
struct Edge{
    int v,w;
};
vector<Edge> g[N];
int sz[N],vis[N],mx,size,l,r;
ll d[N],q[N],ans;
void getroot(int u,int fa){
    sz[u]=1;
    int num=0;
    int l=g[u].size();
    for(int i=0;i<l;i++){
        int v=g[u][i].v;
        if(v==fa||vis[v]){
            continue;
        }
        getroot(v,u);
        sz[u]+=sz[v];
        num=max(num,sz[v]);
    }
    num=max(num,size-sz[u]);
    if(num<mx){
        mx=num;
        root=u;
    }
}
void getdis(int u,int fa){
    q[++r]=d[u];
    int l=g[u].size();
    for(int i=0;i<l;i++){
        int v=g[u][i].v;
        int w=g[u][i].w;
        if(v==fa||vis[v]){
            continue;
        }
        d[v]=d[u]+w;
        getdis(v,u);
    }
}
ll calc(int u,int val){
    r=0;
    d[u]=val;
    getdis(u,0);
    ll sum=0;l=1;
    sort(q+1,q+r+1);
    while(l<r){
        if(q[l]+q[r]<=k){
            sum+=r-l,++l;
        }
        else --r;
    }
    return sum;
}
void dfs(int u){
    ans+=calc(u,0);
    vis[u]=1;
    int l=g[u].size();
    for(int i=0;i<l;i++){
        int v=g[u][i].v;
        int w=g[u][i].w;
        if(vis[v]){
            continue;
        }
        ans-=calc(v,w);
        size=sz[v];
        mx=INF;
        getroot(v,0);
        dfs(root);
    }
}
int main() {
    scanf("%d",&n);
    for(int i=0;i<n-1;i++){
        scanf("%d%d%d",&u,&v,&w);
        g[u].push_back(Edge{v,w});
        g[v].push_back(Edge{u,w});
    }
    scanf("%lld",&k);
    size=n;
    mx=INF;
    ans=0;
    getroot(1, 0);
    dfs(root);
    printf("%lld",ans);
    return 0;
}

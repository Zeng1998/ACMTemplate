#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
vector<int> g[N];
int a[N];
int n,m,u,v,x;
int rt[N];
struct Trie{
    int cnt,tr[N*50][2],val[N*50];
    int dep[N],fa[N][20];
    void init(){
        cnt=0;
        memset(tr,0,sizeof(tr));
        memset(val,0,sizeof(val));
        memset(dep,0,sizeof(dep));
        memset(fa,0,sizeof(fa));
    }
    int ins(int pre,int x){
        int rt=++cnt;
        int now=rt;
        for(int i=16;i>=0;i--){
            int id=(x>>i)&1;
            if(!tr[now][id]){
                tr[now][id]=++cnt;
                tr[now][id^1]=tr[pre][id^1];
                val[tr[now][id]]=val[tr[pre][id]];
            }
            pre=tr[pre][id];
            now=tr[now][id];
            val[now]++;
        }
        return rt;
    }
    void dfs(int u){
        for(int i=1;(1<<i)<=dep[u];i++){
            fa[u][i]=fa[fa[u][i-1]][i-1];
        }
        rt[u]=ins(rt[fa[u][0]],a[u]);
        int siz=g[u].size();
        for(int i=0;i<siz;i++){
            int v=g[u][i];
            if(v==fa[u][0]){
                continue;
            }
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    }
    int lca(int x,int y){
        if(dep[x]<dep[y]){
            swap(x,y);
        }
        //深度大的x先跳
        int t=dep[x]-dep[y];
        for(int i=0;(1<<i)<=t;i++){
            if(t &(1<<i)){
                x=fa[x][i];
            }
        }
        if(x==y){
            return x;
        }
        //同深度,一起跳
        for(int i=16;i>=0;i--){
            if(fa[x][i]!=fa[y][i]){
                x=fa[x][i];
                y=fa[y][i];
            }    
        }
        //fa[x][i]==fa[y][i];
        return fa[x][0];
    }
    int solve(int u,int v,int x){
        //lca单独考虑,因为下面从根到u到v的路径再减去两倍lca(必须减去两倍)
        int lc=lca(u,v);
        int ans=a[lc]^x;
        int t=0;
        u=rt[u];
        v=rt[v];
        lc=rt[lc];
        //每一位考虑异或最大
        for(int i=16;i>=0;i--){
            int id=(x>>i)&1;
            //普通可持久化Trie只要考虑val[tr[r][id^1]]-val[tr[l][id^1]]是否大于0
            //这里就要考虑u到v路径上的val值是否大于0 (注意负数)
            if(val[tr[u][id^1]]+val[tr[v][id^1]]-2*val[tr[lc][id^1]]>0){
                t+=(1<<i);
                id^=1;
            }
            u=tr[u][id];
            v=tr[v][id];
            lc=tr[lc][id];
        }
        //printf("t %d\n",t);
        return max(ans,t);
    }
}T;
int main(void){
    // freopen("in.txt","r",stdin);
    while(~scanf("%d%d",&n,&m)){
        for(int i=1;i<=n;i++){
            g[i].clear();
            scanf("%d",&a[i]);
        }
        memset(rt,0,sizeof(rt));
        for(int i=0;i<n-1;i++){
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        T.init();
        T.dfs(1);
        //printf("%d %d\n",T.lca(1,2),T.lca(2,3));
        //printf("%d %d %d\n",T.dep[1],T.dep[2],T.dep[3]);
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&u,&v,&x);
            int ans=T.solve(u,v,x);
            printf("%d\n",ans);
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int N=1e4+50;
const int INF=0x3f3f3f3f;
int s,t,n,m,k,u,v,w;
bool vis[N][20];
//dis[v][i]: 到v使用i条免费路的最短路
int dis[N][20];
struct Edge{
    int v,w;
};
vector<Edge> g[N];
struct node{
    int v,dis,lev;
    bool operator <(const node& rhs)const{
        return dis>rhs.dis;
    }
};
int dijkstra(int s,int t){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=k;j++){
            vis[i][j]=false;
            dis[i][j]=INF;
        }
    }
    dis[s][0]=0;
    priority_queue<node> pq;
    pq.push(node{s,0,0});
    while(!pq.empty()){
        node t=pq.top();
        pq.pop();
        int u=t.v;
        int lev=t.lev;
        if(vis[u][lev]){
            continue;
        }
        vis[u][lev]=true;
        int siz=g[u].size();
        for(int i=0;i<siz;i++){
            int v=g[u][i].v;
            int w=g[u][i].w;
            if(dis[u][lev]+w<dis[v][lev]){
                dis[v][lev]=dis[u][lev]+w;
                pq.push(node{v,dis[v][lev],lev});
            }
            if(lev<k && dis[u][lev]<dis[v][lev+1]){
                //使用一条免费路
                dis[v][lev+1]=dis[u][lev];
                pq.push(node{v,dis[v][lev+1],lev+1});
            }
        }
    }
    int ans=INF;
    for(int i=0;i<=k;i++){
        ans=min(ans,dis[t][i]);
    }
    return ans;
}
int main(void){
    scanf("%d%d%d",&n,&m,&k);
    scanf("%d%d",&s,&t);
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&u,&v,&w);
        g[u].push_back(Edge{v,w});
        g[v].push_back(Edge{u,w});
    }
    int ans=dijkstra(s,t);
    printf("%d\n",ans);
    return 0;
}
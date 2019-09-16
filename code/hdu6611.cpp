#include <bits/stdc++.h>
using namespace std;
const int N=5e6+50;
const int INF=0x3f3f3f3f;
int T,n,k,w[N],nc,s,t;
struct edge {
    int to, capacity, cost, rev;
};
int h[N],dis[N],PreV[N],p[N],a[N];
//vector<edge> G[N + 5];
//void init() {
//    for (int i = 0; i <N; ++i)G[i].clear();
//}
//void add(int from, int to, int cap, int cost) {
//    G[from].push_back({to, cap, cost, int(G[to].size())});
//    G[to].push_back({from, 0, -cost, int(G[from].size() - 1)});
//}
struct Edge{
    int u,v,w,c,next;
}e[N];
int cnt,head[N];
void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}
void add(int u,int v,int w,int c){
    e[cnt]=Edge{u,v,w,c,head[u]};
    head[u]=cnt++;
    e[cnt]=Edge{v,u,0,-c,head[v]};
    head[v]=cnt++;
}
struct node{
    int v,c;
    bool operator <(const node &rhs)const{
        return c>rhs.c;
    }
};
void mcmf(int &flow, int &cost) {
    flow=0;
    cost=0;
    //初始化势函数，也可以跑一遍spfa计算出dis，赋值给h
    for(int i=1;i<=nc;i++){
        h[i]=0;
    }
    while(true){
        //重复跑dijk堆优化
        //跑费用的最短路，同时记录路径的最小流量
        priority_queue<node> q;
        for(int i=1;i<=nc;i++){
            dis[i]=INF;
        }
        dis[s]=0;
        p[s]=0;
        a[s]=INF;
        q.push({s,0});
        while(!q.empty()){
            node now=q.top();
            q.pop();
            int u=now.v;
            if(dis[u]<now.c){
                continue;
            }
            for(int i=head[u];i!=-1;i=e[i].next){
                int v=e[i].v;
                int w=e[i].w;
                int c=e[i].c;
//            for (int i = 0; i < G[u].size(); ++i) {
//                edge &e = G[u][i];
//                int v=e.to;
//                int w=e.capacity;
//                int c=e.cost;
                if(w>0 && dis[v]>dis[u]+c+h[u]-h[v]){
                    dis[v]=dis[u]+c+h[u]-h[v];
                    a[v]=min(a[u],w);
                    PreV[v] = u;
                    p[v]=i;
                    q.push({v,dis[v]});
                }
            }
        }
        //无法再增广
        if(dis[t]==INF){
            break;
        }
        //更新势函数
        for(int i=1;i<=nc;i++){
            h[i]+=dis[i];
        }
        flow+=a[t];
        cost+=a[t]*h[t];
//        for (int v = t; v != s; v = PreV[v]) {
//            edge &e = G[PreV[v]][p[v]];
//            e.capacity -= a[t];
//            G[v][e.rev].capacity += a[t];
//        }
        for(int u=t;u!=s;u=e[p[u]].u){
            e[p[u]].w-=a[t];
            e[p[u]^1].w+=a[t];
        }
    }
}
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
        }
        s=2*n+1;
        int s1=2*n+2;
        int t1=2*n+3;
        t=2*n+4;
        add(s,s1,k,0);
        add(t1,t,k,0);
        for(int i=1;i<=n;i++){
            add(s1,i,1,-w[i]);
        }
        for(int i=1;i<=n;i++){
            add(i,i+n,1,0);
        }
        for(int i=1;i<=n;i++){
            add(i+n,t1,1,0);
        }
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(w[j]>=w[i]){
                    add(i+n,j,1,-w[j]);
                }
            }
        }
        nc=2*n+4;
        int flow=0,cost=0;
        mcmf(flow,cost);
        printf("%d\n",-cost);
    }
    return 0;
}

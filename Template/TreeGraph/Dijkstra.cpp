/* 
 * 堆优化的Dijkstra(最短距离、最短路条数)
 * dis[i]: i到最短路集合的距离
 * pcnt[i]: 到i的路径条数
 */
void Dijkstra(){
    for(int i=0;i<N;i++){
        dis[i]=INF;
        vis[i]=false;
        pcnt[i]=0;
    }
    priority_queue<node> q;
    dis[s]=0;
    pcnt[s]=1;
    q.push(node{s,0});
    while(!q.empty()){
        node tmp=q.top();
        q.pop();
        int u=tmp.v;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            int w=edge[i].w;
            if(!vis[u] && dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                //多加了一条u-v的边而已，所以到v的最短路条数和到u的相同
                pcnt[v]=pcnt[u];
                q.push(node{v,dis[v]});
            }else if(!vis[u] && dis[v]==dis[u]+w){
                //相等的情况就多出了pcnt[u]条路了
                pcnt[v]+=pcnt[u];
            }
        }
    }
}
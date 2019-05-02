/*
 * 最小费用最大流(mcmf)
 * inq[i]: i节点是否在队列中
 * d[i]: bellmanford算法的距离
 * p[i]: 记录流向i的上一条边编号
 * a[i]: i的可改进量(通过量)
 */ 
bool BellmanFord(int &flow,int &cost){
    for(int i=0;i<N;i++){
        d[i]=INF;
        inq[i]=false;
    }
    d[s]=0;
    p[s]=0;
    a[s]=INF;
    queue<int> q;
    q.push(s);
    inq[s]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            int w=edge[i].w;
            int c=edge[i].c;
            if(w>0 && d[v]>d[u]+c){
                d[v]=d[u]+c;
                p[v]=i;
                a[v]=min(a[u],w);
                if(!inq[v]){
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    if(d[t]==INF){
        return false;
    }
    flow+=a[t];
    cost+=d[t]*a[t];
    for(int u=t;u!=s;u=edge[p[u]].u){
        edge[p[u]].w-=a[t];
        edge[p[u]^1].w+=a[t];
    }
    return true;
}
void mcmf(int &flow,int &cost){
    flow=0,cost=0;
    while(BellmanFord(flow,cost));
}
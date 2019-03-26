/*
 * s,t: 源点，汇点
 * dep[i]: i点的深度
 * cur[i]: i的邻接链表当前访问到的边
 */ 
//=====================
/*
 * bfs构建分层图
 */ 
bool bfs(){
    queue<int> q;
    memset(dep,0,sizeof(dep));
    dep[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            int w=edge[i].w;
            //可用流量大于0 && 未标记深度
            if(w>0 && dep[v]==0){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]!=0;
}
/*
 * dfs增广
 */ 
int dfs(int u,int flow){
    if(u==t){
        return flow;
    }
    //当前弧优化
    for(int &i=cur[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        int w=edge[i].w;
        if(dep[v]==dep[u]+1 && w!=0){
            //dfs向下增广
            int dis=dfs(v,min(w,flow));
            if(dis>0){
                //正向边和反向边更新可用流量
                edge[i].w-=dis;
                edge[i^1].w+=dis;
                return dis;
            }
        }
    }
    return 0;
}
/*
 * dinic算法
 */ 
int dinic(int n){
    int ans=0;
    while(bfs()){
        //不断构建分层图再增广，加上当前弧优化
        for(int i=1;i<=n;i++){
            cur[i]=head[i];
        }
        while(int d=dfs(s,INF)){
            ans+=d;
        }
    }
    return ans;
}
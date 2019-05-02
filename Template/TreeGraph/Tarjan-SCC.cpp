/*
 * 求有向图的强连通分量
 * 强连通分量: 分量内任意两个点都能互相到达
 * low[u]:u能回溯到的最早祖先
 * dfn[u]:dfs序
 * scc[u]:u所属scc编号
 * inSta[u]:u是否在栈中
 * s:暂存节点
 */
void dfs(int u){
    //初始化dfs序
    low[u]=dfn[u]=++idx;
    s.push(u);
    inSta[u]=true;
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i];
        if(dfn[v]==-1){
            //未访问
            dfs(v);
            //此时已经递归到底，可以用low[v]来更新low[u]
            low[u]=min(low[u],low[v]);
        }else if(inSta[v]){
            //访问过，在栈中(low[v]还没完全更新)
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        //能回到的最早节点就是本身，说明得到一个强连通分量
        cnt++;
        while(!s.empty()){
            int t=s.top();
	    scc[t]=cnt;
            s.pop();
            inSta[t]=false;
	    if(t==u){
                break;
	    }
        }
    }
}
void tarjan(int n){
    memset(dfn,-1,sizeof(dfn));
    memset(scc,-1,sizeof(scc));
    while(!s.empty()){
        s.pop();
    }
    idx=cnt=0;
    for(int i=1;i<=n;i++){
        //未访问
        if(dfn[i]==-1){
            dfs(i);
        }
    }
}

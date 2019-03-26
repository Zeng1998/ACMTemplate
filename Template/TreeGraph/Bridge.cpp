/*
 * tarjan算法求桥
 * 注意求出桥后进行重边的特判，重边不可能是桥
 */
void dfs(int u,int f){
    low[u]=dfn[u]=++idx;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==f){
            continue;
        }
        if(dfn[v]==-1){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            //v不能回溯到u之前，说明u-v是桥
            if(low[v]>dfn[u]){
                bridegs.push_back(make_pair(u,v));
            }
        }else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}
void solve(int n){
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    for(int i=1;i<=n;i++){
        if(dfn[i]==-1){
            dfs(i,0);
        }
    }
}

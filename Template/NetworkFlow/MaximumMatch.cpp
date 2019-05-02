/*
 * 可以加个源点汇点跑最大流，但有时候比较毒瘤可能会T...
 * 匈牙利算法
 * g[][]: 图的邻接矩阵表示
 * vis[i]: 本轮是否已访问
 * mt[i]: i所匹配的点
 */ 
bool dfs(int u, int n){
    for(int i=1;i<=n;++i){
        if(!vis[i] && g[u][i]){
            vis[i] = true;
            if(mt[i]==-1 || dfs(mt[i], n)){
                mt[i] = u;
                return true;
            }
        }
    }
    return false;
}
int solve(){
    int ans=0;
    memset(mt,-1,sizeof(mt));
    for(int i=1;i<=n;++i){
        memset(vis,0,sizeof(vis));
        ans += dfs(i, n);
    }
    return ans;
}
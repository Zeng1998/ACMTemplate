/*
 * dfs求树的直径
 * 从任意一点dfs一遍，找到最远的点node，再从node点dfs一遍，找到直径的另一点
 * dfs(1,0)前记得使vis[1]=true
 */ 
void dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        int w=edge[i].w;
        if(!vis[v]){
            vis[v]=true;
            d[v]=d[u]+w;
            if(d[v]>ans){
                ans=d[v];
                node=v;
            }
            dfs(v,d[v]);
        }
    }
}
/*
 * dfs求树的重心
 * dfs一遍求出ans即为重心，siz初始化为INF，即重心的最大子树大小
 * 树重心的一些性质:
 * 0. 树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么他们的距离和一样
 * 1. 把两个树通过一条边相连得到一个新的树，那么新的树的重心在连接原来两个树的重心的路径上
 * 2. 把一个树添加或删除一个叶子，那么它的重心最多只移动一条边的距离
 */ 
void dfs(int u,int f){
    son[u]=1;
    int res=0;
    for (int i=head[u];i!=-1;i=edges[i].next){
        int v=edges[i].v;
        if (v==f){
            continue;
        }
        dfs(v,u);
        son[u]+=son[v];
        res=max(res,son[v]);
    }
    res=max(res,n-son[u]);
    if (res<siz){
        ans=u;
        siz=res;
    }
}
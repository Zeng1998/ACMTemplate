/*
 * d[i]: 节点i的深度
 * fa[u][i]: 表示从u往上跳2^i格可以到达的点
 */ 
void dfs(int u){
    //倍增
    for(int i=1;pw[i]<=d[u];i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(v!=fa[u][0]){
            //fa[v][0]即v往上跳1即v的父节点
            fa[v][0]=u;
            //深度
            d[v]=d[u]+1;
            dfs(v);
        }
    }
}
int lca(int x,int y){
    if(d[x]<d[y]){
        swap(x,y);
    }
    int tmp=d[x]-d[y];
    for(int i=0;pw[i]<=tmp;i++){
        //往上跳
        if(tmp&pw[i]){
            x=fa[x][i];
        }
    }
    //跳到刚好，即y=lca(x,y)
    if(x==y){
        return x;
    }
    for(int i=16;i>=0;i--){
        //x和y一起跳
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

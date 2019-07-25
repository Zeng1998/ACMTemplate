//dfs序
void dfs(int u,int f){
    in[u]=++clk;
    rk[clk]=u;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==f){
            continue;
        }
        dfs(v,u);
    }
    //出是clk
    out[u]=clk;
}
//欧拉序

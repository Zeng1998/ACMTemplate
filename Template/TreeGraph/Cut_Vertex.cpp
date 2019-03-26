/*
 * tarjan算法求割点
 * 根节点满足儿子数≥2
 * 非根节点满足low[v]>=dfn[u] (即v后面的点无法通过其他路径回到u之前,换句话说,只有u这一条路) 
 * cut[u]:u是否为割点
 * rt:根节点(注意不是父节点)
 */ 
void dfs(int u,int rt){
    low[u]=dfn[u]=++idx;
    int son=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(dfn[v]==-1){
            dfs(v,rt);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]{
                if(u==rt){
                    son++;
                }else{
                    cut[u]=true;
                }
            }
        }else{
            low[u]=min(low[u],dfn[v]);
        }
    }
    //根节点特判
    if(son>=2 && u==rt){
        cut[u]=true;
    }
}
void solve(){    
    memset(dfn,-1,sizeof(dfn));
    memset(low,-1,sizeof(low));
    for(int i=1;i<=n;i++){
        if(dfn[i]==-1){
	    //注意调用方式
            dfs(i,i);
        }
    }
}

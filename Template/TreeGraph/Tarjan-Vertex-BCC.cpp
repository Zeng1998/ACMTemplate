/*
 * tarjan算法求割点/点-双连通分量
 * 边/点双连通分量：不存在桥/割点的极大子图
 * 一个割点属于多个点双连通分量，一个桥不属于任何边双连通分量
 * bcc[i]: 表示编号为i的连通分量的节点(vector数组)
 * rt: 根，而不是父节点
 */  
void dfs(int u,int rt){
    low[u]=dfn[u]=++idx;
    //记录儿子节点个数，用于根的特判
    int son=0;
    s.push(u);
    inStack[u]=true;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(dfn[v]==-1){
            dfs(v,rt);
            low[u]=min(low[u],low[v]);
	    //割点的判定
            if(low[v]>=dfn[u]){
                num++;
                while(!s.empty()){
                    int t=s.top();
                    s.pop();
                    inStack[t]=false;
                    bcc[num].push_back(t);
                    if(t==v){
                        break;
                    }
                }
                //点双连通分量点可重复
                bcc[num].push_back(u);
		//根的特判
                if(u==rt){
                    son++;
                }else{
                    cut[u]=true;
                }
            }
        }else if(inStack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    //根节点特判，只要多于两个儿子即为割点
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
    

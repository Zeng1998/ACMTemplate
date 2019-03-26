/*
 * tarjan算法求桥/边-双连通分量
 * 双连通分量即删除桥后的各个连通分量，可以说BCC=SCC+桥的判定
 * 小结论:一个有桥的连通图要变为边双连通图至少需要加几条边？ 
 *     双连通分量缩点建树，求叶子节点数量，答案为(leaf+1)/2
 */
void dfs(int u,int f){
    low[u]=dfn[u]=++idx;
    s.push(u);
    inStack[u]=true;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        //无向图
        if(v==f){
            continue;
        }
        if(dfn[v]==-1){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            //桥的判定
            if(low[v]>dfn[u]){
                bridegs.push_back(make_pair(u,v));
            }
        }else if(inStack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    //删掉桥剩下的就是边-双联通分类
    if(low[u]==dfn[u]){
        num++;
        while(!s.empty()){
            int t=s.top();        
            s.pop();
            inStack[t]=false;
            bcc[t]=num;
            if(t==u){
                break;
            }
       }
    }
}
void solve(int n){
    num=0;
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    for(int i=1;i<=n;i++){
        if(dfn[i]==-1){
            dfs(i,0);
        }
    }
}

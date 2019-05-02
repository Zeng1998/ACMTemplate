/*
 * 贪心求解树上最小支配集/最小点覆盖/最大独立集
 * p[i]: i的父节点
 * dft[i]: dfs序第i个节点
 * s[]: 求解的集合
 * vis[i]: i是否被集合覆盖
 */ 
void dfs(int u,int f){
    //dfs序
    dft[k++]=u;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==f){
            continue;
        }
        p[v]=u;
        dfs(v,u);
    }
}
bool s[N],vis[N];
//最小支配集(覆盖所有点)
int greedy1(){
    int ans=0;
    //逆序进行贪心
    for(int i=n-1;i>=0;i--){
        int t=dft[i];
        //当前点未被覆盖
        if(!vis[t]){
            //父节点不属于支配集
            if(!s[p[t]]){
                //将父节点加入支配集
                s[p[t]]=true;
                ans++;
            }
            //父节点加入支配集，即该节点和父节点的父节点都被覆盖
            vis[t]=true;
            vis[p[t]]=true;
            vis[p[p[t]]]=true;
        }
    }
    return ans;
}
//最小点覆盖集(覆盖所有边)
int greedy2(){
    int ans=0;
    //该贪心策略要排除根节点dft[0]
    for(int i=n-1;i>=1;i--){
        int t=dft[i];
        //当前节点和父节点都不属于覆盖集
        if(!vis[t] && !vis[p[t]]){
            //父节点加入覆盖集
            s[p[t]]=true;
            ans++;
            //当前点和父节点的父节点被覆盖
            vis[t]=true;
            vis[p[t]]=true;
        }
    }
    return ans;
}
//最大点独立集
int greedy3(){
    int ans=0;
    for(int i=n-1;i>=0;i--){
        int t=dft[i];
        //当前节点没有被覆盖
        if(!vis[t]){
            //加入独立集
            s[t]=true;
            ans++;
            //当前节点和父节点被覆盖
            vis[t]=true;
            vis[p[t]]=true;
        }
    }
    return ans;
}
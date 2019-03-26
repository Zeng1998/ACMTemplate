/*
 * 最小生成树Prim算法
 * used[i][j]: i-j这条边是否在MST中
 * path[i][j]: <i...j>的路径上的最长边
 * pre[i]: MST中i的前驱节点，即上一步能够更新low[i]的点，即将i加入MST的点
 */ 
int Prim(){
    for(int i=0;i<n;i++){
        vis[i]=false;
        low[i]=cost[0][i];
        pre[i]=0;
        for(int j=0;j<n;j++){
            used[i][j]=false;
            path[i][j]=false;
        }
    }
    vis[0]=true;
    pre[0]=-1;
    low[0]=0;
    int ans=0;
    for(int i=1;i<n;i++){
        int k=-1;
        int Min=INF;
        for(int j=0;j<n;j++){
            if(!vis[j] && low[j]<Min){
                Min=low[j];
                k=j;
            }
        }
        if(k==-1){
            break;
        }
        ans+=Min;
        vis[k]=true;
        used[k][pre[k]]=used[pre[k]][k]=true;
        for(int j=0;j<n;j++){
            //因为j访问过，也就是在MST中，即此时可以看成是j--pre[k]--k
            //j是MST点集的一点，而k就刚好被选中要加入这个点集
            //pre[k]是k的前驱，也就是点集的边缘，也就是把k带进MST的点
            //所以j到k的最大边就是由两部分更新而来，path[j][pre[k]]和low[k]
            if(vis[j] && j!=k){
                path[j][k]=path[k][j]=max(path[j][pre[k]],low[k]);
            }else if(!vis[j] && low[j]>cost[k][j]){
                low[j]=cost[k][j];
                pre[j]=k;
            }
        }
    }
    return ans;
}
/*
 * 先求出MST，再枚举不在MST中的边求出SST
 */ 
int solve(){
    int ans=Prim();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(!used[i][j]){
                ans=min(ans,ans-path[i][j]+cost[i][j]);
            }
        }
    }
    return ans;
}
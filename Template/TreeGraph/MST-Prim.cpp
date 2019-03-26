/*
 * 最小生成树(MST)Prim算法，使用邻接矩阵
 * 顶点0~n-1
 * dis[i]: 已选点集到i的最短边
 */ 
int Prim(){
    for(int i=0;i<n;i++){
        dis[i]=cost[0][i];
        vis[i]=false;
    }
    vis[0]=true;
    int ans=0;
    for(int i=1;i<n;i++){
        int k=-1;
        int mc=INF;
        for(int j=0;j<n;j++){
            if(!vis[j] && dis[j]<mc){
                mc=dis[j];
                k=j;
            }
        }
        if(k==-1){
            break;
        }
        vis[k]=true;
        ans+=mc;
        for(int j=0;j<n;j++){
            if(!vis[j] && dis[j]>cost[k][j]){
                dis[j]=cost[k][j];
            }
        }
    }
    return ans;
}
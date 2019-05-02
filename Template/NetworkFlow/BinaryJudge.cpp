/*
 * 染色法判断二分图(奇圈): 任何无回路的图都是二分图
 * col[i]: 点i的颜色(1,-1代表不同颜色，0代表未染色)
 */ 
bool dfs(int u,int c){
    //将u涂成c颜色
    col[u]=c;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        //相邻顶点不能同色
        if(col[v]==c){
            return false;
        }
        //如果未涂色则尝试递归涂色，如果失败返回false，则该判断也false
        if(col[v]==0 && !dfs(v,-c)){
            return false;
        }
    }
    return true;
}
bool solve(){
    for(int i=0;i<n;i++){
        if(col[i]==0 && !dfs(i,1)){
            return false;
        }
    }
    return true;
}

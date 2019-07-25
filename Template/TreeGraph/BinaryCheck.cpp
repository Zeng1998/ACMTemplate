/**
 * 染色法判断二分图(奇环)
 */ 
bool dfs(int u,int c){
    col[u]=c;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(col[v]==c){
            return false;
        }
        if(col[v]==0 && !dfs(v,-c)){
            return false;
        }
    }
    return true;
}
bool solve(){
    memset(col,0,sizeof(col));
    for(int i=0;i<n;i++){
        if(col[i]==0){
            if(!dfs(i,1)){
                return false;
            }
        }
    }
    return true;
}
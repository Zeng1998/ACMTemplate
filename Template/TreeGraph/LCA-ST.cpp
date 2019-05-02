/*
 * ver[i]:第i个访问节点的编号
 * fir[i]:编号为i的节点第一次出现的时间
 * dep[i]:第i个访问节点的深度
 * ver,dep注意开两倍空间
 */ 
void dfs(int u,int f,int d){
    tot++;
    ver[tot]=u;
    fir[u]=tot;
    dep[tot]=d;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==f){
            continue;
        }
        dfs(v,u,d+1);
        //回溯再记录一次
        tot++;
        ver[tot]=u;
        dep[tot]=d;
    }
}
/*
 * RMQ初始化
 * dp[i][j]:从dep[i]起2^j个数的编号最小值(ver和dep的编号即访问时间)
 * dp数组注意开两倍空间
 */ 
void RMQ_init(int n){
    for(int i=0;i<n;i++){
        dp[i][0]=i;
    }
    for(int j=1;(1<<j)<=n;j++){
        for(int i=0;i+(1<<j)-1<n;i++){
            //和普通的rmq不同，这里比较的是深度，但dp保存的是位置
            int a=dp[i][j-1];
            int b=dp[i+(1<<(j-1))][j-1];
            dp[i][j]=(dep[a]<dep[b]?a:b);
        }
    }
} 
int RMQ(int l,int r){
    int k = 31 - __builtin_clz(r - l + 1);
    int a=dp[l][k];
    int b=dp[r-(1<<k)+1][k];
    return (dep[a]<dep[b]?a:b);
}
// 找出访问u和v之间(fir[u]...fir[v])深度最小的点的编号idx，由ver映射成节点编号
int LCA(int u,int v){
    int x=fir[u];
    int y=fir[v];
    if(x>y){
        swap(x,y);
    }
    int idx=RMQ(x,y);
    return ver[idx];
}

/*
 * 可持久化字典树查询树上某个节点子树的某个数与所给值的最大异或值
 * 先dfs(1,0)求dfs序
 * 再对于dfs序的每个节点权值a[mp[i]]，建字典树
 * rt[i]=newnode();
 * insert(i-1,i,a[mp[i]]);
 */ 
void dfs(int u,int f){
    in[u]=++cnt;
    mp[cnt]=u;
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i];
        if(v==f){
            continue;
        }
        dfs(v,u);
    }
    //注意这里出树是cnt不是++cnt，这样就不会重复建树
    //这样in[u] out[u]表示的就是u的子树的范围
    out[u]=cnt;
}
int ch[N*100][2],sz[N*100],tot,rt[N];
void init(){
    //注意初始化
    cnt=0;
    tot=1;
    memset(ch,0,sizeof(ch));
    for(int i=1;i<=n;i++){
        g[i].clear();
    }
}
int newnode(){
    memset(ch[tot],0,sizeof(ch[tot]));
    sz[tot]=0;
    return tot++;
}
void insert(int p,int u,int val){
    p=rt[p];
    u=rt[u];
    for(int i=30;i>=0;i--){
        int id=(val>>i)&1;
        if(!ch[u][id]){
            ch[u][id]=newnode();
            ch[u][id^1]=ch[p][id^1];
            sz[ch[u][id]]=sz[ch[p][id]];
        }
        u=ch[u][id];
        p=ch[p][id];
        sz[u]++;
    }
}
int query(int u,int x){
    //前缀和思想
    int l=rt[in[u]-1];
    int r=rt[out[u]];
    int ans=0;
    for(int i=30;i>=0;i--){
        int id=(x>>i)&1;
        //贪心求异或最大
        if(sz[ch[r][id^1]]-sz[ch[l][id^1]]>0){
            ans+=(1<<i);
            id^=1;
        }
        l=ch[l][id];
        r=ch[r][id];
        
    }
    return ans;
}
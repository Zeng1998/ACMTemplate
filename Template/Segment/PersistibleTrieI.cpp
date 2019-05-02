/*
 * 可持久化字典树查询树上任意两个节点路径间某个数与所给值的最大异或值
 * rt[i]: i节点对应的trie树的根
 * ch[][],sz[],tot: 字典树，注意空间开大，sz[i]表示根节点到该节点形成的前缀出现的累计的次数
 * d[],fa[][]: 倍增求lca
 */ 
//创建字典树节点
int newnode(){
    memset(ch[tot],0,sizeof(ch[tot]));
    sz[tot]=0;
    return tot++;
}
void insert(int p,int u,int val){
    //每个节点对应创建一颗字典树,dfs序对应的根的顺序
    p=rt[p];
    u=rt[u];
    for(int i=31;i>=0;i--){
        int id=(val>>i)&1;
        if(!ch[u][id]){
            //当前trie树的节点，剩下的指针指向上一棵树的对应节点位置
            ch[u][id]=newnode();
            ch[u][id^1]=ch[p][id^1];
            //复制上一棵树信息
            sz[ch[u][id]]=sz[ch[p][id]];
        }
        u=ch[u][id];
        p=ch[p][id];
        //u就是当前的trie树特有的节点，所以sz++
        sz[u]++;
    }
}
//dfs序建可持久化trie树
void dfs(int u){
    //u的祖先节点信息都已知，所以同时处理出fa[u]
    for(int i=1;(1<<i)<=d[u];i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    rt[u]=newnode();
    insert(fa[u][0],u,a[u]);
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i];
        if(v==fa[u][0]){
            continue;
        }
        fa[v][0]=u;
        d[v]=d[u]+1;
        dfs(v);
    }
}
int lca(int x,int y){
    //lca省略
}
int query(int x,int y,int val){
    int lc=lca(x,y);
    //单独考虑lca的异或值，因为后面减去两倍lca的贡献，等于除去了lca
    int res=a[lc]^val;
    x=rt[x];
    y=rt[y];
    lc=rt[lc];
    int ans=0;
    for(int i=31;i>=0;i--){
        int id=(val>>i)&1;
        //类似于求两点间的距离dis[u]+dis[v]-2*dis[lca(u,v)]
        //dis表示到根的距离，而这里sz表示的是点到根的所有字典树的这一位上这个值的前缀和
        if(sz[ch[x][id^1]]+sz[ch[y][id^1]]-2*sz[ch[lc][id^1]]>0){
            ans+=(1<<i);
            id=id^1;
        }
        x=ch[x][id];
        y=ch[y][id];
        lc=ch[lc][id];
    }
    return max(ans,res);
}
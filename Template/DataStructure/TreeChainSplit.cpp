/**
 * 给出一棵带点权的树，三种操作，修改某个点权，查询u v路径上的最大点权和点权和
 */ 
#include <bits/stdc++.h>
using namespace std;
#define lson i<<1
#define rson i<<1|1
#define mid (l+r)/2
const int N=1e6+50;
const int INF=0x3f3f3f3f;
struct Edge{
    int v,next;
}edge[N*2];
int cnt,head[N];
void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}
void add(int u,int v){
    edge[cnt]=Edge{v,head[u]};
    head[u]=cnt++;
    edge[cnt]=Edge{u,head[v]};
    head[v]=cnt++;
}
int n,q,u,v,clk;
char qu[10];
//点权，父节点，子树大小，节点深度，重儿子，dfs序双向映射，重链顶点
int a[N],fa[N],siz[N],dep[N],son[N],rk[N],id[N],top[N];
void dfs1(int u,int f,int d){
    fa[u]=f;
    dep[u]=d;
    siz[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==f){
            continue;
        }
        dfs1(v,u,d+1);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]){
            son[u]=v;
        }
    }
}
void dfs2(int u,int t){
    top[u]=t;
    id[u]=++clk;
    rk[clk]=u;
    //只连接重链
    if(!son[u]){
        return;
    }
    dfs2(son[u],t);
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v!=son[u] && v!=fa[u]){
            //轻儿子本身一条链
            dfs2(v,v);           
        }
    }
}
int mx[N],sum[N];
void pushup(int i){
    mx[i]=max(mx[lson],mx[rson]);
    sum[i]=sum[lson]+sum[rson];
}
void build(int i,int l,int r){
    //mx要清空为负inf
    mx[i]=-INF;
    sum[i]=0;
    if(l==r){
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(i);
}
void update(int i,int l,int r,int p,int v){
    if(l==r && l==p){
        sum[i]=mx[i]=v;
        return;
    }
    if(p<=mid){
        update(lson,l,mid,p,v);
    }else{
        update(rson,mid+1,r,p,v);
    }
    pushup(i);
}
int ans;
int query(int i,int l,int r,int ql,int qr,int o){
    if(l>=ql && r<=qr){
        if(o==1){
            return mx[i];
        }else{
            return sum[i];
        }
    }
    int ans=0;
    if(o==1){
        ans=-INF;
        if(ql<=mid){
            ans=max(ans,query(lson,l,mid,ql,qr,o));
        }
        if(qr>mid){
            ans=max(ans,query(rson,mid+1,r,ql,qr,o));
        }
    }else{
        ans=0;
        if(ql<=mid){
            ans+=query(lson,l,mid,ql,qr,o);
        }
        if(qr>mid){
            ans+=query(rson,mid+1,r,ql,qr,o);
        }
    }
    return ans;
}
int solve(int u,int v,int o){
    int res;
    if(o==1){
        res=-INF;
    }else{
        res=0;
    }
    //重链top节点或者本身
    //最好不要直接swap，有时候不能要交换的不是比较的值
    int fu=top[u],fv=top[v];
    while(fu!=fv){
        if(dep[fu]>=dep[fv]){
            if(o==1){
                //计算重链贡献，如果是轻链则为本身节点
                res=max(res,query(1,1,n,id[fu],id[u],1));
            }else{
                res+=query(1,1,n,id[fu],id[u],2);
            }
            //走上下一条链，别写错成u=fa[u] 这条重链已经计算过，要直接跳到fa[fu]
            u=fa[fu];
            fu=top[u];
        }else{
            if(o==1){
                res=max(res,query(1,1,n,id[fv],id[v],1));
            }else{
                res+=query(1,1,n,id[fv],id[v],2);
            }
            v=fa[fv];
            fv=top[v];
        }
    }
    if(id[u]>id[v]){
        if(o==1){
            res=max(res,query(1,1,n,id[v],id[u],1));
        }else{
            res+=query(1,1,n,id[v],id[u],2);
        }
    }else{
        if(o==1){
            res=max(res,query(1,1,n,id[u],id[v],1));
        }else{
            res+=query(1,1,n,id[u],id[v],2);
        }
    }
    return res;
}
int main(void){
    scanf("%d",&n);
    init();
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    dfs1(1,0,0);
    dfs2(1,1);
    build(1,1,n);
    for(int i=1;i<=n;i++){
        update(1,1,n,id[i],a[i]);
    }
    scanf("%d",&q);
    while(q--){
        scanf("%s %d%d",qu,&u,&v);
        if(qu[0]=='C'){
            update(1,1,n,id[u],v);
        }else{
            int res=0;
            if(qu[1]=='M'){
                res=solve(u,v,1);
            }else{
                res=solve(u,v,2);
            }
            printf("%d\n",res);
        }
    }
    return 0;
}
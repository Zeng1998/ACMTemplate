#include <bits/stdc++.h>
using namespace std;
#define lson i<<1
#define rson i<<1|1
#define mid (l+r)/2
const int N=2e5+50;
const int M=4e5+50;
int n,q,x,o,a[N];
char s[10];
struct Edge{
    int v,next;
}edge[M];
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
int clk,in[N],out[N],rk[N];
void dfs(int u,int f){
    in[u]=++clk;
    rk[clk]=u;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(v==f){
            continue;
        }
        dfs(v,u);
    }
    out[u]=clk;
}
int sum[N*4],lazy[N*4];
void pushup(int i){
    sum[i]=sum[lson]+sum[rson];
}
void build(int i,int l,int r){
    if(l==r){
        sum[i]=a[rk[l]];
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(i);
}
void pushdown(int i,int l,int r){
    if(lazy[i]){
        lazy[lson]^=lazy[i];
        lazy[rson]^=lazy[i];
        sum[lson]=mid-l+1-sum[lson];
        sum[rson]=r-mid-sum[rson];
        lazy[i]=0;
    }
}
void update(int i,int l,int r,int ql,int qr){}
int query(int i,int l,int r,int ql,int qr){}
bool isF[N];
int main(void){
    scanf("%d",&n);
    init();
    for(int i=2;i<=n;i++){
        scanf("%d",&x);
        add(x,i);
        isF[x]=true;
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    scanf("%d",&q);
    while(q--){
        scanf("%s %d",s,&o);        
        if(s[0]=='p'){
            //区间更新，如果单点更新in[o]即可
            update(1,1,n,in[o],out[o]);
        }else if(s[0]=='g'){
            //子树查询转化为区间查询
            int ans=query(1,1,n,in[o],out[o]);
            printf("%d\n",ans);
        }
    }
    return 0;
}
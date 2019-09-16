#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+50;
struct Edge{
    int v,next;
}e[N];
int cnt,head[N];
void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}
void add(int u,int v){
    e[cnt]=Edge{v,head[u]};
    head[u]=cnt++;
}
int n,f;
ll m,l[N],w[N],ans,sum[N];
int ls[N],rs[N],dis[N],siz[N];
int merge(int a,int b){
    if(!a || !b){
        return a+b;
    }
    if(w[a]<w[b]){
        swap(a,b);
    }
    //a作为新根，右儿子和b合并
    rs[a]=merge(rs[a],b);
    //维护左偏性质
    if(dis[ls[a]]<dis[rs[a]]){
        swap(ls[a],rs[a]);
    }
    dis[a]=dis[rs[a]]+1;
    return a;
}
int pop(int a){
    //弹出堆顶元素即把左右儿子合并
    int rt=merge(ls[a],rs[a]);
    ls[a]=rs[a]=dis[a]=0;
    return rt;
}
//在u的子树中找到sum(w[v])小于m，使得siz*l[u]最大
int dfs(int u){
    int a=u;
    sum[u]=w[u];
    siz[u]=1;
    for(int i=head[u];i!=-1;i=e[i].next){
        int v=e[i].v;
        int b=dfs(v);
        a=merge(a,b);
        sum[u]+=sum[v];
        siz[u]+=siz[v];
    }
    while(sum[u]>m){
        sum[u]-=w[a];
        siz[u]--;
        a=pop(a);
    }
    ans=max(ans,l[u]*siz[u]);
    return a;
}
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d%lld",&n,&m);
    init();
    int root;
    for(int i=1;i<=n;i++){
        scanf("%d%lld%lld",&f,&w[i],&l[i]);
        if(f){
            add(f,i);
        }else{
            root=i;
        }
    }
    dfs(root);
    printf("%lld\n",ans);
}
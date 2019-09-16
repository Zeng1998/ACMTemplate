#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+50;
struct Edge{
    int v,next;
}e[N],ct[N];
int cnt1,cnt2,head1[N],head2[N];
void init(){
    cnt1=0;
    cnt2=0;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head1));
}
void add(int u,int v,bool tr){
    if(tr){
        e[cnt1]=Edge{v,head1[u]};
        head1[u]=cnt1++;
    }else{
        ct[cnt2]=Edge{v,head2[u]};
        head2[u]=cnt2++;
    }
}
int n,m,fa,fi[N],sis[N],k[N],ls[N],rs[N],dis[N],dep[N];
ll f[N],ai[N],vi[N],g[N],ad[N],mu[N];
//对a子树计算标记
void fun(int a,ll add,ll mul){
    if(a){
        g[a]*=mul;
        g[a]+=add;
        ad[a]*=mul;
        ad[a]+=add;
        mu[a]*=mul;
    }
}
void pushdown(int a){
    fun(ls[a],ad[a],mu[a]);
    fun(rs[a],ad[a],mu[a]);
    ad[a]=0;
    mu[a]=1;
}
int merge(int a,int b){
    if(!a || !b){
        return a+b;
    }
    pushdown(a);
    pushdown(b);
    if(g[a]>g[b]){
        swap(a,b);
    }
    rs[a]=merge(rs[a],b);
    if(dis[ls[a]]<dis[rs[a]]){
        swap(ls[a],rs[a]);
    }
    dis[a]=dis[rs[a]]+1;
    return a;
}
int pop(int a){
    pushdown(a);
    return merge(ls[a],rs[a]);
}
int dfs(int u,int d){
    //因为是小根堆，这里是a=0，如果是大根堆，a=u
    int a=0;
    dep[u]=d;
    //合并在这个城池开始的所有骑士
    for(int i=head2[u];i!=-1;i=ct[i].next){
        int v=ct[i].v;
        a=merge(a,v);
    }
    //合并能从下面上来到这个城池的骑士
    for(int i=head1[u];i!=-1;i=e[i].next){
        int v=e[i].v;
        a=merge(a,dfs(v,d+1));
    }
    //攻击力不够的骑士死在这个城池，记录死的位置，通过深度可知占领的城池数
    while(a && g[a]<f[u]){
        k[a]=u;
        sis[u]++;
        a=pop(a);
    }
    //更新攻击力，回溯到上一层城池进行攻击
    if(ai[u]){
        fun(a,0,vi[u]);
    }else{
        fun(a,vi[u],1);
    }
    return a;
}
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&f[i]);
    }
    init();
    for(int i=2;i<=n;i++){
        scanf("%d%lld%lld",&fa,&ai[i],&vi[i]);
        add(fa,i,true);
    }
    for(int i=1;i<=m;i++){
        scanf("%lld%d",&g[i],&fi[i]);
        add(fi[i],i,false);
    }
    dfs(1,1);
    for(int i=1;i<=n;i++){
        printf("%d\n",sis[i]);
    }
    for(int i=1;i<=m;i++){
        printf("%d\n",dep[fi[i]]-dep[k[i]]);
    }
    return 0;
}
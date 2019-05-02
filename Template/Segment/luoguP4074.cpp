/*
 * 给一棵树，树上每个节点有一个糖果，一共有m种糖果美味度分别为vi，每个游客第i次吃同种糖果的新奇度wi
 * 多组询问: l到r路径上的sum(vi*wi) (注意wi是会随着同种糖果的多次访问而变化)
 */ 
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+50;
int n,m,q,l,r,t,cnt1,cnt2,tot,clk;
vector<int> g[N];
int be[N<<1];
int pw[25];
//用于倍增求lca f[u][i]表示从u往上跳2^i格可以到达的点
int fa[N][17];
int c[N],d[N];
int v[N],w[N],now[N];
//表示第几次访问这个糖果，从而间接访问了wi
int u[N];
//标记是否访问，每次访问就^1，这样子树的节点一进一出最后就不会影响结果的贡献
//(因为l和r的路径是不含有l或r的子树的，但是dfs序有)
bool vis[N];
struct Q{
    int id,l,r,tim;
}a[N];
struct Change{
    int pos,New,Old;
}ch[N];
ll ans[N],sum;
//dfs序
int id[N<<1],in[N],out[N];
void dfs(int u){
    //双向映射
    in[u]=++clk;
    id[clk]=u;
    //倍增
    for(int i=1;pw[i]<=d[u];i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(v!=fa[u][0]){
            //fa[v][0]即v往上跳1即v的父节点
            fa[v][0]=u;
            //深度
            d[v]=d[u]+1;
            dfs(v);
        }
    }
    out[u]=++clk;
    id[clk]=u;
}
int lca(int x,int y){
    if(d[x]<d[y]){
        swap(x,y);
    }
    int tmp=d[x]-d[y];
    for(int i=0;pw[i]<=tmp;i++){
        //往上跳
        if(tmp&pw[i]){
            x=fa[x][i];
        }
    }
    //跳到刚好，即y=lca(x,y)
    if(x==y){
        return x;
    }
    for(int i=16;i>=0;i--){
        //x和y一起跳
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
bool cmp(Q x,Q y){
    return be[x.l]==be[y.l]?(be[x.r]==be[y.r]?x.tim<y.tim:x.r<y.r):x.l<y.l;
}
//修改节点，即修改答案贡献
void revise(int x){
    if(vis[x]){
        //之前访问过，那再修改的话，就要把前面计算的贡献减去
        sum-=1ll*v[c[x]]*w[u[c[x]]--];
    }else{
        //反之加上贡献
        sum+=1ll*v[c[x]]*w[++u[c[x]]];
    }
    //标记访问一次，状态反转
    vis[x]^=1;
}
//在这个时间点，把节点x修改为颜色y
void going(int x,int y){
    if(vis[x]){
        //之前访问过的，必须修改贡献
        revise(x);
        //先减贡献，修改节点值，再加贡献
        c[x]=y;
        revise(x);
    }else{
        //之前没访问过的直接修改
        c[x]=y;
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    pw[0]=1;
    for(int i=1;i<=17;++i){
        pw[i]=pw[i-1]*2;
    }
    for(int i=1;i<=m;++i){
        scanf("%d",&v[i]);
    }
    for(int i=1;i<=n;++i){
        scanf("%d",&w[i]);
    }
    //建树
    for(int i=1;i<n;++i){
        int l,r;scanf("%d%d",&l,&r);
        g[l].push_back(r);
        g[r].push_back(l);
    }
    for(int i=1;i<=n;++i){
        scanf("%d",&c[i]);
        //now记录当前状态用于修改和恢复
        now[i]=c[i];
    }
    //分块单位
    int unit=pow(n,2.0/3);
    //构造dfs序，将树结构转化为序列
    dfs(1);
    for(int i=1;i<=clk;++i){
        //分块
        be[i]=i/unit+1;
    }
    while(q--){
        scanf("%d%d%d",&t,&l,&r);
        if(t){
            //询问
            if(in[l]>in[r]){
                swap(l,r);
            }
            a[++cnt1]=Q{cnt1,(lca(l,r)==l)?in[l]:out[l],in[r],cnt2};
        }else{
            //修改，把l的值修改成r，原来的值是now[l]
            ch[++cnt2]=Change{l,r,now[l]};
            now[l]=r;
        }
    }
    sort(a+1,a+1+cnt1,cmp);
    //初始化空区间 l=1 r=0
    l=1,r=0,t=0;
    for(int i=1;i<=cnt1;++i){
        //同普通带修莫队，先处理时序
        while(t<a[i].tim){
            going(ch[t+1].pos,ch[t+1].New);
            t++;
        }
        while(t>a[i].tim){
            going(ch[t].pos,ch[t].Old);
            t--;
        }
        //再处理空间，注意要用id映射，同普通带修莫队
        while(l<a[i].l){
            revise(id[l]);
            l++;
        }
        while(l>a[i].l){
            revise(id[l-1]);
            l--;
        }
        while(r<a[i].r){
            revise(id[r+1]);
            r++;
        }
        while(r>a[i].r){
            revise(id[r]);
            r--;
        }
        //树上莫队特殊处理
        int x=id[l],y=id[r],tmp=lca(x,y);
        if(x!=tmp&&y!=tmp){
            //xy分别在lca两边，则lca这个点只算了一次，需要再更新一次贡献
            //(可以写个dfs序看下，lca的dfs出序刚好是区间右端点+1)
            revise(tmp);
            ans[a[i].id]=sum;
            revise(tmp);
        }else{
            //x或y是lca(x,y)，直接记录答案
            ans[a[i].id]=sum;
        }
    }
    for(int i=1;i<=cnt1;i++){
        printf("%lld\n",ans[i]);
    }
}
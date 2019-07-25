//莫队核心就是如何从[l,r]的答案推出[l-1,r],[l+1,r],[l,r-1],[l,r+1]的答案
//复杂度O(n*sqrt(n)*区间移动操作)
//分块
bel[i]=(i-1)/block+1;
//询问的排序
struct Q{
    int id,l,r,ans;
}que[N];
bool cmp1(Q a,Q b){ 
    return bel[a.l]==bel[b.l]?a.r<b.r:a.l<b.l;
}
//奇偶排序优化
bool cmp1(Q a,Q b){
    return (bel[a.l])^(bel[b.l])?a.l<b.l:(((bel[a.l])&1)?a.r<b.r:a.r>b.r);
}
//询问区间移动
int l=1,r=0;
ans=0;
for(int i=0;i<q;i++){
    while(l<que[i].l){
        del(l++);
    }
    while(r>que[i].r){
        del(r--);
    }
    while(l>que[i].l){
        add(--l);
    }
    while(r<que[i].r){
        add(++r);
    }
    que[i].ans=ans;
}
//add和del函数
//1. 区间不同数个数
void add(int i){
    if(++cnt[a[i]]==1){
        ans++;
    }
}
void del(int i){
    if(--cnt[a[i]]==0){
        ans--;
    }
}
//2. 异或值为K的子区间个数
void add(int i){
    ans+=1ll*cnt[pre[i]^k];
    cnt[pre[i]]++;

}
void del(int i){
    cnt[pre[i]]--;
    ans-=1ll*cnt[pre[i]^k];
}
//3. 维护区间公式
//区间内选的两个数相同的概率，需要维护每个数出现次数平方和
void add(int i){
    zi--;
    zi+=(2ll*cnt[a[i]]+1);
    cnt[a[i]]++;
}
void del(int i){
    zi++;
    zi-=(2ll*cnt[a[i]]-1);
    cnt[a[i]]--;
}
//4. 询问区间存在性答案
//是否存在a+b=k b-a=k a*b=k
//两个bitset一个维护x一个维护N-x的存在性
void add(int i){
    if(++cnt[a[i]]==1){
        forw[a[i]]=1;
        rev[N-a[i]]=1;
    }
}
void del(int i){
    if(--cnt[a[i]]==0){
        forw[a[i]]=0;
        rev[N-a[i]]=0;
    }
}
//统计答案
int x=que[i].x;
if(que[i].opt==1){
    //有任意a和a+x同时存在
    if((forw & (forw << x)).any()){
        que[i].ans=1;
    }
}else if(que[i].opt==2){
    //求a+b=x即N-b-a=N-x
    //即有任意a和N-b-(N-x)同时存在，即forw & rev >> N-x
    if((forw &(rev >> N-x)).any()){
        que[i].ans=1;
    }
}else{
    //暴力枚举因子
    for(int j=1;j<=(int)sqrt(x);j++){
        if(x%j==0){
            if(forw[j] && forw[x/j]){
                que[i].ans=1;
                break;
            }
        }
    }
}
//5. 询问区间区间逆序数(莫队+树状数组)
void add(int i,int x){}
void query(int i){}
for(int i=0;i<m;i++){
	while(l<que[i].l){
		add(a[l],-1);
        ans-=query(a[l]-1);
        l++;
    }
	while(r>que[i].r){
		add(a[r],-1);
        ans-=r-l-query(a[r]);
        r--;
    }
	while(l>que[i].l){
		l--;
        add(a[l],1);
        ans+=query(a[l]-1);
    }
	while(r<que[i].r){
		r++;
        add(a[r],1);
        now+=r-l+1-query(a[r]);
    }
	que[i].ans=ans;
}
//带修莫队，多了时序的表示
struct Q{
    //tim表示发生在第几次修改之后的询问
    int id,l,r,tim,ans;
}que[N];
bool cmp1(Q a,Q b){
    return bel[a.l]==bel[b.l]?(bel[a.r]==bel[b.r]?a.tim<b.tim:a.r<b.r):a.l<b.l;
}
//修改，当前时刻将a[x]修改为d
void going(int x,int d){
    //修改的位置影响当前询问区间
    if(x>=l && x<=r){
        del(a[x]);
        add(d);
    }
    a[x]=d;
}
//先维护时间顺序
int T=0;
for(int i=0;i<qcnt;i++){
    //维护时间
    while(T<que[i].tim){
        going(c[T].pos,c[T].New);
        T++;
    }
    while(T>que[i].tim){
        //T当前的修改还未执行(初始化T=0，但T为0时的修改并未执行，所以无需抵消T的修改)
        T--;
        going(c[T].pos,c[T].Old);
    }
    //...
}
//树上带修莫队
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
    //这个点访问过，这个时刻的修改会影响到当前询问区间
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
            //如果l就是lca(l,r)，起点就是in[l]，否则起点就是out[l]
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
            t++;
            going(ch[t].pos,ch[t].New);
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
        while(r>a[i].r){
            revise(id[r]);
            r--;
        }
        while(l>a[i].l){
            l--;
            revise(id[l]);
        }
        while(r<a[i].r){
            r++;
            revise(id[r]);
        }
        //树上莫队特殊处理
        int x=id[l],y=id[r],tmp=lca(x,y);
        if(x!=tmp&&y!=tmp){
            //xy分别在lca两边，则lca这个点只算了一次
            //(可以写个dfs看下，lca的dfs出序刚好是区间右端点+1)，需要再更新一次贡献
            revise(tmp);
            revise(tmp);
        }
        //x或y是lca(x,y)，直接记录答案
        ans[a[i].id]=sum;
    }
    for(int i=1;i<=cnt1;i++){
        printf("%lld\n",ans[i]);
    }
}
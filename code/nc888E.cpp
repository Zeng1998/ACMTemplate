#include<bits/stdc++.h>
using namespace std;
#define ls tr[u][0]
#define rs tr[u][1]
const int N=4e5+50;
struct Edge{
    int u,v,l,r;
    //按r值从大到小排序，LCT维护l值最大值
    bool operator <(const Edge& rhs)const{
        return r>rhs.r;
    }
}e[N];
struct LCT{
    int fa[N],tr[N][2],xr[N],lz[N],mx[N];
    int q[N],top;
    //维护信息，这里维护l最最大值的位置
    void pushup(int u){
        mx[u]=u;
        if(ls && e[mx[ls]].l>e[mx[u]].l){
            mx[u]=mx[ls];
        }
        if(rs && e[mx[rs]].l>e[mx[u]].l){
            mx[u]=mx[rs];
        }
    }
    //区间翻转，左右子树交换
    void change(int u){
        int temp=ls;
        ls=rs;
        rs=temp;
        lz[u]^=1;
    }
    //下传标记
    void pushdown(int u){
        if(lz[u]){
            if(ls){
                change(ls);
            }
            if(rs){
                change(rs);
            }
            lz[u]=0;
        }
    }
    //判断u是否为acplay的根，父节点是Path father
    bool isroot(int u){
        return (tr[fa[u]][0]!=u && tr[fa[u]][1]!=u);
    }
    int get(int x){
        return tr[fa[x]][1]==x;
    }
    int connect(int x,int f,int son){
        fa[x]=f;
        tr[f][son]=x;
    }
    //acplay单旋
    void rotate(int x){
        int y=fa[x];
        int z=fa[y];
        int xs=get(x);
        int ys=get(y);
        //区别于普通acplay，如果y已经是acplay的根，z就不属于该acplay
        if(!isroot(y)){
            connect(x,z,ys);
        }else{
            fa[x]=z;
        }
        int b=tr[x][xs^1];
        connect(b,y,xs);
        connect(y,x,xs^1);
        pushup(y);
        pushup(x);
    }
    void splay(int x){
        //区别于普通acplay
        top=1;
        q[top]=x;
        int i=x;
        while(!isroot(i)){
            q[++top]=fa[i];
            i=fa[i];
        }
        while(top){
            pushdown(q[top--]);
        }
        while(!isroot(x)){
            int y=fa[x];
            int z=fa[y];
            if(!isroot(y)){
                rotate(get(x)==get(y)?y:x);
            }
            rotate(x);
        }
    }
    //打通根到u的实链，得到一个中序遍历以根开始、以u结束的acplay
    void access(int u){
        int x=0;
        //u不为整个LCT的根
        while(u){
            //将u旋到根
            splay(u);
            //断开右子树，将x接在u的右子树
            connect(x,u,1);
            pushup(u);
            //往上爬
            x=u;
            u=fa[u];
        }
    }
    //将u变为整个LCT的根
    void makeroot(int u){
        //access后，u成为所在acplay中深度最大的点
        access(u);
        //splay后，u旋至acplay的根，没有右儿子
        splay(u);
        //翻转整个acplay，u没有左子树，也就是u是深度最小的点，也就是LCT的根
        change(u);
    }
    //查找u所在原树的根
    int find(int u){
        //构造出新的acplay后，不断找左儿子，即深度小的
        access(u);
        //find(u)会把u旋至acplay的根
        splay(u);
        while(ls){
            pushdown(u);
            u=ls;
        }
        return u;
    }
    //拉出一条u-v的路径用acplay维护，以v为根
    void split(int u,int v){
        makeroot(u);
        access(v);
        splay(v);
    }
    //断开边(u,v)
    void cut(int u,int v){
        makeroot(u);
        //(u,v)不一定合法
        //1.边存在 2.v是u的父节点 3.v没有右儿子
        //find(v)调用了access(v)，u到v的实链构造一个acplay，v成了acplay的根
        if(find(v)==u && fa[u]==v && !rs){
            fa[u]=tr[v][0]=0;
            pushup(v);
        }
    }
    //连轻边(x,y)
    void link(int u,int v){
        makeroot(u);
        if(find(v)!=u){
            fa[u]=v;
        }
    }
    //查询路径max(li)的位置
    int query(int u,int v){
        makeroot(v);
        access(u);
        splay(u);
        return mx[u];
    }
}ac;
vector<pair<int,int> > vec;
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].l,&e[i].r);
    }
    sort(e+1,e+m+1);
    //main
    //r从大到小枚举，当前e[i].r就是已加入LCT的边中r值最小的边
    //而LCT就必须维护最小的(最大的l值)，也就是max(li)的最小生成树，[l,r]就是这个路径的线段交
    for(int i=1;i<=m;i++){
        int u=e[i].u;
        int v=e[i].v;
        if(ac.find(m+u)==ac.find(m+v)){
            //查询实点，(m+1...m+n)
            int t=ac.query(m+u,m+v);
            if(e[i].l<e[t].l){
                //维护最小生成树(删去原来的边，加入更小的边)
                ac.cut(t,m+e[t].u);
                ac.cut(t,m+e[t].v);
                ac.link(i,m+u);
                ac.link(i,m+u);
            }
        }else{
            //u和v未连通
            //LCT中节点分为边的编号和图节点的编号
            //建立虚拟点，将边权转化为LCT可以维护的点权
            //虚点(1..m)表示实际的边信息，实点(m+1..m+n)只表示点
            ac.link(i,m+u);
            ac.link(i,m+v);
        }
        //1-n连通，查询路径最大l值的位置(边的编号)
        if(ac.find(m+1)==ac.find(m+n)){
            int tmp=ac.query(m+1,m+n);
            if(e[tmp].l<=e[i].r){
                vec.push_back({e[tmp].l,e[i].r});
            }
        }
    }
    int siz=vec.size();
    //特判0 卡9%
    if(siz==0){
        printf("0\n");
        return 0;
    }
    //线段并
    sort(vec.begin(),vec.end());
    int lst=vec[0].second+1;
    int ans=vec[0].second-vec[0].first+1;
    for(int i=1;i<siz;i++){
        ans+=vec[i].second-max(lst,vec[i].first)+1;
        lst=max(lst,vec[i].second+1);
    }
    printf("%d\n",ans);
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define ls tr[u][0]
#define rs tr[u][1]
const int N=3e5+7;
int n,m,a[N],o,x,y;
struct LCT{
    int fa[N],tr[N][2],xr[N],lz[N],q[N],top;
    //维护信息，这里维护路径点权异或值
    void pushup(int u){
        xr[u]=xr[ls]^xr[rs]^a[u];
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
    //判断u是否为Splay的根，父节点是Path father
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
    //Splay单旋
    void rotate(int x){
        int y=fa[x];
        int z=fa[y];
        int xs=get(x);
        int ys=get(y);
        //区别于普通Splay，如果y已经是Splay的根，z就不属于该Splay
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
        //区别于普通Splay
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
    //打通根到u的实链，得到一个中序遍历以根开始、以u结束的Splay 
    void access(int u){
        /**
         * 先将x旋至所在Splay的根，然后断开右子树，然后沿着偏爱路径往上爬
         * 每遇到一条虚边，把虚边连向的节点y旋至所在Splay的根，断开y的右子树，并把x所在splay接在y的右子树
         * Splay中右儿子==>深度大，要打通的实链中u是深度最大的，从下往上
         * 因此每次将旋转后的Splay接到下一个Splay的右儿子上
         */
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
        //access后，u成为所在Splay中深度最大的点
        access(u);
        //splay后，u旋至Splay的根，没有右儿子
        splay(u);
        //翻转整个Splay，u没有左子树，也就是u是深度最小的点，也就是LCT的根
        change(u);
    }
    //查找u所在原树的根
    int find(int u){
        //构造出新的Splay后，不断找左儿子，即深度小的
        access(u);
        //find(u)会把u旋至Splay的根
        splay(u);
        while(ls){
            pushdown(u);
            u=ls;
        }
        //加上这个就WA了一个点
        // splay(u);
        return u;
    }
    //拉出一条u-v的路径用Splay维护，以v为根
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
        //find(v)调用了access(v)，u到v的实链构造一个Splay，v成了Splay的根
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
}T;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        T.xr[i]=a[i];
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&o,&x,&y);
        if(o==0){
            //构造出一个Splay维护路径(x,y)，根为y，xr[y]就是该Splay维护的信息
            T.split(x,y);
            printf("%d\n",T.xr[y]);
        }else if(o==1){
            T.link(x,y);
        }else if(o==2){
            T.cut(x,y);
        }else if(o==3){
            //先旋到根，再修改点权，pushup更新信息
            T.splay(x);
            a[x]=y;
            T.pushup(x);
        }
    }
    return 0;
} 
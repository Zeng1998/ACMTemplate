#include <bits/stdc++.h>
using namespace std;
const int N=1e6+50;
//因为是维护序列问题,所以splay里存的是下标而不是权值
int tr[N][2],fa[N];
int val[N];
int siz[N];
int rt;
int tot;
//懒惰标记数组(该子树是否需要旋转)
bool lazy[N];
void pushup(int x) {
    //这里节点维护的不是权值,所以直接+1,而不是加重复次数cnt[i]
    siz[x]=siz[tr[x][0]]+siz[tr[x][1]]+1;
}
void pushdown(int x){
    //左右子树互换并下传标记
    if (lazy[x]){
        swap(tr[x][0], tr[x][1]);
        lazy[tr[x][0]]^=1;
        lazy[tr[x][1]]^=1;
        lazy[x]^=1;
    }
}
int get(int x){
    return tr[fa[x]][1]==x;
}
void connect(int x,int f,int son){
    fa[x]=f;
    tr[f][son]=x;
}
void rotate(int x) {
    int y=fa[x];
    int yy=fa[y];
    int ys=get(y);
    int xs=get(x);
    //比普通splay多了pushdown的操作
    pushdown(x);
    pushdown(y);
    int b=tr[x][xs^1];
    connect(b,y,xs);
    connect(y,x,(xs^1));
    connect(x,yy,ys);
    pushup(y);
    pushup(x);
}
//x旋转到to的儿子
void splay(int x,int to){
    while(fa[x]!=to){
        int f=fa[x];
        int ff=fa[f];
        if(ff!=to){
            rotate(get(x)==get(f)?f:x);
        }
        rotate(x);
    }
    if(to==0){
        rt=x;
    }
}
int kth(int k) {
    int now=rt;
    while(true){
        pushdown(now);
        int t=siz[tr[now][0]]+1;
        if(k<t){
            now=tr[now][0];
        }else if(k>t){
            k-=t;
            now=tr[now][1];
        }else{
            break;
        }
    }
    //返回节点位置
    return now;
}
//解决区间最重要的就是提取区间
//提取区间[l,r]的方法就是将节点l-1旋转到根节点,将节点r+1旋转到根节点的右儿子
//此时根节点的右儿子的左子树就是提取的区间
//然后为了能够提取区间[1,n],我们设立两个哨兵节点1和n+1,把下标都+1
//所以要提取区间[l,r]也就是要旋转l-1和r+1,+1之后就是l和r+2
void reverse(int l, int r) {
    int x=kth(l);
    int y=kth(r+2);
    splay(x,0);
    splay(y,x);
    pushdown(rt);
    //根节点的右儿子的左儿子,标记翻转一次
    lazy[tr[y][0]]^=1;
}
void Build(int l,int r,int f) {
    if(l>r){
        return;
    }
    int mid=(l+r)/2;
    Build(l,mid-1,mid);
    Build(mid+1,r,mid);
    fa[mid]=f;
    //本题,下标和权值一样
    val[mid]=mid-1;
    pushup(mid);
    tr[f][mid>f]=mid;
}
int n,m,l,r;
int main(void) {
    scanf("%d%d",&n,&m);
    //增加两个哨兵节点
    Build(1,n+2,0);
    //中间的点即为根
    rt=(1+n+2)/2;
    for(int i=0;i<m;i++){
        scanf("%d%d",&l,&r);
        reverse(l,r);
    }
    for(int i=2;i<=n+1;i++){
        //维护的是下标,最后映射成权值
        printf("%d ", val[kth(i)]);
    }
    return 0;
}

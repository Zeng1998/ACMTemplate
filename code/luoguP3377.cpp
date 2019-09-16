#include <bits/stdc++.h>
using namespace std ;
const int N=1e5+50;
int n,m,o,x,y;
int dis[N],val[N],ls[N],rs[N],p[N];
void init(){
    for(int i=1;i<=n;i++){
        p[i]=i;
    }
}
int find(int x){
    return x==p[x]?p[x]:p[x]=find(p[x]);
}
int merge(int a,int b){
    if(!a || !b){
        return a+b;
    }
    //val[a]>val[b] 小根堆
    if(val[a]>val[b] || (val[a]==val[b] && a>b)){
        swap(a,b);
    }
    rs[a]=merge(rs[a],b);
    if(dis[ls[a]]<dis[rs[a]]){
        swap(ls[a],rs[a]);
    }
    //更新并查集的根
    p[ls[a]]=p[rs[a]]=p[a]=a;
    dis[a]=dis[rs[a]]+1;
    return a;
}
//删除x所在堆顶元素
void pop(int x){
    val[x]=-1;
    //先断开，更新并查集的根
    p[ls[x]]=ls[x];
    p[rs[x]]=rs[x];
    //合并，更新并查集的根
    p[x]=merge(ls[x],rs[x]);
    ls[x]=rs[x]=dis[x]=0;
}
int main(){
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    for(int i=0;i<m;i++){
        scanf("%d",&o);
        if(o==1){
            scanf("%d%d",&x,&y);
            int fx=find(x);
            int fy=find(y);
            if(val[x]==-1 || val[y]==-1 || fx==fy){
                continue;
            }
            p[fx]=p[fy]=merge(fx,fy);
        }else{
            scanf("%d",&x);
            if(val[x]==-1){
                printf("-1\n") ;
            }else{
                int fx=find(x);
                printf("%d\n",val[fx]);
                pop(fx);
            }
        }
    }
    return 0 ;
}

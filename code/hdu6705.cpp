#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e4+50;
struct Edge{
    int v;
    ll w;
    bool operator <(const Edge &rhs)const{
        return w<rhs.w;
    }
};
vector<Edge> g[N];
int T,n,m,q,k,u,v,w;
struct node{
    int u,id;
    ll w;
    bool operator <(const node &rhs)const{
        return w>rhs.w;
    }
};
int que[N];
ll ans[N];
priority_queue<node> pq;
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&q);
        for(int i=1;i<=n;i++){
            g[i].clear();
        }
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            g[u].push_back(Edge{v,1ll*w});
        }
        int mx=0;
        for(int i=1;i<=q;i++){
            scanf("%d",&que[i]);
            mx=max(mx,que[i]);
        }
        while(!pq.empty()){
            pq.pop();
        }
        for(int i=1;i<=n;i++){
            sort(g[i].begin(),g[i].end());
            if(g[i].size()>0){
                pq.push(node{i,0,g[i][0].w});
            }
        }
        int kk=0;
        //取一条加两条
        while(!pq.empty()){
            node tmp=pq.top();
            pq.pop();
            kk++;
            ans[kk]=tmp.w;
            /**
             * if(kk==que[i].k){
             *      i++;
             *      if(i>q){
             *          break;
             *      }
             * }
             * 这种写法是错的，如果有多个相同的k，只会计算第一个的答案，后面死循环
             */
            if(kk==mx){
                break;
            }
            int u=tmp.u;
            int id=tmp.id;
            int v=g[u][id].v;
            ll w=tmp.w;
            if(g[u].size()>id+1){
                pq.push(node{u,id+1,w-g[u][id].w+g[u][id+1].w});
            }
            if(g[v].size()>0){
                pq.push(node{v,0,w+g[v][0].w});
            }
        }
        for(int i=1;i<=q;i++){
            printf("%lld\n",ans[que[i]]);
        }
    }
    return 0;
}
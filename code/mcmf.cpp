#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
const int INF=0x3f3f3f3f;
int T,n,k,w[N];
struct Edge{
    int u,v,w,c,next;
}e[N];
int cnt,head[N];
void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}
void add(int u,int v,int w,int c){
    e[cnt]=Edge{u,v,w,c,head[u]};
    head[u]=cnt++;
    e[cnt]=Edge{v,u,0,-c,head[v]};
    head[v]=cnt++;
}
int d[N],inq[N],p[N],a[N];
int nc,s,t;
bool BF(int &flow,int &cost){
    for(int i=0;i<=nc;i++){
        d[i]=INF;
        inq[i]=false;
    }
    d[s]=0;
    p[s]=0;
    a[s]=INF;
    queue<int> q;
    q.push(s);
    inq[s]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(int i=head[u];i!=-1;i=e[i].next){
            int v=e[i].v;
            int w=e[i].w;
            int c=e[i].c;
            if(w>0 && d[v]>d[u]+c){
                d[v]=d[u]+c;
                p[v]=i;
                a[v]=min(a[u],w);
                if(!inq[v]){
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    if(d[t]==INF){
        return false;
    }
    flow+=a[t];
    cost+=d[t]*a[t];
    for(int u=t;u!=s;u=e[p[u]].u){
        e[p[u]].w-=a[t];
        e[p[u]^1].w+=a[t];
    }
    return true;
}
void mcmf(int &flow,int &cost){
    flow=0;
    cost=0;
    while(BF(flow,cost));
}
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
        }
        s=2*n+1;
        int s1=2*n+2;
        int t1=2*n+3;
        t=2*n+4;
        add(s,s1,k,0);
        add(t1,t,k,0);
        for(int i=1;i<=n;i++){
            add(s1,i,1,-w[i]);
        }
        for(int i=1;i<=n;i++){
            add(i,i+n,1,0);
        }
        for(int i=1;i<=n;i++){
            add(i+n,t1,1,0);
        }
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(w[j]>=w[i]){
                    add(i+n,j,1,-w[j]);
                }
            }
        }
        nc=2*n+4;
        int flow=0,cost=0;
        mcmf(flow,cost);
        printf("%d\n",-cost);
    }
    return 0;
}

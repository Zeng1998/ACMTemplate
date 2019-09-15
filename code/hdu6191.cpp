#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int n,q,a[N],f,u,x;
vector<int> g[N];
int cnt,tr[N*40][2],val[N*40];
int rt[N];
int insert(int pre,int x){
    int rt=++cnt;
    int now=rt;
    for(int i=31;i>=0;i--){
        int id=(x>>i)&1;
        if(!tr[now][id]){
            tr[now][id]=++cnt;
            tr[now][id^1]=tr[pre][id^1];
            val[tr[now][id]]=val[tr[pre][id]];
        }
        pre=tr[pre][id];
        now=tr[now][id];
        val[now]++;
    }
    return rt;
}
int query(int l,int r,int x){
    int ans=0;
    for(int i=31;i>=0;i--){
        int id=(x>>i)&1;
        if(val[tr[r][id^1]]-val[tr[l][id^1]]>0){
            l=tr[l][id^1];
            r=tr[r][id^1];
            ans=ans*2+1;
        }else{
            l=tr[l][id];
            r=tr[r][id];
            ans=ans*2;
        }
    }
    return ans;
}
int idx,in[N],ot[N],mp[N];
void dfs(int u,int f){
    in[u]=++idx;
    mp[idx]=u;
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i];
        if(v==f){
            continue;
        }
        dfs(v,u);
    }
    ot[u]=idx;
}
void init(){
    cnt=0;
    memset(tr,0,sizeof(tr));
    memset(val,0,sizeof(val));
    memset(rt,0,sizeof(rt));
    idx=0;
    memset(in,0,sizeof(in));
    memset(ot,0,sizeof(ot));
}
int main(void){
    // freopen("in.txt","r",stdin);
    while(~scanf("%d%d",&n,&q)){
        init();
        for(int i=1;i<=n;i++){
            g[i].clear();
            scanf("%d",&a[i]);
        }
        for(int i=2;i<=n;i++){
            scanf("%d",&f);
            g[f].push_back(i);
            g[i].push_back(f);
        }
        dfs(1,0);
        for(int i=1;i<=n;i++){
            rt[i]=insert(rt[i-1],a[mp[i]]);
        }
        while(q--){
            scanf("%d%d",&u,&x);
            int ans=query(rt[in[u]-1],rt[ot[u]],x);
            printf("%d\n",ans);
        }
    }
    return 0;
}
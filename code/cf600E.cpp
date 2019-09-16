//树上启发式合并，求子树出现次数最多的数之和
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+50;
int n,a[N],u,v;
vector<int> g[N];
int sz[N],son[N];
void dfs1(int u,int f){
    sz[u]=1;
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i];
        if(v==f){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]){
            son[u]=v;
        }
    }
}
bool vis[N];
int maxv;
ll sum,ans[N];
int hsh[N];
void calc(int u,int f,int k){
    //a[u]颜色++
    hsh[a[u]]+=k;
    //更新众数，计算答案
    if(k>0 && hsh[a[u]]==maxv){
        sum+=a[u];
    }
    if(k>0 && hsh[a[u]]>maxv){
        maxv=hsh[a[u]];
        sum=a[u];
    }
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i];
        //vis[v]=1 表示hsh数组中已经存了这棵子树
        //即暴力添加轻儿子信息
        if(v==f || vis[v]){
            continue;
        }
        calc(v,u,k);
    }
}
//z表示u是否是重儿子
void dfs2(int u,int f,bool z){
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i];
        if(v==f || v==son[u]){
            continue;
        }
        //先走轻儿子，处理完不保留信息
        dfs2(v,u,0);
    }
    //再走重儿子
    if(son[u]){
        dfs2(son[u],u,1);
        vis[son[u]]=1;
    }
    //计算u为根的子树答案
    calc(u,f,1);
    ans[u]=sum;
    //重儿子等父节点信息统计完再清空
    if(son[u]){
        vis[son[u]]=0;
    }
    if(!z){
        //擦除轻儿子贡献
        calc(u,f,-1);
        maxv=sum=0;
    }
}
int main(void){
    // freopen("in.txt","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0,0);
    for(int i=1;i<=n;i++){
        printf("%lld%c",ans[i],i==n?'\n':' ');
    }
    return 0;
}

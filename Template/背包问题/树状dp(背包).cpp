#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=10050;
struct node{
    int v,next;
}edge[MAXN];
int value;
int head[MAXN];
int vis[MAXN];
int dp[MAXN][2];
void addEdge(int x,int y){
    edge[value].v=y;
    edge[value].next=head[x];
    head[x]=value++;
    edge[value].v=x;
    edge[value].next=head[y];
    head[y]=value++;
}
void dfs(int u){
    //int i,j,k;
    vis[u]=1;
    //操作：u节点dp初始化
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(vis[v]){
            continue;
        }
        dfs(v);
        //操作：状态转移（子节点-->父节点）
    }
}
int main(void){
    //输入
    //建图 addEdge()
    //dfs(root)
    //输出
    addEdge(1,2);
    addEdge(2,3);
    addEdge(1,5);
    for(int i=0;i<6;i++){
        printf("edeg.v:%d ",edge[i].v);
        printf("edeg.next:%d \n",edge[i].next);
    }
    printf("\n");
    for(int i=1;i<=6;i++){
        printf("head:%d ",head[i]);
    }
    printf("\n");
}

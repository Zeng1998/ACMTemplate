#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+50;
struct SAM{
    int next[N*2][26];
    int fa[N*2],len[N*2],num[N*2],cnt,lst;
    int newnode(int l,int s){
        memset(next[cnt],0,sizeof(next[cnt]));
        len[cnt]=l;
        num[cnt]=s;
        return cnt++;
    }
    void init(){
        cnt=0;
        lst=newnode(0,0);
        fa[lst]=-1;
    }
    void add(int c){
        c-='a';
        int p=lst;
        int cur=newnode(len[p]+1,1);
        while(p!=-1 && !next[p][c]){
            next[p][c]=cur;
            p=fa[p];
        }
        if(p==-1){
            fa[cur]=0;
        }else{
            int q=next[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int cl=newnode(len[p]+1,0);
                fa[cl]=fa[q];
                memcpy(next[cl],next[q],sizeof(next[cl]));
                while(p!=-1 && next[p][c]==q){
                    next[p][c]=cl;
                    p=fa[p];
                }
                fa[q]=fa[cur]=cl;
            }
        }
        lst=cur;
    }
    ll dp[N*2],pd[N*2];
    int w[N],tp[N];
    void topo(int l){
        for(int i=0;i<=l;i++){
            w[i]=0;
        }
        for(int i=1;i<cnt;i++){
            w[len[i]]++;
        }
        for(int i=2;i<=l;i++){
            w[i]+=w[i-1];
        }
        for(int i=cnt-1;i>=1;i--){
            tp[w[len[i]]--]=i;
        }
    }
    void go(){
        for(int i=cnt-1;i>=1;i--){
            num[fa[tp[i]]]+=num[tp[i]];
        }
        //S状态是空串
        num[0]=0;
    }
    void dfs(int u){
        dp[u]=u==0?0:1ll;
        pd[u]=u==0?0:1ll*num[u];
        for(int i=0;i<26;i++){
            int v=next[u][i];
            if(v){
                if(!dp[v]){
                    dfs(v);
                }
                dp[u]+=dp[v];
                pd[u]+=pd[v];
            }
        }
    }
    //在以u节点开始的路径中查找第k小
    void solve1(int u,int k){
        if(k<=0){
            return;
        }
        for(int i=0;i<26;i++){
            int v=next[u][i];
            if(v){
                if(dp[v]>=k){
                    printf("%c",i+'a');
                    solve1(v,k-1);
                    break;
                }else{
                    k-=dp[v];
                }
            }
        }
    }
    void solve2(int u,int k){
        if(k<=num[u]){
            return;
        }
        for(int i=0;i<26;i++){
            int v=next[u][i];
            if(v){
                if(pd[v]>=k-num[u]){
                    printf("%c",i+'a');
                    solve2(v,k-num[u]);
                    break;
                }else{
                    k-=pd[v];
                }
            }
        }
    }
    void debug(){
        for(int i=0;i<cnt;i++){
            printf("%d %d %lld %lld\n",i,num[i],dp[i],pd[i]);
            for(int j=0;j<26;j++){
                if(next[i][j]){
                    printf("%c %d\n",'a'+j,next[i][j]);
                }
            }
        }
        for(int i=1;i<=dp[0];i++){
            printf("%d: ",i);
            solve1(0,i);
            printf("\n");
        }
        for(int i=1;i<=pd[0]-num[0];i++){
            printf("%d: ",i);
            solve2(0,i);
            printf("\n");
        }
    }
}ac;
int q;
ll k;
char s[N];
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%s",s);
    int n=strlen(s);
    ac.init();
    for(int i=0;i<n;i++){
        ac.add(s[i]);
    }
    ac.topo(n);
    ac.go();
    ac.dfs(0);
    scanf("%d%lld",&q,&k);
    if(q){
        //相同子串算多个
        if(k>ac.pd[0]){
            printf("-1\n");
            return 0;
        }
        ac.solve2(0,k);
        printf("\n");
    }else{
        //相同子串算一个
        if(k>ac.dp[0]){
            printf("-1\n");
            return 0;
        }
        ac.solve1(0,k);
        printf("\n");
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+50;
int vis[N],ndp[N],fdp[N];
struct PT{
    int next[N][26],fail[N],cnt[N],num[N],len[N];
    int S[N],last,id[N],n,p;
    int newnode(int l){
        for(int i=0;i<26;i++){
            next[p][i]=0;
        }
        cnt[p]=num[p]=0;
        len[p]=l;
        return p++;
    }
    void init(){
        p=0;
        newnode(0);
        newnode(-1);
        last=0;
        n=0;
        S[n]=-1;
        fail[0]=1;
    }
    int getFail(int x){
        while(S[n-len[x]-1]!=S[n]){
            x=fail[x];
        }
        return x;
    }
    void add(int c){
        c-='a';
        S[++n]=c;
        int cur=getFail(last);
        if(!next[cur][c]){
            int now=newnode(len[cur]+2);
            fail[now]=next[getFail(fail[cur])][c];
            num[now]=num[fail[now]]+1;
            next[cur][c]=now;
        }
        last=next[cur][c];
        cnt[last]++;
        id[last]=n;
    }
    void count(){
        for(int i=p-1;i>=0;i--){
            cnt[fail[i]]+=cnt[i];
        }
    }
    int dfs(int u){
        ndp[u]=1;
        fdp[u]=0;
        //计算向上跳的fail指针次数，vis保证不重复(比如bb跳的fail指针，bbbb不能再跳)，>1保证不走到奇偶根
        for(int t=u;!vis[t] && t>1;t=fail[t]){
            vis[t]=u;
            fdp[u]++;
        }
        for(int i=0;i<26;i++){
            if(next[u][i]){
                ndp[u]+=dfs(next[u][i]);
            }
        }
        //清空标记
        for(int t=u;vis[t]==u && t>1;t=fail[t]){
            vis[t]=0;
        }
        return ndp[u];
    }
    ll solve(){
        //从两个根dfs
        dfs(0);
        dfs(1);
        ll ans=0;
        for(int i=2;i<p;i++){
            //除去根，每个节点的贡献(作为另一个回文子串的子串)为
            //比如对于样例abba，回文节点bb的next指针指向abba，fail指针指向b
            //因此ndp和fdp都为2，贡献为2*2-1=3
            //即(b,bb) (b,abba) (bb,bb) (bb,abba)，减1就是要减掉本身
            ans+=1ll*ndp[i]*fdp[i]-1;
        }
        return ans;
    };
}ac;
int T;
char s[N];
int main(void){
    // freopen("in.txt","r",stdin);
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        scanf("%s",s);
        ac.init();
        int len=strlen(s);
        for(int i=0;i<len;i++){
            ac.add(s[i]);
        }
        ac.count();
        memset(vis,0,sizeof(vis));
        printf("Case #%d: %lld\n",cas,ac.solve());
    }
    return 0;
}
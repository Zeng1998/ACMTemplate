#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+50;
struct PT{
    int next[N][26],fail[N];
    int cnt[N],num[N],len[N];
    int S[N*2],last[2],L,R,id[N],n,p;
    ll ans;
    int newnode(int l){
        for(int i=0;i<26;i++){
            next[p][i]=0;
        }
        cnt[p]=0;
        num[p]=0;
        len[p]=l;
        return p++;
    }
    void init(int allLen){
        ans=0;
        p=0;
        newnode(0);
        newnode(-1);
        fail[0]=1;
        //两个last分别维护前端和后端插入
        last[0]=last[1]=0;
        //普通的后端插入是n从0开始，然后S[++n]
        //这里分为前后端插入，将S扩大两倍，后端插入的放在S[allLen...]，前端插入的放在S[0...allLen-1]
        //因为添加的时候是S[++R]和S[--L]，所以L初值为allLen，R初值为allLen-1
        L=allLen;
        R=allLen-1;
        memset(S,-1,sizeof(S));
    }
    int getFail(int x,int d){
        if(d){
            //后端添加
            while(S[R-len[x]-1]!=S[R]){
                x=fail[x];
            }
        }else{
            //前端添加
            while(S[L+len[x]+1]!=S[L]){
                x=fail[x];
            }
        }
        return x;
    }
    void add(int c,int d){
        c-='a';
        if(d){
            S[++R]=c;
        }else{
            S[--L]=c;
        }
        int cur=getFail(last[d],d);
        if(!next[cur][c]){
            int now=newnode(len[cur]+2);
            fail[now]=next[getFail(fail[cur],d)][c];
            num[now]=num[fail[now]]+1;
            next[cur][c]=now;
        }
        last[d]=next[cur][c];
        cnt[last[d]]++;
        //添加字符之后当前整个串为回文，修改另一个last
        if(len[last[d]]==R-L+1){
            last[d^1]=last[d];
        }
        ans+=1ll*num[last[d]];
    }
    void count(){
        for(int i=p-1;i>=0;i--){
            cnt[fail[i]]+=cnt[i];
        }
    }
}ac;
int n,op;
char s[3];
int main(){
//    freopen("in.txt","r",stdin);
    while(~scanf("%d",&n)){
        ac.init(n);
        for(int i=0;i<n;i++){
            scanf("%d",&op);
            if(op==1){
                scanf("%s",s);
                ac.add(s[0],0);
            }else if(op==2){
                scanf("%s",s);
                ac.add(s[0],1);
            }else if(op==3){
                //不同回文子串个数
                printf("%d\n",ac.p-2);
            }else{
                //回文子串个数
                printf("%lld\n",ac.ans);
            }
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+50;
const ll mod=20071027;
char s[N];
int n;
int tr[N*2][26],cnt,val[N*2];
ll dp[N*2];
char w[105];
void init(){
    memset(tr,0,sizeof(tr));
    cnt=0;
    memset(val,0,sizeof(val));
    memset(dp,0,sizeof(dp));
}
void insert(char *s){
    int len=strlen(s);
    int now=0;
    for(int i=0;i<len;i++){
        int id=s[i]-'a';
        if(!tr[now][id]){
            tr[now][id]=++cnt;
        }
        now=tr[now][id];
    }
    val[now]++;
}
void query(char *s,int len,int x){
    int now=0;
    //因为包含一个已确定字符s[0],所以是<=len
    for(int i=0;i<=len;i++){
        int id=s[i]-'a';
        if(!tr[now][id]){
            break;
        }else if(val[tr[now][id]]){
            dp[x]=(dp[x]+dp[x+i+1])%mod;
        }
        now=tr[now][id];
    }
}
int main(void){
    // freopen("in.txt","r",stdin);
    int cas=1;
    while(~scanf("%s",s)){
        init();
        scanf("%d",&n);
        int len=strlen(s);
        for(int i=0;i<n;i++){
            scanf("%s",w);
            insert(w);
        }
        //dp[i]表示s[i...len-1]这个串由单词表示的方案数
        //dp[i]+=dp[j] s[i...j-1]是单词
        dp[len]=1;
        for(int i=len-1;i>=0;i--){
            //所以这里要查询以s[i]开头,长度为min(len-i,100)的单词数,累加其方案数
            query(s+i,min(100,len-i+1),i);
        }
        printf("Case %d: %lld\n",cas++,(dp[0]%mod+mod)%mod);
    }
    return 0;
}

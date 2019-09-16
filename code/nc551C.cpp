#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+50;
struct SAM{
    struct state{
        int len,fa,next[26];
    }st[N*2];
    int cnt,lst;
    void init(){
        st[0]={0,-1};
        memset(st[0].next,0,sizeof(st[0].next));
        cnt++;
        lst=0;
    }
    void add(int c){
        c-='a';
        int cur=cnt++;
        int p=lst;
        st[cur].len=st[p].len+1;
        while(p!=-1 && !st[p].next[c]){
            st[p].next[c]=cur;
            p=st[p].fa;
        }
        if(p==-1){
            st[cur].fa=0;
        }else{
            int q=st[p].next[c];
            if(st[q].len==st[p].len+1){
                st[cur].fa=q;
            }else{
                int cl=cnt++;
                st[cl]={st[p].len+1,st[q].fa};
                memcpy(st[cl].next,st[q].next,sizeof(st[c].next));
                while(p!=-1 && st[p].next[c]==q){
                    st[p].next[c]=cl;
                    p=st[p].fa;
                }
                st[q].fa=st[cur].fa=cl;
            }
        }
        lst=cur;
    }
    ll solve(int m){
        ll ans=0;
        for(int i=1;i<cnt;i++){
            ans+=(max(0,st[i].len-max(st[st[i].fa].len,m-1)));
        }
        return ans;
    }
}ac;
int n,m;
char s[N];
int main(){
    scanf("%d%d",&n,&m);
    scanf("%s",s);
    ac.init();
    for(int i=0;i<n;i++){
        ac.add(s[i]);
    }
    ll ans=ac.solve(m);
    printf("%lld\n",ans);
    return 0;
}
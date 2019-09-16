#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+50;
struct SAM{
    struct state{
        int len,fa;
        //状态对应endpos大小，即子串出现次数
        int siz;
        int next[26];
    }st[N*2];
    //后缀自动机
    void topo(int len){
        //按len从小到大排序 O(n)
        for(int i=0;i<=len;i++){
            ws[i]=0;
        }
        for(int i=1;i<cnt;i++){
            ws[st[i].len]++;
        }
        for(int i=1;i<=len;i++){
            ws[i]+=ws[i-1];
        }
        for(int i=cnt-1;i>=1;i--){
            tp[ws[st[i].len]--]=i;
        }
        //从叶子节点递推到S，累加siz，得到endpos的大小
        for(int i=cnt-1;i>0;i--){
            printf("%d add %d\n",st[tp[i]].fa,tp[i]);
            st[st[tp[i]].fa].siz+=st[tp[i]].siz;
        }
        for(int i=0;i<cnt;i++){
            printf("%d %d %d\n",i,tp[i],st[i].siz);
        }
    }
    ll solve(int k){
        ll ans=0;
        for(int i=1;i<cnt;i++){
            //siz表示状态的endpos大小，也就是子串集合出现的次数
            if(st[i].siz==k){
                //st[i].len-st[st[i].fa].len表示该状态对应的子串数
                ans+=st[i].len-st[st[i].fa].len;
            }
        }
        return ans;
    }
}ac;
char s[N];
int T,k;
int main(void){
   freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%d",&k);
        scanf("%s",s);
        int n=strlen(s);
        ac.init();
        for(int i=0;i<n;i++){
            ac.add(s[i]);
        }
        ac.topo(n);
        ll ans=ac.solve(k);
        printf("%lld\n",ans);
    }
    return 0;
}
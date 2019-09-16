#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int N=3e5+50;
char a[N],b[N],s[N];
int sa[N],rk[N],h[N];
int t[N],t2[N],c[N];
int al,bl,n,k;
void build(int n,int m){
    //后缀数组
}
//答案就是对任意两个不同后缀a[i...]和b[j...]的sum(lcp(ai,bj)-k+1)
//两个单调栈，一个维护h[i]，一个维护贡献之和
ll he[N],ct[N];
ll solve(){
    //考虑用单调栈优化到O(n)，即对于每一个后缀求与前面后缀的lcp之和，不重不漏
    ll ans=0;
    //当前后缀与前面每个后缀的lcp之和
    //由性质可知，当前后缀和前面某一个后缀的lcp应该是之间的h[i]最小值
    //因此可以将递减的h[i]合并为最小的那个h[min]*cnt
    ll sum=0;
    int tp=0;
    for(int i=2;i<=n;i++){
        if(h[i]<k){
            tp=0;
            sum=0;
            continue;
        }
        ll cnt=0;
        //维护单调栈，由于lcp只跟区间h最小值有关，将所有栈顶大于当前h[i]的都合并
        while(tp && he[tp]>h[i]){
            //减去无效栈顶的贡献(h[i]-k+1)
            sum-=(he[tp]-k+1)*ct[tp];
            //暂时累计cnt，存储到新的栈顶
            cnt+=ct[tp];
            //栈顶出栈
            tp--;
        }
        //入栈，保持单调性
        he[++tp]=h[i];
        if(sa[i-1]<al) {
            //有效贡献的串，个数加1
            cnt++;
        }
        ct[tp]=cnt;
        //累加栈顶贡献
        sum+=(he[tp]-k+1)*ct[tp];
        if(sa[i]>al){
            //将当前累加的贡献加到答案中，即b串后缀与前面所有a串后缀的lcp之和
            ans+=sum;
        }
    }
    tp=sum=0;
    for(int i=2;i<=n;i++){
        if(h[i]<k){
            tp=0;
            sum=0;
            continue;
        }
        ll cnt=0;
        while(tp && he[tp]>h[i]){
            sum-=(he[tp]-k+1)*ct[tp];
            cnt+=ct[tp];
            tp--;
        }
        if(sa[i-1]>al){
            he[++tp]=h[i];
            ct[tp]=cnt+1;
            sum+=(he[tp]-k+1)*ct[tp];
        }else{
            he[++tp]=h[i];
            ct[tp]=cnt;
            sum+=(he[tp]-k+1)*ct[tp];
        }
        //累加b串后缀与前面所有a串后缀的lcp之和
        if(sa[i]<al){
            ans+=sum;
        }
    }
    return ans;
}
int main(){
//    freopen("in.txt","r",stdin);
    while(~scanf("%d",&k) && k){
        scanf("%s",a);
        scanf("%s",b);
        al=strlen(a);
        bl=strlen(b);
        for(int i=0;i<al;i++){
            s[i]=a[i];
        }
        s[al]='~';
        for(int i=0;i<bl;i++){
            s[al+1+i]=b[i];
        }
        n=al+bl+1;
        s[n]='\0';
        build(n,300);
        ll ans=solve();
        printf("%lld\n",ans);
    }
    return 0;
}
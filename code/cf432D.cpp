#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+50;
char str[N];
int s[N],n;
int sa[N],rk[N],h[N];
int t[N],t2[N],c[N];
int st[N][25];
int le[N],ri[N];
void build(int n,int m){
    //后缀数组
}
void init_rmq(){
    for(int i=0;i<=n;i++){
        st[i][0]=h[i];
    }
    for(int j=1;(1<<j)<=n;j++){
        for(int i=0;i+(1<<j)-1<=n;i++){
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}
int rmq(int l,int r){
    int k=0;
    while((1<<(k+1))<=r-l+1){
        k++;
    }
    return min(st[l][k],st[r-(1<<k)+1][k]);
}
int lcp(int l,int r){
    // printf("rk %d %d\n",l,r);
    if(l==r){
        return n-sa[l];
    }
    if(l>r){
        swap(l,r);
    }
    return rmq(l+1,r);
}
vector<pair<int,int> > ans;
void solve(){
    stack<int> sta;
    while(!sta.empty()){
        sta.pop();
    }
    for(int i=1;i<=n;i++){
        while(!sta.empty() && h[i]<=h[sta.top()]){
            sta.pop();
        }
        if(!sta.empty()){
            le[i]=sta.top()+1;
        }else{
            le[i]=1;
        }
        sta.push(i);
    }
    while(!sta.empty()){
        sta.pop();
    }
    for(int i=n;i>=1;i--){
        while(!sta.empty() && h[i]<=h[sta.top()]){
            sta.pop();
        }
        if(!sta.empty()){
            ri[i]=sta.top()-1;
        }else{
            ri[i]=n;
        }
        sta.push(i);
    }
    //枚举后缀长度
    int L,R;
    for(int len=1;len<n;len++){
        if(lcp(rk[0],rk[n-len])==len){
            //即h[rk[n-len]+1]...h[rk[0]]的最小值为len
            R=ri[rk[n-len]+1];
            if(h[rk[n-len]]<len){
                //必须有效(按h分组后)的后缀才能以最小值延伸，比如len为3，但是h[rk[n-len]]只有2，那么前面的后缀都不能算的，但是如果按照单调栈预处理的结果，2作为最小值可能延伸到很前面
                L=rk[n-len];
            }else{
                L=le[rk[n-len]];
            }
            ans.push_back({len,R-L+1});
        }
    }
    //母串单独考虑
    ans.push_back({n,1});
    int siz=ans.size();
    printf("%d\n",siz);
    for(int i=0;i<siz;i++){
        printf("%d %d\n",ans[i].first,ans[i].second);
    }
}
int main(){
    freopen("in.txt","r",stdin);
    scanf("%s",str);
    n=strlen(str);
    for(int i=0;i<n;i++){
        s[i]=str[i]-'A'+1;
    }
    build(n,256);
    debug();
    init_rmq();
    solve();
    return 0;
}
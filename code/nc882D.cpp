#include <bits/stdc++.h>
using namespace std;
const int N=105;
typedef long long ll;
typedef bitset<N> bs;
int n,k;
ll a[N];
char s[N];
struct node{
    //表示从id开始往下找的团，为了保证不重复
    int id;
    ll val;
    //当前团的状态
    bs sta;
    bool operator <(const node& rhs)const{
        return val>rhs.val;
    }
};
bs g[N];
bs t;
priority_queue<node> pq;
int main(void){
    // freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%s",s);
        for(int j=0;j<n;j++){
            g[i][j]=s[j]-'0';
        }
    }
    if(k==1){
        printf("0\n");
        return 0;
    }
    k--;
    for(int i=0;i<n;i++){
        t.reset();
        t[i]=1;
        pq.push(node{i,a[i],t});
    }
    while(!pq.empty()){
        node tmp=pq.top();
        pq.pop();
        if(k==1){
            printf("%lld\n",tmp.val);
            return 0;
        }
        k--;
        for(int i=tmp.id+1;i<n;i++){
            //如果一个点所连的所有点(g[i]刚好是当前团的所有点sta，那么加入i后仍然是团)
            if((g[i]&tmp.sta)==tmp.sta){
                bs now=tmp.sta;
                now[i]=1;
                pq.push(node{i,tmp.val+a[i],now});
            }
        }
    }
    printf("-1\n");
    return 0;
}
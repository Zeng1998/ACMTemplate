#include <bits/stdc++.h>
using namespace std;
const int N=6e5+05;
struct SAM{
    map<long long,int> next[N*2];
    //后缀自动机
    void solve(int n){
        //贪心找最小的转移边
        int p=0;
        for (int i=0;i<n;i++) {
            auto t=next[p].begin();
            p=t->second;
            printf("%d ",t->first);
        }
        printf("\n");
    }
}ac;
int n;
long long a[N/2];
int main(){
    ac.init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=2*n;i++){
        ac.add(a[(i-1)%n+1]);
    }
    ac.solve(n);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+50;
int h[N],n;
int le[N],ri[N];
int main(void){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&h[i]);
    }
    //求出每个数作为最大值/最小值能延伸到的区间
    stack<int> ss;
    for(int i=1;i<=n;i++){
        while(ss.size()>0 && h[i]<=h[ss.top()]){
            ss.pop();
        }
        if(ss.size()>0){
            le[i]=ss.top()+1;
        }else{
            le[i]=1;
        }
        ss.push(i);
    }
    while(!ss.empty()){
        ss.pop();
    }
    for(int i=n;i>=1;i--){
        while(ss.size()>0 && h[i]<=h[ss.top()]){
            ss.pop();
        }
        if(ss.size()>0){
            ri[i]=ss.top()-1;
        }else{
            ri[i]=n;
        }
        ss.push(i);
    }
    return 0;
}
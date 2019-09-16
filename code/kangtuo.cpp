//给定一个排列45231，求排名
//每个数后面比该数小的数分别有[3 3 1 1 0]个
//所以排名为3*4!+3*3!+1*2!+1*1+0*0!+1=94
//给定排名96，求对应排列(n=5)
//96-1=95 95/4!=3...23 23/3!=3...5 5/2!=2...1 1/1!=0...0
//商就对应每个数后面比该数小的数的个数
//因为阶乘，适合n小的情况
#include <bits/stdc++.h>
using namespace std;
const int N=1001;
int fac[]={1,1,2,6,24,120,720,5040,40320};
int n,m;
int a[N],vis[15];
void solve(int n,int m){
     m--;
     memset(a,0,sizeof(a));
     memset(vis,0,sizeof(vis));
     int k=m;
     for(int i=0;i<n;i++){
          int t=k/fac[n-i-1];
          int j=1;
          for(;j<=n;j++){
               if(!vis[j]){
                   if(t==0){
                       break;
                   }
                   t--;
               }
          }
          vis[j]=1;
          a[i]=j;
          k=k%fac[n-i-1];
     }
}
int main(){
    while(~scanf("%d%d",&n,&m)){
        solve(n,m);
        for(int i=0;i<n;i++){
            printf("%d%c",a[i],i==n-1?'\n':' ');
        }
    }
    return 0;
}

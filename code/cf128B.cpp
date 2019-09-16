#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
char s[N];
int k;
int sa[N],rk[N],h[N];
int t[N],t2[N],c[N];
void build(int n,int m=128){
    //后缀数组
}
//a[i]记录第i个后缀目前枚举到第几个子串
int a[N];
void solve(int n){
    memset(a, 0, sizeof(a));
    //从排名第一的后缀开始
    int r=1;
    //复杂度不会超过K
    while(k){
        a[r]++;
        //大于后缀的长度，下一个后缀
        if(a[r]>n-sa[r]){
            r++;
            continue;
        }
        k--;
        //枚举r之后的所有后缀，h[i]>=a[r]即扫过所有相同子串(当前a[r]长度)
        for(int i=r+1;i<=n && h[i]>=a[r] && k;i++){
            a[i]++;
            k--;
        }
    }
    //第k小子串在第r个后缀里，长度为a[r]
    for(int i=0;i<a[r];i++){
        printf("%c",s[sa[r]+i]);
    }
    printf("\n");
}
int main(void){
    scanf("%s",s);
    scanf("%d",&k);
    int n=strlen(s);
    build(n);
    if(k>1ll*n*(n+1)/2){
        printf("No such line.\n");
        return 0;
    }
    solve(n);
    return 0;
}
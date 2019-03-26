#include <bits/stdc++.h>
using namespace std;
const int N=10050;
char s[N];
//"banana" 后缀为[banana anana nana ana na a]
//sa[i]: 排名第i(从0开始)小的后缀的首字符下标 比如[6 5 3 1 0 4 2]==>[$ a$ ana$ anana$ banana$ na$ nana$]
//rk[i]: 下标i开始的后缀(不含$)的排名(按字典序从小到大，相当于sa的逆)
//h[i]:排名为i的后缀和排名前i-1的后缀的最长公共前缀
int sa[N],rk[N],h[N],t[N],t2[N],c[N];
void build_sa(int n, int m){ 
    //n为字符串的长度,字符集的值为0~m-1
    //相当于在后面加一个$
    n++;
    int *x = t, *y = t2;
    //基数排序
    for (int i = 0; i < m; i++) c[i] = 0;
    for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
    for (int i = 1; i < m; i++) c[i] += c[i - 1];
    for (int i = n - 1; ~i; i--) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1){ //直接利用sa数组排序第二关键字
        int p = 0;
        for (int i = n - k; i < n; i++) y[p++] = i;
        for (int i = 0; i < n; i++)
        if (sa[i] >= k) y[p++] = sa[i] - k;
        //基数排序第一关键字
        for (int i = 0; i < m; i++) c[i] = 0;
        for (int i = 0; i < n; i++) c[x[y[i]]]++;
        for (int i = 0; i < m; i++) c[i] += c[i - 1];
        for (int i = n - 1; ~i; i--) sa[--c[x[y[i]]]] = y[i];
        //根据sa和y数组计算新的x数组
        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]? p - 1 : p++;
        if (p >= n) break; //以后即使继续倍增,sa也不会改变,推出
        m = p; //下次基数排序的最大值
    }
    //-------------------------
    for(int i=0;i<n;i++){
        printf("%d ",sa[i]);
    }
    printf("\n");
    //去掉$
    n--;
    int k = 0;
    for (int i = 0; i <= n; i++){
        rk[sa[i]] = i;
    }
    //------------------------
    for(int i=0;i<n;i++){
        printf("%d ",rk[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++){
        if (k){
            k--;
        }
        int j = sa[rk[i] - 1];
        while(s[i + k] == s[j + k]){
            k++;
        }
        h[rk[i]] = k;
    }
    //-------------------------
    for(int i=2;i<=n;i++){
        printf("%d ",h[i]);
    }
    printf("\n");
}
int main(void){
    freopen("in.txt","r",stdin);
    scanf("%s",s);
    int n=strlen(s);
    int m=128;
    build_sa(n,m);
    return 0;
}
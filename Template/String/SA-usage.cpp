#include <bits/stdc++.h>
using namespace std;
const int N=1005;
const int INF=0x3f3f3f3f;
int n;
//"banana" 后缀为[banana anana nana ana na a $]
//sa[i]: 排名第i(从0开始)小的后缀的首字符下标 
//比如[6 5 3 1 0 4 2]==>[$ a$ ana$ anana$ banana$ na$ nana$]
//rk[i]: 下标i开始的后缀(不含$)的排名(按字典序从小到大，相当于sa的逆)  
//[4 3 6 2 5 1]
//h[i]:排名为i的后缀和排名为i-1的后缀的最长公共前缀  
//[1(ana$-a$) 3(anana$-ana$) 0 0 2]
//一些应用:
//-- 求两个后缀的最长公共前缀
// 两个后缀的首字符编号为a,b，LCP(a,b)
//-- 不同字串个数，由于子串一定是某个后缀的前缀，所以h数组就是lcp，也是是相同前缀个数
//所以ans=n*(n+1)/2-\sum(h)
//-- 出现次数大于等于k次的最大子串长度
//二分子串长度，调用check(mid,k) 
//-- 出现次数大于等于l小于等于r的子串个数
//RMQ+容斥  RMQ维护h[]数组的区间最小值(省略)  调用solve(l,r)
//-- 最长不重叠重复出现(2次以上)子串
//未完待续
char s[N];
int sa[N],rk[N],h[N];
//辅助数组
int t[N],t2[N],c[N];
int dp[N][30];
void build_sa(int n, int m){ 
    //n为字符串的长度,字符集的值为0~m-1
    //相当于在后面加一个$
    n++;
    int *x=t, *y=t2;
    //基数排序
    for(int i=0;i<m;i++){
        c[i]=0;
    }
    for(int i=0;i<n;i++){
        c[x[i]=s[i]]++;
    }
    for(int i=1;i<m;i++){
        c[i]+=c[i-1];
    }
    //或者~i 表示i!=-1
    for(int i=n-1;i>=0;i--){
        sa[--c[x[i]]]=i;
    }
    for(int k=1; k<=n; k<<=1){ 
        int p=0;
        for(int i=n-k;i<n;i++){
            y[p++]=i;
        }
        for(int i=0;i<n;i++){
            if(sa[i]>=k){
                y[p++]=sa[i]-k;
            }
        }
        for(int i=0;i<m;i++){
            c[i]=0;
        }
        for(int i=0;i<n;i++){
            c[x[y[i]]]++;
        }
        for(int i=1;i<m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n-1;i>=0;i--){
            sa[--c[x[y[i]]]]=y[i];
        }
        swap(x, y);
        p=1;
        x[sa[0]]=0;
        for(int i=1;i<n;i++){
            x[sa[i]]=y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]? p-1 : p++;
        }
        if (p>=n){
            break; 
        }
        m = p;
    }
    //去掉$
    n--;
    for(int i = 0; i <= n; i++){
        rk[sa[i]] = i;
    }
    //计算h
    int k=0;
    for(int i = 0; i < n; i++){
        if(k){
            k--;
        }
        int j = sa[rk[i] - 1];
        while(s[i + k] == s[j + k]){
            k++;
        }
        h[rk[i]] = k;
    }
}
//判断是否存在长度为mid的子串出现次数大于等于k
bool check(int mid,int k){
    int cnt=1;
    for(int i=1;i<=n;i++){
        if(h[i]>=mid){
            cnt++;
        }else{
            cnt=1;
        }
        if(cnt>=k){
            return true;
        }
    }
    return false;
}
bool check2(int mid){
    int low=INF,hight=-INF;
    bool flag=false;
    for(int i=2;i<=n;i++){
        if(h[i]<mid){
            low=INF;
            hight=-INF;
        }else{
            low=min(low,min(sa[i],sa[i-1]));
            hight=max(hight,max(sa[i],sa[i-1]));
            if(hight-low>=mid){
                flag=true;
                break;
            }
        }
    }
    return flag;
}
/*
 * 预处理 O(nlogn)
 * dp[i][j]:从a[i]开始2^j个数的最小值
 */
void RMQ_init(int n){
    for(int i=0;i<n;i++){
        dp[i][0]=h[i];
    }
    for(int j=1;(1<<j)<=n;j++){
	    for(int i=0;i+(1<<j)-1<n;i++){
	        //两段重叠部分小区间
	        dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
	    }
    }
}
/*
 * 查询[l,r]最小值，最大值同理
 */
int RMQ(int l,int r){
    int k=0;
    //保证刚好[l,l+2^k]和[r-2^k,r]重叠
    while((1<<(k+1))<=r-l+1){
        k++;
    }
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
}

//===========后缀数组应用总结============
//====任意两个后缀的最长公共前缀长度========
//转化为求两个后缀对应排名区间的最小h值，即RMQ问题
/*
 * 要先初始化RMQ(n+1)，求回文串时RMQ(2*n+2)
 * 分清查询的是两个后缀首字符还是两个后缀排名
 * l,r为两个后缀的排名
 */ 
int solve0(int l,int r){
    if(l==r){
        return n-sa[l];
    }
    if(l>r){
        swap(l,r);
    }
    //这里可灵活处理，有时候不需要+1
    return RMQ(l+1,r);
}
/*
 * i,j为两个后缀的首字符下标
 */  
int solve1(int i,int j){
    if(i==j){
        return n-i;
    }
    int ri=rk[i];
    int rj=rk[j];
    if(ri>rj){
        swap(ri,rj);
    }
    //注意h数组是类似差分的表示，区间n其实只有n-1的h数组
    return RMQ(ri+1,rj);
}
//====可重叠最长重复子串长度===============
//重复子串＝最长公共前缀＝区间内min(h)
//最长重复子串＝所有区间max(min(h))=max(h)
int solve2(){
    int ans=0;
    //注意从1开始，排名为0的是无效后缀'$'
    for(int i=1;i<=n;i++){
        ans=max(ans,h[i]);
    }
    return ans;
}
//====不可重叠最长重复子串=================
//先二分答案(子串长度)将问题转化为判定性问题
//即判断字符串里是否存在长度为mid的重复子串
//将后缀按排名顺序进行分组，每组后缀间h值>=mid
//否则单独一个组
//同一组中判断max(sa[i])和min(sa[i])
//即最左后缀和最右后缀的差值是否>=mid(即不重叠)
int solve3(){
    int ans=0;
    int l=0,r=n/2;
    //分组和判断同时进行
    //mx mn分别维护组内最右和最左后端
    int mx=-INF,mn=INF;
    while(l<=r){
        int mid=(l+r)/2;
        bool flag=false;
        //可以直接从2开始，因为1和0的h值在这里无意义
        for(int i=2;i<=n;i++){
            if(h[i]<mid){
                //新的分组
                mx=-INF;
                mn=INF;
            }else{
                //h[i]表示的就是sa[i]和sa[i-1]这两个后缀的LCP
                //所以这两个位置都有可能
                mx=max(mx,max(sa[i],sa[i-1]));
                mn=min(mn,min(sa[i],sa[i-1]));
                //poj1743求的是差分数组所以这里是>
                if(mx-mn>=mid){
                    flag=true;
                    break;
                }
            }
        }
        if(flag){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return ans;
}
//====可重叠出现至少k次的最长重复子串========
//同样是二分答案，后缀分组再进行判断
//不过这里判断的是组内后缀个数是否>=k
int solve4(int k){
    int ans=0;
    int l=0,r=n/2;
    while(l<=r){
        int mid=(l+r)/2;
        int cnt=1;
        bool flag=false;
        for(int i=2;i<=n;i++){
            if(h[i]<mid){
                cnt=1;
            }else{
                cnt++;
                if(cnt>=k){
                    flag=true;
                    break;
                }
            }
        }
        if(flag){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return ans;
}
//====不同子串个数==================
//按排名枚举后缀，对于排名为i的后缀来说，贡献为n-sa[i]+h[i]
//即后缀长度(从后缀第一个字符到后缀第i个字符算一个子串)减去重复部分
int solve5(){
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=(n-sa[i]-h[i]);
    }
    return ans;
}
//====最长回文子串=================
//将字符串反转接在原串后面(中间加入特殊分隔符)，将问题转化为求LCP
//枚举每一个位置分别求出奇数回文串和偶数回文串长度
int solve6(){
    //要先把字符串反转拼接再求sa
    int ans=0;
    for(int i=0;i<n;i++){
        //奇数回文串
        ans=max(ans,2*solve1(i,2*n-i)-1);
        //偶数回文串
        ans=max(ans,2*solve1(i,2*n-i+1));
    }
    return ans;
}
//=======出现次数[a,b]/k次(即[k,k])的子串个数=====
//设cal(k)为出现次数大于等于k的子串个数
//问题转化为求cal(a)-cal(b+1)
int cal(int k){
    //特判k
    if(k==1){
        //即所有不同子串个数
        return solve5();
    }
    int ans=0;
    //不断枚举每一段k-1的h区间(其实就是k个后缀)
    //0没有h值，1的h值恒为0
    int l=2,r=k;
    int pre=0;
    while(r<=n){
        //这里直接使用RMQ
        int now=RMQ(l,r);
        if(now>=pre){
            ans+=now-pre;
        }
        pre=now;
        l++;
        r++;
    }
    return ans;
}
int solve7(int a,int b){
    return cal(a)-cal(b+1);
}
int main(void){
    scanf("%s",s);
    n=strlen(s);
    s[n]='$';
    for(int i=0;i<n;i++){
        s[i+n+1]=s[n-i-1];
    }
    build_sa(n*2+1,250);
    RMQ_init(n*2+2);
    printf("%s\n",s);
    for(int i=0;i<=n*2+1;i++){
        printf("%d ",sa[i]);
    }
    printf("\n");
    for(int i=0;i<=n*2+1;i++){
        printf("%d ",rk[i]);
    }
    printf("\n");
    for(int i=0;i<=n*2+1;i++){
        printf("%d ",h[i]);
    }
    printf("\n");
    // printf("%d\n",check(3,2));
    // printf("%d\n",check2(3));
    // int i,j;
    // RMQ_init(n+1);
    // while(~scanf("%d%d",&i,&j)){
    //     printf("%d\n",solve1(i,j));
    // }
    // int k;
    // while(~scanf("%d",&k)){
    //     printf("%d\n",solve4(k));
    // }
    printf("%d\n",solve6());
    return 0;
}
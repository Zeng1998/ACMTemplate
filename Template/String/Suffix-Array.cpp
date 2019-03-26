//"banana" 后缀为[banana anana nana ana na a $]
//sa[i]: 排名第i(从0开始)小的后缀的首字符下标 
//比如[6 5 3 1 0 4 2]==>[$ a$ ana$ anana$ banana$ na$ nana$]
//rk[i]: 下标i开始的后缀(不含$)的排名(按字典序从小到大，相当于sa的逆)  
//[4 3 6 2 5 1]
//h[i]:排名为i的后缀和排名为i-1的后缀的最长公共前缀  
//[1(ana$-a$) 3(anana$-ana$) 0 0 2]
//一些应用:
//*** 求两个后缀的最长公共前缀
// 两个后缀的首字符编号为a,b，LCP(a,b)
//*** 不同字串个数，由于子串一定是某个后缀的前缀，所以h数组就是lcp，也是是相同前缀个数
//所以ans=n*(n+1)/2-\sum(h)
//*** 出现次数大于等于k次的最大子串长度
//二分子串长度，调用check(mid,k) 
//*** 出现次数大于等于l小于等于r的子串个数
//RMQ+容斥  RMQ维护h[]数组的区间最小值(省略)  调用solve(l,r)
//*** 最长不重叠重复出现(2次以上)子串
//二分子串长度，调用check(mid)
char s[N];
int sa[N],rk[N],h[N];
//辅助数组
int t[N],t2[N],c[N];
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
        //类似上面，只是把i换成y[i]
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
int LCP(int a,int b){
    a=rk[a];
    b=rk[b];
    if(a>b){
        swap(a,b);
    }
    return ask(a,b);
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
//判断是否存在长度为mid的不重叠重复子串
bool check2(int mid){
    int low=INF,hight=-INF;
    bool flag=false;
    for(int i=2;i<=n;i++){
        if(h[i]<mid){
            //不连续 断开，相当于把所有后缀分组
            //例如aabaaaab
            //最后后缀和排名和h数组是
            /*
              $
              aaaab
            3 aaab
            2 aab
            3 aabaaaab
            ----------------
            1 ab
            2 abaaaab
            ----------------
            0 b
            ----------------
            1 baaaab
            */
            //当k=2时分组如上所示，分组就是把有最大相同前缀的后缀放在一起，然后比较这个公共的前缀(重复子串)
            //如果大于等于mid，说明存在，如果小于，说明这一组已经结束了
            //重置low hight判断下一组(h数组的连续性)
            low=INF;
            hight=-INF;
        }else{
            //更新相同LCP的一组后缀中的最左和最右的sa值
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
//查询排名区间在[l,r]的后缀的最长公共前缀
//查询排名区间在[l,r]的后缀含有的出现次数大于等于r-l+1次的子串个数
int ask(int l,int r){
    //因为h[i]就是表示排名为i和排名为i-1的后缀的最长公共前缀
    //RMQ得到的就是[l,r]这一段所有排名后缀的最长公共前缀
    if(l==r){
        //特判l==r，即求的是排名为r的后缀的长度，即n-sa[r]
        return n-sa[r];
    }else{
        return RMQ(l+1,r);
    }
}
//查询出现次数在[l,r]区间内的子串个数
//设f(k)表示出现次数大于等于k的子串个数，即f(k)=ask(区间长度为k)
//答案为f(l)-f(r+1)
//因此我们枚举长度为l的区间，再从两端构造出r+1的区间，利用容斥定理解决
int solve(int l,int r){
    initRMQ(n);
    int ans=0;
    //枚举区间
    for(int i=1;i+l-1<=n;i++){
        //查询排名[i,i+l-1]这一段的后缀出现次数大于等于l的子串个数
        ans+=ask(i,i+l-1);
        //这里固定减1
        if(i-1>0){
            //同理，减去出现次数至少为l+1的
            ans-=ask(i-1,i+r-1);
        }
        if(i+r<=n){
            //减去出现次数至少为r+1的
            ans-=ask(i,i+r);
        }
        if(i-1>0 && i+r<=n){
            //容斥，加上出现次数至少为r+2的，因为被上面两个if重复减去
            ans+=ask(i-1,i+r);
        }
    }
    return ans;
}
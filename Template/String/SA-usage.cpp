/*
 * 预处理 O(nlogn)
 * dp[i][j]:从a[i]开始2^j个数的最小值
 */
void RMQ_init(int n){
    for(int i=0;i<=n;i++){
        dp[i][0]=h[i];
    }
    for(int j=1;(1<<j)<=n;j++){
	    for(int i=0;i+(1<<(j-1)<n;i++){
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

//=====================后缀数组应用总结========================
//1.任意两个后缀的最长公共前缀长度
/* 
 * 转化为求两个后缀对应排名区间的最小h值，即RMQ问题
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
//2.可重叠最长重复子串长度
/*
 * 重复子串＝最长公共前缀＝区间内min(h)
 * 最长重复子串＝所有区间max(min(h))=max(h)
 */ 
int solve2(){
    int ans=0;
    //注意从1开始，排名为0的是无效后缀'$'
    for(int i=1;i<=n;i++){
        ans=max(ans,h[i]);
    }
    return ans;
}
//3.不可重叠最长重复子串
/*
 * 先二分答案(子串长度)将问题转化为判定性问题
 * 即判断字符串里是否存在长度为mid的重复子串
 * 将后缀按排名顺序进行分组，每组后缀间h值>=mid
 * 否则单独一个组
 * 同一组中判断max(sa[i])和min(sa[i])
 * 即最左后缀和最右后缀的差值是否>=mid(即不重叠)
 */ 
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
//4.重叠出现至少k次的最长重复子串
/* 
 * 同样是二分答案，后缀分组再进行判断
 * 不过这里判断的是组内后缀个数是否>=k
 */
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
//5.(长度大于等于k)的不同子串个数
/*
 * 按排名枚举后缀，对于排名为i的后缀来说，贡献为n-sa[i]+h[i](k为1的情况)
 * 即后缀长度(从后缀第一个字符到后缀第i个字符算一个子串)减去重复部分
 */
int solve5(){
    int ans=0;
    for(int i=1;i<=n;i++){
        if(h[i]){
            h[i]=max(0,h[i]-(k-1));
        }
        ans+=max(0,(n-sa[i]-(k-1)-h[i]));
        //k为1的情况
        //ans+=(n-sa[i]-h[i]);
    }
    return ans;
}
//6.最长回文子串
/*
 * 将字符串反转接在原串后面(中间加入特殊分隔符)，将问题转化为求LCP
 * 枚举每一个位置分别求出奇数回文串和偶数回文串长度
 */
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
//7.出现次数[a,b]/k次(即[k,k])的子串个数
/*
 * 设cal(k)为出现次数大于等于k的子串个数
 * 问题转化为求cal(a)-cal(b+1)
 */ 
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
//8.字符串S由字符串T重复Q次得到，求最大Q
/*
 * 使用kmp更方便，如果非要用后缀数组请用dc3模板
 * 枚举T串长度k，先判断len(S)%len(T)==0？
 * 再判断lcp(suffix(0),suffix(k))==n-k?
 * suffix(i)指首字符位置为i的后缀
 * 因为suffix(0)固定，无需预处理出整个RMQ
 * 只需O(n)求出所有lcp(suffix(0),x)即可
 */ 
int solve8(){
    lcp[rk[0]]=n;
    for(int i=rk[0]-1;i>=0;i--){
        lcp[i]=min(lcp[i+1],h[i+1]);
    }
    for(int i=rk[0]+1;i<=n;i++){
        lcp[i]=min(lcp[i-1],h[i-1]);
    }
    for(int k=1;k<=n;k++){
        if(n%k==0 && lcp[rk[k]]==n-k){
            return n/k;
        }
    }
}
//9.重复次数最多的连续重复子串
/*
 * 暂时无法理解,贴个题解板子
 */ 
void solve9(){
    int ans=0,pos=0,lenn;
    //保证有重复,所以是len/2
    for(int i=1;i<=len/2;i++){
        for(int j=0;j<len-i;j+=i){
            if(str[j]!=str[j+i]){
                continue;
            }
            //通过下标查询
            int k=solve1(j,j+i);
            int tol=k/i+1;
            int r=i-k%i;
            int p=j;
            int cnt=0;
            for(int m=j-1;m>j-i&&str[m]==str[m+i]&&m>=0;m--){
                cnt++;
                if(cnt==r){
                    tol++;
                    p=m;
                }
                else if(rk[p]>rk[m]){
                    p=m;
                }
            }
            if(ans<tol){
                ans=tol;
                pos=p;
                lenn=tol*i;
            }else if(ans==tol && rk[pos]>rk[p]){
                pos=p;
                lenn=tol*i;
            }
        }
    }
    //这里，如果字符总长度小于2，那么就在原串中找出一个最小的字符就好
    if(ans<2){
        char ch='z';
        for(int i=0;i<len;i++){
            if(str[i]<ch){
                ch=str[i];
            }
        }
        printf("%c\n",ch);
        return;
    }
    for(int i=pos;i<pos+lenn;i++){
        printf("%c",str[i]);
    }
    printf("\n");
}
//10.最长公共子串
/*
 * 求A和B的最长公共子串即转化为求A和B后缀的最长公共前缀
 * 将A和B拼接求出h数组，当suffix(sa[i])和suffix(sa[i-1])不在同个字符串时
 * h[i]才有效，求出最大值即可
 */ 
int solve10(){
    int ans=0;
    for(int i=1;i<=n;i++){
        //al为第一个字符串长度
        if(sa[i]<al && sa[i-1]<al || sa[i]>=al && sa[i-1]>=al){
            continue;
        }
        ans=max(ans,h[i]);
    }
    return ans;
}
//11.求长度大于等于k的公共子串个数
/*
 * 同样是转化为A和B所有后缀的最长公共前缀大于等于k的贡献累加起来
 * 用常用的处理方法，将两个字符串拼接，中间用分隔符隔开，求出h数组
 * 然后对h数组分组(把h值大于等于k的分在一组)
 * 然后在这道题里要使用一个单调栈来维护前面的后缀对后面的后缀的贡献
 * 单调栈维护一个h值和一个该h值在前面充当lcp的
 * sta[i][0]: 维护h值 sta[i][1]: 维护这个h值代表前面多少个后缀的lcp贡献(最小h值)
 * 维护的类似一种前缀和的东西，具体看代码详细注释
 */
int solve11(int k){
    int top=0;
    int tot=0, ans=0;
    //对h分组
    for(int i=1;i<=n;i++){
        if(h[i]<k){
            //单独一个后缀的分组，无需考虑
            top=0;
            tot=0;
        }else{
            //cnt表示h[i]作为lcp的后缀个数
            int cnt=0;
            //前一个后缀属于A，计算贡献
            //即能产生多少个长度大于等于k的公共子串
            if(sa[i-1]<al){
                //前面(i-1)必须是属于A的后缀，才能计算这个贡献
                //所以后面把B的后缀入栈是没毛病的，这里维护的实际上是一个类似前缀和的东西
                //即栈顶元素已经是累加了栈底所有元素的贡献
                //但是这个单调栈是动态变化的，所以不能单纯保留栈顶元素
                cnt++;
                //比如h[i]=4，例如abcd，那么大于等于k的子串就可以是
                //ab abc abcd这三个，所以是h[i]-k+1
                tot+=h[i]-k+1;
            }
            //维护单调栈(栈顶到栈底递减)
            //这里不用考虑h[i]是A的还是B的
            while(top && h[i]<=sta[top-1][0]){
                top--;
                //更新贡献
                //这里实际上应该是tot(贡献)减去sta[top][0]*sta[top][1]
                //再加上h[i]*sta[top][1]
                //相当于就是栈顶被替换了，所以栈顶这个h值之前充当了多少后缀的lcp
                //都要改成这个新的栈顶h[i]的贡献了
                tot+=(h[i]-sta[top][0])*sta[top][1];
                //既然h[i]比sta[top][0]小，那么sta[top][0]能作为lcp(h最小值)的h[i]
                //肯定也可以，所以累加上即可
                cnt+=sta[top][1];
            }
            //此时栈里的所有h值都小于h[i]
            //入栈，维持单调性
            sta[top][0]=h[i];
            sta[top][1]=cnt;
            top++;
            //属于B的后缀，累加A的贡献
            if(sa[i]>al){
                ans+=tot;
            }
        }
    }
    //同理对B串的后缀维护单调栈，累计B的贡献
    top=tot=0;
    for(int i=1;i<=n;i++){
        if(h[i]<k){
            top=0;
            tot=0;
        }else{
            int cnt=0;
            if(sa[i-1]>al){
                cnt++;
                tot+=h[i]-k+1;
            }
            while(top && h[i]<=sta[top-1][0]){
                top--;
                tot+=(h[i]-sta[top][0])*sta[top][1];
                cnt+=sta[top][1];
            }
            sta[top][0]=h[i];
            sta[top][1]=cnt;
            top++;
            if(sa[i]<al){
                ans+=tot;
            }
        }
    }
    return ans;
}
//12.给n个字符串，出现在不少于k个字符串的最长子串
/*
 * 同样是拼接字符串对h数组分组，二分答案进行判断
 */ 
bool check12(int mid){
    bool flag=false;
    for(int i=1;i<len;i++){
        //不满足要求的组直接不用管
        if(h[i]<mid){
            continue;
        }
        //组内不同字符串个数
        int cnt=0;
        //标记某个字符串是否出现过
        memset(vis,false,sizeof(vis));
        while(h[i]>=mid && i<len){
            if(!vis[idx[sa[i-1]]]){
                vis[idx[sa[i-1]]]=true;
                cnt++;
            }
            //找到1组
            i++;
        }
        //注意最后一个的判断
        if(!vis[idx[sa[i-1]]]){
            vis[idx[sa[i-1]]]=1;
            cnt++;
        }
        //出现在k个不同字符串中
        if(cnt>k){
            if(!flag){
                flag=true;
                //清空之前的答案
                //ans存储出现在至少k个不同字符串的后缀sa值
                ans.clear();
                ans.push_back(sa[i-1]);
            }
            else{
                //只需加入最后一个满足条件后缀的sa
                ans.push_back(sa[i-1]);
            }
        }
    }
    //是否有满足要求的答案
    return flag;
}
void solve12(){
    ans.clear();
    int l=1,r=len;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    //输出多个最长公共子串(至少在k个字符串中出现过)
    for(int i=0;i<ans.size();i++){
        for(int j=ans[i];j<ans[i]+r;j++)
            printf("%c",s[j]-1+'a');
        printf("\n");
    }
}
//13.给n个字符串，在每个字符串中至少出现两次且不重叠的最长子串
/*
 * 把每个字符串拼接起来，中间用分隔符分开，求h数组
 * 二分子串长度，对h数组分组，维护每一个字符串在当前组的最小和最大sa值 
 * 然后判断不重叠即可(也同时判断了出现2次)
 */ 
bool check13(int mid){
    //后缀起始位置的最大最小值
    for(int i=0;i<n;i++){
        mx[i]=0;
        mn[i]=INF;
    }
    for(int i=1;i<=len;i++){
        if(h[i]<mid){
            //重置分组
            for(int i=0;i<n;i++){
                mx[i]=0;
                mn[i]=INF;
            }
        }else{
            //一个h值表示两个后缀
            mx[idx[sa[i]]]=max(mx[idx[sa[i]]],sa[i]);
            mn[idx[sa[i]]]=min(mn[idx[sa[i]]],sa[i]);
            mx[idx[sa[i-1]]]=max(mx[idx[sa[i-1]]],sa[i-1]);
            mn[idx[sa[i-1]]]=min(mn[idx[sa[i-1]]],sa[i-1]);
            bool flag=true;
            //需要判断每个字符串(都要出现两次以上，且不重叠)
            for(int j=0;j<n;j++){
                if(mx[j]-mn[j]<mid){
                    flag=false;
                    break;
                }
            }
            if(flag){
                return true;
            }
        }
    }
    return false;
}
int solve13(){
    //len为拼接后的字符串长度
    int l=0,r=len+1;
    int ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check13(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return ans;
}
//14.给n个字符串，正序或逆序出现在每个字符串的最长子串
/*
 * 把每个字符串正序和逆序拼接起来，中间用分隔符分开，求h数组
 * 二分子串长度，对h数组分组，判断是否存在一组h值里面所属n个不同字符串
 * 所以在拼接字符串的时候要把每个字符串(正序和逆序)的每个字符标记是第几个字符串
 * for(int j=0;j<siz;j++){
        idx[len]=i;   
        //加2*n+1保证不会跟分隔符相同
        s[len++]=ss[i][j]-'A'+2*n+1;
    }
    idx[len]=i;
    s[len++]=sep++;
 */ 
bool check14(int mid){
    //这里用set来进行组内所属字符串的去重
    set<int> se;
    for(int i=1;i<len;i++){
        if(h[i]>=mid){
            se.insert(idx[sa[i]]);
            se.insert(idx[sa[i-1]]);
        }else{
            if(se.size()==n){
                return true;
            }
            se.clear();
        }
    }
    //注意最后一个组
    return se.size()==n;
}
int solve14(){
    if(n==1){
        return strlen(ss[0]);
    }
    int l=1,r=100;
    //变量记得初始化！！！
    int ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check14(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return ans;
}
//15.求两个字符串的公共子串，且只能在母串中出现一次，求满足的最短子串
/*
 * 两字符串拼接，按求最长公共子串的方法，不过要判断是否重复出现，重复出现的话，
 * 其对应后缀一定是相邻的，所以要判断相邻的是否有可能重复出现，要枚举从h[i]到1
 */
int solve(int n){
    int ans=0x3f3f3f3f;
    for(int i=1;i<=n;i++){
        if(h[i]==0 || sa[i]<len1 && sa[i-1]<len1 || sa[i]>=len1 && sa[i-1]>=len1){
            continue;
        }
        for(int j=h[i];j>=1;j--){
            if(j>h[i-1] && j>h[i+1]){
                ans=min(ans,j);
            }
        }
    }
    if(ans==0x3f3f3f3f){
        ans=-1;
    }
    return ans;
}
//几个注意点
//字符串数组一般可以用一个int数组来表示,特别是需要拼接字符串的题目
//拼接字符串先设定一个比较大的分隔符,比如300,然后每次分割一次都要+1
//注意最后一位补0 s[len]=0
/*
    len=0;
    int sep=30;
    for(int i=0;i<n;i++){
        scanf("%s",str[i]);
        siz[i]=strlen(str[i]);
        for(int j=0;j<siz[i];j++){
             s[len++]=str[i][j]-'a'+1;
             idx[len-1]=i;
        }
        s[len++]=sep++;
    }
    s[len]=0;
    build_sa(len,250);
 */ 
/*
 * AC自动机
 * tr[u][i]: 表示节点u的子节点('a'-'z'=>0-25)编号
 * cnt: 总节点数/节点编号
 * fail[u]: 节点u的fail指针指向节点编号
 * ==> fail指针: 指向当前失配的字符串的最长后缀字符串
 * ==> 比如匹配到abcd，d失配，那么c的fail指针指向的就是后缀为abc(或者bc或者c)的最长字符串
 * val[u]: 以节点u所表示字符串作为结尾的单词数
 * sum[u]: 以节点u所表示字符串作为前缀的单词数
 */ 
//插入单词，构建字典树
void insert(char *s){
    int len=strlen(s);
    int now=0;
    for(int i=0;i<len;i++){
        int id=s[i]-'a';
        if(!tr[now][id]){
            tr[now][id]=++cnt;
        }
        now=tr[now][id];
        sum[now]++;
    }
    val[now]++;
}
//使用bfs构造fail指针
void build(){
    queue<int> q;
    //第一层节点均指向根
    for(int i=0;i<26;i++){
        if(tr[0][i]){
            fail[tr[0][i]]=0;
            q.push(tr[0][i]);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        //处理出fail指针或者该节点走一步(fail跳转不算)能到达的节点
        for(int i=0;i<26;i++){
            if(tr[u][i]){
                //已经路径压缩，子节点fail直接指向父节点的fail的对应子节点
                //(无论是否存在，若不存在会自动指向上一级fail)
                fail[tr[u][i]]=tr[fail[u]][i];
                q.push(tr[u][i]);
            }else{
                //预处理该节点走一步(fail跳转不算)能到达的节点
                //相当于路径压缩，这样下面的节点就不用while(fail[fail[...]])这样跳
                tr[u][i]=tr[fail[u]][i];
            }
        }
    }
}
int query(char *s){
    int len=strlen(s);
    int now=0;
    int ans=0;
    for(int i=0;i<len;i++){
        int id=s[i]-'a';
        now=tr[now][id];
        //从当前节点一直往上跳转直到根或者val[t]为-1
        for(int t=now;t&&~val[t];t=fail[t]){
            ans+=val[t];
            //避免重复匹配
            val[t]=-1;
        }
    }
    return ans;
}
/*
 * 01异或字典树
 */
void insert(ll x){
    int rt=0;
    for(int i=32;i>=0;i--){
        //从高位，分解为二进制数位
        int id=(x>>i)&1;
        if(!tr[rt][id]){
            tr[rt][id]=++cnt;
        }
        rt=tr[rt][id];
    }
    //末尾标记原数字
    val[rt]=x;
}
ll query(ll x){
    int rt=0;
    for(int i=32;i>=0;i--){
        int id=(x>>i)&1;
        //不管这一位(id)是1还是0，优先找与这一位不同的节点，这样异或值就会尽量大
        if(tr[rt][id^1]){
            rt=tr[rt][id^1];
        }
        else{
            rt=tr[rt][id];
        }
    }
    return val[rt];
}
/*
 * AC自动机上dp
 * bzoj1030: 求长度为m且不含有所给n个单词的字符串的个数
 * dp[i][j]: 长度为i(从trie树根节点走i步)在节点j的满足条件字符串个数
 * ans=sum(dp[m][i]) i(0-cnt)
 * val[i]: 标记i节点是否可以访问(即对应字符串是否含有所给单词)
 *         在构建fail指针的时候，也要更新val[u]|=val[fail[u]]
 */ 
int solve(){
    dp[0][0]=1;
    //枚举步数
    for(int i=1;i<=m;i++){
        //枚举所有节点
        for(int j=0;j<=cnt;j++){
            //标记的单词(或是fail指针有标记)都不能经过 
            if(val[j]){
                continue;
            }
            for(int k=0;k<26;k++){
                dp[i][tr[j][k]]=(dp[i][tr[j][k]]+dp[i-1][j])%MOD;
            }
        }
    }
    int sum=1;
    for(int i=1;i<=m;i++){
        sum=(sum*26)%MOD;
    }
    int ans=0;
    for(int i=0;i<=cnt;i++){
        if(!val[i]){
            ans+=dp[m][i];
        }
    }
    return ((sum-ans)%MOD+MOD)%MOD;
}
/*
 * AC自动机上数位dp
 * bzoj3530: 给定整数n和其他m个整数，求0-N中，不含有这m个整数子串的数的个数
 * 先将模式串插入trie树中，跑数位dp模板(不用分解数位了)，dp数组多加一维标记节点位置
 * 判断下一个节点有效性(即是否含有模式串，注意题目是含有任意一个还是含有全部(状态压缩))
 * zero: 是否有前导零限制，即zero为true时，该位不能选0
 * flag: 表示是否含有trie树中的串
 * dp[i][j][k]: 表示前i位数在u节点上前面是否含有无效串的数的个数
 */ 
int dfs(int len,int u,int flag,int limit,int zero){
    //递归边界，即枚举完一个可能的数，如果没有任何限制就返回1，即一个满足要求的数
	if(len<0){
        return (!flag && !zero) ? 1 : 0;
    }
    //在没有上限限制和没有前导零限制的情况下直接记忆化搜索
	if(dp[len][u][flag]!=-1 && !limit && !zero){
        return dp[len][u][flag];
    }
	int up = limit ? n[len]-'0' : 9; 
    int ans = 0;
	for(int i=0;i<=up;i++){
        //有前导零限制且当前枚举位为0，相当于这一状态下面递归的所有状态都是无效的
        //所以直接舍弃掉这一位从下一位开始并从trie树根节点开始
        //比如1234，枚举最高位的时候0是不可以的，有前导零限制
        //所以0000,0001,0002等这些数都是无效的
        //直接从高二位开始算，也就相当于是234，同理这一位枚举到也不行
        //枚举到1的时候100，101这些就是有效状态
    	if(i==0 && zero){
            ans=(ans+dfs(len-1,0,flag,limit && i==up, 1))%MOD;
        }else{
            //当前节点含有trie树的串或者是下一个节点含有
            ans=(ans+dfs(len-1,tr[u][i],flag|val[tr[u][i]],limit && i==up,zero && i==0))%MOD;
        } 
    }
    if(!limit && !zero){
        dp[len][u][flag] = ans;
    }
	return ans;
}
int solve(){
    len=strlen(n);
    //反转，从高位枚举
    reverse(n,n+len);
    memset(dp,-1,sizeof(dp));
    return dfs(len-1,0,0,1,1);
}
/*
 * 矩阵快速幂加速dp(递推)
 * 有时候推出ac自动机加dp，结果n的范围是1e9，就需要用到矩阵快速幂来优化dp
 * bzoj1009: 求有多少个n位数不含有所给m位数的子串
 * 和上面ac自动机上dp是一样的，枚举长度，枚举节点，枚举子节点(0-9)，状态转移
 * 由于n比较大，而m比较小，我们可以把问题转化为求出从trie树根节点走n步的有效路径数
 * 所以通过构建fail树后，可以计算出trie树初始邻接矩阵(1步能走到的)，注意无效状态
 * 然后使用矩阵快速幂加速，计算邻接矩阵的n次方，即走n步的路径数矩阵
 * 枚举i，计算sum(m[0][i])即为答案(从根节点开始到其他各个节点刚好走n步的路径数)
 */ 
int solve(){
    Mat tmp,a;
    memset(tmp.m,0,sizeof(tmp.m));
    //dp初始状态
    tmp.m[0][0]=1;
    for(int i=0;i<=tot;i++){
        for(int j=0;j<10;j++){
            if(!val[tr[i][j]]){
                //从i节点到j节点存在可行路径(包括计算fail指针时指向祖先节点的关系)
                a.m[i][tr[i][j]]+=1;
            }
        }
    }
    //矩阵快速幂求长度为n的路径条数
    a=tmp*(a^n);
    int ans=0;
    for(int i=0;i<=tot;i++){
        //所有从根节点到任意节点n步的路径数
        ans+=a.m[0][i];
        ans%=k;
    }
    return ans;
}
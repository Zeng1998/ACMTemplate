/*
 * 数位dp，核心就是定义状态，并从高位枚举，从前一位(pre**)的状态转移而来
 * a[i]:第i个数位
 * dp[i][j][k][l]:
 *     从最高位到第i位，前一个数字是j，前面数字模为k，前面是/否已经出现13的所有数的个数
 */ 
//pos 当前位 mod 前面数字模13余数 pre 前一位数字 sta 前面是否有13 
ll dfs(int pos,int mod,int pre,int sta,bool limit){
    //递归边界，枚举完所有位数
    if(pos<0){
        return (sta==1 && mod==0);
    }
    //记忆化搜索，必须是没有上限的情况下
    if(!limit && dp[pos][pre][mod][sta]!=-1){
        return dp[pos][pre][mod][sta];
    }
    //上限
    int up=limit?a[pos]:9;
    ll ans=0;
    for(int i=0;i<=up;i++){
        //枚举当前位数字
	ans+=dfs(pos-1,(mod*10+i)%13,i,sta||(pre==1 && i==3),limit&&(i==up));
    }
    //dp数组定义，必须是所有数
    if(!limit){
        dp[pos][pre][mod][sta]=ans;
    }
    return ans;
}
ll solve(ll x){
    //如果有多次询问，memset一次dp即可
    int k=0;
    while(x){
        a[k++]=x%10;
        x/=10;
    }
    return dfs(k-1,0,0,false,true);
}

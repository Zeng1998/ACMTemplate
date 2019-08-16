//1
//s+=s build...
void solve(int n){
    int p=0;
    for (int i=0;i<n;i++) {
        auto t=next[p].begin();
        p=t->second;
        printf("%c",t->first+'a');
    }
    printf("\n");
}
//2 3
//dfs(0) dp[0] ans[0]...
void dfs(int u){
    dp[u]=u==0?0:1ll;
    for(int i=0;i<26;i++){
        int v=next[u][i];
        if(v){
            if(!dp[v]){
                dfs(v);
            }
            dp[u]+=dp[v];
            ans[u]+=ans[v]+dp[v];
        }
    }
}
//5
//topo(len(str)) go() num[i]=|endpos(i)|
void topo(int l){
    for(int i=0;i<=l;i++){
        w[i]=0;
    }
    for(int i=1;i<cnt;i++){
        w[len[i]]++;
    }
    for(int i=2;i<=l;i++){
        w[i]+=w[i-1];
    }
    for(int i=cnt-1;i>=1;i--){
        tp[w[len[i]]--]=i;
    }
}
void go(){
    for(int i=cnt-1;i>=1;i--){
        num[fa[tp[i]]]+=num[tp[i]];
    }
    //S状态是空串
    num[0]=0;
}
//4 6
//get dp[] pd[] solve(0,k) ...
void solve1(int u,int k){
    if(k<=0){  //k<=num[u]
        return;
    }
    for(int i=0;i<26;i++){
        int v=next[u][i];
        if(v){
            if(dp[v]>=k){  //pd[v]>=k
                printf("%c",i+'a');
                solve1(v,k-1);  //solve2(v,k-num[u])
                break;
            }else{
                k-=dp[v];  //k-=pd[v]
            }
        }
    }
}



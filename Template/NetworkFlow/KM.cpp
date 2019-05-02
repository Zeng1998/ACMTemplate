
/* * KM算法计算二分图带权最优匹配
 * n个男生和n个女生，两两之间有好感度(边权)，匹配使得总好感度最大
 * love[i][j]: 女生i和男生j的好感度
 * exg[i]/exb[i]: 女生期望值(初始值为最高好感度)，男生期望值(初始值为0)
 * visg[i]/visb[i]: 记录每一轮匹配中是否匹配过
 * match[i]: 男生i匹配到的女生，初始值为-1
 * slack[i]: 男生i还需要多少期望值才能匹配到女生
 */ 
bool dfs(int u){
    visg[u]=true;
    for(int i=0;i<n;i++){
        if(visb[i]){
            continue;
        }
        //计算期望度和好感度差值
        int gap=exg[u]+exb[i]-love[u][i];
        //这里改成gap!=0可以求出最小完备匹配
        if(gap==0){
            //符合要求
            visb[i]=true;
            //男生没有匹配，或者男生对应女生可以找另一个男生
            if(match[i]==-1 || dfs(match[i])){
                match[i]=u;
                return true;
            }
        }else{
            //无法找到匹配的，必须修改期望度(对当前女生u，也就是KM算法里枚举的i)
            slack[i]=min(slack[i],gap);
        }
    }
    return false;
}
int km(){
    memset(match,-1,sizeof(match));
    memset(exb,0,sizeof(exb));
    for(int i=0;i<n;i++){
        exg[i]=love[i][0];
        for(int j=1;j<n;j++){
            exg[i]=max(exg[i],love[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        memset(slack,INF,sizeof(slack));
        while(true){
            memset(visg,false,sizeof(visg));
            memset(visb,false,sizeof(visb));
            //找到
            if(dfs(i)){
                break;
            }
            //找不到
            int d=INF;
            //枚举男生
            for(int j=0;j<n;j++){
                if(!visb[j]){
                    //降到某个slack[j]
                    d=min(d,slack[j]);
                }
            }
            //这一轮问过的女生降低期望值，男生增加期望值
            for(int j=0;j<n;j++){
                if(visg[j]){
                    exg[j]-=d;
                }
                if(visb[j]){
                    exb[j]+=d;
                }else{
                    //没访问过的男生，因为女生期望值降低，所以距离女生期望值又近一步
                    slack[j]-=d;
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        ans+=love[match[i]][i];
    }
    return ans;
}
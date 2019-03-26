/*
 * SG函数打表找规律
 * mex(S): 表示不属于集合S的最小非负整数
 * sg[x]=mex(s);    sg[x]=0当且仅当x为必败态
 * f[i]: 表示每一步可走的情况(步数/可取的石子数)
 */
void getSG(int n){
    memset(sg,0,sizeof(sg));
    for(int i=1;i<=n;i++){
        memset(s,0,sizeof(s));
        for(int j=1;j<N && f[j]<=i;j++){
            //打标记
            s[sg[i-f[j]]]=1;
        }
        for(int j=0;j<=n;j++){
            if(s[j]==0){
                sg[i]=j;
                break;
            }
        }
    }
}
/*
 * 初始化f[]
 * 示例: Bash博弈
 */ 
void init(){
    for(int i=1;i<N;i++){
        if(i<=m){
            f[i]=i;
        }else{
            f[i]=m;
        }
    }
}
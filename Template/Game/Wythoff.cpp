/*
 * 有两堆石子(a,b)，两人轮流从一堆或者两堆中取出相同个数，每次最少取一个
 */ 
bool solve(int a,int b){
    if(a>b){
        swap(a,b);
    }
    int c=int((b-a)*(sqrt(5.0)+1)/2);
    //根据(0,0)先手必败态来判断
    return c!=a;
}
/*
 * SG函数打表
 */ 
void getSG(int n){
    //枚举两堆分别的数量和取的数量
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            //记录后继状态形式
            int win=0,lose=0;
            //同时从两堆中取k个
            for(int k=1;k<=min(i,j);k++){
                if(!sg[i-k][j-k]){
                    win++;
                }else{
                    lose++;
                }
            }
            for(int k=1;k<=i;k++){
                if(!sg[i-k][j]){
                    win++;
                }else{
                    lose++;
                }
            }
            for(int k=1;k<=j;k++){
                if(!sg[i][j-k]){
                    win++;
                }else{
                    lose++;
                }
            }
            //后继都是必败态，则当前状态是必胜态
            if(lose==0){
                sg[i][j]=1;
            }else{
                sg[i][j]=0;
            }
        }
    }
}
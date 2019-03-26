/*
 * 有三堆石子(a,b,c)，两人轮流取，每次从一堆中取至少一个
 */ 
bool solve(int a,int b,int c){
    //可拓展到n堆
    //根据必败态(0,0,0)判断
    return a^b^c;
}
/*
 * SG函数打表
 */
void getSG(int n){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int g=0;g<=n;g++){
                int win=0,lose=0;
                for(int k=1;k<=i;k++){
                    if(!sg[i-k][j][g]){
                        win++;
                    }else{
                        lose++;
                    }
                }
                for(int k=1;k<=j;k++){
                    if(!sg[i][j-k][g]){
                        win++;
                    }else{
                        lose++;
                    }
                }
                for(int k=1;k<=g;k++){
                    if(!sg[i][j][g-k]){
                        win++;
                    }else{
                        lose++;
                    }
                }
                if(lose==0){
                    sg[i][j][k]=1;
                }else{
                    sg[i][j][k]=0;
                }
            }
        }
    }
} 
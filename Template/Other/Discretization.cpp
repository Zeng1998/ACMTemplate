/*
 * 离散化
 */ 
void solve(){
    int x[]={0,2,10000,1,3,500,19999999,212222222,13};
    int n=8;
    sort(x+1,x+1+n);
    for(int i=1;i<=n;i++){
        //根据具体题目调整
        int k=lowerbound(x+1,x+1+n,x[i])-x;
    }
}
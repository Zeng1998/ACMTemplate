/*
 * 线性筛同时筛出素数和欧拉函数
 * check[i]: i是否是合数(被筛)
 * p[i]: 第i个素数，p[0]为个数
 * phi[i]: i的欧拉函数值
 */ 
void init(){
    check[1]=true;
    phi[1]=1;
    for(int i=2;i<=N;i++){
        if(!check[i]){
            p[++p[0]]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=p[0];j++){
            int t=i*p[j];
            if(t>N){
                break;
            } 
            check[t]=true;
            //t拥有多个相同质因子(p[j]至少就2次)
            if(i%p[j]==0){
                //i是p[j]的倍数，那t和i的质因子相同，由欧拉函数计算式可得两者只差一个系数
                phi[t]=phi[i]*p[j];
            }else{
                //欧拉函数是积性函数 phi[t]=phi[i]*phi[p[j]]
                phi[t]=phi[i]*(p[j]-1);
            }
        }
    }
}
/*
 * 求单个欧拉函数 O(sqrt(n))
 */ 
int getPhi(int x){
    int res=x;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            res=res-res/i;
            while(x%i==0){
                x/=i;
            }
        }
    }
    if(x!=1){
        res=res-res/x;
    }
    return res;
}
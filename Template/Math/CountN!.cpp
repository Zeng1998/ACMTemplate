/*
 * 使用斯特林公式求解n阶乘的位数
 */ 
int count(ll n){
    if(n==1){
        return 1;
    }
    return (int)ceil(0.5*log10(2*M_PI*n)+n*log10(n)-n*log10(M_E));
}
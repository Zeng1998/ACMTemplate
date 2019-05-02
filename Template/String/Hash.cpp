typedef unsigned long long ull;
const ull seed1=146527,seed2=19260817;
const ull MOD1=1000000009,MOD2=998244353;
/*
 * 字符串哈希，记得初始化(init())
 */
void init(){
    p[0]=1;
    for(int i=1;i<N;i++){
        p[i]=p[i-1]*seed1%MOD1;
    }
}
void Hash(char s[],int n,ull *h1){
    h[0]=0;
    for(int i=1;i<=n;i++){
        h[i]=(h[i-1]*seed1%MOD1+s[i-1])%MOD1;
    }
}
ull substr(int l,int len,ull *h1){
    return (h1[l+len]-h1[l]*p[len]%MOD1+MOD1)%MOD1;
}
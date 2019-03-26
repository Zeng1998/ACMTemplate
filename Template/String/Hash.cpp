typedef unsigned long long ull;
const ull seed1=146527;
const ull seed2=19260817;
const ull MOD1=1000000009;
const ull MOD2=998244353;
/*
 * 字符串哈希(双哈希)
 * 记得初始化(init())
 */
void init(){
    p1[0]=p2[0]=1;
    for(int i=1;i<N;i++){
        p1[i]=p1[i-1]*seed1%MOD1;
        p2[i]=p2[i-1]*seed2%MOD2;
    }
}
void Hash(char s[],ull *h1,ull *h2){
    int n=strlen(s);
    h1[0]=h2[0]=0;
    for(int i=1;i<=n;i++){
        h1[i]=(h1[i-1]*seed1%MOD1+s[i-1])%MOD1;
        h2[i]=(h2[i-1]*seed2%MOD2+s[i-1])%MOD2;
    }
}
pair<ull,ull> substr(int l,int len,ull *h1,ull *h2){
    int r=l+len;
    pair<ull,ull> res;
    res.first=(h1[r]-h1[l]*p1[r-l]%MOD1+MOD1)%MOD1;
    res.second=(h2[r]-h2[l]*p2[r-l]%MOD2+MOD2)%MOD2;
}
//单哈希很容易卡；取模很慢
ull seeds[]={27,146527,19260817,91815541};
ull mods[]={1000000009,998244353,4294967291ull,212370440130137957ll};
struct Hash{
    ull seed,mod;
    ull bas[N];
    ull sum[N];
    void init(int sidx,int midx,int len,char *s){
        seed=seeds[sidx];
        mod=mods[midx];
        bas[0]=1;
        for(int i=1;i<=len;i++){
           bas[i]=bas[i-1]*seed%mod;
        }
        for(int i=1;i<=len;i++){
            sum[i]=(sum[i-1]*seed%mod+s[i])%mod;
        }
    }
    ull getHash(int l,int r){
        return (sum[r]-sum[l-1]*bas[r-l+1]%mod+mod)%mod;
    }
}hs;

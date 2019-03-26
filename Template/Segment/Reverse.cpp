/*
 * 离散化+树状数组求逆序数
 */ 
int solve(){
    for(int i=1;i<=n;i++){
        int k=lower_bound(b+1,b+n+1,a[i])-b;
        add(k,1);
        ans+=i-sum(k);
    }
    return ans;
}
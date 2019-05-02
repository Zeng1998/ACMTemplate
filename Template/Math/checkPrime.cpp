/* O(logN)判定单个素数
 * 最好都开long long
 * for循环里i*i可能会爆int导致TLE(天梯赛L1-028)
 */
bool check(ll n){
    if(n==1){
        return false;
    }
    for(ll i=2;i*i<=n;i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}
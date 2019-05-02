/*
 * 大步小步算法用于解决：已知A, B, C，求x使得A^x=B(mod C)成立
 * 令x = im - j | m = ceil(sqrt(C))， i = [1, m]， j = [0, m]
 * 原式变成  A^(im) = A^j * B
 * 枚举j，把A^j*B加入哈希表，再枚举i，在表中查找A^(i*m)，复杂度为O(n^0.5)
 */ 
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll p, a, b, X1, t, T;
ll pow(ll a, ll b, ll p) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % p;
        b >>= 1;
        a = a * a % p;
    }
    return ans;
}
ll inv(ll a, ll p) {
    return pow(a, p-2, p);
}
map<ll, ll> mp;
ll BSGS(ll A, ll B, ll C) {
    mp.clear();
    if(A % C == 0) return -2;
    ll m = ceil(sqrt(C));
    ll ans;
    for(int i = 0; i <= m; i++) {
        if(i == 0) {
            ans = B % C;
            mp[ans] = i;
            continue;
        }
        ans = (ans * A) % C;
        mp[ans] = i;
    }
    ll t = pow(A, m, C); 
    ans = t;
    for(int i = 1; i <= m; i++) {
        if(i != 1)ans = ans * t % C;
        if(mp.count(ans)) {
            int ret = i * m % C - mp[ans] % C;
            return (ret % C + C)%C;
        }
    }
    return -2;
} 
int main() {
    scanf("%lld", &T);
    while(T--) {
        scanf("%lld %lld %lld %lld %lld", &p, &a, &b, &X1, &t);
        if(X1 == t) {
            printf("%d\n", 1);
            continue;
        }
        if(a == 0) {
            if(t == b) {
                printf("%d\n", 2);
            }
            else printf("%d\n", -1);
            continue;
        }
        if(a == 1) {
            if(b == 0) {
                printf("%d\n", -1);
                continue;
            }
            ll ans = (((t-X1)%p + p)%p * inv(b, p)) % p;
            printf("%lld\n", ans+1);
            continue;
        }
        X1 %= p, a %= p, b %= p, t%= p;
        ll tmp = (b%p * inv(a-1, p))%p;
        ll B = ((t+tmp)%p * inv((X1+tmp) % p, p)) % p;
        ll A = a;
        ll ans = BSGS(A, B, p);
        printf("%lld\n", ans+1);
    }
    return 0;
}
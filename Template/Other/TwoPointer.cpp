/*
 * 封装成一个滑窗结构体，维护区间内不同字母个数(根据题目需要)
 */
struct window{
    int siz;
    int cnt[26];
    window(){
        siz=0;
        memset(cnt,0,sizeof(cnt));
    }
    void add(int x){
        if(!cnt[x]){
            siz++;
        }
        cnt[x]++;
    }
    void remove(int x){
        cnt[x]--;
        if(!cnt[x]){
            siz--;
        }
    }
};
void solve(char s[],int n,int k){
	window w;
    int n=strlen(s);
    int l=0,r=0;
    ll ans=0;
    while(l<n){
        //右指针速度大于左指针
        while(w.siz<k && r<n){
            w.add(s[r++]-'a');
        }
        if(w.siz<k){
            break;
        }
        //同时更新答案
        ans+=(n-r+1);
        w.remove(s[l++]-'a');
    }
}

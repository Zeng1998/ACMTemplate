#include <bits/stdc++.h>
using namespace std;
const int N=3e5+50;
int n,q,a[N];
char s[2];
int l,r,x;
//在序列后添加一个数  询问[l,r]中某一个p 使得(sum(n)^sum(p-1))^x最大,也就是(sum(n)^x)^sum(p-1)
//转化为求区间里与x异或最大的那个值  类似于线段树求全局 主席树求区间 这里trie树求全局 可持久化trie树求区间
//为了方便求前缀和,设第一个数a[0]为0 而且为了方便建可持久化树(第一个根rt[0]是个空树) 我们将数组设置为a[1]=0 a[2]才是的序列第一个数
int p[N];
int rt[N];
struct Trie{
    int cnt,tr[N*30][2],val[N*30];
    void init(){
        cnt=0;
        memset(tr,0,sizeof(tr));
        memset(val,0,sizeof(val));
    }
    int insert(int pre,int x){
        int rt=++cnt;
        int now=rt;
        for(int i=31;i>=0;i--){
            int id=(x>>i)&1;
            if(!tr[now][id]){
                tr[now][id]=++cnt;
                tr[now][id^1]=tr[pre][id^1];
                val[tr[now][id]]=val[tr[pre][id]];
            }
            pre=tr[pre][id];
            now=tr[now][id];
            val[now]++;
        }
        return rt;
    }
    int query(int l,int r,int x){
        int ans=0;
        for(int i=31;i>=0;i--){
            int id=(x>>i)&1;
            if(val[tr[r][id^1]]-val[tr[l][id^1]]){
                ans=ans*2+1;
                l=tr[l][id^1];
                r=tr[r][id^1];
            }else{
                ans=ans*2;
                l=tr[l][id];
                r=tr[r][id];
            }
        }
        return ans;
    }
}T;
int main(void){
    freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&q);
    T.init();
    rt[1]=T.insert(0,0);
    n++;
    for(int i=2;i<=n;i++){
        scanf("%d",&a[i]);
        p[i]=p[i-1]^a[i];
        rt[i]=T.insert(rt[i-1],p[i]);
    }
    while(q--){
        scanf("%s",s);
        if(s[0]=='A'){
            n++;
            scanf("%d",&a[n]);
            p[n]=p[n-1]^a[n];
            rt[n]=T.insert(rt[n-1],p[n]);
        }else if(s[0]=='Q'){
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",T.query(rt[l-1],rt[r],p[n]^x));
        }
    }
    return 0;
}

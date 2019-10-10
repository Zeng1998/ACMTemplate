#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int n,m,l,r,c[N],a[N],p[N],ans[N];
struct node{
    int o,id,l,r;
    bool operator<(const node& rhs)const{
        if(r==rhs.r){
            if(l==rhs.l){
                //注意l和r都相同，询问点要放在后面...
                return o<rhs.o;
            }else{
                return l>rhs.l;
            }
        }else{
            return r<rhs.r;
        }
    }
};
vector<node> ns;
int lowbit(int x){
    return x&(-x);
}
void add(int i,int x){
    while(i<=n){
        c[i]+=x;
        i+=lowbit(i);
    }
}
int sum(int i){
    int ans=0;
    while(i){
        ans+=c[i];
        i-=lowbit(i);
    }
    return ans;
}
int main(){
//     freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        p[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+i;j<=n;j+=i){
            int a=p[i],b=p[j];
            if(a>b){
                swap(a,b);
            }
            ns.push_back({1,0,a,b});
        }
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&l,&r);
        ns.push_back(node{2,i,l,r});
    }
    sort(ns.begin(),ns.end());
    int ad=0;
    int siz=ns.size();
    for(int i=0;i<siz;i++){
        if(ns[i].o==1){
            add(ns[i].l,1);
            ad++;
        }else{
            ans[ns[i].id]=ad-sum(ns[i].l-1);
        }
    }
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
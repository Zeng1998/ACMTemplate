#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N=1e5+50;
//三维LIS(偏序),第一维排序,第二维cdq分治,第三维树状数组
struct node{
    int x,y,z,id;
    bool operator <(const node &r)const{
        return x!=r.x?x<r.x:y!=r.y?y<r.y:z<r.z;
    }
}q[N],tmp[N];
//维护一个二维的权值bit(i表示z坐标 x表示dp状态) first表示长度 second表示大小
//普通bit表示前缀和,这里的bit表示前i个三维点的LIS(长度和方案数)
pii dp[N],c[N];
pii zero(0,0);
int lowbit(int x){
    return x&(-x);
}
//实现一个pii的dp状态的相加
void update(pii &a,pii &b){
    if(a.first<b.first){
        a=b;  //长度大于当前的,更新长度
    }else if(a.first==b.first){
        a.second+=b.second;  //长度相等的,更新方案数
    }
}
void add(int i,pii x){
    while(i<=n){
        update(c[i],x); //bit里维护的是一个pair,所以这里不是简单的c[i]+=x
        i+=lowbit(i);
    }
}
pii sum(int i){
    pii ans=zero;
    while(i>0){
        update(ans,c[i]);
        i-=lowbit(i);
    }
    return ans;
}
void clr(int i){
    while(i<=n){
        c[i]=zero;
        i+=lowbit(i);
    }
}
void cdq(int l,int r){
    if(l>=r){
        return;
    }
    int mid=(l+r)/2;
    cdq(l,mid);  //单独处理左区间,即处理出前半部分的dp状态
    //利用左区间信息更新右区间
    //tmp临时记录这个区间内的操作
    int k=0;
    for(int i=l;i<=r;i++){
        tmp[k]=q[i];
        tmp[k++].x=0;  //第一维x已经降掉
    }
    sort(tmp,tmp+k);  //对y和z排序
    for(int i=0;i<k;i++){
        node& t=tmp[i];
        //这里tmp是排好序的,所以先出来的y和z肯定小
        if(t.id<=mid){
            //属于左区间的操作,已经在cdq(l,mid)中处理完毕
            //加入权值bit,表示t.z累加上dp[t.id]个
            add(t.z,dp[t.id]);
        }else{
            //属于右区间的操作(未操作),查询t.z前面的dp状态前缀和
            //并累加到当前id的dp状态
            pii a=sum(t.z);
            a.first++;
            update(dp[t.id],a);
        }
    }
    //处理右区间前把属于左区间的操作的bit清空
    for(int i=0;i<k;i++){
        if(tmp[i].id<=mid){
            clr(tmp[i].z);
        }
    }
    cdq(mid+1,r);  //单独处理右区间
}
int main(void){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%d%d%d",&x,&y,&z);
            q[i]=node{x,y,z,i};
            Z[i]=z;
        }
        sort(q,q+n);
        sort(Z,Z+n);  //离散化z
        kn=unique(Z,Z+n)-Z;
        for(int i=0;i<n;i++){
            q[i].z=lower_bound(Z,Z+kn,q[i].z)-Z+1;
            q[i].id=i;  //注意是排序后的id
        }
        for(int i=0;i<n;i++){
            dp[i].first=dp[i].second=1;
        }
        cdq(0,n-1);
        pii ans=zero;
        for(int i=0;i<n;i++){
            update(ans,dp[i]);  //直接update累加,同时更新LIS和方案数
        }
        printf("%d %d\n",ans.first,ans.second);
    }
    return 0;
}
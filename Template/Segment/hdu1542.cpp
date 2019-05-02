/*
 *  线段排序之后从下往上扫描，遇到下边(即d=1)，更新线段树对应区间(注意线段的[1...3]对应线段树[1..2])
 *  更新后计算当前线段树覆盖的总长度(即根节点的sum)，乘以下一条线段(上面一条)即得到一部分的面积
*/
#include <bits/stdc++.h>
using namespace std;
#define lson i<<1
#define rson i<<1|1
#define mid (l+r)/2
int n;
const int N=1005;
double xa,ya,xb,yb;
struct node{
    double l,r,h;
    int d;
    bool operator <(const node& rhs)const{
        return h<rhs.h;
    }
}a[N];
double all[N];
//覆盖边数量(即d值的累加)
int cnt[N];
//离散化区间所对应的真正长度
double sum[N];
void pushup(int i,int l,int r){
    if(cnt[i]){
        //注意实际的线段和线段树的区别
        //实际是[1...2...3]三个点两段
        //建树时最好是[l,r-1]，也就是以段来建树
        //计算长度再恢复到[1...3]
        sum[i]=all[r+1]-all[l];
    }else{
        sum[i]=sum[lson]+sum[rson];
    }
}
void build(int i,int l,int r){
    cnt[i]=sum[i]=0;
    if(l==r){
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
}
void update(int i,int l,int r,int L,int R,int v){
    if(L<=l && R>=r){
        cnt[i]+=v;
        //一定要pushup
        pushup(i,l,r);
        return;
    }
    if(l==r){
        return;
    }
    if(L<=mid){
        update(lson,l,mid,L,R,v);
    }
    if(R>mid){
        update(rson,mid+1,r,L,R,v);
    }
    pushup(i,l,r);
}
int main(void){
    int cas=1;
    while(~scanf("%d",&n)){
        if(n==0){
            break;
        }
        for(int i=1;i<=n;i++){
            scanf("%lf%lf%lf%lf",&xa,&ya,&xb,&yb);
            a[i]=node{xa,xb,ya,-1};
            a[i+n]=node{xa,xb,yb,1};
            all[i]=xa;
            all[i+n]=xb;
        }
        n*=2;
        sort(a+1,a+1+n);
        sort(all+1,all+1+n);
        int m=unique(all+1,all+1+n)-all-1;
        build(1,1,m);
        double ans=0;
        for(int i=1;i<n;i++){
            int l=lower_bound(all+1,all+1+m,a[i].l)-all;
            int r=lower_bound(all+1,all+1+m,a[i].r)-all;
            if(l<r){
                update(1,1,m,l,r-1,a[i].d);
            }
            //每次扫描到一条边映射到线段树上，然后计算部分面积
            //等于上面一条(即下一条)线段与该线段差值乘以线段树(根)覆盖区间实际长度
            ans+=sum[1]*(a[i+1].h-a[i].h);
        }
        printf("Test case #%d\n",cas++);
        printf("Total explored area: %.2lf\n\n",ans);
    }
    return 0;
}
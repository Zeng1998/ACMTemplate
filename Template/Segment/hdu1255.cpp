/*
 *  线段排序之后从下往上扫描，遇到下边(即d=1)，更新线段树对应区间(注意线段的[1...3]对应线段树[1..2])
 *  更新后计算当前线段树覆盖两次的总长度(即根节点的two)，乘以下一条线段(上面一条)即得到一部分的面积
*/
#include <bits/stdc++.h>
using namespace std;
#define lson i<<1
#define rson i<<1|1
const int N=1050;
int t,n;
double xa,ya,xb,yb;
struct Seg{
    double l,r,h;
    int d;
    Seg(){}
    Seg(double l,double r,double h,int d):l(l),r(r),h(h),d(d){}
    bool operator <(const Seg& rhs)const{
        return h<rhs.h;
    }
}a[N<<1];
double all[N<<1];
int le[4*N],ri[4*N];
//覆盖边数量(即d值的累加)
int cnt[4*N];
//区间覆盖1次和2次的真正长度
double one[4*N],two[4*N];
//扫描线中的PushUp是用来通过cnt来更新sum(或者one,two)
void PushUp(int i){
    if(cnt[i]>=2){
        //覆盖两次
        two[i]=one[i]=all[ri[i]+1]-all[le[i]];
    }else if(cnt[i]==1){
        //覆盖一次
        one[i]=all[ri[i]+1]-all[le[i]];
        if(le[i]==ri[i]){
            two[i]=0;
        }else{
            //该区间覆盖一次，子节点又覆盖一次
            two[i]=one[lson]+one[rson];
        }
    }else{
        if(le[i]==ri[i]){
            two[i]=one[i]=0;
        }else{
            two[i]=two[lson]+two[rson];
            one[i]=one[lson]+one[rson];
        }
    }
}
void Build(int i,int l,int r){
    le[i]=l;
    ri[i]=r;
    cnt[i]=one[i]=two[i]=0;
    if(l==r){
        return;
    }
    int mid=(l+r)>>1;
    Build(lson,l,mid);
    Build(rson,mid+1,r);
}
void Update(int i,int l,int r,int v){
    if(l<=le[i] && r>=ri[i]){
        cnt[i]+=v;
        PushUp(i);
        return;
    }
    int mid=(le[i]+ri[i])>>1;
    if(l<=mid){
        Update(lson,l,r,v);
    }
    if(r>mid){
        Update(rson,l,r,v);
    }
    PushUp(i);
}
int main(void){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%lf%lf%lf%lf",&xa,&ya,&xb,&yb);
            a[i]=Seg(xa,xb,ya,1);
            a[i+n]=Seg(xa,xb,yb,-1);
            all[i]=xa;
            all[i+n]=xb;
        }
        n<<=1;
        sort(a+1,a+1+n);
        sort(all+1,all+1+n);
        int m=unique(all+1,all+1+n)-all-1;
        Build(1,1,m);
        double ans=0;
        for(int i=1;i<n;i++){
            int l=lower_bound(all+1,all+1+m,a[i].l)-all;
            int r=lower_bound(all+1,all+1+m,a[i].r)-all;
            if(l<r){
                Update(1,l,r-1,a[i].d);
            }
            ans+=two[1]*(a[i+1].h-a[i].h);
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
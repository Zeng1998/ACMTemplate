#include <cstdio>
#include <algorithm>
using namespace std;
#define lson i<<1
#define rson i<<1|1
const int N=1e4+50;
struct Seg{
    //线段的左右端点(x)，上下边(1下 -1上)，高(y)
    int l,r,d,h;
    Seg(){}
    Seg(int l,int r,int h,int d):l(l),r(r),h(h),d(d){}
    //从下到上处理线段
    bool operator <(const Seg& rhs)const{
        return h<rhs.h;
    }
}a[2][N];
int le[4*N],ri[4*N];
//边的覆盖，线段长度
int cnt[4*N],sum[4*N];
int all[2][N<<1];
int n;
int xa,ya,xb,yb;
void PushUp(int p,int i){
    if(cnt[i]){
        //i有覆盖，那更新覆盖长度
        sum[i]=all[p][ri[i]+1]-all[p][le[i]];
    }else{
        sum[i]=sum[lson]+sum[rson];
    }
}
void Build(int i,int l,int r){
    le[i]=l;
    ri[i]=r;
    cnt[i]=sum[i]=0;
    if(l==r){
        return;
    }
    int mid=(l+r)>>1;
    Build(lson,l,mid);
    Build(rson,mid+1,r);
}
void Update(int p,int i,int l,int r,int v){
    if(l<=le[i] && r>=ri[i]){
        cnt[i]+=v;
        //记得pushup，因为扫描线没有query操作，所以也无需懒惰标记，区间更新后直接推到根
        PushUp(p,i);
        return;
    }
    int mid=(le[i]+ri[i])>>1;
    if(l<=mid){
        Update(p,lson,l,r,v);
    }
    if(r>mid){
        Update(p,rson,l,r,v);
    }
    PushUp(p,i);
}
int main(void){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        //矩形左下角和右上角坐标
        scanf("%d%d%d%d",&xa,&ya,&xb,&yb);
        //a[0]保存横边 a[1]保存竖边
        //all[0]保存离散化的横坐标 all[1]保存纵坐标
        a[0][i]=Seg(xa,xb,ya,1);
        a[0][i+n]=Seg(xa,xb,yb,-1);
        all[0][i]=xa;
        all[0][i+n]=xb;
        a[1][i]=Seg(ya,yb,xa,1);
        a[1][i+n]=Seg(ya,yb,xb,-1);
        all[1][i]=ya;
        all[1][i+n]=yb;
    }
    //别忘记扩大两倍
    n<<=1;
    //对线段排序
    sort(a[0]+1,a[0]+1+n);
    sort(a[1]+1,a[1]+1+n);
    //对坐标排序，为了离散化
    sort(all[0]+1,all[0]+1+n);
    sort(all[1]+1,all[1]+1+n);
    //去重
    int m[2];
    m[0]=unique(all[0]+1,all[0]+1+n)-all[0]-1;
    m[1]=unique(all[1]+1,all[1]+1+n)-all[1]-1;
    int ans=0;
    //求周长并需要计算横边和竖边
    for(int i=0;i<2;i++){
        Build(1,1,m[i]);
        //上一条边长度
        int last=0;
        for(int j=1;j<=n;j++){
            //离散化
            int l=lower_bound(all[i]+1,all[i]+1+m[i],a[i][j].l)-all[i];
            int r=lower_bound(all[i]+1,all[i]+1+m[i],a[i][j].r)-all[i];
            if(l>r){
                swap(l,r);
            }
            //区间更新
            Update(i,1,l,r-1,a[i][j].d);
            //根节点覆盖的总和即为当前高度的总边长
            ans+=abs(sum[1]-last);
            //减去前一次已经计算过的周长
            last=sum[1];
        }
    }
    printf("%d\n",ans);
    return 0;
}
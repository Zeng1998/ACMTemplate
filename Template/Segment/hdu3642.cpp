/*
 * 三维扫描线就是枚举z坐标然后做二维的扫描线
 */ 
#include <bits/stdc++.h>
using namespace std;
#define lson i<<1
#define rson i<<1|1
typedef long long ll;
const int N=2550;
struct Seg{
    int l,r,h,d;
    bool operator <(const Seg& rhs)const{
        return h<rhs.h;
    }
}a[N];
//立方体
struct Rect{
    int xa,ya,za,xb,yb,zb;
}r[N];
int le[4*N],ri[4*N];
int cnt[4*N],one[4*N],two[4*N],three[4*N];
int X[N],Z[N];
void PushUp(int i){
	int l=le[i],r=ri[i];
	if (cnt[i]>=3){
		three[i] = X[r+1]-X[l];
		two[i]=one[i]=0;
	}else if(cnt[i]==2){
		three[i]=three[lson]+three[rson]+two[lson]+two[rson]+one[lson]+one[rson];
		two[i]=X[r+1]-X[l]-three[i];
		one[i]=0;
	}else if(cnt[i]==1) {
		three[i]=three[lson]+three[rson]+two[lson]+two[rson];
		two[i]=one[lson]+one[rson];
		one[i]=X[r+1]-X[l]-three[i]-two[i]; 
	}else{
		three[i]=three[lson]+three[rson];
		two[i]=two[lson]+two[rson];
		one[i]=one[lson]+one[rson];
	}
}
void Build(int i,int l,int r){
    le[i]=l;
    ri[i]=r;
    cnt[i]=one[i]=two[i]=three[i]=0;
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
int t,n;
int xa,xb,ya,yb,za,zb;
int main(void){
    scanf("%d",&t);
    for(int cas=1;cas<=t;cas++){
        scanf("%d",&n);
        //x z坐标的个数
        int cnt_x=0;
        int cnt_z=0;
        //点的个数
        int pcnt=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d%d%d%d%d",&xa,&ya,&za,&xb,&yb,&zb);
            r[pcnt++]=Rect{xa,ya,za,xb,yb,zb};
            X[cnt_x++]=xa;
            X[cnt_x++]=xb;  
            Z[cnt_z++]=za;
            Z[cnt_z++]=zb;
        }
        //离散化z用于枚举每一层
        //离散化x用于每一层的扫描线
        sort(X,X+cnt_x);
        sort(Z,Z+cnt_z);
        cnt_x=unique(X,X+cnt_x)-X;
        cnt_z=unique(Z,Z+cnt_z)-Z;
        ll V=0;
        //枚举离散化后的z
        for(int i=0;i<cnt_z-1;i++){
            //这一层边的数量
            int k=0;
            ll S=0;
            //枚举立方体
            for(int j=0;j<pcnt;j++){
                //找处于Z[i]位置的立方体 映射在Z[i]平面上进行二维的扫描线
                if(r[j].za<=Z[i] && r[j].zb>Z[i]){
                    a[k++]=Seg{r[j].xa,r[j].xb,r[j].ya,1};
                    a[k++]=Seg{r[j].xa,r[j].xb,r[j].yb,-1};
                }
            }
            sort(a,a+k);
            //这里如果build 1到cnt_x会t
            Build(1,1,N);
            for(int j=0;j<k-1;j++){
                int ql=lower_bound(X,X+cnt_x,a[j].l)-X;
                int qr=lower_bound(X,X+cnt_x,a[j].r)-X;
                Update(1,ql,qr-1,a[j].d);
                S+=(ll)three[1]*(ll)(a[j+1].h-a[j].h);
            }
            V+=S*(ll)(Z[i+1]-Z[i]);
        }
        printf("Case %d: %lld\n",cas,V);
    }
}
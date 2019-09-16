#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e6+50;
ll n;
int ans[N];
ll get(int i,int j){
    //获取值
}
int val(ll x){
    int ans=0;
    while(x){
        ans+=x%10;
        x/=10;
    }
    return ans;
}
int T,m,p,x,y,xb,yb,mx,cnt,c[N];
int lowbit(int x){}
void add(int i,int x){}
int sum(int i){}
void clr(int i){
    while(i<=mx){
        if(!c[i]){
            break;
        }
        c[i]=0;
        i+=lowbit(i);
    }
}
struct node{
    int type,x,y,w,id;
}a[N],b[N];
void cdq(int l,int r){
    if(l==r){
        return;
    }
    int mid=(l+r)/2;
    cdq(l,mid);
    cdq(mid+1,r);
    int i=l,j=mid+1,kk=l;
    //左边和右边单独的贡献已经递归算出
    //这里计算跨左右两边的贡献，即左边加入bit，右边查询
    while(i<=mid && j<=r){
        //两边此时都按x，y的顺序排序
        if(a[i].x<=a[j].x){
            if(a[i].type==1){
                //权值点，加入bit
                add(a[i].y,a[i].w);
            }
            //按x归并排序
            b[kk++]=a[i++];
        }else{
            if(a[j].type==2){
                ans[a[j].id]+=sum(a[j].y);
            }else if(a[j].type==3){
                ans[a[j].id]-=sum(a[j].y);
            }
            b[kk++]=a[j++];
        }
    }
    //处理剩下的
    while(i<=mid){
        if(a[i].type==1){
            add(a[i].y,1);
        }
        b[kk++]=a[i++];
    }
    while(j<=r){
        if(a[j].type==2){
            ans[a[j].id]+=sum(a[j].y);
        }else if(a[j].type==3){
            ans[a[j].id]-=sum(a[j].y);
        }
        b[kk++]=a[j++];
    }
    for(int i=l;i<=r;i++){
        clr(a[i].y);
        a[i]=b[i];
    }
}
int main(){
    scanf("%d",&T);
    while(T--){
        cnt=0,mx=0;
        scanf("%lld%d%d",&n,&m,&p);
        for(int i=1;i<=m;i++){
            //加入有价值的点
            scanf("%d%d",&x,&y);
            a[++cnt]=node{1,x,y,val(get(x,y)),i};
            mx=max(mx,y);
        }
        for(int i=1;i<=p;i++){
            //加入询问点
            scanf("%d%d%d%d",&x,&y,&xb,&yb);
            a[++cnt]=node{2,x-1,y-1,1,i};
            a[++cnt]=node{2,xb,yb,1,i};
            a[++cnt]=node{3,x-1,yb,1,i};
            a[++cnt]=node{3,xb,y-1,1,i};
            mx=max(mx,yb);
            ans[i]=0;
        }
        cdq(1,cnt);
        for(int i=1;i<=p;i++){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}

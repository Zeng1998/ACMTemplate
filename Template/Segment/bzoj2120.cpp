/*
 * 有n个不同颜色，两种操作，修改某个位置的颜色，查询某个区间[l,r]里不同颜色个数
 * 比普通的莫队多了一个修改的操作，所以Q结构体多了一个时间戳tim
 * 排序的时候也要多加一个判断，在l，r都同块的情况下对tim排序
 * 除了询问要保存时间，修改也要在对应时间保存起来，记录原来的颜色和修改后的颜色
 * 查询答案时，先对时间T进行调整，再套用普通莫队
 */ 
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int n,m,a[N],be[N];
struct Q{
    //多了一个tim类似于保存版本号
    int id,l,r,tim,ans;
}q[N];
bool cmp1(Q a,Q b){
    return be[a.l]==be[b.l]?(be[a.r]==be[b.r]?a.tim<b.tim:a.r<b.r):a.l<b.l;
}
bool cmp2(Q a,Q b){
    return a.id<b.id;
}
struct Change{
    int pos,New,Old;
}c[N];
char qe[2];
int x,y;
int Time;
int now[N];
int ans,color[N*100],l,r;
void revise(int x,int d){
    //这里的x对应going的d，而d则是代表加或减
    //x这种颜色的个数
    color[x]+=d;
    if(d>0){
        //刚好第一次出现这种颜色，更新答案
        ans+=color[x]==1;
    }
    if(d<0){
        //这种颜色刚好被删完，更新答案
        ans-=color[x]==0;
    }
}
//带时间修改，将x的颜色改为d
void going(int x,int d){
    //x如果在当前的区间内
    if(l<=x && x<=r){
        //更新答案
        revise(d,1);
        revise(a[x],-1);
        //修改颜色
        a[x]=d;
    }
}
int main(void){
    scanf("%d%d",&n,&m);
    int unit=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        be[i]=i/unit+1; 
        now[i]=a[i];
    }
    int qcnt=0;
    for(int i=1;i<=m;i++){
        scanf("%s%d%d",qe,&x,&y);
        if(qe[0]=='Q'){
            q[++qcnt]=Q{qcnt,x,y,Time,0};
        }else if(qe[0]=='R'){
            //记录修改状态
            c[++Time]=Change{x,y,now[x]}; 
            now[x]=y;     
        }
    }
    sort(q+1,q+1+qcnt,cmp1);
    l=1,r=0;
    int T=0;
    for(int i=1;i<=qcnt;i++){
        //维护时间T
        //q[i].tim表示在这个时刻发生的查询，所以维护当前时刻T直到为tim
        while(T<q[i].tim){
            //所以在这个过程中要执行修改
            going(c[T+1].pos,c[T+1].New);
            T++;
        }
        while(T>q[i].tim){
            going(c[T].pos,c[T].Old);
            T--;
        }
        //时间维护完，维护空间顺序，同普通莫队
        while(l<q[i].l){
            revise(a[l],-1);
            l++;
        }
        while(l>q[i].l){
            revise(a[l-1],1);
            l--;
        }
        while(r<q[i].r){
            revise(a[r+1],1);
            r++;
        }
        while(r>q[i].r){
            revise(a[r],-1);
            r--;
        }
        q[i].ans=ans;
    }
    sort(q+1,q+1+qcnt,cmp2);
    for(int i=1;i<=qcnt;i++){
        printf("%d\n",q[i].ans);
    }
    return 0;
}
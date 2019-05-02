/**
 * 线段树维护最大连续区间
 */
#include <bits/stdc++.h>
using namespace std;
#define lson i<<1
#define rson i<<1|1
const int N=5e4+50;
int n,m;
int le[4*N],ri[4*N];
//左最大连续区间 右最大连续区间 总最大连续区间
int lm[4*N],rm[4*N],mx[4*N];
void PushUp(int i){
    lm[i]=lm[lson];
    rm[i]=rm[rson];
    mx[i]=max(max(mx[lson],mx[rson]),rm[lson]+lm[rson]);
    //左儿子区间满，父节点左区间要加上右儿子左区间
    if(mx[lson]==ri[lson]-le[lson]+1){
        lm[i]+=lm[rson];
    }
    //右儿子区间满，父节点右区间要加上左儿子右区间
    if(mx[rson]==ri[rson]-le[rson]+1){
        rm[i]+=rm[lson];
    }
}
void Build(int i,int l,int r){
    le[i]=l;
    ri[i]=r;
    lm[i]=rm[i]=mx[i]=r-l+1;   
    if(l==r){
        return;
    }
    int mid=(l+r)>>1;
    Build(lson,l,mid);
    Build(rson,mid+1,r);
}
void Update(int i,int l,int r,int v){
    if(le[i]==ri[i]){
        //修复1 破坏0
        lm[i]=rm[i]=mx[i]=v;
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
int ans;
void Query(int i,int t){
    //叶子 最大连续区间为空 最大连续区间为整段 
    if(le[i]==ri[i] || mx[i]==0 || mx[i]==ri[i]-le[i]+1){
        ans+=mx[i];
        return;
    }
    int mid=(le[i]+ri[i])>>1;
    //看左子树
    if(t<=mid){
        if(t>=ri[lson]-rm[lson]+1){
            //t在左子树的右区间内
            Query(lson,t);
            Query(rson,mid+1);
        }else{
            //t不在左子树的右区间内
            Query(lson,t);
        }
    }else{
        if(t<=le[rson]+lm[rson]-1){
            //t在右子树的左区间内
            Query(rson,t);
            Query(lson,mid);
        }else{
            //t不在左子树的右区间内
            Query(rson,t);
        }
    }
}
int main(void){
    while(~scanf("%d%d",&n,&m)){
        char s[2];
        int x;
        Build(1,1,n);
        stack<int> sta;
        while(m--){
            scanf("%s",s);
            if(s[0]=='D'){
                scanf("%d",&x);
                sta.push(x);
                Update(1,x,x,0);
            }else if(s[0]=='Q'){
                scanf("%d",&x);
                ans=0;
                Query(1,x);
                printf("%d\n",ans);
            }else if(s[0]=='R'){
                x=sta.top();
                sta.pop();
                Update(1,x,x,1);
            }
        }
    }
}
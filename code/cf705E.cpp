#include <bits/stdc++.h>
using namespace std;
#define ls i<<1
#define rs i<<1|1
#define mid (l+r)/2
const int N=2e5+50;
const int INF=0x3f3f3f3f;
char s[N];
//矩阵a[i][j]表示状态i转移到状态j的最小花费
//0 初始状态
//1 2
//2 20
//3 201
//4 2017
struct Mat{
    int a[5][5];
    Mat operator+(const Mat& rhs)const{
       Mat ans;
       for(int i=0;i<5;i++){
           for(int j=0;j<5;j++){
               ans.a[i][j]=INF;
               for(int k=0;k<5;k++){
                   ans.a[i][j]=min(ans.a[i][j],a[i][k]+rhs.a[k][j]);
               }
           }
       }
       return ans;
    }
}t[N*4];
void pushup(int i){
    t[i]=t[ls]+t[rs];
}
void build(int i,int l,int r){
    if(l==r){
        //叶子节点表示单个字符的状态
        for(int j=0;j<5;j++){
            for(int k=0;k<5;k++){
                t[i].a[j][k]=(j==k)?0:INF;
            }
        }
        if(s[l]=='2'){
            t[i].a[0][1]=0;
            t[i].a[0][0]=1;
        }else if(s[l]=='0'){
            t[i].a[1][2]=0;
            t[i].a[1][1]=1;
        }else if(s[l]=='1'){
            t[i].a[2][3]=0;
            t[i].a[2][2]=1;
        }else if(s[l]=='7'){
            t[i].a[3][4]=0;
            t[i].a[3][3]=1;
        }else if(s[l]=='6'){
            t[i].a[3][3]=1;
            t[i].a[4][4]=1;
        }
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(i);
}
void print(Mat a){
    for(int j=0;j<5;j++){
        for(int k=0;k<5;k++){
            printf("%d ",a.a[j][k]);
        }
        printf("\n");
    }
}
Mat query(int i,int l,int r,int ql,int qr){
    if(ql<=l && qr>=r){
        return t[i];
    }
    //换个写法，不用写零元
    if(qr<=mid){
        return query(ls,l,mid,ql,qr);
    }else if(ql>mid){
        return query(rs,mid+1,r,ql,qr);
    }else{
        return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
    }
}
int n,q,l,r;
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    build(1,1,n);
    while(q--){
        scanf("%d%d",&l,&r);
        Mat ans=query(1,1,n,l,r);
        printf("%d\n",ans.a[0][4]==INF?-1:ans.a[0][4]);
    }
    return 0;
}

/**
 * 数列分块6：动态插值，单点查询
 */ 
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int a[N],bel[N];
int n,block,o,l,r,c;
vector<int> vec[400];
//a[i]前面插入值x
void insert(int x,int v){
    //找到要插入的块
    int now=0;
    int whi=0;
    for(int i=1;;i++){
        int siz=vec[i].size();
        now+=siz;
        if(now>=x){
            whi=i;
            x-=(now-siz);
            break;
        }
    }
    vec[whi].insert(vec[whi].begin()+x-1,v);
}
//查询a[x]
int pos(int x){
    int now=0;
    for(int i=1;;i++){
        int siz=vec[i].size();
        now+=siz;
        if(now>=x){
            int iii=x-(now-siz);
            return vec[i][iii-1];
        }
    }
}
int main(void){
    scanf("%d",&n);
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        bel[i]=(i-1)/block+1;
        vec[bel[i]].push_back(a[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&o,&l,&r,&c);
        if(o==0){
            insert(l,r);
        }else{
            printf("%d\n",pos(r));
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
/*
 * 求1-n字典序排列的第m个数
 */ 
int solve(int n,int m){
    //考虑一颗完全10叉树，树的所有节点就是1-n，要求的就是前序遍历的第m个节点
    //m是可以走的步数
    int i=1;
    m--;
    while(m!=0){
        //计算i到i+1的字典序中间相隔的个数
        int s=i,e=i+1;
        int num=0;
        //防止越界
        while(s<=n){
            //计算每一层相差的个数
            //n+1: 比如20-29其实是10个，而e就不用+1，因为e在这里表示30(40/50...)
            num+=min(n+1,e)-s;
            s*=10;
            e*=10;
        }
        if(m<num){
            //向下
            i*=10;
            //走一步
            m--;
        }else{
            //向右
            i++;
            //对前序遍历来说，走了num步
            m-=num;
        }
    }
    return i;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    printf("%d\n",solve(n,m));
    return 0;
     
}

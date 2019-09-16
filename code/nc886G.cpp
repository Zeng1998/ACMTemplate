#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
int T,n;
int ms[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
bool leap(int y){
    return ((y%4==0 && y%100!=0) || y%400==0);
}
//判断日期合法性
bool check(int y,int m,int d){
    if(m==0 || m>12 || d==0){
        return false;
    }
    int t=ms[m];
    if(leap(y) && m==2){
        t++;
    }
    return d<=t;
}
//基姆拉尔森公式
bool cl(int y,int m,int d){
    if(!check(y,m,d)){
        return false;
    }
    //题面...
    if(y<1600){
        return false;
    }
    //1 2月要转成上一年13 14月
    if(m<=2){
        m+=12;
        y--;
    }
    int w=((d+2*m+3*(m+1)/5+y+y/4-y/100+y/400+1)%7+7)%7;
    return w==5;
}
int main(void){
    //main
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
int a[5];
int main(void){
    int mx=0;
    int idx=-1;
    for(int i=0;i<4;i++){
        scanf("%d",&a[i]);
        if(a[i]>mx){
            mx=a[i];
            idx=i;
        }
    }
    for(int i=0;i<4;i++){
        if(i!=idx){
            printf("%d ",mx-a[i]);
        }
    }
    printf("\n");
    return 0;
}
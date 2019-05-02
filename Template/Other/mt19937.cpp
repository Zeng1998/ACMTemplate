#include <bits/stdc++.h>
using namespace std;
int main(void){
    mt19937 rnd(time(0));
    for(int i=0;i<5;i++){
        printf("%lld\n",rnd());
    }
    return 0;
}
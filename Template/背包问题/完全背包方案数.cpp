#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=105;
int f[MAXN];
int main(void){
	int n=3;
	int a[]={1,2,5};
	f[0]=1;
	for(int i=0;i<n;i++){
		//比如f[6]=f[5]+f[4]+f[1]
		//其实也就是爬楼梯问题了，多种可能的状态方案加起来
		for(int j=MAXN-1j>=v[i];j--){
			f[j]+=f[j-a[i]];
		}
	}
	for(int i=0;i<MAXN;i++){
		printf("%d ",f[i]);
	}
	printf("\n");
	return 0;
}

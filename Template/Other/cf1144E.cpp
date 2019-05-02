#include <bits/stdc++.h>
using namespace std;
const int N=2e5+50;
char s[N],t[N];
int n,a[N],b[N],c[N];
int main(void){
	scanf("%d",&n);
	scanf("%s",s);
	scanf("%s",t);
	for(int i=0;i<n;i++){
		//后移一位，可能有进位
		a[i+1]=s[i]-'a';
		b[i+1]=t[i]-'a';
	}
	//加法
	for(int i=n;i>=1;i--){
		c[i]+=(a[i]+b[i]);
		if(c[i]>=26){
			c[i]-=26;
			c[i-1]++;
		}
	}
	//除法
	for(int i=0;i<=n;i++){
		int t=c[i]%2;
		if(t){
			c[i+1]+=26;
		}
		c[i]=c[i]/2;
	}
	for(int i=1;i<=n;i++){
		printf("%c",(char)('a'+c[i]));
	}
	printf("\n");
	return 0;
}
/*
 * 树状数组(普通版): 单点更新，区间求和(sum(r)-sum(l-1))
 * c[i]: 树状数组，c[i]=a[i-lowbit(i)+1]+a[i-lowbit(i)+2]+...+a[i]
 */ 
int lowbit(int x){
    return x&(-x);
}
int add(int i,int x){
    while(i<=n){
        c[i]+=x;
        i+=lowbit(i);
    }
}
int sum(int i){
    int ans=0;
    while(i>0){
        //这里也可以维护最值 ans=max(ans,c[i]);
        ans+=c[i];
        i-=lowbit(i);
    }
    return ans;
}
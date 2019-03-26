/*
 * 树状数组(加强版2): 区间更新，区间求和
 * 维护两个树状数组 c1保存d[i]的前缀和 c2保存d[i]*i的前缀和
 * 求和ans=\sum[((k+1)*c1[i]-c2[i])]
 */ 
void add(int i,int x){
    int k=i;
    while(i<=n){
        c1[i]+=x;
        c2[i]+=k*x;
        i+=lowbit(i);
    }
}
void add_range(int l,int r,int x){
    add(l,x);
    add(r+1,-x);
}
int sum(int i){
    int ans=0;
    int k=i;
    while(i>0){
        ans+=((k+1)*c1[i]-c2[i]);
        i-=lowbit(i);
    }
    return ans;
}
int ask_range(int l,int r){
    return sum(r)-sum(l-1);
}
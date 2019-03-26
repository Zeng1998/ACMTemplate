/*
 * 树状数组(加强版1): 区间更新，单点查询(sum(i))
 * 设d[i]=a[i]-a[i-1] 所以a[i]=d[1]+d[2]+...+d[i]
 * 树状数组c维护d的前缀和，也相当于变相维护了a[i]，所以单点查询是查询sum
 */ 
void update(int l,int r){
    add(l,1);
    add(r+1,-1);
}
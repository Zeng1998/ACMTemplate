/*
 * 二维数组数组(I)，单点更新，区间求和(sum(x2,y2)-sum(x1-1,y2)-sum(x2,y1-1)+sum(x1-1,y1-1))
 */ 
void add(int x,int y,int z){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=m;j+=lowbit(j)){
            c[i][j]+=z;
        }    
    }
}
int sum(int x,int y){
    int ans=0;
    for(int i=x;i>=1;i-=lowbit(i)){
        for(int j=y;j>=1;j-=lowbit(j)){
            ans+=c[i][j];
        }
    }
    return ans;
}
/*
 * 二维尺取法(枚举一维): 求满足01矩阵中1个数大于等于k的最小矩形大小
 * pre[i][j]: 从(1,1)到(i,j)的1个数(二维前缀和)
 */ 
void solve(){
    int ans=INF;
    //枚举列，确定矩形左右边界
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            //尺取
            int l=1,r=1;
            while(r<=n){
                while(pre[r][j]-pre[r][i-1]-pre[l-1][j]+pre[l-1][i-1]<k && r<=n){
                    r++;
                }
                if(pre[r][j]-pre[r][i-1]-pre[l-1][j]+pre[l-1][i-1]<k){
                    break;
                }
                ans=min(ans,(j-i+1)*(r-l+1));
                l++;
            }
        }
    }
}

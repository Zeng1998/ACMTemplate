/*
 * O(n^2) 求最大上升/下降子序列(不连续)
 * d[i]: 到i位置的最长上升子序列长度
 */  
void solve(){
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(a[j]<a[i]){
                d[i]=max(d[i],d[j]+1);
            }
        }
    }
}
/*
 * O(nlogn) 算法
 * 也许不是dp...
 */ 
void solve2(){
    for(int i=1;i<=n;i++){
        g[i]=INF;
    }
    //求下降子序列将原数组取反即可
    //g[i]表示LIS为i的子序列的最后一个数的最小值
    for(int i=0;i<n;i++){
        //找到g[k]刚好大于a[i]
        //改成upper_bound()可以求最大不下降序列
        int k=lower_bound(g+1,g+1+n,a[i])-g;
        d[i]=k;
        //更新g[k]
        g[k]=a[i];
    }
}
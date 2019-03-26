/*
 * 矩阵快速幂
 * Mat: 矩阵类型，包含一个二维数组
 */ 
Mat operator * (Mat a, Mat b) {
    Mat ans;
    memset(ans.mat, 0, sizeof(ans.mat));
    for(int i=0; i<n; i++) {
        for(int k=0; k<n; k++) {
            for(int j=0; j<n; j++) {
                ans.mat[i][j] += (a.mat[i][k] % mod) * (b.mat[k][j] % mod) % mod;
                ans.mat[i][j] %= mod;
            }
        }
    }
    return c;
}
Mat operator ^ (Mat a, ll n)  {
    Mat ans;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
             ans.mat[i][j]=(i==j);
        }
    }
    while(n) {
        if(n%2){
            ans=ans*a;
        }
        a=a*a;
        n/=2;
    }
    return ans;
}
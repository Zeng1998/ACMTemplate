//求循环字符串s的最小/最大表示
//i,j: 当前比较两个字符串的起始位置
//k: 这两个字符串已比较的长度
int getMin(char s[]){
    int n=strlen(s);
    int i=0,j=1,k=0;
    while(i<n && j<n && k<n){
        int t=s[(i+k)%n]-s[(j+k)%n];
        if(!t){
            k++;
        }else{
            if(t>0){
                //如果是求最大表示则为j+=k+1
                i+=k+1; 
            }else{
                j+=k+1;
            }
            if(i==j){
                j++;
            }
            k=0;
        }
    }
    return min(i,j);
}

//"banana" 后缀为[banana$ anana$ nana$ ana$ na$ a$ $]
//sa[i]: 排名第i(从0开始)小的后缀的首字符下标 
//比如[6 5 3 1 0 4 2]==>[$ a$ ana$ anana$ banana$ na$ nana$]
//rk[i]: 下标i开始的后缀(不含$)的排名(按字典序从小到大，相当于sa的逆)  
//[4 3 6 2 5 1]
//h[i]:排名为i的后缀和排名为i-1的后缀的最长公共前缀  
//[1(ana$-a$) 3(anana$-ana$) 0 0 2]
//辅助数组: t[N],t2[N],c[N];
void build_sa(int n, int m){ 
    //n为字符串的长度,字符集的值为0~m-1
    //相当于在后面加一个$
    //有时候是数字数组而不是字符数组，最好加上s[n]=0
    n++;
    int *x=t, *y=t2;
    //基数排序
    for(int i=0;i<m;i++){
        c[i]=0;
    }
    for(int i=0;i<n;i++){
        c[x[i]=s[i]]++;
    }
    for(int i=1;i<m;i++){
        c[i]+=c[i-1];
    }
    //或者~i 表示i!=-1
    for(int i=n-1;i>=0;i--){
        sa[--c[x[i]]]=i;
    }
    for(int k=1; k<=n; k<<=1){ 
        int p=0;
        for(int i=n-k;i<n;i++){
            y[p++]=i;
        }
        for(int i=0;i<n;i++){
            if(sa[i]>=k){
                y[p++]=sa[i]-k;
            }
        }
        //类似上面，只是把i换成y[i]
        for(int i=0;i<m;i++){
            c[i]=0;
        }
        for(int i=0;i<n;i++){
            c[x[y[i]]]++;
        }
        for(int i=1;i<m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n-1;i>=0;i--){
            sa[--c[x[y[i]]]]=y[i];
        }
        swap(x, y);
        p=1;
        x[sa[0]]=0;
        for(int i=1;i<n;i++){
            x[sa[i]]=y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]? p-1 : p++;
        }
        if (p>=n){
            break; 
        }
        m = p;
    }
    //去掉$
    n--;
    for(int i = 0; i <= n; i++){
        rk[sa[i]] = i;
    }
    //计算h
    int k=0;
    for(int i = 0; i < n; i++){
        if(k){
            k--;
        }
        int j = sa[rk[i] - 1];
        while(s[i + k] == s[j + k]){
            k++;
        }
        h[rk[i]] = k;
    }
}
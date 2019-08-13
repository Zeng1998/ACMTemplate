//nex[i]表示t串中以i开始的后缀与t串的最长公共前缀
//ext[i]表示s串中以i开始的后缀与t串的最长公共前缀
void getNex(char *t,int len){
    int a=0;
    while(a<len-1 && t[a]==t[a+1]){
        a++;
    }
    nex[1]=a;
    int po=1;
    for(int i=2;i<len;i++){
        int p=po+nex[po]-1;
        int l=nex[i-po];

        if(l>=p-i+1){
            int j=max(0,p-i+1);
            while(i+j<len && t[i+j]==t[j]){
                j++;
            }
            nex[i]=j;
            po=i;
        }else{
            nex[i]=l;
        }
    }
}
void getExt(char *s,int n,char *t,int m){
    int a=0;
    getNex(t,m);
    int mlen=min(n,m);
    //计算ext[0]
    while(a<mlen && s[a]==t[a]){
        a++;
    }
    ext[0]=a;
    //po表示当前最右的i+ext[i]-1所对应的i
    int po=0;
    for(int i=1;i<n;i++){
        //p表示最右的i+ext[i]-1
        int p=po+ext[po]-1;
        //此时前面已匹配的s[po..p]==t[0..p-po]，即s[i..p]==t[i-po..p-po]
        //所以l就是表示t[i-po...m-1]和t[0..m-1]的lcp
        //也就是s[i..p]和t[0..m-1]的**部分**lcp
        //得看l和p-i+1(ext[i]可能的最大值)哪个大
        int l=nex[i-po];
        if(l>=p-i+1){
            //l大，那么从p-i+1(目前可以保证的ext[i]的值)继续暴力往下匹配
            int j=max(0,p-i+1);
            while(i+j<n && j<m && s[i+j]==t[j]){
                j++;
            }
            ext[i]=j;
            po=i;
        }else{
            //p-i+1大，那么ext[i]就只能是l了
            ext[i]=l;
        }
    }
}
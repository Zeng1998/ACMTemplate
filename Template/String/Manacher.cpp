/*
 * 求字符串s的最大回文子串
 * ma[]:新字符串(ma,mp都注意要开两倍空间!)
 * mp[i]:表示以i为中心的回文子串的半径(包括特殊字符)
 * mx:能延伸到最右端的位置 
 * id:能延伸到最右端的回文串中心位置
 */
int manacher(char s[],int len){
    //构造新字符串 两个字符之间插入一个其他字符 
    //第0个字符忽略(即加入另一种字符)
    int l=0;
    ma[l++]='$';
    ma[l++]='#';
    for(int i=0;i<len;i++){
        ma[l++]=s[i];
        ma[l++]='#';
    }
    ma[l]='\0';
    int mx=0,id=0;
    for(int i=1;i<l;i++){
        //递推部分 比较mx和i的位置
        //右边:2*id-i表示i以id的对称点 因为不能超出mx 所以要和mx-i取min
        //左边: mp[i]=1
        mp[i]=mx>i?min(mp[2*id-i],mx-i):1;
        //更新部分 
        //往两边更新
        while(ma[i+mp[i]]==ma[i-mp[i]]){
            mp[i]++;
        }
        //更新全局mx和id
        if(i+mp[i]>mx){
            mx=i+mp[i];
            id=i;
        }
    }
    return *max_element(mp,mp+l)-1;
}

//fail[x]指向以x为结尾的后缀在**其他模式串中**所能匹配的最长前缀
//当tr[now][i]失配时，就可以跳转到以已匹配的这部分后缀作为前缀的其他模式串。
struct ACM{
    int tr[N][26],val[N],fail[N],cnt;
    void insert(char *s){
        int len=strlen(s);
        int now=0;
        for(int i=0;i<len;i++){
            int id=s[i]-'a';
            if(!tr[now][id]){
                tr[now][id]=++cnt;
            }
            now=tr[now][id];
        }
        val[now]++;
    }
    //比Trie树多了构建fail指针
    void build(){
        queue<int> q;
        //初始化第一层
        for(int i=0;i<26;i++){
            if(tr[0][i]){
                fail[tr[0][i]]=0;
                q.push(tr[0][i]);
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                if(tr[u][i]){
                    fail[tr[u][i]]=tr[fail[u]][i];
                    q.push(tr[u][i]);
                }else{
                    tr[u][i]=tr[fail[u]][i];
                }
            }
        }
    }
    //查询所有模式串出现的总次数
    int query(char *s){
        int len=strlen(s);
        int ans=0;
        int now=0;
        for(int i=0;i<len;i++){
            int id=s[i]-'a';
            now=tr[now][id];
            //打标记暴力跳fail，避免重复计数
            for(int t=now;t && val[t]!=-1; t=fail[t]){
                ans+=val[t];
                val[t]=-1;
            }
        }
        return ans;
    }
}ac;
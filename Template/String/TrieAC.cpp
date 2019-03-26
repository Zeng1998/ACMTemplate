/*
 * 字典树/tr自动机
 */
struct node{
    int son[26];
    //根据需要维护一些奇奇怪怪的东西
    //被查询次数
    int cnt;
    //是否完整单词
    bool flag;
    //作为前缀次数
    int sum;
    //=======AC自动机=======
    //模式串下标
    int end;
    //失配指针，表示以当前失配的字符串的最长后缀字符串
    //比如匹配到abcd，d失配，那么c的fail指针指向的就是后缀为abc(或者bc或者c)的最长字符串
    int fail;
}tr[N];
int tot;
void init(){
    tot=0;
    memset(tr,0,sizeof(tr));
}
/*
 * 插入字符串构建Trie树
 */ 
void insert(char *s,int num){
    int len=strlen(s);
    int rt=0;
    for(int i=0;i<len;i++){
        int id=s[i]-'a';
        if(!tr[rt].son[id]){
            tr[rt].son[id]=++tot;
        }
        rt=tr[rt].son[id];
        tr[rt].sum++;
    }
    //标记完整单词
    tr[rt].flag=true;
    tr[rt].end=num;
}
/*
 * 字典树简单查询: 以所给串作为前缀个模式串个数
 */
int search(char *s){
    int len=strlen(s);
    int rt=0;
    int ans=0;
    for(int i=0;i<len;i++){
        int id=s[i]-'a';
        if(!tr[rt].son[id]){
            //not found
            return 0;
        }
        rt=tr[rt].son[id];
    }
    return tr[rt].sum;
}
/*
 * 构建tr自动机fail指针
 */
void getFail(){
    queue<int> q;
    //先处理第一层,都指向根
    for(int i=0;i<26;i++){
        if(tr[0].son[i]!=0){
            tr[tr[0].son[i]].fail=0;
            q.push(tr[0].son[i]);
        }
    }
    //bfs处理
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(tr[u].son[i]!=0){
                //子节点的fail指向父节点fail的对应子节点
                tr[tr[u].son[i]].fail=tr[tr[u].fail].son[i];
                //记得入队
                q.push(tr[u].son[i]);
            }else{
                //不存在这个子节点，指向fail指针的对应子节点
                tr[u].son[i]=tr[tr[u].fail].son[i];
            }
        }
    }
}
/*
 * tr自动机简单查询: 每个模式串在所给串中分别出现的次数
 * ans[]: 结构体数组{pos,num}表示模式串的下标和出现次数
 */ 
void query(char s[]){
    int len=strlen(s);
    int rt=0;
    for(int i=0;i<len;i++){
        int id=s[i]-'a';
        rt=tr[rt].son[id];
        //沿着失配路径到根
        //比如两个模式串abcd和bcd，所给字符串abcdbcd
        //一开始直接匹配到abcd出现一次，然后这时候沿着fail找到bcd，
        //所以bcd也出现了一次，同理直到根
        //就能把出现的子串都记录一遍
        for(int j=rt;j!=0;j=tr[j].fail){
            ans[tr[j].end].num++;
        }
    }
}
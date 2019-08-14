//空间足够的情况下开大点
struct SAM{
    //转移边
    int next[N*2][26];
    //link边
    int fa[N*2];
    //状态内最长后缀长度
    int len[N*2];
    //状态对应endpos大小，即子串出现次数
    int num[N*2];
    //总节点数
    int cnt;
    //上一个节点
    int lst;
    int newnode(int l,int s){
        for(int i=0;i<26;i++){
            next[cnt][i]=0;
        }
        len[cnt]=l;
        num[cnt]=s;
        return cnt++;
    }
    //初始化
    void init(){
        cnt=0;
        lst=newnode(0,0);
        fa[lst]=-1;
    }
    void add(int c){
        c-='a';
        int p=lst;
        int cur=newnode(len[p]+1,1);
        //假设当前sam为"aabb"，起点S为空串，节点5是{b}，节点4是{aabb,abb,bb}
        //定义suffix-path为当前字符串的所有后缀的状态，即S[1..i]，S[2..i]...
        //此时的s-p就是S-5-4，(b这个后缀因为endpos大于其他，所以在节点5)
        //插入的字符是a，而s-p上5和4节点都没有a，因此将节点5和4 fa节点6
        //节点6此时为{aabba,abba,bba,ba}
        //当路径上的节点已经有a
        while(p!=-1 && !next[p][c]){
            next[p][c]=cur;
            p=fa[p];
        }
        if(p==-1){
            //对应上面整个路径都没有a的情况
            fa[cur]=0;
        }else{
            //路径上找到一个有a，往前肯定都有a
            int q=next[p][c];
            if(len[q]==len[p]+1){
                //这里节点S(p)为空串，而节点1(q)为{a}，因此将新节点6 fa节点1
                fa[cur]=q;
            }else{
                //st[q].len>st[p].len+1
                //假设当前sam为"aab"，起点S为空串，节点4是{aab,ab,b}
                //此时的s-p就是S-3，要插入的字符是b，路径上S节点有b，指向节点3
                //而st[3].len>st[S].len+1，因此需要将节点3拆分
                //把从节点S+b得到的后缀{b}分给新的节点5
                //将q拆成两个节点，p->cl->new
                int cl=newnode(len[p]+1,0);
                fa[cl]=fa[q];
                memcpy(next[cl],next[q],sizeof(next[cl]));
                while(p!=-1 && next[p][c]==q){
                    //之前路径上所有p走向q的，现在全部走向q拆出的新节点
                    next[p][c]=cl;
                    p=fa[p];
                }
                //q和新节点都fa向拆出节点
                fa[q]=fa[cur]=cl;
            }
        }
        //更新最后一个节点
        lst=cur;
    }
}ac;
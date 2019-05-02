/*
 * 带权并查集
 * 所谓带权并查集就是在并查集的基础上除了维护根节点再维护一些其他的值
 * 例如集合大小，元素移动次数，元素到根节点的距离等
 * 状态的转移在find和unit都要考虑，而且要注意顺序
 * eg. poj1182——食物链 设r[i]表示i和父节点(根)的关系
 * r[i]=0表示和父节点同类，1表示被父节点吃，2表示吃父节点
 */ 
int find(int x){
    if(x!=p[x]){
        //暂存当前根节点，用于状态转移更新信息
        int t=p[x];
        //递归压缩路径，此时p[x]信息已更新
        p[x]=find(p[x]);
        //元素移动次数/元素到根距离
        cnt[x]+=cnt[t];
        //假设r[x]=1，即x被t吃，如果r[t]=2，即t吃p[x]
        //那说明x和p[x]同类，r[x]=(1+2)%3=0，其他同理
        r[x]=(r[x]+r[t])%3;
    }
    return p[x];
}
void unit(int a,int b){
    int fa=find(a);
    int fb=find(b);
    if(fa!=fb){
        p[fa]=fb;
        //hdu2818 将一堆放到另一堆上 维护某一元素下方元素个数，即到根的距离
        cnt[fa]=siz[fb];
        //集合大小
        siz[fb]+=siz[fa];
    }
}
bool unit(int a,int b,int q){
    q--;
    //q是操作，0表示同类，1表示a吃b
    int fa=find(a);
    int fb=find(b);
    if(fa!=fb){
        p[fb]=fa;
        //可以画图去看 r[fb]即求fb到fa的关系
        //必须通过fb->b(-r[b]) b->a(q) a->fa(r[a])三个向量相加即可
        r[fb]=(-r[b]+r[a]+q+3)%3;
        return false;
    }else{
        //已在同一集合
        //同样通过画图，此时a,b有相同根f
        //r[a]+q即b->a(q) a->f(r[a])==r[b]，若不符合，即矛盾
        return (r[a]+q)%3!=r[b];
    }
}
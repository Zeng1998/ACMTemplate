#include <bits/stdc++.h>
using namespace std;
const int N=1e6+50;
//树结构
int tr[N][2],fa[N];
//节点值
int val[N];
//节点值重复次数
int cnt[N];
//子树大小(包括重复元素,非节点数)
int siz[N];
//根节点
int rt;
//节点个数
int tot;
//更新信息
void update(int x){
    siz[x]=siz[tr[x][0]]+siz[tr[x][1]]+cnt[x];
}
//查找x值位置
int find(int x){
    int now=rt;
    while(x!=val[now]){
        if(x<val[now]){
            if(tr[now][0]==0){
                break;
            }
            now=tr[now][0];
        }else{
            if(tr[now][1]==0){
                break;
            }
            now=tr[now][1];
        }
    }
    return now;
}
//同时更新父节点和子节点连接
void connect(int x,int f,int son){
    fa[x]=f;
    tr[f][son]=x;
}
//创建节点
void newnode(int v,int f){
    tot++;
    val[tot]=v;
    siz[tot]=cnt[tot]=1;
    tr[tot][0]=tr[tot][1]=0;
    connect(tot,f,v>val[f]);
}
//获取是父节点的左儿子还是右儿子
int get(int x){
    return tr[fa[x]][1]==x;
}
//单旋转,x上旋
void rotate(int x){
    int y=fa[x];
    int yy=fa[y];
    int xs=get(x);
    int ys=get(y);
    int b=tr[x][xs^1];
    //右旋,x的右儿子变成y的左二子;左旋,x的左儿子变成y的右儿子
    connect(b,y,xs);
    //右旋,父节点y变成右儿子,左旋,父节点y变成左二子
    connect(y,x,(xs^1));
    //x顶替y的位置,连接yy
    connect(x,yy,ys);
    //x和y发生变动,更新信息
    //注意这里要先更新y的信息,再更新x的信息!!
    update(y);
    update(x);
}
//伸展,通过多次旋转将x旋转到to的儿子
void splay(int x,int to){
    while(fa[x]!=to){
        int f=fa[x];
        int ff=fa[f];
        if(ff!=to){
            //分两种情况,x,y,yy成一条链的,直接单旋y
            //yy左儿子是y,y右儿子是x,或者yy右儿子是y,y左儿子是z,单旋x
            rotate(get(x)==get(f)?f:x);
        }
        rotate(x);
    }
    //旋转到根则更新根
    if(to==0){
        rt=x;
    }
}
//插入元素
void insert(int x){
    //特判插入第一个节点
    if(rt==0){
        newnode(x,0);
        rt=tot;
        return;
    }
    //找到x位置
    int ip=find(x);
    if(val[ip]==x){
        //找到,重复次数直接+1
        cnt[ip]++;
        //更新信息
        update(ip);
        //旋转到根
        splay(ip,0);
    }else{
        //找不到,创建节点
        newnode(x,ip);
        //更新信息,旋转到根
        update(ip);
        splay(tot,0);
    }
}
//删除元素
void del(int x){
    int ip=find(x);
    //旋转到根
    splay(ip,0);
    //找不到
    if(val[ip]!=x){
        return;
    }
    //此时已旋转到根
    if(cnt[ip]>1){
        //存在不止一个值
        cnt[ip]--;
        update(ip);
    }else if(tr[ip][0]==0 && tr[ip][1]==0){
        //剩一个节点,删除即为空树
        rt=0;
        tot=0;
        //清空子树
        tr[rt][0]=tr[rt][1]=0;
    }else if(tr[ip][0]!=0 && tr[ip][1]==0){
        //只有左子树,删除后左子树即为根
        rt=tr[ip][0];
        fa[tr[ip][0]]=0;
    }else if(tr[ip][0]==0 && tr[ip][1]!=0){
        //只有右子树
        rt=tr[ip][1];
        fa[tr[ip][1]]=0;
    }else{
        //有左右子树
        //找到左子树的最右节点
        int p=tr[ip][0];
        while(tr[p][1]!=0){
            p=tr[p][1];
        }
        //旋转到ip的子树,不能直接旋转到根,因为后面还要用到ip的信息
        splay(p,ip);
        //成为新的根
        rt=p;
        fa[p]=0;
        fa[tr[ip][1]]=p;
        tr[p][1]=tr[ip][1];
        update(p);
    }
}
//获取v的排名(第几小)
int rnk(int x){
    //找到元素位置
    int ip=find(x);
    //旋转到根
    splay(ip,0);
    //排名即左儿子大小+1
    return siz[tr[ip][0]]+1;
}
//获取第k小元素,排名的逆操作
int kth(int k){
    int now=rt;
    while(true){
        if(k<=siz[tr[now][0]]){
            //左儿子
            now=tr[now][0];
        }else if(k>cnt[now]+siz[tr[now][0]]){
            //右儿子
            k-=cnt[now]+siz[tr[now][0]];
            now=tr[now][1];
        }else{
            //当前节点
            break;
        }
    }
    return val[now];
}
int pre(int x){
    //先将x插入,splay到根,直接找左子树的最右节点,再删除x
    insert(x);
    int now=tr[rt][0];
    int ans;
    while(now){   
        if(!tr[now][1]){
             ans=val[now]; 
             break;
        }
        now=tr[now][1];
    }
    del(x);
    return ans;
}
int nxt(int x){ 
    //同理,找到右子树的最左节点
    insert(x);
    int now=tr[rt][1];
    int ans;
    while(now){   
        if(!tr[now][0]){
             ans=val[now]; 
             break;
        }
        now=tr[now][0];
    }
    del(x);
    return ans;
}
int m,o,x;
int main(void){
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&o,&x);
        if(o==1){
            insert(x);
        }else if(o==2){
            del(x);
        }else if(o==3){
            printf("%d\n",rnk(x));
        }else if(o==4){
            printf("%d\n",kth(x));
        }else if(o==5){
            printf("%d\n",pre(x));
        }else if(o==6){
            printf("%d\n",nxt(x));
        }
        //如果是简单的求前驱后继，用set即可
        /**
         * auto it=s.upper_bound(x)
         * if(it!=s.end()){
         *      *it为后继
         * }
         * if(it!=s.begin()){
         *      it++;
         *      *it为前驱
         * }
         */ 
    }
    return 0;
}
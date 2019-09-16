#include <bits/stdc++.h>
using namespace std;
const int N=1e6+50;
const int INF=0x3f3f3f3f;
struct FhqTreap{
    int tot,seed;
    struct node{
        int val,rk,lc,rc,siz;
    }tr[N];
    int Rand(){
        return seed=int(seed*482711ll%2147483647);
    }
    void pushup(int rt){
        tr[rt].siz=tr[tr[rt].lc].siz+tr[tr[rt].rc].siz+1;
    }
    int newnode(int v){
        tr[++tot]=node{v,Rand(),0,0,1};
        return tot;
    }
    //将一颗treap分成两棵，小于等于v的在a树，大于v的在b树
    void split(int rt,int &a,int &b,int v){
        if(!rt){
            a=b=0;
            return;
        }
        if(tr[rt].val<=v){
            a=rt;
            split(tr[rt].rc,tr[a].rc,b,v);
        }else{
            b=rt;
            split(tr[rt].lc,a,tr[b].lc,v);
        }
        pushup(rt);
    }
    //将两棵treap合并成一颗
    void merge(int &rt,int a,int b){
        if(a==0 || b==0){
            //rt=a || rt=b
            rt=a+b;
            return;
        }
        if(tr[a].rk<tr[b].rk){
            //b合并在a的右子树
            rt=a;
            merge(tr[a].rc,tr[a].rc,b);
        }else{
            //a合并在b的左子树
            rt=b;
            merge(tr[b].lc,a,tr[b].lc);
        }
        pushup(rt);
    }
    void ins(int &rt,int v){
        int x=0,y=0;
        int no=newnode(v);
        //将当前的树根据v分成两棵
        split(rt,x,y,v);
        //合并在x树上
        merge(x,x,no);
        //再重新合并到根上
        merge(rt,x,y);
    }
    void del(int &rt,int v){
        int x=0,y=0,z=0;
        //将值为v的节点分开
        split(rt,x,y,v);
        split(x,x,z,v-1);
        //分出的三棵树再合并，z树包含v节点，所以只合并tr[z].lc和tr[z].rc
        merge(z,tr[z].lc,tr[z].rc);
        merge(x,x,z);
        merge(rt,x,y);
    }
    //第k大
    int kth(int rt,int k){
        while(true){
            int t=tr[tr[rt].lc].siz+1;
            if(k<t){
                rt=tr[rt].lc;
            }else if(k>t){
                k-=t;
                rt=tr[rt].rc;
            }else{
                break;
            }
        }
        return tr[rt].val;
    }
    //v的排名(重复的数算第一个排名)
    int rnk(int &rt,int v){
        int x=0,y=0;
        split(rt,x,y,v-1);
        int tmp=tr[x].siz+1;
        merge(rt,x,y);
        return tmp;
    }
    //前驱
    int pre(int &rt,int v){
        int x=0,y=0;
        //将v-1分离，查询前k大，即最大一个小于v
        split(rt,x,y,v-1);
        int tmp=kth(x,tr[x].siz);
        merge(rt,x,y);
        return tmp;
    }
    //后继
    int nex(int &rt,int v){
        int x=0,y=0;
        //将v分离，查询第1大，即最小一个大于v
        split(rt,x,y,v);
        int tmp=kth(y,1);
        merge(rt,x,y);
        return tmp;
    }
    int init(){
        tot=0;
        seed=233;
        return newnode(INF);
    }
}ac;
int n,o,v;
int main(){
    scanf("%d",&n);
    int rt=ac.init();
    for(int i=1;i<=n;i++){
        scanf("%d%d",&o,&v);
        if(o==1){
            ac.ins(rt,v);
        }else if(o==2){
            ac.del(rt,v);
        }else if(o==3){
            printf("%d\n",ac.rnk(rt,v));
        }else if(o==4){
            printf("%d\n",ac.kth(rt,v));
        }else if(o==5){
            printf("%d\n",ac.pre(rt,v));
        }else if(o==6){
            printf("%d\n",ac.nex(rt,v));
        }
    }
    return 0;
}
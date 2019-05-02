/*
 * 权值线段树，维护的是值域的关系，普通线段树维护的是定义域的关系，相当于一颗反的线段树
 * 一般需要离散化(ai>=1e7)，从而转化为离线数据结构
 */ 
//建树
void build(int i,int l,int r){
    le[i]=l;
    ri[i]=r;
    if(l==r){
        return;
    }
    int mid=(l+r)/2;
    build(lson,l,mid);
    build(rson,mid+1,r);
}
//插入或删除一个数
void update(int i,int p,int v){
    tr[i]+=v;
    if(le[i]==ri[i]){
        return;
    }
    int mid=(le[i]+ri[i])/2;
    if(p<=mid){
        update(lson,p,v);
    }else{
        update(rson,p,v);
    }
}
//查询一个数出现次数
int find(int i,int x){
    if(le[i]==ri[i]){
        return tr[i];
    }
    int mid=(le[i]+ri[i])/2;
    if(x<=mid){
        return find(lson,x);
    }else{
        return find(rson,x);
    }
}
//查询区间(值域区间)内数出现的次数
//比如查询[1,3]即1 2 3这三个数共出现了多少次
int ans;
void find(int i,int l,int r){
    if(l<=le[i] && r>=ri[i]){
        ans+=tr[i];
        return;
    }
    int mid=(le[i]+ri[i])/2;
    if(l<=mid){
        find(lson,l,r);
    }
    if(r>mid){
        find(rson,l,r);
    }
}
//查询全局第k大
int kth(int i,int k){
    if(le[i]==ri[i]){
        return le[i];
    }
    if(k<=tr[lson]){
        return kth(lson,k);
    }else{
        return kth(rson,k-tr[lson]);
    }
}
//查询数字x的排名
int rnk(int i,int x){
    if(le[i]==ri[i]){
        return 1;
    }
    int mid=(le[i]+ri[i])/2;
    if(x<=mid){
        return rnk(lson,x); 
    }else{
        return tr[lson]+rnk(rson,x);
    }
}
//查询x的前驱(小于x且最大的数)
int Pre(int x){
    //如果离散化了，最外再套一个原数组 b[kth(...)]
    return kth(1,rnk(1,x)-1);
}
//查询x的后继(大于x最小的数)
int Nex(int x){
    return kth(1,rnk(1,x+1));
}
//Build,PushUp,Update同单点更新，主要多了tag数组以及将标记下放的PushDown函数
void PushDown(int i){
    if(tag[i]){
        //先累加父节点标记
        tag[lson]+=tag[i];
        tag[rson]+=tag[i];
        //和的累加使用的是父节点标记，因为自身的标记有可能是之前的累加
        sum[lson]+=(ri[lson]-le[lson]+1)*tag[i];
        sum[rson]+=(ri[rson]-le[rson]+1)*tag[i];
        //父节点标记记得清空
        tag[i]=0;
    }
}
void Update(int i,int l,int r,ll v){
    if(l<=le[i] && r>=ri[i]){
        //整个区间更新，无需更新每一个叶子
        tag[i]+=v;
        sum[i]+=(ri[i]-le[i]+1)*v;
        return;
    }
    //不同于单点更新，这里需要先下放标记，更新子节点信息，再递归下去查询
    PushDown(i);
    if(le[i]==ri[i]){
        return;
    }
    int mid=(le[i]+ri[i])>>1;
    if(l<=mid){
        Update(lson,l,r,v);
    }
    if(r>mid){
        Update(rson,l,r,v);
    }
    PushUp(i);
}
//hdu4027——区间开根号更新，区间开根号没有什么更好的方法，只能暴力到叶子
//但是可以加一个优化，但叶子的值为1时，标记vis[i]=true，然后PushUp到父节点
//这样当遇到一个区间全为1时，就直接返回
void PushUp_sqrt(int i){
    tr[i].sum=tr[lson].sum+tr[rson].sum;
    //整个区间都是1
    tr[i].vis=tr[lson].vis&&tr[rson].vis;
}
void Update(int i,int l,int r){
    if(tr[i].vis){
        return;
    }
    if(tr[i].l==tr[i].r){
        //暴力到叶子
        tr[i].sum=floor(sqrt(tr[i].sum));
        if(tr[i].sum==1){
            //标记为1，无需再更新
            tr[i].vis=1;
        }
        return;
    }
    //......
}
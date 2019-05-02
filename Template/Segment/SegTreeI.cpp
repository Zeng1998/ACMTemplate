//数组记得开4倍空间 
//子节点信息更新父节点信息
void PushUp(int i){
    sum[i]=sum[lson]+sum[rson];
    Max[i]=max(Max[lson],Max[rson]);
}
//建树
void Build(int i,int l,int r){
    le[i]=l;
    ri[i]=r;
    if(l==r){
        //是a[l]不是a[i]
        sum[i]=Max[i]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    Build(lson,l,mid);
    Build(rson,mid+1,r);
    PushUp(i);
}
//单点更新(累加/覆盖)
void Update(int i,int p,int v){
    if(le[i]==ri[i]){
        sum[i]+=v;
        Max[i]+=v;
        //sum[i]=Max[i]=v;
        return;
    }
    int mid=(le[i]+ri[i])>>1;
    if(p<=mid){
        Update(lson,p,v);
    }
    if(p>mid){
        Update(rson,p,v);
    }
    PushUp(i);
}
//区间查询(和/最值)
int ans;
void Query(int i,int l,int r){
    if(l<=le[i] && ri[i]<=r){
        ans+=sum[i];
        //ans=max(ans,Max[i]);
        return;
    }
    if(le[i]==ri[i]){
        return;
    }
    int mid=(le[i]+ri[i])>>1;
    if(l<=mid){
        Query(lson,l,r);
    }
    if(r>mid){
        Query(rson,l,r);
    }
}
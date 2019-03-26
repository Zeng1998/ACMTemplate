/*
 * 基础并查集 (注意初始化p[i]=i)
 * p[i]: i的根
 */ 
int find(int x){
    //递归写法
    return x==p[x]?p[x]:p[x]==find(p[x]);
}
//=========================//
//有时候需要写成这样
int find(int x){
    if(x!=p[x]){
        int fa=p[x];
        p[x]=find(p[x]);
        //这里就可以对临时保存的fa进行操作，特别在带权并查集中
        //也可以直接p[x]=find(p[x])，然后对修改后的p[x]进行操作
        v[x]+=v[fa];       
    }
    return p[x];
}
int find(int x){
    //有时需要维护多个信息(带权并查集)，需要非递归写法
    int fa=x;
    //找到x的根
    while(fa!=p[fa]){
        fa=p[fa];
    }
    //从x重新一步一步往上，沿途更新
    while(x!=p[x]){
        x=p[x];
        p[x]=fa;
    }
    return p[x];
}
int unit(int a,int b){
    //最基础的合并
    int fa=find(a);
    int fb=find(b);
    if(fa!=fb){
        p[fa]=fb;
    }
}
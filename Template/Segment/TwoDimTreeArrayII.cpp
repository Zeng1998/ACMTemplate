/*
 * 二维树状数组(II): 区间更新，单点查询(sum(x,y))
 * 和一维的一样也是用树状数组维护一个差分数组
 */ 
void add_range(int x1,int y1,int x2,int y2,int w){
    add(x1,y1,w);
    add(x2+1,y2+1,w);
    add(x2+1,y1,-w);
    add(x1,y2+1,-w);
}
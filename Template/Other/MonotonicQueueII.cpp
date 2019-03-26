/*
 * m区间的最小值
 * 有时候要根据题目需要手写单调队列
 * 这题也可以直接用deque维护下标即可
 * 维护pair(idx,val)，val从小到大
 */ 
struct Queue{
    pair<int,int> a[N];
    int l,r;
    Queue(){
        memset(a,0,sizeof(a));
        l=0;
        r=0;
    }
    void push(int i,int x){
        if(isEmpty()){
            a[r++]=make_pair(i,x);
            return;
        }
        //维护单调递增性
        while(l<r && a[r-1].second>x){
            r--;
        }
        //去除过老的元素
        while(l<r && a[l].first+m<=i){
            l++;
        }
        a[r++]=make_pair(i,x);
    }

    //直接取出堆头(最小值)
    int getMin(){
        return a[l].second;
    }

    bool isEmpty(){
        return l==r;
    }
}q;
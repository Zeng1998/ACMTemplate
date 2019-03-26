/*
 * 一般来说单调栈就是半个单调队列
 * 子段长度小于等于m的最大和
 * pre[]: 前缀和数组
 * q: 单调队列(双端)，维护下标，对应的前缀和从小到大
 */ 
int solve(int n,int m){
    deque<int> q;
    q.push_back(1);
    int ans=0;
    int i=2;
    while(i<=n){
        //维护单调性
        while(!q.empty() && pre[q.back()]>pre[i]){
            q.pop_back();
        }
        //后来的下标总是放在队尾
        q.push_back(i);
        //把老的下标(超过i-m范围)出队
        while(!q.empty() && q.front()<i-m){
            q.pop_front();
        }
        ans=max(ans,pre[i]-pre[q.front()]);
        i++;
    }
    return ans;
}
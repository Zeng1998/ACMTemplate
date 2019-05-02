/*
 * 笛卡尔树，一种特殊的二叉树
 * key满足二叉搜索树的特性(下标小的在左边，下标大的在右边)
 * value满足堆的性质(小根堆: 父节点比子节点小，大根堆相反)
 */ 
int build(){
    for(int i=1;i<=n;i++){
        le[i]=ri[i]=fa[i]=0;
    }
    stack<int> st;
    for(int i=1;i<=n;i++){
        bool flag=false;
        int tmp;
        //维护一个递增的单调栈，构造大根堆
        while(st.size()>0 && a[st.top()]<a[i]){
            tmp=st.top();
            st.pop();
            flag=true;
        }
        //栈中还有元素，那么这个即将入栈的元素i就是右子树
        if(st.size()>0){
            ri[st.top()]=i;
            fa[i]=st.top();
        }
        //维护单调性过程中最后一个出栈的就是左子树
        if(flag){
            le[i]=tmp;
            fa[tmp]=i;
        }
        st.push(i);
    }
    for(int i=1;i<=n;i++){
        if(!fa[i]){
            return i;
        }
    }
}
/*
 * 拓扑排序(bfs)
 * to[i]: 拓扑排序第i个节点
 * flag: 是否存在环
 */
void topo(){
    queue<int> q;
    int k=0;
    for(int i=1;i<=n;i++){
        if(ind[i]==0){
            q.push(i);
            topo[k++]=u;
        }
    }
    int cnt=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cnt++;
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            ind[v]--;
            if(!ind[v]){
                q.push(v);
                topo[k++]=v;
            }
        }
    }
    if(cnt!=n){
        //有环
        flag=true;
    }
}

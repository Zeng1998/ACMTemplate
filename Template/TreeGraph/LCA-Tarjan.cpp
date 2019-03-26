/*
 * Tarjan算法+并查集求LCA(离线)
 * vis[u]:访问标记
 * p[u]:u的根/父节点
 * que[u]:跟u有联系的查询链表
 */
void LCA(int u,int f){
    vis[u]=true;
    int siz=g[u].size();
    for(int i=0;i<siz;i++){
        int v=g[u][i].v;
        if(v==f){
            continue;
        }
        LCA(v,u);
        //回溯之后更新父节点
        p[v]=u;
    }
    int qsiz=que[u].size();
    for(int i=0;i<qsiz;i++){
        // 遍历跟u有查询关系的点
        int v=que[u][i].q;
        int id=que[u][i].idx;
        if(vis[v]){
            //如果已经访问过则lca为并查集中v的根
            lca[id]=Find(v);
        }
    }
}

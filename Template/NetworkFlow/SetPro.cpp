/*
    1. 二分图一些性质
        最小点覆盖数==最大匹配数   ||  最小边覆盖数==最大独立数==顶点数-最大匹配数
        最大独立集==补图的最大团
        (最大独立集: 一个最大的点的集合，该集合内的任意两点没有边相连) 
        (最大团: 一个最大的点的集合，该集合内的任意两点都有边相连)
    2. 有向图的最小路径覆盖问题==>二分图解决
        路径覆盖: 通过几条路径(多条边)覆盖有向图所有顶点，一个点也可成为路径覆盖，长度为0
        2.1 最小不相交路径覆盖：每一条路径经过的顶点各不相同。例如1->3>4，2，5
            将有向图的每个点拆成入点和出点，对每一条有向边(u,v)，都在二分图中将u的入点连向v的出点
            结论: 最小路径覆盖数=|V(G)|-二分图最大匹配数
        2.2 打印出每条路径: 
            在dinic算法的dfs增广中，记录流向
            if(dis>0){
                ......
                to[u]=v;
                return dis;
            }
            枚举所有入点(1-n)，当to[i]不为零时，沿着i=to[i]路径输出即可
            for(int i=1;i<=n;i++){
                if(to[i]){
                    int t=i;
                    do{
                        if(t>n){
                            t-=n;
                        }
                        printf("%d ",t);
                        int x=to[t];
                        to[t]=0;
                        t=x;
                    }while(t);
                printf("\n");
            }
        2.3 最小可相交路径覆盖：每一条路径经过的顶点可以相同。例如1->3->4，2->3>5
            先用floyd求出传递闭包，然后对当前的图求最大匹配(可以直接用邻接矩阵跑匈牙利算法)
            for(int k=1;k<=n;k++){
                for(int i=1;i<=n;i++){
                    for(int j=1;j<=n;j++){
                        if(a[i][k]&&a[k][j]){
                            a[i][j]=true;
                        }
                    }
                }
            }
 */ 
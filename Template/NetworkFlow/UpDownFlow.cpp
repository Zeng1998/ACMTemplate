/*
 * 0. 假设流量上下界为[l,r]
 * 1. 无源汇可行流(循环流)  
 *     添加超级源汇ss,tt,对于每一条弧(u,v),拆成(u,v,(r-l)),(u,tt,l),(ss,v,l)
 *     跑一遍ss到tt的最大流，若附加边(u,tt),(ss,v)都满流，说明存在可行流
 * 2. 有源汇可行流
 *     建立弧(t,s,(INF)),转化为无源汇可行流,按无源汇可行流的方法建图跑一遍最大流即可,
 *     而且此时(t,s)的流量就是原图的总流量
 * 3. 有源汇最大流
 *     按照有源汇可行流的方法建图,如果存在可行流,不用清空流量,再跑一遍从s到t的最大流
 * 4. 有源汇最小流
 *     按照有源汇可行流建图,但不要建立弧(t,s),跑一遍ss到tt的最大流,再建立弧(t,s,(INF)),
 *     再跑一遍ss到tt的最大流
 * */
/*
 * 有一堆n个石子，两人轮流取，一次可以取任意多个但不能取完，也不能超过上一个人取的两倍
 * 预处理出斐波那契数列，先手必败态当且仅当n为斐波那契数
 */ 
bool solve(int n){
    bool flag=false;
    for(int i=0;i<100;i++){
        if(n==fib[i]){
            return true;
        }
    }
    return false;
}

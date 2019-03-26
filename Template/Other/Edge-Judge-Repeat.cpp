map<int,int> mp; 
bool isHash(int u,int v){
    if(mp[u*N+v] || mp[v*N+u]){
        return true;
    }
    mp[u*N+v]=mp[v*N+u]=1;
    return false;
}

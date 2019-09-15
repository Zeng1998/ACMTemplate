#include <bits/stdc++.h>
using namespace std;
const int N=2e5+50;
int ans,len;
bool yes,vis[N];
char s[40];
//编辑距离三种操作
//delete  索引+1 节点不变    (del s[idx+1])
//add     索引不变 节点nex   (add in s[idx] idx->idx+1)
//replace 索引+1 节点nex     
struct Trie{
    int cnt,tr[N][26],val[N];
    void init(){
        cnt=0;
        memset(tr,0,sizeof(tr));
        memset(val,0,sizeof(val));
    }
    void insert(char *s){
        int len=strlen(s);
        int now=0;
        for(int i=0;i<len;i++){
            int id=s[i]-'a';
            if(!tr[now][id]){
                tr[now][id]=++cnt;
            }
            now=tr[now][id];
        }
        val[now]=1;
    }
    int query(){
        len=strlen(s+1);
        ans=0;
        yes=false;
        memset(vis,false,sizeof(vis));
        dfs(0,0,0);
        if(yes){
            return -1;
        }else{
            return ans;
        }
    }
    //trie树根节点是0，所以考虑将字符串从1计数
    //字符串下标，trie数节点，是否修改(编辑距离为1)
    void dfs(int idx,int u,int f){
        if(idx==len){
            if(val[u]){
                if(f){
                    if(!vis[u]){
                        ans++;
                        vis[u]=true;
                    }
                }else{
                    yes=true;
                }
                return;
            }
        }
        if(!f){
            //delete 删除s[idx+1]
            dfs(idx+1,u,1);
            for(int i=0;i<26;i++){
                if(tr[u][i]){
                    //add 在idx前添加'a'+i
                    dfs(idx,tr[u][i],1);
                    if(i!=s[idx+1]-'a'){
                        //replace 将s[idx+1]换成'a'+i
                        dfs(idx+1,tr[u][i],1);
                    }
                }
            }
        }
        //无操作
        int id=s[idx+1]-'a';
        if(tr[u][id]){
            dfs(idx+1,tr[u][id],f);
        }
    }
}T;
int n,m;
int main(void){
    //freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    T.init();
    for(int i=0;i<n;i++){
        scanf("%s",s);
        T.insert(s);
    }
    for(int i=0;i<m;i++){
        scanf("%s",s+1);
        printf("%d\n",T.query());
    }
    return 0;
}
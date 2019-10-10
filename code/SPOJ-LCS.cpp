#include <bits/stdc++.h>
using namespace std;
const int N=1e6+50;
char s[N];
struct SAM{
    int nex[N*2][26],fa[N*2],len[N*2],num[N*2];
    int cnt,lst;
    int newnode(int l,int s){
        for(int i=0;i<26;i++){
            nex[cnt][i]=0;
        }
        num[cnt]=s;
        len[cnt]=l;
        return cnt++;
    }
    void init(){
        cnt=1;
        lst=newnode(0,0);
        fa[lst]=-1;
    }
    void add(int c){
        c-='a';
        int p=lst;
        int cur=newnode(len[p]+1,1);
        while(p!=-1 && !nex[p][c]){
            nex[p][c]=cur;
            p=fa[p];
        }
        if(p==-1){
            fa[cur]=1;
        }else{
            int q=nex[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int cl=newnode(len[p]+1,0);
                fa[cl]=fa[q];
                memcpy(nex[cl],nex[q],sizeof(nex[cl]));
                while(p!=-1 && nex[p][c]==q){
                    nex[p][c]=cl;
                    p=fa[p];
                }
                fa[q]=fa[cur]=cl;
            }
        }
        lst=cur;
    }
    int solve(char *s){
        int p=1;
        int ans=0;
        int tmp=0;
        int n=strlen(s+1);
        for(int i=1;i<=n;i++){
            int idx=s[i]-'a';
            if(nex[p][idx]){
                tmp++;
                p=nex[p][idx];
            }else{
                while(p!=-1 && !nex[p][idx]){
                    //失配，跳fa边，也就是最长后缀
                    p=fa[p];
                }
                if(p==-1){
                    p=1;
                    tmp=0;
                }else{
                    //这里存在nex[p][idx]，所以长度要+1
                    tmp=len[p]+1;
                    p=nex[p][idx];
                }
            }
            ans=max(ans,tmp);
        }
        return ans;
    }
}sam;
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%s",s+1);
    int n=strlen(s+1);
    sam.init();
    for(int i=1;i<=n;i++){
        sam.add(s[i]);
    }
    scanf("%s",s+1);
    int ans=sam.solve(s);
    printf("%d\n",ans);
    return 0;
}
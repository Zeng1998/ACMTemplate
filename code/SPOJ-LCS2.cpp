#include<bits/stdc++.h>
#define clr(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
const int maxn=100010;
char s[maxn];
int len[maxn<<1],ch[maxn<<1][27],fa[maxn<<1],tot=1,root=1,last=1,siz;
void extend(int x){
    int now=++tot,pre=last;
    last=now,len[now]=len[pre]+1;
    while( pre && !ch[pre][x]){
        ch[pre][x]=now;
        pre=fa[pre];
    }
    if(!pre)fa[now]=root;
    else{
        int q = ch[pre][x];
        if(len[q]==len[pre]+1)fa[now]=q;
        else {
            int nows=++tot;
            memcpy(ch[nows],ch[q],sizeof(ch[q]));
            len[nows]=len[pre]+1;
            fa[nows]=fa[q];
            fa[q]=fa[now]=nows;
            while(pre&&ch[pre][x]==q){
                ch[pre][x]=nows;
                pre=fa[pre];
            }
        }
    }
}
int mn[maxn<<1],mx[maxn<<1],c[maxn<<1],a[maxn<<1];
int main(){
    scanf("%s",s);
    siz=strlen(s);
    for(int i=0;i<siz;i++)
    {
        int p=s[i]-'a';
        extend(p);
    }
    for(int i=1;i<=tot;i++)c[len[i]]++;
    for(int i=1;i<=tot;i++)c[i]+=c[i-1];
    for(int i=tot;i>0;i--)a[c[len[i]]--]=i;
    for(int i=tot;i>0;i--)mn[i]=len[i];
    while(scanf("%s",s)!=EOF){
        clr(mx,0);
        int cur=1,maxx=0;
        siz=strlen(s);
        for(int i=0;i<siz;i++)
        {
            int p=s[i]-'a';
            if(ch[cur][p]){
                maxx++;
                cur=ch[cur][p];
            }else{
                while(cur&&ch[cur][p]==0)cur=fa[cur];
                if(cur){
                    maxx=len[cur]+1;
                    cur=ch[cur][p];
                }else{
                    cur=1;
                    maxx=0;
                }
            }
            mx[cur]=max(mx[cur],maxx);
        }
        for(int i=tot;i>0;i--){
            int p=a[i];
            mx[fa[p]]=max(mx[fa[p]],mx[p]);
        }
        for(int i=tot;i>0;i--)mn[i]=min(mn[i],mx[i]);
    }
    int ans=0;
    for(int i=tot;i>0;i--){
        ans=max(ans,mn[i]);
    }
    cout<<ans<<endl;
}

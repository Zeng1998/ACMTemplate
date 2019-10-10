#include <bits/stdc++.h>
using namespace std;
const int N=2e5+50;
char s[N];
int n,l,r;
//字符串每个前缀对应的sam节点
int pos[N];
//t串每个前缀对应sam节点
int p[N];
//动态开点线段树+合并
struct SegmentTree{
#define mid (l+r)/2
    int tot,rt[N],ls[N*40],rs[N*40],sum[N*40];
    void insert(int &now,int l,int r,int x){
        if(!now){
            now=++tot;
        }
        sum[now]=1;
        if(l<r){
            if(x<=mid){
                insert(ls[now],l,mid,x);
            }else{
                insert(rs[now],mid+1,r,x);
            }
        }
    }
    int merge(int a,int b){
        if(!a || !b){
            return a+b;
        }
        int now=++tot;
        sum[now]=sum[a]|sum[b];
        ls[now]=merge(ls[a],ls[b]);
        rs[now]=merge(rs[a],rs[b]);
        return now;
    }
    int query(int now,int l,int r,int ql,int qr){
        if(!now){
            return 0;
        }
        if(ql<=l && qr>=r){
            return sum[now];
        }
        if(!sum[now]){
            return 0;
        }
        if(ql<=mid){
            if(query(ls[now],l,mid,ql,qr)){
                return 1;
            }
        }
        if(qr>mid){
            if(query(rs[now],mid+1,r,ql,qr)){
                return 1;
            }
        }
        return 0;
    }
    void debug(int now,int l,int r){
        if(l==r){
            printf("%d %d\n",l,sum[now]);
            return;
        }
        debug(ls[now],l,mid);
        debug(rs[now],mid+1,r);
    }
}ac;
//后缀自动机
struct SAM{
    int nex[N*2][26],fa[N*2],len[N*2],num[N*2];
    int cnt,lst;
    int w[N*2],tp[N*2];
    int newnode(int l,int s){
        for(int i=0;i<26;i++){
            nex[cnt][i]=0;
        }
        len[cnt]=l;
        num[cnt]=s;
        return cnt++;
    }
    void init(){
        //将节点编号从1开始，避免根节点被认为空的线段树，合并出错
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
            //根节点为1
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
    void gao(int l){
        for(int i=0;i<=l;i++){
            w[i]=0;
        }
        //根节点为1，从2开始计数
        for(int i=2;i<cnt;i++){
            w[len[i]]++;
        }
        for(int i=2;i<=l;i++){
            w[i]+=w[i-1];
        }
        //根节点为1
        for(int i=cnt-1;i>=2;i--){
            tp[w[len[i]]--]=i;
        }
        //除去根节点，拓扑序从1到cnt-2
        // for(int i=1;i<cnt-1;i++){
        //     printf("%d %d\n",tp[i],fa[tp[i]]);
        // }
        //权值线段树合并维护每个sam节点的right集合
        for(int i=1;i<=l;i++){
            ac.insert(ac.rt[pos[i]],1,l,i);
        }
        for(int i=cnt-1;i>=1;i--){
            num[fa[tp[i]]]+=num[tp[i]];
            ac.rt[fa[tp[i]]]=ac.merge(ac.rt[fa[tp[i]]],ac.rt[tp[i]]);
        }
    }
}sam;
struct solver{
    void gao(int l,int r,int len,int n){
        //先找出t串(前缀)对应节点
        int now=1;
        int pre=len;
        for(int i=1;i<=len;i++){
            int idx=s[i]-'a';
            if(sam.nex[now][idx]){
                now=sam.nex[now][idx];
                p[i]=now;
            }else{
                pre=i-1;
                break;
            }
        }
        //尝试在t前缀后面加入字符，若不存在，删去一个字符再尝试
        //如果整个前缀都删完，要置为根节点1
        p[0]=1;
        for(int i=pre;i>=0;i--){
            for(int j=(i==len?0:s[i+1]-'a'+1);j<26;j++){
                if(ac.query(ac.rt[sam.nex[p[i]][j]],1,n,l+i,r)){
                    for(int k=1;k<=i;k++){
                        printf("%c",s[k]);
                    }
                    printf("%c\n",char('a'+j));
                    return;
                }
            }
        }
        printf("-1\n");
    }
}solver;
int main(){
    // freopen("in.txt","r",stdin);
    scanf("%s",s+1);
    int len=strlen(s+1);
    sam.init();
    for(int i=1;i<=len;i++){
        sam.add(s[i]);
        pos[i]=sam.lst;
    }
    sam.gao(len);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%s",&l,&r,s+1);
        int cd=strlen(s+1);
        solver.gao(l,r,cd,len);
    }
    return 0;
}

struct PT{
	//回文树中每个节点表示一个回文串，所以有偶数长度的树和奇数长度的树两棵
	//next指针 next[u][i]表示u节点左右添加字符i之后得到的回文串节点
	int next[N][26];
	//fail指针 失配后跳转到最长后缀回文串对应的节点
	int fail[N];
	//节点对应回文串在原串中出现次数，需先调用count函数
	int cnt[N];
	//num[i]表示**以节点i所表示的回文串右端点结尾**的回文串个数(包括自身)
    //即fail指针的深度
	int num[N];
	//节点对应回文串的长度
	int len[N];
	//存放添加的字符
	int S[N];
	//上一个字符所在节点
	int last;
	//节点对应的最新字符位置，反向映射last(可以改成vector<int>[])
	int id[N];
	//字符数，不等于节点数
	int n;
	//回文树总结点数，包括奇偶两个空节点，节点编号为0到p-1
	//不同回文子串个数 p-2 回文子串个数 \sum num[i]
	int p;
	//创建长度为l的新节点
	int newnode(int l){
		for(int i=0;i<26;i++){
			next[p][i]=0;
		}
		cnt[p]=0;
		num[p]=0;
		len[p]=l;
		return p++;
	}
	//初始化
	void init(){
		p=0;
		//奇偶空节点，先偶再奇
		newnode(0);
		newnode(-1);
		last=0;
		n=0;
		S[n]=-1;
		//偶根fail指向奇根
		fail[0]=1;
	}
	//找到新插入字符c的回文匹配位置
	int getFail(int x){
		//在节点x对应串的后面加上一个字符，就判断x前面字符是否相同
		//若相同直接构成新的回文串，不同就跳到fail，即最长回文后缀
		//S[n-len[x]-1]就是新加的字符(S[n])关于x串的对称字符
		while(S[n-len[x]-1]!=S[n]){
			x=fail[x];
		}
		return x;
	}
	//插入字符c
	void add(int c){
		c-='a';
		S[++n]=c;
		//找到当前回文串匹配位置，也就是当前回文串节点的父节点
		int cur=getFail(last);
		if(!next[cur][c]){
			//出现了一个新的本质不同的回文串
			int now=newnode(len[cur]+2);
			//类似于AC自动机，往上跳直到找到满足条件的串节点
			//getFail其实就是不断比较当前加入的字符和x节点对称的那个字符
			fail[now]=next[getFail(fail[cur])][c];
			//fail指针深度加1
			num[now]=num[fail[now]]+1;
			//这句要放最后，前面的指针关系处理好再连上子节点
			next[cur][c]=now;
		}
		//最新回文串节点
		last=next[cur][c];
		cnt[last]++;
		id[last]=n;
	}
	//统计每个节点回文串出现次数
	void count(){
		//从子节点逆推
		for(int i=p-1;i>=0;i--){
			//i节点出现，说明其最长回文后缀fail[i]也出现
			cnt[fail[i]]+=cnt[i];
		}
	}
}ac;
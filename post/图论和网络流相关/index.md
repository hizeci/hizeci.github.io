
<!--more-->

## 强连通分量(scc)

在有向图$G$中，若两个顶点$u,v$之间能够互相到达，则称$u,v$是强连通的。若有向图$G$的每两个顶点都强连通，则$G$就是一个强连通图。

有向图的极大强连通子图，称作强连通分量。

## 强连通缩点

将一个图中的每一个强连通分量都缩成一个点的过程，称为强连通缩点。容易发现。缩点后的图一定是个DAG。

强连通缩点可以由Kosaraju算法或者Tarjan算法（似乎还有一种）

下面稍微讲一下Kosaraju算法

### Kosaraju

![Picture1.png](https://i.loli.net/2021/04/17/k7Jidwv21g4MqyU.png)

先跑一遍，记录它的posorder，也就是它的返回顺序。

如对于上面这张图从12开始dfs，它的posorder就是$1,2,\ldots ,12$

以及在DAG中，posorder是拓扑序的反序。

在记录这个的posorder后，将这个图的边反向。

![Picture2.png](https://i.loli.net/2021/04/17/6JetWY47iaAwhkH.png)

从最后一个点开始(还是12)在反向图上跑一遍dfs，然后每一次dfs就访问一些点，可以发现这一些点就是一个强连通分量。

大概是因为posorder是DAG的拓扑序列的逆序，将原图的边反向之后，所以最终第二遍dfs的顺序其实就是缩点之后DAG的拓扑序。

![Picture3.png](https://i.loli.net/2021/04/17/bWnXtL2xo3FZAYm.png)

### 例题1

https://codeforces.ml/contest/949/problem/C

阅读理解题

题意 

$n$个点，每个点$i$有一个值$a_i$。$m$个条件，每个条件有2个点$x,y$且$a_x\neq a_y$。选择最少的$k$个点，使其值加$1$后，$m$个条件仍成立。

solution

考虑如果有一个人选了两个点$x,y$，且$(a_x+1)\bmod h=a_y$，那么就连一条从$x\to y$的有向边。表示如果选了$x$，就必须选$y$。然后将得到的图强连通缩点，容易发现一定是选最小的且出度为0的块。因为如果选了一个出度不为$0$的点，之后还要将其他出度为0的点选上，由于是DAG一定有出度为0的点

```c++
pii g[N];int tot_e;
vector<int>e[N];
int instk[N],stk[N],top,totscc;
int bel[N],dfn[N],low[N],siz[N],tim;
int n,m,h,isnlef[N];
int a[N];
void tarjan(int u)
{
	//printf("%lld\n",u);
	low[u]=dfn[u]=++tim;
	stk[++top]=u,instk[u]=1;
	for(int v:e[u]) 
	{
		if(!dfn[v]) tarjan(v),ckmin(low[u],low[v]);
		else if(instk[v]) ckmin(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++totscc;
		while(stk[top+1]!=u)
		{
			siz[totscc]++;
			bel[stk[top]]=totscc;
			instk[stk[top--]]=0;
		}
	}
}
signed main()
{
	n=read(),m=read(),h=read();
	R(i,1,n) a[i]=read();
	int u,v;
	R(i,1,m) 	
	{
		u=read(),v=read();
		if((a[u]+1)%h==a[v]) e[u].pb(v),g[++tot_e]=mkp(u,v);
		if((a[v]+1)%h==a[u]) e[v].pb(u),g[++tot_e]=mkp(v,u);
	}
	R(i,1,n) if(!dfn[i]) tarjan(i);
	//test
	R(i,1,tot_e) 
	{
		u=bel[g[i].fi],v=bel[g[i].se];
		if(u^v) isnlef[u]=1;
	}
	siz[0]=inf;
	int ans=0;
	R(i,1,totscc) if(!isnlef[i]&&siz[ans]>siz[i]) ans=i;
	writeln(siz[ans]);
	R(i,1,n) if(bel[i]==ans) writesp(i);
	return 0; 
}
```



## 2-SAT

SAT指一类对于某一组布尔表达式，求它的一组使得最终结果为1的一组解

布尔表达式都形如：一个条件$\and$一个条件$\and$一个条件，一个条件是$a\oplus b\oplus c\ldots \oplus z$之类的

如果里面的条件只有两个变量就称作2-SAT问题。

如下图就是一个2-SAT

![Picture11.png](https://i.loli.net/2021/04/18/7cIlYXFADNm2P1y.png)

考虑具体怎么求一组合法解：

我们对于每一个变量建两个点，一个表示取真，一个表示取假。

对于一个表达式，我们需要满足它的所有条件

对于如$a\or \neg b$的条件，$a$取真和$b$取假必须满足一个

如果$a$取假那么$b$也要取假

所以从$a$取假向$b$取假连一条边

由于$b$取真那么$a$也要取真，所以从$b$取真向$a$取真连一条边。



然后对于所有的表达式都进行这样建边，最终就会得到一张图

图中从$x$到$y$的一条边表示如果要取$x$这个状态，那么必须要取$y$这个状态。

(2-SAT一条边存在，那么它的逆否命题一定存在)

然后强连通缩点一下

接着对于任何一个$a$来说，若$a$取真和$a$取假在一个强连通分量中，那么是无解的。

$a$取真能推到$a$取假且$a$取假能推到$a$取真，那么这显然是错的。

否则的话这个2-SAT是一定有解的

找一个解的话就是$a$取真的强连通分量与$a$取假的强连通分量比较一下，取拓扑序较大的就行了，这样一定能得到一组合法的解。

[板子题](https://www.luogu.com.cn/problem/P4782)

```c++
void tarjan(int u)
{
	low[u]=dfn[u]=++tim;
	stk[++top]=u,instk[u]=1;
	for(int v:e[u]) 
	{
		if(!dfn[v]) tarjan(v),ckmin(low[u],low[v]);
		else if(instk[v]) ckmin(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++totscc;
		/*
		do
		{
			bel[u]=totscc;
			instk[u=stk[top--]]=0;
		}while(low[u]!=dfn[u]);
		*/
		
		while(stk[top+1]!=u)
		{
			bel[stk[top]]=totscc;
			instk[stk[top--]]=0;
		}
		
	}
}
signed main()
{
	n=read(),m=read();
	int u,v,a,b;
	R(i,1,m)
	{
		u=read(),a=read(),v=read(),b=read();
		e[u+n*(a&1)].pb(v+n*(b^1));
		e[v+n*(b&1)].pb(u+n*(a^1));
	}
	R(i,1,(n<<1)) if(!dfn[i]) tarjan(i);
	R(i,1,n) if(bel[i]==bel[i+n]) return puts("IMPOSSIBLE")&0;
	puts("POSSIBLE");
	R(i,1,n) printf("%d ",bel[i]<bel[i+n]); 
} 
```

### 例题2

https://loj.ac/p/3101

题意：

给定$n$个人和$m$组限制。限制分为两种：

1. 如果$x$在$t$时间已经死了，则$y$在$t+1$时间前死了。
2. 如果$x$在$t$时间还活着，则$y$在$t$时间前死了。

请你对每一个人计算出在$T+1$时间时可能与其同时存活的人数。如果这个人在$T+1$时刻必然死则答案为0。

$T\leq 10^6,n\leq 5\times 10^4,m\leq 10^5$



sol：

对于每一个人在每一个时间点建两个点，一个点代表他在这个时间点还活着，另一个点代表已经死了。然后直接跑2-SAT。

具体建图是对于每一个表示活着的点$(x,t)$，如果这个人在第$t$时间还活着，那么他在第$t-1$时间一定也活着，所以$(x,t)\to(x,t-1)$

同理，对于每一个表示死了的点$(x,t)$，如果这个人在第$t$时间已经死了，那么他在第$t+1$时间一定已经死了，所以$(x,t)\to (x,t+1)$

然后再按照两个特殊限制相应连边

1. 从$(x,t)$的死亡点，连向$(y,t+1)$的死亡点
2. 从$(x,t)$的生存点，连向$(y,t)$的生存点

然后可以发现因为$T\times N\leq 5\times 10^{10}$

考虑优化

容易发现对于每一个人来说只有最后的时刻和特殊限制对应的时刻是有用的。于是点数最多只有$2\cdot (n+m)$个。

然后考虑因为最后全部都死肯定是一组合法解，所有$live(x,y)=1$当且仅当满足以下三个条件：

1. $x$取真不能推出$x$取假。
2. $y$取真不能推出$y$取假。
3. $x$取真不能推出$y$取假。

对于前两个条件考虑直接若某个点出现这个情况就直接把这个点忽略掉就行了。

接下来就是对于每一个没有被忽略的点$x$，统计有多少个$y$满足$x$取真不能推出$y$取假。

考虑建出的图一定是一个DAG。

因为对于生存状态，因为只有连上死亡状态的边

对于死亡状态来说，对于$t$来说，只有$t$小的向$t$大的连边，所以整个图一定是一个DAG。

直接用bitset维护即可。

（本题中关键点指T+1时刻一定死的点）

具体对于一个DAG，上面的图有一些是关键点，有一些是不关键的点。

对于图上一个点，求它能到达多少个关键点。

令$dp_{i,j}$表示第$i$开始能否到达$j$

转移就是枚举出边，然后从出边或过来

第二维可以压成一个bitset

时间复杂度大概为点数除以一个$\omega$。

至于空间问题，每次分10000个关键点做，对于所有点，考虑在10000个中的贡献。

空间复杂度大概就是10000乘点数除以一个$\omega$

```c++
const int B=10000;
int T,n,m;
int l[555555],d[555555];
map<int,int>live[555555],dead[555555];
int cnt;
int in[555555];

inline int insL(int x,int t) 
{
	if(!live[x].count(t)) live[x][t]=++cnt;
	return live[x][t];
}
inline int insD(int x,int t) 
{
	if(!dead[x].count(t)) dead[x][t]=++cnt;
	return dead[x][t];
}
int qua[5555555],tim;
int can[555555],ans[555555];
vector<int>e[1155555];
inline void add_edge(int u,int v) {e[u].pb(v);in[v]++;}
void toposort() 
{
	deque<int>q;
	int u;
	R(i,1,cnt) if(!in[i]) q.pb(i);
	while((int)q.size()>0)
	{
		u=q.front();q.pop_front();
		//printf("u:%d\n",u);
		qua[++tim]=u;
		for(int v:e[u])
		{
			//printf("v:%d\n",v);
			if(!(--in[v])) q.pb(v);
		}
	}
}
bitset<10010>dp[555555],tmp;
void solve(int L,int R) 
{
	int u,v;
	R(i,L,R) dp[d[i]].set(i-L);
	L(i,1,tim) 
	{
		u=qua[i];
		for(int v:e[u]) 
			dp[u]|=dp[v];
	}
	tmp.reset();
	R(i,L,R)
	{
		if(dp[l[i]][i-L]) can[i]=0,tmp[i-L]=1;
		else can[i]=1;
	}
	R(i,1,n) ans[i]+=(R-L+1-(dp[l[i]]|tmp).count());
	R(i,1,cnt) dp[i].reset();
}
signed main()
{
	T=read(),n=read(),m=read();
	R(i,1,n) l[i]=insL(i,T+1),d[i]=insD(i,T+1)/*,printf("%d %d\n",l[i],d[i])*/;
	int opt,t,x,y;
	R(i,1,m)
	{
		opt=read(),t=read(),x=read(),y=read();
		if(!opt) 
		{
			add_edge(insD(x,t),insD(y,t+1));
			add_edge(insL(y,t+1),insL(x,t));
		}
		else
		{
			add_edge(insL(x,t),insD(y,t));
			add_edge(insL(y,t),insD(x,t));
		}
	}
	int nt;
	R(i,1,n) 
	{
		nt=-1;
		for(map<int,int>::iterator it=live[i].begin();it!=live[i].end();it++)
		{
			//printf("l:%d %d\n",it->se,nt);
			if(~nt) add_edge(it->se,nt);
			nt=it->se;
		}
		nt=-1;
		for(map<int,int>::iterator it=dead[i].begin();it!=dead[i].end();it++)
		{
			//printf("d:%d %d\n",nt,it->se);
			if(~nt) add_edge(nt,it->se);
			nt=it->se;
		}
	}
	toposort();
	for(int L=1,R=min(n,B);L<=n;L=R+1,R=min(n,L+B-1)) solve(L,R);
	R(i,1,n) printf("%d ",!can[i]?0:ans[i]-1);puts("");
}
```



## 欧拉回路

首先就是判定一个图中是否有欧拉回路

如果一个图是无向图，它有欧拉回路当且仅当每一个点的度数都为偶数

如果是有向图有欧拉回路，当且仅当所有顶点属于一个强连通分量且每个点出度等于入度。

（前提是整个图是联通的）

如何找欧拉回路呢

### 圈套圈算法

还是考虑每次随便找一条边出去，然后如果当前无路可走了就把这条边退回来，然后再维护一个栈，表示答案，将这条边加入到栈中，然后不断退，并将边加入到栈中直到又有路可以走了。然后继续走。

具体就是每一次如果当前的点还有边可以走的话就走，如果没有边可以走了就压入一个栈中然后回来，最后栈从顶往底就是一个欧拉回路。

链式前向星213ms

```c++
int opt,nok;
int n,m,s;
int vis[400040];
int head[100010],cnt_e;
int stk[200040],top;
struct edge {int nxt,to,id;}e[400040];
inline void add_edge(int u,int v,int d){e[++cnt_e]=(edge){head[u],v,d};head[u]=cnt_e;};
namespace sub1//无向图
{
	int deg[100010];
	void dfs(int u) 
	{
		for(int i=head[u];i;i=head[u]) 
		{
			while(i&&vis[i]) i=e[i].nxt;
			head[u]=i;
			if(i) vis[i]=vis[i^1]=1,dfs(e[i].to),stk[++top]=e[i].id;
		}
	}
	void mian()
	{
		cnt_e=1;
		n=read(),m=read();
		int u,v;
		R(i,1,m) 
		{
			u=read(),v=read();
			add_edge(u,v,i),add_edge(v,u,-i);
			deg[u]++,deg[v]++;s=u;
		} 
		R(i,1,n) if(deg[i]&1){nok=1;break;}
		if(nok) {puts("NO");return;}
		dfs(s);
		if(top^m) puts("NO");
		else 
		{
			puts("YES");
			L(i,1,top) writesp(stk[i]);puts("");
		}
	}
}
namespace sub2
{
	int in[100010],out[100010];
	void dfs(int u) 
	{
		for(int i=head[u];i;i=head[u]) 
		{
			while(i&&vis[i]) i=e[i].nxt;
			head[u]=i;
			if(i) vis[i]=1,dfs(e[i].to),stk[++top]=e[i].id;
		}
	}
	void mian()
	{
		n=read(),m=read();
		int u,v;
		R(i,1,m) 
		{
			u=read(),v=read();
			add_edge(u,v,i);
			in[u]++,out[v]++;s=u;
		}
		R(i,1,n) if(in[u]^out[u]) {nok=1;break;}
		if(nok) {puts("NO");return;}
		dfs(s);
		if(top^m) {puts("NO");}
		else 
		{
			puts("YES");
			L(i,1,top) writesp(stk[i]);puts("");
		}
	}
}
signed main()
{
	opt=read();
	if(opt==1) sub1::mian();
	else sub2::mian(); 
}
```

vector322ms

```c++
vector<pii>e[200010];
int opt,s;
int n,m;
int vis[200010];
int stk[200020],top;
namespace sub1
{
	void dfs(int u)
	{
		int v,id;
		while((int)e[u].size()>0)
		{
			v=e[u].back().fi,id=e[u].back().se;
			e[u].pop_back();
			if(!vis[abs(id)]) 
			{
				vis[abs(id)]=1;
				dfs(v);
				stk[++top]=id;
			}
		}
	}
	void mian()
	{
		n=read(),m=read();
		int u,v;
		R(i,1,m) 
		{
			u=read(),v=read();
			e[u].pb(mkp(v,i)),e[v].pb(mkp(u,-i));s=u;
		}
		R(i,1,n) if(e[i].size()&1){puts("NO");return;}
		dfs(s);
		if(top^m) puts("NO");
		else
		{
			puts("YES");
			L(i,1,top) writesp(stk[i]);puts("");
		}
	}
}
namespace sub2
{
	int in[100010];
	void dfs(int u) 
	{
		int v,id;
		while((int)e[u].size()>0)
		{
			v=e[u].back().fi,id=e[u].back().se;
			e[u].pop_back();
			dfs(v);
			stk[++top]=id;
		}
	}
	void mian()
	{
		n=read(),m=read();
		int u,v;
		R(i,1,m) 
		{
			u=read(),v=read();
			e[u].pb(mkp(v,i));
			s=u;
			in[v]++;
		}
		R(i,1,n) if(e[i].size()^in[i]) {puts("NO");return;}
		dfs(s);
		if(top^m) puts("NO");
		else 
		{
			puts("YES");
			L(i,1,top) writesp(stk[i]);puts("");
		}
	}
}
signed main() 
{
	opt=read();
	if(opt==1) sub1::mian();
	else sub2::mian();
}
```

### 例题3

https://codeforces.com/contest/1361/problem/C

sol：

考虑如何判断答案是否 >=k，将 % 2^k 相同的珍珠分成一组，对于每一组建立一个点。将两个珍珠所在的组连一条边，即需要得到的图中有没有欧拉回路即可。

```c++
const int M=(1<<20);
int n,s,nok;
pii a[N];
int stk[N],top;
int cnt_e,head[N];
struct edge {int nxt,to,id;}e[N];
int deg[N],vis[N];
inline void add_edge(int u,int v,int d){e[++cnt_e]=(edge){head[u],v,d};head[u]=cnt_e;}

void dfs(int u) 
{
	for(int i=head[u];i;i=head[u]) 
	{
		while(i&&vis[i]) i=e[i].nxt;
		head[u]=i;
		if(i) vis[i]=vis[i^1]=1,dfs(e[i].to),stk[++top]=e[i].id; 
	}
} 
signed main()
{
	n=read(),cnt_e=1;	
	int A,B;R(i,1,n)A=read(),B=read(),a[i]=mkp(A,B);
	L(j,0,20) 
	{
		R(i,0,M-1) vis[i]=head[i]=deg[i]=0;
		cnt_e=1;nok=0;
		int mdu=(1<<j)-1;
		R(i,1,n) 
		{
			A=a[i].fi&mdu,B=a[i].se&mdu;s=A;
			add_edge(A,B,i),add_edge(B,A,-i);\
			deg[A]++,deg[B]++;
		}
		R(i,1,mdu) if(deg[i]&1) {nok=1;break;}
		if(nok) continue;		
		top=0;
		dfs(s);
		if(top^n) continue;	
		writeln(j);
		L(i,1,top) 
		{
			if(stk[i]>0) writesp(2*abs(stk[i])-1),writesp(2*abs(stk[i]));
			else writesp(2*abs(stk[i])),writesp(2*abs(stk[i])-1);
		}
		return 0;
	}
}
```

## 割顶和桥

对于无向图G，如果删除某个节点u之后，连通分量数目增加，则称u为图的割顶

如果删除某条边后，连通分量数目增加，则称该边为图的桥。

所有割顶和桥都可以使用tarjan算法求出

### tarjan算法

对图进行dfs并找出一棵dfs树。

维护两个数组$dfn$和$low$，$dfn$表示$dfs$序，$low$表示它自身以及它的子树的返祖边的$dfn$的最小值。

关于找出所有桥

如果一条树边$u\to v$满足$low[v]>dfn[u]$那么$u\to v$一定是桥

而非树边一定不是桥，所以就找出了所有的桥

关于找割顶

对于非根节点$u$，如果$u$有一个儿子$v$满足$low[v]\ge dfn[u]$，那么$u$一定是一个割顶。

但是对于根节点不满足这种情况，所以要特判掉。

### 双连通图

双连通图分为点双连通图和边双连通图。

点双连通图的定义为在图中对于任意两个点$x,y$都存在两条**点不相交**的路径从$x$到$y$（路径不包含$x$和$y$）即不存在割顶。边双连通图的定义为在图中对于任意两个点$x,y$都存在两条**边不相交**的路径从$x$到$y$，即不存在桥。

无向图的极大点/边双连通子图，称作该图的点/边双连通分量。（就类似强连通分量）

### 如何求点双连通分量

由于点双连通分量一定是由割顶组成的，所以说每找到一个割顶就相当于找到一个点双连通分量。考虑当前走到了$u\to v$且$low[v]\ge dfn[u]$，那么$v$下面包含$u$的某一块就一定是一个点双连通分量。

具体是用在访问到$v$之前，用一个栈把访问到的边都记录下来包括$u\to v$，然后从$v$访问回来后，肯定还会留下一些边，所以就不断弹栈直到当前的边是$u\to v$为止。然后弹出来的那些边都是点双连通分量的一个点集。不断做就找出了所有点双连通分量。

就是说我们在从$u$转移到$v$之前，把$u\to v$这条边加入某一个栈中，然后考虑这个$v$下去又搜了一些又弹了一些最后又剩下一些边，把这些边弹出来，然后考虑这些边的点集就是点双连通分量的点集。
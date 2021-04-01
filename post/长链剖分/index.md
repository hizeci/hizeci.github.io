
<!--more-->

[fjzzq2002](https://www.cnblogs.com/zzqsblog/p/6700133.html)

[租酥雨](https://www.cnblogs.com/zhoushuyu/p/9468669.html)

[oi-wiki](https://oi-wiki.org/graph/hld/#_14)



长链剖分是和重链剖分，dsu on tree一类的trick，不过它的适用范围与dsu on tree不同，它适用与涉及到深度的查询。

先来定义一下长链剖分是什么。它与重链剖分十分类似，但是原来的重儿子是子树大小最大的儿子，现在的"重"儿子(因为不是重儿子了，大概是preffered child)是往下延伸到叶子节点那条链最长的儿子。

整个长链剖分的过程与轻重链剖分的过程类似，只要一遍dfs即可。

具体实现方式&复杂度证明：

对每个点寻找深度最大的儿子作为重儿子，其余作为轻儿子。由此得到了若干条互不相交的长链。
在维护信息的过程中，先$O(1)$继承重儿子的信息，再暴力合并其余轻儿子的信息。
因为每个点仅属于一条长链，且一条长链只会在链顶位置作为轻儿子暴力合并一次，所以时间复杂度线性。
在$O(1)$继承重儿子信息这点上有不同的实现方式，一个巧妙的方法是利用指针实现，具体可以参见代码。

#### 长链剖分优化 DP

一般情况下可以使用长链剖分来优化的 DP 会有一维状态为深度维。

我们可以考虑使用长链剖分优化树上 DP。

具体的，我们每个节点的状态直接继承其重儿子的节点状态，同时将轻儿子的 DP 状态暴力合并。

例题：[codeforces1009F](http://codeforces.com/problemset/problem/1009/F) 这好像也是一道dsu on tree板子题（

题意：给定一棵以1为根，$n$个节点的树。设$d(u,x)$为$u$子树中到$u$距离为$x$的节点数。

对于每个点，求一个最小的$k$，使得$d(u,k)$最大。



设$f_{i,k}$表示在子树$i$内，和$i$距离$j$的点数。

暴力转移时间复杂度为$O(n^2)$

我们考虑每次转移我们直接继承重儿子的DP数组和答案，并且考虑在此基础上进行更新。

首先我们需要将重儿子的DP数组前面插入一个元素1，这代表着当前节点。

然后我们将所有亲儿子的DP数组暴力和当前节点的DP数组合并。

注意到因为轻儿子的DP数组长度为轻儿子所在重链长度，而所有重链长度和为$n$。

也就是说，我们直接暴力合并轻儿子的总时间复杂是$O(n)$。



注意，一般情况下DP数组的内存分配为一条重链整体分配内存，链上不同的节点有不同的首位置指针。

DP数组的长度我们可以根据子树最深节点算出。

代码：

```c++
const int N=2111111;
vector<int>e[N];
int n,fa[N];
int d[N],pson[N];
int dfn[N],tim;
int *f[N],g[N];
int ans[N];
void dfs1(int u)
{	
	d[u]=1;
	for(int v:e[u]) if(v^fa[u])
	{
		fa[v]=u;
		dfs1(v);
		ckmax(d[u],d[v]+1);
		pson[u]=(d[v]>d[pson[u]])?v:pson[u];
	}
}
void dfs2(int u)
{
	dfn[u]=++tim;
	f[u]=g+dfn[u];
	if(pson[u]) dfs2(pson[u]);
	for(int v:e[u]) if(v^fa[u]&&v^pson[u]) dfs2(v);
}
void dfs3(int u)
{
	if(pson[u])
	{
		dfs3(pson[u]);
		ans[u]=ans[pson[u]]+1;
	}
	f[u][0]=1;
	if(f[u][ans[u]]<=1) ans[u]=0;
	for(int v:e[u]) if(v^fa[u]&&v^pson[u])
	{
		dfs3(v);
		R(j,0,d[v]-1) 
		{
			f[u][j+1]+=f[v][j];
			if(f[u][j+1]>f[u][ans[u]]) ans[u]=j+1;
			if(f[u][j+1]==f[u][ans[u]]&&j+1<ans[u]) ans[u]=j+1;
		}
	} 
}
signed main()
{
	n=read();
	int u,v;R(i,2,n)u=read(),v=read(),e[u].pb(v),e[v].pb(u);
	dfs1(1);dfs2(1);dfs3(1);
	R(i,1,n) writeln(ans[i]);
}
```



例题:[lgP5904[POI2014]Hot-Hotels](https://www.luogu.com.cn/problem/P5904)

题意：给你一棵树，从中选3个点，两两距离相等，求方案数。

考虑暴力dp。令$f_{i,j}$表示$i$**子树**内与$i$距离为$j$的点的个数。但是这样直接对每个节点深度进行统计会重复。所以再令$g_{i,j}$表示$i$的子树内，有多少二元组$(a,b)$满足满足$\text{dis(LCA(a,b),a)=dis(LCA(a,b),b)=dis(LCA(a,b),i)+j}$。

可以推出节点$u$对答案的贡献为
$$
g_{u,0}+\sum_j \sum_{x,y\in	son(u)} f_{x,j-1}\times g_{y,j+1}
$$
考虑$f$的转移为
$$
f_{u,j}=\sum_{x\in son(u)} f_{u,j-1}
$$
接下来考虑$g$的转移，$g$可以有两种从儿子转移的方式：

![img](https://lcuter.gitee.io/picture/Picture/clpf3.png)

对于第一种情况，就是$j$少了一个。对于第二种情况，发现$\text{LCA(a,b)=u}$,那么$\text{dis(LCA(a,b),a)=dis(LCA(a,b),b)=j}$，又因为$u$到自身距离为0，于是有：
$$
g_{u_j}=\sum _{x,y\in son(u),x\ne y} f_{x,j-1}\times f_{y,j-1}+\sum_{x\in son(u) g_{x,j+1}}
$$
然后可以长剖将时间复杂度优化为$O(n)$

简易版：

设$f_{i,j}$表示$i$子树内与$i$距离为$j$的点的个数，$g_{i,j}$表示$i$子树内，满足第三个点和$i$距离为$j$的点对数目。

这样每次可以拿$f_{u,j}\times g_{v,j+1}$和$g_{u,j+1}\times f_{v,j}$更新答案，拿$f_{u,j}\times f_{v,j-1}$更新$g_{u,j}$，$f_{v,j}$更新$f_{u,j+1}$，$g_{v,j}$更新$g_{u,j-1}$。

```c++
const int N=444444;
vector<int>e[N];
int d[N],pson[N];
int n;
int fa[N];
int dfn[N],tim;
int tmp[N],*id=tmp;
int *f[N],*g[N],q[N];
int ans;
void dfs1(int u)
{
	for(int v:e[u]) if(v^fa[u])
	{
		fa[v]=u;
		dfs1(v);
		pson[u]=(d[v]>d[pson[u]])?v:pson[u];
	}
	d[u]=d[pson[u]]+1;
}

void dfs3(int u)
{
	if(pson[u]) f[pson[u]]=f[u]+1,g[pson[u]]=g[u]-1,dfs3(pson[u]);
	f[u][0]=1;ans+=g[u][0];
	for(int v:e[u]) if(v^fa[u]&&v^pson[u])
	{
		f[v]=id;id+=(d[v]<<1);g[v]=id;id+=(d[v]<<1);
		dfs3(v);
		R(j,0,d[v]-1)
		{
			if(j) ans+=f[u][j-1]*g[v][j];
			ans+=g[u][j+1]*f[v][j];
		}
		R(j,0,d[v]-1)
		{
			g[u][j+1]+=f[u][j+1]*f[v][j];
			if(j) g[u][j-1]+=g[v][j];
			f[u][j+1]+=f[v][j];
		}
	}
}
signed main()
{
	n=read();
	int u,v;R(i,2,n) u=read(),v=read(),e[u].pb(v),e[v].pb(u);
	dfs1(1);
	f[1]=id;id+=(d[1]<<1);g[1]=id;id+=(d[1]<<1);
	dfs3(1);
	writeln(ans);
}
```



例题：k-th ancestor query

https://zhuanlan.zhihu.com/p/25984772

性质：任意一个点的k级祖先所在链的链长一定$\ge k$。这个证明十分简单，因为它到祖先长度就为k了，如果它到祖先不是重链，链长肯定不会更短。

求出长链剖分之后我们对于每条重链的链头，设这条重链长度为len，记录一下这条重链每个深度的点，然后记录链头往上len个点是哪些（显然不会影响复杂度，顶多*2）。

我们同样预处理倍增跳的数组，但是我们还要记录一下1~n每个数的high-bit（最高位的1在哪）。

我们现在考虑向上跳k，那么我们先跳k的最高位r，然后还要跳k-r这么高。考虑这个点往上r的祖先，那么它所在重链链长>=r，注意到k-r<r，那么我们只要在链头向上向下跳就可以了。



<!--more-->

这是一种既需要离线跑得还非常慢的树状数组做法。



令$dp_i$表示一些`2-path`从$i$号点开始又以$i$号点结束的最大收益。

令$f_i$表示只能从$i$的子树走的最大收益。

$f_i$的转移相对好想，即枚举它的所有儿子，然后选或不选即可。
$$
f_u=a_u+\sum_{v\in son(u)} \max(0,f_v-2\cdot w(u,v))
$$
然后考虑计算$dp_i$，与$f$的转移不同的是它不仅可以从它的儿子转移过来，它还可以从它的父亲转移过来
$$
dp_u=a_u+\sum_{v\in Neighbour(u)} \max(0,f_v-2\cdot w(u,v))
$$
但是显然这样直接转移一条边的贡献会算多次，所以要剔除原先自己的贡献，每次往儿子方向转移时记录所有的$\max(0,f_v-2\cdot w(u,v))$丢到$dv(u,v)$中，并更新$f_u=dp_u-\max(0,f_v-2\cdot w(u,v))$。

然后考虑处理所有的询问

为了取得最大收益，一条路径$(u,v)$一定是在两点的简单路径基础上走一些其他并不是简单路径上的边然后返回取得的。

由于已经预处理出了$dp$和$dv$，假设要求出$(u,u)$的`2-path`并且不能走$(u,v_1),(u,v_2)$的最大收益，显然为$dp_u-dv(u,v_1)-dv(u,v_2)$。

所以对于每个询问$(qu,qv)$，令$l=\operatorname{lca}(qu,qv)$，可以将询问拆成$(qu,l),(qv,l)$。

考虑将所有询问离线下来，然后进行一次dfs，并且维护一个支持单点修改的数据结构（如树状数组）。

当到达点$u$时，在$dep(u)$处增加$dp_u-dv(v,fa_v)$，并且在回溯时注意删除。

而对于每一个询问$(u,l)$，显然最大利益为$[dep_l,dep_u]$的和（注意这里还要处理好$l$处的值）

当从$u$转移到$v$时，需要删除在$dep_u$处删除$dv(u,v)$的值（这里可以直接减去$w(u,v)$）

具体实现可以见代码

时间复杂度$O((n+m)\log n)$

```c++
const int N=4e5+10;
int n,m;
int a[N];
vector<pii>e[N],qs[N];
int dep[N];
ll f[N],dp[N];
int st[22][1111111],fa[N],tim,bg[N];
ll ans[N];
int Lg[1111111];
vector<ll>dv[N];
void dfs1(int u)
{
	bg[u]=++tim;
	st[0][tim]=u;
	f[u]+=a[u];
	int v;
	for(auto qwq:e[u])
	{
		v=qwq.fi;
		if(v==fa[u]) continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		dfs1(v);
		f[u]+=max(0ll,f[v]-2ll*qwq.se);
		st[0][++tim]=u;
	}
}
void dfs2(int u)
{
	dp[u]=a[u];
	int v;
	ll cur;
	for(auto qwq:e[u]) 
	{
		v=qwq.fi;
		cur=max(0ll,f[v]-2ll*qwq.se);
		dp[u]+=cur;
		dv[u].pb(cur);
	}
	cur=f[u];
	for(int i=0;i<(int)e[u].size();i++)
	{
		v=e[u][i].fi;
		if(fa[u]==v) continue;
		f[u]=dp[u]-dv[u][i];
		dfs2(v);
	}
	f[u]=cur;
}
inline int get_lp(int x,int y) {return dep[x]<dep[y]?x:y;}
inline void init_ST()
{
	R(i,2,tim+5) Lg[i]=Lg[i>>1]+1;
	for(int i=1;(1<<i)<=tim;i++) 
	{
		int w=(1<<i);
		R(j,1,tim-w+1) st[i][j]=get_lp(st[i-1][j],st[i-1][j+(w>>1)]);
	}
}
inline int get_LCA(int x,int y)
{
	x=bg[x],y=bg[y];
	if(x>y) Swap(x,y);
	int i=Lg[y-x+1],w=(1<<i);
	return get_lp(st[i][x],st[i][y-w+1]);
}
inline ll get_dv(int u) 
{
	int f=fa[u];
	int pos=(lower_bound(e[u].begin(),e[u].end(),pii(f,-1))-e[u].begin());
	if(pos>=(int)e[u].size()||e[u][pos].fi!=f) return 0;
	return dv[u][pos];
}
ll BIT[N];
inline int lowbit(int x) {return x&(-x);}
inline void modify(int pos,ll val) 
{
	for(int i=pos;i<N;i+=lowbit(i)) BIT[i]+=val;
}

inline ll query(int pos) 
{
	ll ret=0;
	for(int i=pos;i;i-=lowbit(i)) ret+=BIT[i];return ret;
}
inline ll query_SUM(int l,int r) {return query(r)-query(l-1);}
void dfs3(int u)
{
	ll vadd=dp[u]-get_dv(u);
	modify(dep[u],vadd);
	int v;
	ll cur;
	for(auto qwq:qs[u])
	{
		v=qwq.fi;
		ans[qwq.se]+=query_SUM(dep[v],dep[u])+get_dv(v);
	}
	for(int i=0;i<(int)e[u].size();i++) 
	{
		v=e[u][i].fi;
		if(fa[u]==v) continue;
		cur=dv[u][i]+e[u][i].se;
		modify(dep[u],-cur);
		dfs3(v);
		modify(dep[u],cur);
	}
	modify(dep[u],-vadd);
}
signed main()
{	
	n=read(),m=read();
	R(i,1,n) a[i]=read();
	int u,v;
	ll d;
	R(i,2,n)
	{
		u=read(),v=read(),d=read();
		e[u].pb(mkp(v,d));
		e[v].pb(mkp(u,d));
	}
	R(i,1,n) sort(e[i].begin(),e[i].end());
 	dfs1(1);
 	R(i,1,n) dep[i]++;
 	init_ST();
 	dfs2(1);
 	R(i,1,m) 
 	{
 		u=read(),v=read();
 		int L_A=get_LCA(u,v);
 		ans[i]=-dp[L_A];
 		qs[u].pb(mkp(L_A,i));
 		qs[v].pb(mkp(L_A,i));
 	}
 	dfs3(1);
 	R(i,1,m) writeln(ans[i]);

}
```


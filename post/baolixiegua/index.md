
nothing

<!--more-->

考虑枚举$T'$中两点的$lca$,之后要做的为最大化$dep_x+dep_y-dep_{lca(x,y)}$,转化一下式子就是$\frac {dep_x+dep_y+dist_{x,y} }{2}$.
那么我们考虑在边分树的每一个节点维护往左最大的$dep_x+dist_{a,x}$和往右最大的$dep_y+dist_{b,y}$.

考虑因为边分树的树高是$\log n$的，每次加入一个节点可以暴力更新他的所有祖先。

最后是合并，由于边分树是一棵二叉树，与线段树的结构相似，所以可是使用类似线段树合并的方式合并边分树。

时间复杂度为边分树合并均摊$O(n \log n )$和边分治本身复杂度$O(n\log n)$

```cpp
int n,ans=-inf;
int Rt[444444];
namespace T1r1e1e
{
	int m,rt,egn,Mn_r,tot;
	int siz[888888],vis[888888];
	int val[444444],now[444444];
	int Mx_a[10000010],dis[10000010],son[10000010][2];
	vector<pii>e[444444];
	int cnt_e=1,head[888888];
	struct edge{int nxt,to,val;}g[1688888];
	inline void add_edge1(int u,int v,int d){e[u].pb(mkp(v,d));}
	inline void add_edge2(int u,int v,int d){g[++cnt_e]=(edge){head[u],v,d};head[u]=cnt_e;}
	void build_tr(int u,int f)
	{
		int lst=0;
		for(auto qwq:e[u])
		{
			int v=qwq.fi,d=qwq.se;
			if(v==f) continue;
			//printf("u:%lld f:%lld lst:%lld m:%lld\n",u,f,lst,m);
			if(!lst) {add_edge2(u,v,d),add_edge2(v,u,d),lst=u;}
			else {m++;add_edge2(lst,m,0),add_edge2(m,lst,0);add_edge2(m,v,d),add_edge2(v,m,d);lst=m;}
			val[v]=val[u]+d;
			build_tr(v,u);
		}
	}
	void dfs1(int u,int f,int siz_tr)
	{
		siz[u]=1;
		for(int i=head[u];i;i=g[i].nxt)
		{
			int v=g[i].to;
			if(v==f||vis[i>>1]) continue;
			dfs1(v,u,siz_tr);
			siz[u]+=siz[v];
			//printf("%lld %lld %lld %lld %lld\n",u,v,Mn_r,siz_tr,siz[v]);
			if(ckmin(Mn_r,max(siz_tr-siz[v],siz[v]))) rt=v,egn=i;
		}
	}
	void dfs2(int u,int f,int dp,int wh,int dist)
	{
		if(u<=n) 
		{
			dis[now[u]]=dist;
			son[now[u]][wh]=++tot;
			now[u]=tot;
			Mx_a[tot]=val[u]+dp;
		}
		for(int i=head[u];i;i=g[i].nxt)
		{
			int v=g[i].to;
			if(v==f||vis[i>>1]) continue;
			dfs2(v,u,dp+g[i].val,wh,dist);
		}
	}
	int mer_ge(int x,int y,int tt)
	{
		if(!x||!y) return x^y;
		ckmax(ans,max(Mx_a[son[x][0]]+Mx_a[son[y][1]],Mx_a[son[x][1]]+Mx_a[son[y][0]])+dis[x]-tt);
		ckmax(Mx_a[x],Mx_a[y]);
		son[x][0]=mer_ge(son[x][0],son[y][0],tt);
		son[x][1]=mer_ge(son[x][1],son[y][1],tt);
		return x;
	}
	void solve(int u,int siz_tr)
	{
		//printf("rt:%lld siz:%lld\n",u,siz_tr);
		if(siz_tr==1) return;
		Mn_r=inf,rt=0,egn=0;
		dfs1(u,-1,siz_tr);
		assert(u>0);
		assert(siz_tr>1);
		assert(siz[u]==siz_tr);
		assert((egn&1)==0);
		int cur=egn;
		int siz_str=siz[g[egn].to];
		vis[cur>>1]=1;
		dfs2(g[cur].to,-1,0,0,g[cur].val);
		dfs2(g[cur^1].to,-1,0,1,g[cur].val);
		solve(g[cur].to,siz_str);
		solve(u,siz_tr-siz_str);
	}
	void mian()
	{
		tot=m=n;
		build_tr(1,-1);
		R(i,1,n) Rt[i]=now[i]=i;
		Mx_a[0]=-inf;
		solve(1,m);
	}
}
namespace T2r2e2e
{
	int dis[444444];
	vector<pii>e[444444];
	inline void add_edge(int u,int v,int d){e[u].pb(mkp(v,d));}
	void dfs(int u,int f)
	{
		ckmax(ans,2*(T1r1e1e::val[u]-dis[u]));
		for(auto qwq:e[u])
		{
			int v=qwq.fi;
			if(v==f) continue;
			dis[v]=dis[u]+qwq.se;
			dfs(v,u);
			Rt[u]=T1r1e1e::mer_ge(Rt[u],Rt[v],2*dis[u]);
		}
	}
}
signed main()
{
	n=read();int u,v,d;
	R(i,1,n-1) u=read(),v=read(),d=read(),T1r1e1e::add_edge1(u,v,d),T1r1e1e::add_edge1(v,u,d);
	R(i,1,n-1) u=read(),v=read(),d=read(),T2r2e2e::add_edge(u,v,d),T2r2e2e::add_edge(v,u,d);
	T1r1e1e::mian();
	T2r2e2e::dfs(1,-1);
	printf("%lld\n",ans>>1);
}
```
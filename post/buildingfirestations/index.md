
<!--more-->

题意：

在树上选出两个点，使得所有点到最近的这两个点的最大值最小。



可以发现这些点仍然是选在直径上最优。

考虑求出直径上中间的两个点，然后将这条边断掉，将整棵树分为两棵树。

然后考虑在两棵树上反着BFS（即从所有叶子节点开始BFS，然后等一轮遍历之后再从它的父亲开始BFS）。

显然最后访问到的两个点就是答案。

单次时间复杂度为$O(n)$

```c++
vector<int>e[222222],zj;
int pre[222222],dep[222222];
int pos,st,ed;
int n;
int vis[222222],tot[222222];
int in[222222];
deque<pii>q;
	
void dfs(int u,int f)
{
	pre[u]=f,pos=(dep[pos]<dep[u])?u:pos;
	for(int v:e[u]) if(v^f) dep[v]=dep[u]+1,dfs(v,u);
}
void dfs2(int u,int f)
{
	//printf("u:%lld\n",u);
	if(in[u]==1) q.pb(mkp(u,0));
	for(int v:e[u]) if(v^f) dfs2(v,u);
}
pii bfs(int u,int f)
{
	//test
	//printf("ASD:%lld",in[u]);
	if(!in[u]) return mkp(u,0);
	//test
	dfs2(u,f);
	pii ret;
	memset(tot,0,sizeof(tot));
	while((int)q.size()>0) 
	{
		auto qwq=q.front();q.pop_front();
		//printf("qwq:%lld\n",qwq.fi);
		ret=qwq;
		tot[ret.se]++;
		for(int v:e[qwq.fi]) if(v^f&&in[v]^1)
		{
			in[v]--;
			if(in[v]==1) q.pb(mkp(v,ret.se+1));
		}
	}
	ret.se+=(tot[ret.se]>1);
	return ret;
}
signed main()
{
	for(int _=read();_;_--)
	{
		n=read();memset(in,0,sizeof(in));
		R(i,0,n+1) e[i].clear();zj.clear(),dep[pos=0]=0;
		int u,v;R(i,2,n) u=read(),v=read(),e[u].pb(v),e[v].pb(u),in[u]++,in[v]++; 
		dfs(1,-1);st=pos;dep[st]=0;
		dfs(st,-1);ed=pos;
		for(int cur=ed;~cur;cur=pre[cur]) zj.pb(cur);int len=(int)zj.size();
		int uuu=zj[len/2],vvv=zj[len/2-1];in[uuu]--,in[vvv]--;
		//printf("???:%lld %lld\n",uuu,vvv);
		//printf("asd:%lld %lld\n",in[uuu],in[vvv]);
	    pii r1=bfs(uuu,vvv);
	    //puts("2:");
	    pii r2=bfs(vvv,uuu);
		printf("%lld %lld %lld\n",max(r1.se,r2.se),r1.fi,r2.fi);
	}
}
```


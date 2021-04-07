
<!--more-->

单纯想记录一些动态维护树的直径的方法。

以下初始例题都是[CF1192B Dynamic Diameter](https://www.luogu.com.cn/problem/CF1192B)

- 欧拉序+线段树维护RMQ

可以用来解决一些树形态不变的问题。

线段树维护全$dfs$序
全$dfs$序为，仍然$dfs$遍历一棵树，每次访问到一个节点就把它记到序列末端
(下面称这时序列的长度为该的$bg$,序列称为$dfn$)
同时每当一个节点的子树的访问正式结束，也把它的父亲记到序列末端

考虑节点$u$,$v$不妨设$bg[u]<bg[v]$以及它们的LCA
显然$u$,$v$必然分属LCA的两个子树，于是在访问$v$之前,$u$所在子树的访问一定已经结束,所以LCA必定存在于$(bg[u],bg[v])$之间
显然，访问v时，对LCA子树访问不可能结束，于是$(bg[u],bg[v])$之间不可能有比LCA更浅的节点
LCA的深度是$[bg[u],bg[v]]$这一段区间里所有节点的深度的下界，而且它一定存在。所以它就是这段区间里的深度最小值，假设$u,v$两点在欧拉序的任意一个区间的两个端点是$l,r$，那么$dep[LCA(u,v)]=\min\limits_{l\leq k \leq r}\{dep[dfn[k]] \}$。

树上两点距离可以表示为$dis[u]+dis[v]-2\times dis[LCA(u,v)]$

考虑维护一条长为$2N-1$的序列$A[i]=dep[dfn[i]]$。所以求直径的问题可以转化为求
$$
\max\limits_{1\leq l\leq r\leq 2N-1}\{A[l]+A[r]-2\times \min\limits_{l\leq k\leq r}\{ A[k]\} \}
$$


考虑使用线段树维护这个东西。

设
$$
Diameter[L,R]=\max\limits_{L\leq l\leq r\leq R} \{A[l]+A[r]-2\times \min_{l\leq k\leq r}\{A[k] \} \}
$$
直径为$Diameter[1,2N-1]$。

考虑固定$l$，式子将变为$(k,r)$两个变量。考虑维护区间内下式的值$(l\leq i,j\leq r)$
$$
rmx[l,r]=A[i]-2\times \min\limits_{i\leq j}\{A[j]\}
$$

$$
lmx[l,r]=A[i]-2\times \min\limits_{j\leq i}\{A[j]\}
$$

令$m$为$(l,r)$中点，考虑$l,k,r$和$m$的关系，有
$$
\begin{equation}     
Diameter[L,R]=\max \left\{\begin{array}{lr} Diameter[m+1,R] & , & (m<l\leq k\leq r) \\ mx[L,m]+rmx[m+1,R] & , & (l\leq m<k\leq r) \\ lmx[L,m]+mx[m+1,R] & , &(l\leq k\leq m< r) \\ Diameter[L,m] & , &(l\leq k\leq r\leq m)  \end{array} \right.
\end{equation}
$$
同时$rmx$和$lmx$也可以使用这种思路求出
$$
\begin{equation}     
rmx[L,R]=\max \left\{\begin{array}{lr} rmx[m+1,R] & , & (m<l \leq r)\\ mx[L,m]-2\times mn[m+1,R] & , &(l\leq m< r)\\ rmx[L,m] & , &(l\leq r\leq m) \end{array} \right.
\end{equation}
$$

$$
\begin{equation}     
lmx[L,R]=\max \left\{\begin{array}{lr} lmx[L,m] & , &(l\leq r\leq m)\\ mx[m+1,R]-2\times mn[L,m] & , &(l\leq m<r) \\ lmx[m+1,R] & , &(m<l\leq r) \end{array} \right.
\end{equation}
$$

因为修改边权只对这条边**深度较深一段的子树**造成影响，而子树可以转化为**欧拉序上的一段区间**的修改。记录每个点对应的子树区间，也就是在欧拉序上的最早和最晚出现的位置，就可以将**边权修改**也转化为**区间操作**。只要记录这五个值和懒标记就可以维护这道题的信息了。

时间复杂度为$O(n\log n)$

```c++
int n,m,mxw;
const int N=866666;
struct edge {int nxt,to,val;}e[N<<1];
int len[N];
int head[N],cnt;
int fa[N],bg[N],en[N],tim,id[N],to[N];
int dis[N];
int mx[N],mn[N],lmx[N],rmx[N],mxd[N],la[N];
int lst_ans;
inline void add_edge(int u,int v,int d){e[++cnt]=(edge){head[u],v,d};head[u]=cnt;}
void dfs1(int u)
{
	id[++tim]=u;bg[u]=tim;int v;
	for(int i=head[u];i;i=e[i].nxt) 
	{
		v=e[i].to;if(v==fa[u]) continue;
		fa[v]=u;to[(i-1)/2]=v;
		dis[v]=dis[u]+e[i].val;
		dfs1(v);
		id[++tim]=u;
	}
	en[u]=tim;
}
inline void push_add(int x,int k) {mx[x]+=k,mn[x]+=k,lmx[x]-=k,rmx[x]-=k,la[x]+=k;}
inline void push_down(int x) {push_add(x<<1,la[x]),push_add(x<<1|1,la[x]);la[x]=0;}
inline void push_up(int x)
{
	mn[x]=min(mn[x<<1],mn[x<<1|1]);mx[x]=max(mx[x<<1],mx[x<<1|1]);
	lmx[x]=max(mx[x<<1]-2*mn[x<<1|1],max(lmx[x<<1],lmx[x<<1|1]));
	rmx[x]=max(mx[x<<1|1]-2*mn[x<<1],max(rmx[x<<1],rmx[x<<1|1]));
	mxd[x]=max(max(mx[x<<1]+rmx[x<<1|1],mx[x<<1|1]+lmx[x<<1]),max(mxd[x<<1],mxd[x<<1|1]));
}
void build(int l,int r,int x)
{
	if(l==r) 
	{
		mx[x]=mn[x]=dis[id[l]];
		lmx[x]=rmx[x]=-dis[id[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	push_up(x);
}
void modify(int L,int R,int l,int r,int x,int k)
{
	if(L<=l&&r<=R) return push_add(x,k);
	push_down(x);
	int mid=(l+r)>>1;
	if(L<=mid) modify(L,R,l,mid,x<<1,k);
	if(mid<R) modify(L,R,mid+1,r,x<<1|1,k);
	push_up(x);
}
signed main()
{	
	n=read(),m=read(),mxw=read();
	int u,v,d;R(i,0,n-2)u=read(),v=read(),d=read(),add_edge(u,v,d),add_edge(v,u,d),len[i]=d;
	dfs1(1);
	build(1,tim,1);
	//printf("%lld\n",mxd[1]);
	int e;
	//R(i,1,10) printf("st:%lld en:%lld to:%lld\n",bg[i],en[i],to[i]);
	while(m--)
	{
		e=read(),d=read();
		e=(e+lst_ans)%(n-1),d=(d+lst_ans)%mxw;
		//printf("%lld %lld\n",bg[to[e]],en[to[e]]);
		modify(bg[to[e]],en[to[e]],1,tim,1,d-len[e]);
		len[e]=d;
		writeln(lst_ans=mxd[1]);
	}
}
```

- 树剖维护维护点集

考虑树上两个点集$S,T$

设$d(S)$表示$S$点集中距离最远的某两个点,$S\cup T$中必然存在两个点，使得其距离最远
且两端均在$d(S)\cup d(T)$中。也就是说在合并两个点集并直径时,只需要讨论$O(1)$种可能的直径
在dfs序上建一棵线段树。线段树的每个区间$[l,r]$，维护dfs序在$[l,r]$内这些点组成的点集的直径
一次修改只会修改$[beg[x],en[x]]$相交且不包含的区间，容易发现这样的区间只有$O(\log n)$个,暴力更新即可.
即所经过的所有非终点节点。

时间复杂度$O(n+q\log ^2)$

```c++
int n,q,WWW,delt;
const int N=5e5+55;
struct egd
{
	int u,v,d;
}eg[N];
std::vector<pii>e[N];
int beg[N],en[N],dep[N],dis[N],tim;
int hson[N],siz[N],fa[N],htop[N],rbeg[N];

void dfs1(int u,int f){
	fa[u]=f;
	dep[u]=dep[f]+1;
	siz[u]=1;
	beg[u]=++tim;
	for(auto qwq:e[u]) {
		int v=qwq.fi,d=qwq.se;
		if(v==f) continue;
		dis[v]=dis[u]+d;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[hson[u]]<siz[v]) hson[u]=v;
	}
	en[u]=tim;
}
void dfs2(int u,int topf){
	htop[u]=topf;
	if(!hson[u]) return ;
	dfs2(hson[u],topf);
	for(auto qwq:e[u]) {
		int v=qwq.fi;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
inline int get_lca(int x,int y){
	while(htop[x]!=htop[y])
	{
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		x=fa[htop[x]];
	}
	return (dep[x]<dep[y])?x:y;
}
struct segmentree
{
	struct trnode
	{
		int u,v,len;
	}val[N];
	int dval[N];
	int query_dis(int pos,int l,int r,int x){
		if(l==r) return dval[x];
		int mid=(l+r)>>1,ret=0;
		if(pos<=mid) ret+=query_dis(pos,l,mid,x<<1);
		else ret+=query_dis(pos,mid+1,r,x<<1|1);
		return ret+dval[x];
	}
	int query_dist(int x,int y){
		return query_dis(beg[x],1,n,1)+query_dis(beg[y],1,n,1)-2*query_dis(beg[get_lca(x,y)],1,n,1);
	}
	inline void updt(int aa,int bb,int a,int b,int x){
		int tmp=aa+bb-query_dis(beg[get_lca(a,b)],1,n,1)*2;
		if(tmp>val[x].len) val[x].len=tmp,val[x].u=a,val[x].v=b;
	}
	inline void push_up(int x){
		val[x].len=-inf;
		int lensa=query_dis(beg[val[x<<1].u],1,n,1),lensb=query_dis(beg[val[x<<1].v],1,n,1);
		int lenta=query_dis(beg[val[x<<1|1].u],1,n,1),lentb=query_dis(beg[val[x<<1|1].v],1,n,1);
		updt(lensa,lensb,val[x<<1].u,val[x<<1].v,x);
		updt(lenta,lentb,val[x<<1|1].u,val[x<<1|1].v,x);
		updt(lensa,lenta,val[x<<1].u,val[x<<1|1].u,x);
		updt(lensb,lentb,val[x<<1].v,val[x<<1|1].v,x);
		updt(lensa,lentb,val[x<<1].u,val[x<<1|1].v,x);
		updt(lensb,lenta,val[x<<1].v,val[x<<1|1].u,x);
	}	
	void build(int l,int r,int x){
		if(l==r) {
			dval[x]=dis[rbeg[l]];
			val[x].u=val[x].v=rbeg[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		push_up(x);
	}
	void modify(int L,int R,int l,int r,int x,int k){
		if(L<=l&&r<=R) { 
			dval[x]+=k;
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid) modify(L,R,l,mid,x<<1,k);
		if(mid<R) modify(L,R,mid+1,r,x<<1|1,k);
	}
	void update(int L,int R,int l,int r,int x){
		if(L<=l&&r<=R) return;
		int mid=(l+r)>>1;
		if(L<=mid) update(L,R,l,mid,x<<1);
		if(mid<R)  update(L,R,mid+1,r,x<<1|1);
		push_up(x);
	}
	void print(){
		R(i,1,20) printf("val[%lld]:u:%lld v:%lld len:%lld dval:%lld\n",i,val[i].u,val[i].v,val[i].len,dval[i]);puts("");
	}
}st;
signed main()
{
	n=read(),q=read(),WWW=read();
	FR(i,1,n) {
		int u=read(),v=read(),d=read();
		eg[i]=(egd){u,v,d};
		e[u].pb(mkp(v,d)),e[v].pb(mkp(u,d));
	}
	dfs1(1,0);
	dfs2(1,1);
	//printf("%lld\n",get_lca(3,6));
	R(i,1,n) rbeg[beg[i]]=i;
	FR(i,1,n) if(fa[eg[i].v]==eg[i].u) Swap(eg[i].u,eg[i].v);
	st.build(1,n,1);
	//st.print();
	int lst_ans=0;
	R(i,1,q) 
	{
		int d=read(),e=read();
		d=(lst_ans+d)%(n-1)+1;
		e=(lst_ans+e)%WWW;
		//printf("e:%lld d:%lld\n",e,d);
		delt=e-eg[d].d;
		eg[d].d=e;
		st.modify(beg[eg[d].u],en[eg[d].u],1,n,1,delt);

		st.update(beg[eg[d].u],en[eg[d].u],1,n,1);
		lst_ans=st.val[1].len;
		printf("%lld\n",lst_ans);
	}
}
```

- LCT（还支持加边删边操作）

LCT的辅助树维护树内维护的是一条链，考虑维护这条**实链**上的最浅和最深的节点到**当前子树内**的最远距离。由于轻边实际上是父亲与这棵Splay上深度最小的点连的边，设$lmx[i]$表示$i$这棵**Splay子树**内深度最小的点往下的最大深度。当然因为Splay需要支持翻转操作，我们还需要维护这棵Splay上深度最大的点往下的最大深度rmx，当将Splay翻转过来时直接$swap(lmx,rmx)$即可。

接下来考虑lmx和rmx如何转移。以lmx的转移为例。

先考虑实链的转移

有
$$
lmx[x]=\max(lmx[x],lmx[son[x][0]])
$$
即直接从原树的祖先转移下来。

以及
$$
lmx[x]=\max(lmx[x],lmx[son[x][1]]+sum[son[x][0]]+len[x])
$$
即保留子树的答案再加上祖先和自身这条边的距离。

再考虑虚子树的转移。由于实链上深度最小的点实际上也是原树上子树的根节点。所以$lmx[x]$也可以表示为**子树内深度最小的节点**到子树内一点最远距离，那么有
$$
lmx[x]=\max(lmx[x],Chain.Fir+sum[son[x][0]]+len[x])
$$
即从虚儿子中深度最大的节点转移即可，这可以使用一个可删堆或者multiset来维护。

rmx同理。

接下来考虑$mxd[i]$最长链的转移。

仍然先考虑实链的转移有
$$
mxd[x]=\max(mxd[x],rmx[son[x][0]]+lmx[son[x][1]]+len[x])
$$
即祖先深度最大的点到子树深度最小的点以及自身这条边的距离。

以及
$$
mxd[x]=\max(mxd[x],mxd[son[x][0]],mxd[son[x][1]])
$$
即祖先和子树本来就有的最长链

再考虑虚子树的转移

最长链有可能是虚子树中本来就有的一条最长链，这同样也可以使用可删堆或者multiset维护。
$$
mxd[x]=\max(mxd[x],Path.Fir)
$$
当然也有可能是两条虚子树的链和自身这条边拼起来的，所以还有：
$$
mxd[x]=\max(mxd[x],Chain.Fir+Chain.Sec+len[x])
$$
最后附上代码

```c++
const int N=4e5+10;
int lmx[N],rmx[N],mxd[N];
int fa[N],len[N],tag[N],son[N][2];
int sum[N];
int n,m,MXW,ans,lst_ans;
vector<int>e[N];
struct inandelheap
{
	priority_queue<int>whl,del;
	inline void ist(int x){if(x!=-inf)whl.push(x);}
	inline void era(int x){if(x!=-inf)del.push(x);}
	inline int Top(){
		while(1)
		{
			if(whl.empty()) return -inf;
			if(del.empty()) return whl.top();
			if(whl.top()==del.top()) whl.pop(),del.pop();
			else return whl.top();
		}
	}
	inline int Sec() {
		int tmp=Top();era(tmp);
		int tmp2=Top();ist(tmp);
		return tmp2;
	}
}chain[N],path[N];
inline void INS(int u,int v) {chain[u].ist(lmx[v]),path[u].ist(mxd[v]);}
inline void ERA(int u,int v) {chain[u].era(lmx[v]),path[u].era(mxd[v]);}
inline int get(int x) {return x==son[fa[x]][1];}	
inline int isnotroot(int x) {return son[fa[x]][0]==x||son[fa[x]][1]==x;}
inline void push_up(int x)
{
	sum[x]=sum[son[x][0]]+sum[son[x][1]]+len[x];
	int oth=max(0ll,chain[x].Top());
	int up=max(oth,rmx[son[x][0]])+len[x];
	int dwn=max(oth,lmx[son[x][1]])+len[x];
	lmx[x]=max(lmx[son[x][0]],sum[son[x][0]]+dwn);
	rmx[x]=max(rmx[son[x][1]],sum[son[x][1]]+up);
	mxd[x]=max(lmx[son[x][1]]+up,rmx[son[x][0]]+dwn);
	mxd[x]=max(mxd[x],max(mxd[son[x][0]],mxd[son[x][1]]));
	mxd[x]=max(mxd[x],path[x].Top());
	mxd[x]=max(mxd[x],oth+max(0ll,chain[x].Sec())+len[x]);
}

inline void rotate(int x){
	int f=fa[x],gf=fa[f],wh=get(x);
	if(isnotroot(f)) son[gf][get(f)]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	push_up(f);
	push_up(x);
}

inline void splay(int x)
{
	for(int f;f=fa[x],isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
}
inline int access(int x)
{
	int y;
	for(y=0;x;y=x,x=fa[x]) {splay(x);if(y)ERA(x,y);if(son[x][1])INS(x,son[x][1]);son[x][1]=y,push_up(x);}
	return y;
}
void dfs1(int u) 
{
	for(int v:e[u]) if(v^fa[u])
	{
		fa[v]=u;
		dfs1(v);
		INS(u,v);
	}
	push_up(u);
}

inline void modify(int u,int d)
{	
	access(u);
	splay(u);
	len[u]=d;
	push_up(u);
	ans=mxd[u];
}

signed main()
{
	n=read(),m=read(),MXW=read();
	int u,v,d;
	R(i,1,n-1)
	{
		u=read(),v=read(),d=read();
		e[u].pb(i+n),e[i+n].pb(u);
		e[v].pb(i+n),e[i+n].pb(v);
		len[i+n]=d;
	}
	dfs1(1);
	while(m--)
	{
		u=read(),d=read();
		u=(u+lst_ans)%(n-1)+1;
		d=(d+lst_ans)%MXW;
		//printf("u:%lld val:%lld\n",u,d);
		modify(u+n,d);
		writeln(lst_ans=ans);
	}
}
```


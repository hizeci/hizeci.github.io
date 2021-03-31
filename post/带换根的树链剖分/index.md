
<!--more-->

题意：普通的轻重链剖分模板+换根操作。



关于路径的操作与根没有什么关系，影响的只有子树操作。

显然换根不能真正意义上的换根。（

考虑怎么得到根改变后找到当前的子树。

假设当前的树根为$rt$，现在询问的子树根节点为$u$

考虑分类讨论（这里的LCA指原树的LCA）。

1. $u=rt$，$u$的子树为整棵树。直接给整棵树权值$+k$。
2. $LCA(u,rt)\neq u$，即$rt$不在$u$的子树内，说明$u$的子树就是原树的子树，正常修改即可。
3. $LCA(u,rt)=u$，即$u$在原来的树中是$rt$的祖先。那找到$u$到$rt$路径上的第一个儿子。这个儿子对应原树中的子树，就是$u$子树的补集。给整棵树权值$+k$，然后给儿子的子树$-k$即可。

```c++
const int N=2e5+10;
int htop[N],siz[N],fa[N],dep[N],hson[N];
int st[N],en[N],tim;
int a[N],a_n[N];
int val[N<<2],la[N<<2];
int n,rt;
vector<int>e[N];

void dfs1(int u,int f)
{
	siz[u]=1;dep[u]=dep[f]+1;
	for(int v:e[u]) if(v^f)
	{
		dfs1(v,u);
		siz[u]+=siz[v];
		hson[u]=(siz[v]>siz[hson[u]])?v:hson[u];
	}
}
void dfs2(int u,int topf)
{
	st[u]=++tim;
	a_n[tim]=a[u];
	htop[u]=topf;
	if(hson[u]) dfs2(hson[u],topf);
	for(int v:e[u]) if(v^fa[u]&&v^hson[u]) dfs2(v,v);
	en[u]=tim;
}
inline int get_LCA(int x,int y)
{
	while(htop[x]!=htop[y]) 
	{
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		x=fa[htop[x]]; 
	}
	return dep[x]<dep[y]?x:y;
}
inline void push_up(int x){val[x]=val[x<<1]+val[x<<1|1];}
inline void push_down(int l,int r,int x)
{
	if(!la[x])return;
	int len=r-l+1;
	la[x<<1]+=la[x],la[x<<1|1]+=la[x];
	val[x<<1]+=(len-(len>>1))*la[x];
	val[x<<1|1]+=(len>>1)*la[x];
	la[x]=0;
}
void build(int l,int r,int x)
{
	if(l==r){val[x]=a_n[l];return;}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	push_up(x);
}
void modify_add(int L,int R,int l,int r,int x,int k)
{
	if(L<=l&&r<=R){val[x]+=(r-l+1)*k,la[x]+=k;return;}
	push_down(l,r,x);
	int mid=(l+r)>>1;
	if(L<=mid) modify_add(L,R,l,mid,x<<1,k);
	if(mid<R) modify_add(L,R,mid+1,r,x<<1|1,k);
	push_up(x);
}
int query(int L,int R,int l,int r,int x)
{
	if(L<=l&&r<=R) return val[x];
	push_down(l,r,x);
	int mid=(l+r)>>1,ret=0;
	if(L<=mid) ret+=query(L,R,l,mid,x<<1);
	if(mid<R) ret+=query(L,R,mid+1,r,x<<1|1);
	return ret;
}
void modify_path(int x,int y,int k)
{
	while(htop[x]!=htop[y]) 
	{
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		modify_add(st[htop[x]],st[x],1,n,1,k);
		x=fa[htop[x]];
	}
	if(dep[x]>dep[y]) Swap(x,y);
	modify_add(st[x],st[y],1,n,1,k);
}
int query_path(int x,int y)
{
	int ret=0;
	while(htop[x]!=htop[y])
	{
		//printf("x:%lld y:%lld htop[x]:%lld htop[y]:%lld\n",x,y,htop[x],htop[y]);
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		ret+=query(st[htop[x]],st[x],1,n,1);
		x=fa[htop[x]];
	}
	if(dep[x]>dep[y]) Swap(x,y);
	ret+=query(st[x],st[y],1,n,1);
	return ret;
}
int find_son(int x,int y)
{
	while(htop[x]!=htop[y])
	{
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		if(fa[htop[x]]==y) return htop[x];
		x=fa[htop[x]];
	}
	return dep[x]<dep[y]?hson[x]:hson[y];
}
void modify_son(int x,int k)
{
	if(x==rt){modify_add(1,n,1,n,1,k);return;}
	int l_a=get_LCA(x,rt);
	if(l_a!=x){modify_add(st[x],en[x],1,n,1,k);return;}
	int son=find_son(x,rt);
	modify_add(1,n,1,n,1,k),modify_add(st[son],en[son],1,n,1,-k);
}
int query_son(int x)
{
	if(x==rt) return query(1,n,1,n,1);
	int l_a=get_LCA(x,rt);
	if(l_a!=x) return query(st[x],en[x],1,n,1);
	int son=find_son(x,rt);
	return query(1,n,1,n,1)-query(st[son],en[son],1,n,1);
} 
signed main()
{
	n=read(),rt=1;
	R(i,1,n) a[i]=read();
	R(i,2,n) fa[i]=read(),e[fa[i]].pb(i),e[i].pb(fa[i]);
	dfs1(1,0);dfs2(1,1);
	build(1,n,1);
	int opt,x,y,k;
	for(int _=read();_;_--)
	{
		opt=read(),x=read();
		if(opt==1) rt=x;
		if(opt==2) y=read(),k=read(),modify_path(x,y,k);
		if(opt==3) k=read(),modify_son(x,k);
		if(opt==4) y=read(),writeln(query_path(x,y));
		if(opt==5) writeln(query_son(x)); 
	}
}	
```


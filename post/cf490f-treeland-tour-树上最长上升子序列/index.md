
<!--more-->

对于树上的每一个点，计算子树内所有点到自己为结尾的$\text{LIS,LDS}$，然后丢到权值线段树上合并信息。更新答案时具体做法为用左儿子的$\text{LIS}$和右儿子的$\text{LDS}$以及左儿子的$\text{LDS}$以及右儿子的$\text{LIS}$。

注意需要离散化。

```c++
const int N=222222;
vector<int>e[N];
int n,ans,cnt,tot_seg;
int a[N],b[N],Rt[N];
int Ls[N*20],Rs[N*20],vai[N*20],vad[N*20];
int fi[N],fd[N];
int gi[N],gd[N];
void mer_ge(int &x,int y)
{
	if(!x||!y) {x^=y;return;}
	ckmax(vai[x],vai[y]),ckmax(vad[x],vad[y]);
	ckmax(ans,max(vai[Ls[x]]+vad[Rs[y]],vad[Rs[x]]+vai[Ls[y]]));
	mer_ge(Ls[x],Ls[y]),mer_ge(Rs[x],Rs[y]);
}
inline void push_up(int x,int opt){!opt?vai[x]=max(vai[Ls[x]],vai[Rs[x]]):vad[x]=max(vad[Ls[x]],vad[Rs[x]]);}
void modify(int pos,int l,int r,int &x,int k,int opt)
{
	if(!x) x=++tot_seg;
	if(l==r) {!opt?ckmax(vai[x],k):ckmax(vad[x],k);return;}
	int mid=(l+r)>>1;
	pos<=mid?modify(pos,l,mid,Ls[x],k,opt):modify(pos,mid+1,r,Rs[x],k,opt);
	push_up(x,opt);
}
int query(int L,int R,int l,int r,int x,int opt)
{
	if(!x) return 0;
	if(L<=l&&r<=R) return !opt?vai[x]:vad[x];
	int mid=(l+r)>>1,ret=-(1e9+7);
	if(L<=mid) ckmax(ret,query(L,R,l,mid,Ls[x],opt));
	if(mid<R) ckmax(ret,query(L,R,mid+1,r,Rs[x],opt));
	return ret;
}
void dfs(int u,int f)
{
	for(int v:e[u]) if(v^f)
	{
		dfs(v,u);
		gi[u]=query(1,a[u]-1,1,cnt,Rt[v],0),gd[u]=query(a[u]+1,cnt,1,cnt,Rt[v],1);
		ckmax(ans,max(gi[u]+fd[u]+1,gd[u]+fi[u]+1));
		ckmax(fi[u],gi[u]),ckmax(fd[u],gd[u]);
		mer_ge(Rt[u],Rt[v]);
	}
	modify(a[u],1,cnt,Rt[u],fi[u]+1,0),modify(a[u],1,cnt,Rt[u],fd[u]+1,1);
}
signed main()
{
	n=read();if(n==1) return puts("1")&0;
	R(i,1,n) b[i]=a[i]=read();
	sort(b+1,b+n+1);cnt=unique(b+1,b+n+1)-b-1;
	R(i,1,n) a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	int u,v;R(i,2,n) u=read(),v=read(),e[u].pb(v),e[v].pb(u);
	dfs(1,0);
	writeln(ans);
}	
```


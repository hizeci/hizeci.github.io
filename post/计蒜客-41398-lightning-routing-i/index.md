
<!--more-->

题意：

给出一棵树，两种操作：

1. 修改边权
2. 查询离某个点最远的点的距离。

对于每个询问，可以想到这个距离最远的点一定是，树的直径的一端，证明可以使用反证法。

那么就只需要动态维护直径，每次查询到两个直径端点的最长距离即可。

这些操作可以使用LCT维护。

```c++
const int N=888888;
int n;
pii e[N];
int fa[N],val[N];
int sum[N];
int siz[N];
int tag[N],son[N][2];
int lmx[N],rmx[N];
int mxd[N];

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
}h[N],p[N];

inline void INS(int x,int y) {h[x].ist(lmx[y]),p[x].ist(mxd[y]);}
inline void ERA(int x,int y) {h[x].era(lmx[y]),p[x].era(mxd[y]);}
inline int get(int x){return x==son[fa[x]][1];}
inline int isnotroot(int x){return son[fa[x]][0]==x||son[fa[x]][1]==x;}
inline void push_up(int x)
{
	siz[x]=siz[son[x][0]]+siz[son[x][1]];
	sum[x]=sum[son[x][0]]+sum[son[x][1]]+val[x];
	int t=max(h[x].Top(),0ll),L=max(t,rmx[son[x][0]])+val[x],R=max(t,lmx[son[x][1]])+val[x];
	//int t=max(Top(H[x]),0ll),L=max(t,rmx[son[x][0]])+val[x],R=max(t,lmx[son[x][1]])+val[x];
	lmx[x]=max(lmx[son[x][0]],sum[son[x][0]]+R);rmx[x]=max(rmx[son[x][1]],sum[son[x][1]]+L);
	mxd[x]=max(max(rmx[son[x][0]]+R,lmx[son[x][1]]+L),max(mxd[son[x][0]],mxd[son[x][1]]));
	ckmax(mxd[x],max(t+val[x]+max(0ll,h[x].Sec()),p[x].Top()));
	//ckmax(mxd[x],max(t+val[x]+max(0ll,Sec(H[x])),Top(P[x])));

}
inline void push_flp(int x){Swap(lmx[x],rmx[x]);Swap(son[x][0],son[x][1]);tag[x]^=1;}
inline void push_down(int x)
{
	if(tag[x])
	{
		if(son[x][0]) push_flp(son[x][0]);
		if(son[x][1]) push_flp(son[x][1]);
		tag[x]=0;
	}
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
void update(int x) {if(isnotroot(x))update(fa[x]);push_down(x);}
inline void splay(int x)
{
	update(x);
	for(int f;f=fa[x],isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
	push_up(x);
}
inline int access(int x)
{
	int y;
	for(y=0;x;y=x,x=fa[x]) {splay(x);if(y)ERA(x,y); if(son[x][1])INS(x,son[x][1]); son[x][1]=y,push_up(x);}
	return y;
}
inline void make_root(int x){access(x);splay(x);push_flp(x);}
inline int find_root(int x)
{
	access(x),splay(x);
	while(son[x][0])push_down(x),x=son[x][0];
	splay(x);
	return x;
}
inline void spilt(int x,int y){make_root(x);access(y);splay(y);}


inline void link(int x,int y) 
{
	make_root(x);splay(x);
	if(find_root(y)!=x){fa[x]=y;INS(y,x);}
}
inline void cut(int x,int y)
{
	spilt(x,y);
	if(son[y][0]==x&&!son[x][1]) son[y][0]=fa[x]=0;
}	
inline int query(int x) {access(x),splay(x); return rmx[x];}
void print()
{
	puts("");
	puts("---------------up--------------");
	R(i,0,10) printf("x:%lld ls:%lld rs:%lld\n",i,son[i][0],son[i][1]);
	printf("sum:");R(i,0,10) printf("%lld ",sum[i]);puts("");
	printf("lmx:");R(i,0,10) printf("%lld ",lmx[i]);puts("");
	printf("rmx:");R(i,0,10) printf("%lld ",rmx[i]);puts("");
	printf("mxd:");R(i,0,10) printf("%lld ",mxd[i]);puts("");
	printf("val:");R(i,0,10) printf("%lld ",val[i]);puts("");
	puts("--------------down-------------");
	puts("");
}

signed main()
{
	//h[1].ist(1),h[1].ist(2),h[1].ist(3),h[1].ist(100);
	//writeln(h[1].Sec());
	n=read();
	int u,v;R(i,1,n-1) u=read(),v=read(),e[i]=mkp(u,v),sum[i+n]=val[i+n]=read(),link(u,i+n),link(v,i+n);
	char opt[11];
	int nm,w,vl;
	for(int _=read();_;_--)
	{
		//print();
		scanf("%s",opt+1);
		if(opt[1]=='C') 
		{
			nm=read(),w=read();
			cut(e[nm].fi,nm+n),cut(e[nm].se,nm+n);
			//cut(e[nm].fi,nm+n),cut(nm+n,e[nm].se);
			sum[nm+n]=val[nm+n]=w;
			//link(e[nm].fi,nm+n),link(nm+n,e[nm].se);
			link(e[nm].fi,nm+n),link(e[nm].se,nm+n);
		}
		if(opt[1]=='Q') vl=read(),writeln(query(vl));
	}
}
/*
test #7:
	10
	10 2 8506666
	4 7 4366355
	4 6 22029
	6 9 3986792
	4 1 4712693
	6 2 4817176
	5 6 2143758
	8 5 8103920
	3 10 9511674
	10
	Q 3
	Q 3
	Q 9
	C 9 2486896
	Q 9
	C 2 5488953
	C 9 4165296
	C 8 9119928
	Q 3
	C 4 851632
	
good:
	33083194
	33083194
	26822308
	19797530
	28752824
	
bad:
	27570238
	27570238
	26822308
	19797530
	53935320
	
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
//printf("%lld ",dist(rand_num));
const int n=10,m=10;
int fa[1111111];
inline int find_fa(int x){return x==fa[x]?x:fa[x]=find_fa(fa[x]);}
signed main()
{
	R(i,1,n) fa[i]=i;
	printf("%lld\n",n);
	int u,v,d,fu,fv;
	R(i,1,n-1)
	{
		while(1)
		{
			u=dist(rand_num)%n+1,v=dist(rand_num)%n+1,d=dist(rand_num);
			fu=find_fa(u),fv=find_fa(v);
			if(fu!=fv&&u!=v) break;
		}
		fa[fu]=fv;
		printf("%lld %lld %lld\n",u,v,d);
	}
	printf("%lld\n",m);
	int opt,x,y;
	R(i,1,m)
	{
		opt=dist(rand_num)%2;
		int fuck=dist(rand_num)%n;if(fuck==0) fuck=1;
		if(!opt) printf("Q %lld\n",dist(rand_num)%n+1);
		else printf("C %lld %lld\n",fuck,dist(rand_num));
	}
}
*/
```


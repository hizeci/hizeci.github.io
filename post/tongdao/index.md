
想不出来题

简要不精确题意:给定三棵树,求$\max(dist_1(a,b)+dist_2(a,b)+dist_3(a,b))$

<!--more-->

考虑两个树的时候，直接在第二棵树的每个节点下面挂上一个新点，之间的边权为它在第一棵树上的深度。然后考虑枚举第一棵树上的$lca$动态维护直径即可.(经典结论,两个直径合并起来最长直径就在这$4$个点选,边权为正).总结一下就是把两棵树合并起来,$dfs$枚举$lca$,顺便合并,然后在合并时顺便求一下贡献就行了.

然后考虑三棵树时怎么做.先将第一棵树的边分树求出来,枚举边分树上的$lca$,假设这个点为$a$,再把$a$子树内的点在第二棵树上的虚树建出来.在$a$的子树内的点分为两种类型一种为$A$型，一种为$B$ 型,分别表示在$a$的左子树和右子树,接下来的问题就是要选一个$A$型点和一个$B$型点,使得它们三个点的距离最远

(设$a$的两端分别为$x$和$y$,则距离可以表示为$dist_1(A,x)+dist_1(y,B)+dist_2(A,x)+dist_2(y,B)+dist_3(A,x)+dist_3(y,B)$加上$x,y$之间的常数).

这次的第三棵树下接的点就不只是$dep$了,还要加上在第一棵树上到对应点的距离.

之后考虑再枚举第二棵树上的$lca$，这里就相当于要在它的两棵子树内,选一个$A$型点,选一个$B$型点,使得它们在第三棵子树上的距离最大.此时就并不能单单维护一条直径了,我们要维护一个点集,维护两端都是$A$型,两端都是$B$型,以及一端为$A$,一端为$B$型的最长距离,这样算贡献时,有贡献的点只有这六个,同样这也是可合并的.

这样时间复杂度是$O(n\log^2 n)$,一个$\log$是边分树,一个$\log$是虚树的排序，然后边分树的子树和也是$O(n\log n)$级别的,所以总共虚树点数也是$O(n\log n)$级别的(但是你可以通过$O(1)lca$以及虚树可以离线使用基数排序然后搞成$O(n\log n)$的).以及带一个巨大常数($36$)的$\log$,即合并.

不过yysy直接爬山乱搞实际上过的概率应该挺高的.

代码:



```c++
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define fi first
#define se second
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define ll long long
#define ull unsigned long long
//#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x, T y) { return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x, T y) { return x>y?x=y,true:false;}
using namespace std;
//const ll inf=0x7f7f7f7f7f7f7f3f;
const ll inf=(1ll<<60);
//const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
const double eps=1e-6;
inline int fpow(int a,int b=mod-2,int p=mod){int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}
/*
const int qwq=2000010;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}

inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return 1ll*F[n]%mod*1ll*Finv[m]*1ll%mod*1ll*Finv[n-m]%mod;}
*/

//#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline ll read()
{
    char c=getchar();ll x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}

inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
int n;
ll ans;
namespace t3r3e3e3
{
	vector<pair<int,ll> >g[111111];
	int st[111111],dep[111111],Lg[333333];
	int fa[23][333333],tim;
	ll dis[111111],ano[111111];
	inline void add_edge(int u,int v,ll d){g[u].pb(mkp(v,d));}
	void dfs1(int u,int f) 
	{
		fa[0][++tim]=u;st[u]=tim;
		for(auto qwq:g[u])
		{
			int v=qwq.fi;
			if(v==f) continue;
			dep[v]=dep[u]+1,dis[v]=dis[u]+qwq.se;
			dfs1(v,u);
			fa[0][++tim]=u;
		}
	}
	inline int get_lopoi(int x,int y){return dep[x]<dep[y]?x:y;}
	void init_st() 
	{
		R(i,2,tim+5) Lg[i]=Lg[i>>1]+1;
		for(int i=1;(1<<i)<=tim;i++)
		{
			int w=(1<<i);
			R(j,1,tim-w+1) fa[i][j]=get_lopoi(fa[i-1][j],fa[i-1][j+(w>>1)]);
		}
	}
	inline int get_LCA(int x,int y)
	{
		x=st[x],y=st[y];
		if(x>y) Swap(x,y);
		int i=Lg[y-x+1],w=(1<<i);
		return get_lopoi(fa[i][x],fa[i][y-w+1]);
	}
	inline ll get_DIS(int x,int y){return dis[x]+dis[y]-2*dis[get_LCA(x,y)]+ano[x]+ano[y];}
	void mian()
	{
		//dep[1]=1;
		dfs1(1,-1);
		init_st();
	}
	void print()
	{
		puts("");
		puts("----------------");
		//R(i,1,10) writeln(dis[i]);
		R(i,1,5){ R(j,1,5) printf("i:%d j:%d (i,j)'s LCA:%d\n",i,j,get_LCA(i,j));}
		puts("----------------");
		puts("");
	}
}
namespace t2r2e2e2
{
	vector<pair<int,ll> >g[111111];
	vector<int>e[111111];
	int k;
	int dfn[111111],st[111111],rnk[111111],dep[111111],Lg[333333];
	int fa[23][333333],tim;
	ll dis[111111];
	bool vis[111111];
	int cnt_n;
	int stk[111111],top;
	ll A[111111][3],B[111111][3];
	int a[111111],typ[111111];
	ll ano[111111];
	ll res;
	inline void add_edge(int u,int v,ll d){g[u].pb(mkp(v,d));}
	void dfs1(int u,int f)
	{
		fa[0][++tim]=u;st[u]=tim;rnk[++cnt_n]=u,dfn[u]=cnt_n;
		for(auto qwq:g[u]) 
		{
			int v=qwq.fi;
			if(v==f) continue;
			dep[v]=dep[u]+1,dis[v]=dis[u]+qwq.se;
			dfs1(v,u);
			fa[0][++tim]=u;
		}	
	}
	inline int get_lopoi(int x,int y){return dep[x]<dep[y]?x:y;}
	void init_st() 
	{
		R(i,2,tim+5) Lg[i]=Lg[i>>1]+1;
		for(int i=1;(1<<i)<=tim;i++)
		{
			int w=(1<<i);
			R(j,1,tim-w+1) fa[i][j]=get_lopoi(fa[i-1][j],fa[i-1][j+(w>>1)]);
		}
	}
	inline int get_LCA(int x,int y)
	{
		x=st[x],y=st[y];
		if(x>y) Swap(x,y);
		int i=Lg[y-x+1],w=(1<<i);
		return get_lopoi(fa[i][x],fa[i][y-w+1]);
	}
	void mian()
	{
		dfs1(1,-1);
		init_st();
	}
	void print()
	{
		puts("");
		puts("----------------");
		//R(i,1,10) writeln(dis[i]);
		printf("\ndis:");R(i,1,10) printf("%lld ",dis[i]);puts("");
		printf("\ndep:");R(i,1,10) printf("%d ",dep[i]);puts("");
		printf("\nst:");R(i,1,10) printf("%d ",st[i]);puts("");
		printf("\nrnk:");R(i,1,10) printf("%d ",rnk[i]);puts("");
		printf("\ndfn:");R(i,1,10) printf("%d ",dfn[i]);puts("");
		R(i,1,5){ R(j,1,5) printf("i:%d j:%d (i,j)'s LCA:%d\n",i,j,get_LCA(i,j));}
		puts("----------------");
		puts("");
	}
	void ins_ert(int x)
	{
		if(!top) {stk[++top]=x;return;}
		while(top>1&&dep[stk[top-1]]>=dep[get_LCA(x,stk[top])]) {/*printf("1:u:%d v:%d\n",stk[top-1],stk[top]);*/e[stk[top-1]].pb(stk[top]),top--;}
		int tt=get_LCA(x,stk[top]);
		if(tt!=stk[top]) {/*printf("2:u:%d v:%d\n",tt,stk[top]);*/e[tt].pb(stk[top]),stk[top]=tt;}
		stk[++top]=x;
	}
	void dfs2(int u)
	{
		A[u][0]=A[u][1]=A[u][2]=B[u][0]=B[u][1]=B[u][2]=0;
		if(vis[u])
		{
			if(!typ[u]) A[u][0]=A[u][1]=u;
			else B[u][0]=B[u][1]=u;  
		} 
		for(int v:e[u])
		{		
			//printf("u:%d A0:%lld A1:%lld A2:%lld B0:%lld B1:%lld B2:%lld\n",u,A[u][0],A[u][1],A[u][2],B[u][0],B[u][1],B[u][2]);
			dfs2(v);
			vector<int>LA(0),LB(0),RA(0),RB(0);
			LA.pb(A[u][0]),LA.pb(A[u][1]);
			LB.pb(B[u][0]),LB.pb(B[u][1]);
			RA.pb(A[v][0]),RA.pb(A[v][1]);
			RB.pb(B[v][0]),RB.pb(B[v][1]);
			if(!A[u][0]||ckmax(A[u][2],A[v][2])) A[u][0]=A[v][0],A[u][1]=A[v][1],A[u][2]=A[v][2];
			if(!B[u][0]||ckmax(B[u][2],B[v][2])) B[u][0]=B[v][0],B[u][1]=B[v][1],B[u][2]=B[v][2];
			for(int x:LA) for(int y:RA) if(x&&y&&ckmax(A[u][2],t3r3e3e3::get_DIS(x,y))) A[u][0]=x,A[u][1]=y;
			for(int x:LB) for(int y:RB) if(x&&y&&ckmax(B[u][2],t3r3e3e3::get_DIS(x,y))) B[u][0]=x,B[u][1]=y;
			for(int x:LA) for(int y:RB) if(x&&y) ckmax(res,t3r3e3e3::get_DIS(x,y)-2*dis[u]);
			for(int x:LB) for(int y:RA) if(x&&y) ckmax(res,t3r3e3e3::get_DIS(x,y)-2*dis[u]);
		}
		e[u].clear();
	}
	ll solve()
	{
		top=res=0;
		R(i,1,k) t3r3e3e3::ano[a[i]]=ano[a[i]]+dis[a[i]],vis[a[i]]=1;
		if(a[1]!=1) ins_ert(1);R(i,1,k) ins_ert(a[i]);
		while(top>1) {/*printf("3:u:%d v:%d\n",stk[top-1],stk[top]);*/e[stk[top-1]].pb(stk[top]),top--;}
		//R(i,1,k) 
		dfs2(1);
		R(i,1,k) vis[a[i]]=0;
		return res;
	}
}

namespace t1r1e1e1
{
	vector<pair<int,ll> >g[222222];
	bool vis[222222];
	ll dis[222222];
	int a[222222];
	struct edge{int nxt,to;ll val;}e[444444];
	int head[222222],cnt_e=1;
	int col[222222],siz[222222];
	int m,rt,eg_rt;
	ll Mn_rt;
	int tmp[222222];
	inline void add_edge1(int u,int v,ll d){g[u].pb(mkp(v,d));}
	inline void add_edge2(int u,int v,ll d){e[++cnt_e]=(edge){head[u],v,d};head[u]=cnt_e;}
	inline void link(int u,int v,ll d) {add_edge2(u,v,d),add_edge2(v,u,d);}
	void build_tr(int u,int f)
	{
		int lst=0;
		for(auto qwq:g[u])
		{
			ll v=qwq.fi,vl=qwq.se;
			if(v==f) continue;
			if(!lst) 
			{
				link(u,v,vl);
				//add_edge2(u,v,vl),add_edge2(v,u,vl);
				lst=u;
			}
			else
			{
				m++;
				link(lst,m,0);
				link(m,v,vl);
				//add_edge2(lst,m,0),add_edge2(m,lst,0);
				//add_edge2(m,v,vl),add_edge2(v,m,vl);
				lst=m;
			}
			build_tr(v,u);
		}
	}
	void dfs1(int u,int f,int siz_tr)
	{
		siz[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(v==f||vis[i>>1]) continue;
			dfs1(v,u,siz_tr);siz[u]+=siz[v];
			if(ckmin(Mn_rt,1ll*max(siz[v],siz_tr-siz[v]))) rt=v,eg_rt=i;
		}
	}
	void dfs2(int u,int f,int wh)
	{
		if(u<=n) col[u]=wh;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(v==f||vis[i>>1]) continue;
			dis[v]=dis[u]+e[i].val;
			dfs2(v,u,wh);
		}
	}
	void solve(int u,int siz_tr,int l,int r)
	{
		if(siz_tr==1) return;
		Mn_rt=inf,eg_rt=rt=0;
		dfs1(u,-1,siz_tr);
		//printf("u:%d siz_tr:%d l:%d r:%d Mn_rt:%lld eg_rt:%d rt:%d \n",u,siz_tr,l,r,Mn_rt,eg_rt,rt);
		int cur=eg_rt,siz_str=siz[e[cur].to];
		assert(u>0);
		assert(siz_tr>1);
		assert(siz[u]==siz_tr);
		assert((cur&1)==0);
		vis[cur>>1]=1;
		dis[e[cur].to]=dis[e[cur^1].to]=0;
		dfs2(e[cur].to,-1,0),dfs2(e[cur^1].to,-1,1);
		if(l<r) 
		{
			t2r2e2e2::k=r-l+1;
			R(i,l,r) t2r2e2e2::a[i-l+1]=a[i],t2r2e2e2::typ[a[i]]=col[a[i]],t2r2e2e2::ano[a[i]]=dis[a[i]];
			/*
			puts("");
			puts("------------------------");
			puts("");
			printf("l:%d r:%d\n",l,r);
			R(i,l,r) printf("%d %d %lld\n",a[i],col[a[i]],dis[a[i]]);
			printf("eg:%lld sl:%lld\n",e[cur].val,t2r2e2e2::solve());
			puts("");
			puts("------------------------");
			puts("");
			*/
			ckmax(ans,t2r2e2e2::solve()+e[cur].val);
			
		}
		int p1=l,p2=r;
		R(i,l,r)
		{
			if(!col[a[i]]) tmp[p1++]=a[i];
			else tmp[p2--]=a[i];
		}
		R(i,l,r) a[i]=tmp[i];
		reverse(a+p1,a+r+1);
		solve(e[cur].to,siz_str,l,p1-1);
		solve(u,siz_tr-siz_str,p1,r);
	}
	void mian()
	{
		m=n;
		R(i,1,n) a[i]=t2r2e2e2::rnk[i];
		build_tr(1,-1);
		solve(1,m,1,n);
	}
}

signed main()
{
//	freopen("1.1.in","r",stdin);
	n=read();int u,v;ll d;
	R(i,1,n-1) 
	{
		u=read(),v=read(),d=read();
		t1r1e1e1::add_edge1(u,v,d);
		t1r1e1e1::add_edge1(v,u,d);
	}
	R(i,1,n-1)
	{
		u=read(),v=read(),d=read();
		t2r2e2e2::add_edge(u,v,d);
		t2r2e2e2::add_edge(v,u,d);
	}
	R(i,1,n-1)
	{
		u=read(),v=read(),d=read();
		t3r3e3e3::add_edge(u,v,d);
		t3r3e3e3::add_edge(v,u,d);
	}
	t3r3e3e3::mian();
	//t3r3e3e3::print();
	//writeln(t3r3e3e3::get_DIS(1,2));
	t2r2e2e2::mian();
	//t2r2e2e2::print();
	t1r1e1e1::mian();
	writeln(ans);
}
```


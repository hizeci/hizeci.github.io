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
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x, T y) { return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x, T y) { return x>y?x=y,true:false;}
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=(1ll<<60);
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
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
inline void write(int x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(int x){write(x),putchar(' ');}
inline void writeln(int x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
int n;
int ans;
namespace t3r3e3e3
{
	vector<pii>g[111111];
	int st[111111],dep[111111],Lg[111111];
	int fa[23][111111],dis[111111],tim;
	int ano[111111];
	inline void add_edge(int u,int v,int d){g[u].pb(mkp(v,d));}
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
	inline int get_DIS(int x,int y){return dis[x]+dis[y]-2*dis[get_LCA(x,y)]+ano[x]+ano[y];}
	void mian()
	{
		//dep[1]=1;
		dfs1(1,-1);
		init_st();
	}
}
namespace t2r2e2e2
{
	vector<pii>g[111111];
	vector<int>e[111111];
	int k;
	int dfn[111111],st[111111],rnk[111111],dep[111111],Lg[111111];
	int fa[23][111111],dis[111111],tim;
	int vis[111111];
	int cnt_n;
	int stk[111111],top;
	int A[111111][3],B[111111][3];
	int a[111111],ano[111111],typ[111111];
	int res;
	inline void add_edge(int u,int v,int d){g[u].pb(mkp(v,d));}
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
	void ins_ert(int x)
	{
		if(!top) {stk[++top]=x;return;}
		while(top>1&&dep[stk[top-1]]>=dep[get_LCA(x,stk[top])]) e[stk[top-1]].pb(stk[top]),top--;
		int tt=get_LCA(x,stk[top]);
		if(tt!=stk[top]) e[tt].pb(stk[top]),stk[top]=tt;
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
	void mian()
	{
		dfs1(1,-1);
		init_st();
	}
	int solve()
	{
		top=res=0;
		R(i,1,k) t3r3e3e3::ano[a[i]]=ano[a[i]]+dis[a[i]],vis[a[i]]=1;
		if(a[1]!=1) ins_ert(1);
		R(i,1,k) ins_ert(a[i]);
		while(top>1) e[stk[top-1]].pb(stk[top]),top--;
		dfs2(1);
		R(i,1,k) vis[a[i]]=0;
		return res;
	}
}

namespace t1r1e1e1
{
	vector<pii>g[1111111];
	int vis[222222];
	int dis[222222],a[222222];
	struct edge{int nxt,to,val;}e[444444];
	int head[222222],cnt_e=1;
	int col[111111],siz[222222];
	int m,Mn_rt,rt,eg_rt;
	int tmp[222222];
	inline void add_edge1(int u,int v,int d){g[u].pb(mkp(v,d));}
	inline void add_edge2(int u,int v,int d){e[++cnt_e]=(edge){head[u],v,d};head[u]=cnt_e;}
	void build_tr(int u,int f)
	{
		int lst=0;
		for(auto qwq:g[u])
		{
			int v=qwq.fi,vl=qwq.se;
			if(v==f) continue;
			if(!lst) 
			{
				add_edge2(u,v,vl),add_edge2(v,u,vl);
				lst=u;
			}
			else
			{
				m++;
				add_edge2(lst,m,0),add_edge2(m,lst,0);
				add_edge2(m,v,vl),add_edge2(v,m,vl);
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
			if(ckmin(Mn_rt,max(siz[v],siz_tr-siz[v]))) rt=v,eg_rt=i;
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
	n=read();int u,v,d;
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
	//writeln(t3r3e3e3::get_DIS(1,2));
	t2r2e2e2::mian();
	t1r1e1e1::mian();
	writeln(ans);
}
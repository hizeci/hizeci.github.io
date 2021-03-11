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
template <typename T> bool ckmax(T &x, T y) { return x < y ? x = y, true : false;}
template <typename T> bool ckmin(T &x, T y) { return x > y ? x = y, true : false;}
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
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define us unsigned 
#define ll long long
#define ull unsigned long long
#define int long long
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x,T y){return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x,T y){return x>y?x=y,true:false;}
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
const ld eps=1e-8;
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
const int N=4e5+10;
int n,_n,L,R,ansu,ansv;
int val[N];
int siz[N];
int vis[N],cxy=50;
int dis[N],dep[N],que[N],fa[N],cnt[N],rev[N],ljt[N];
int M;
int g[N],gg[N];
vector<pii>e[N];
int bfs(int G)
{
	int st=1,en=0;que[++en]=G;fa[G]=0;
	for(;st<=en;st++) 
	{
		int u=que[st];
		for(auto qwq:e[u]) 
		{
			int v=qwq.fi;
			if(vis[v]==cxy) continue;
			if(v!=fa[u]) 
				fa[v]=u,que[++en]=v,dep[v]=dep[u]+1,cnt[v]=cnt[u]+(qwq.se<val[M]?-1:1);
		}
	}
	return en;
}
int find_gra(int G)
{
	int Mn=inf,Mnpos;
	int en=bfs(G);
	L(t,1,en)
	{
		int u=que[t];
		int mx=0;siz[u]=1;
		for(auto qwq:e[u])
		{
			int v=qwq.fi;
			if(vis[v]==cxy||v==fa[u]) continue;
			siz[u]+=siz[v];
			ckmax(mx,siz[v]);
		}
		ckmax(mx,en-siz[u]);
		if(mx<Mn) Mn=mx,Mnpos=u;
	}
	return Mnpos;
}
int calc(int u) 
{
	int en=bfs(u);
	R(i,1,en) if(rev[dep[que[i]]]<cnt[que[i]]) rev[dep[que[i]]]=cnt[que[i]],gg[dep[que[i]]]=que[i];
	int ok=0,bg=1,ed=0;
	for(int i=en,j=0;i;i--) 
	{
		int ql=L-i,qr=R-i;if(ql>_n) break; 
		ckmax(j,ql);
		for(;j<=qr&&j<=_n;j++) {for(;bg<=ed&&dis[j]>dis[ljt[ed]];ed--);ljt[++ed]=j;}
		for(;bg<=ed&&ljt[bg]<ql;bg++);
		if(bg<=ed&&dis[ljt[bg]]+rev[i]>=0) {ansu=g[ljt[bg]],ansv=gg[i],ok=1;break;}
	}
	_n=max(_n,en);
	R(i,1,en) {if(rev[i]>dis[i])dis[i]=rev[i],g[i]=gg[i];rev[i]=-inf;}
	return ok;
}

int solve(int u)
{
	int G=find_gra(u);
	dep[G]=cnt[G]=0;
	int en=bfs(G);
	vis[G]=cxy;dis[0]=_n=0;g[0]=G;
	R(i,1,en) dis[i]=rev[i]=-inf;
	for(auto qwq:e[G]) 
	{
		int v=qwq.fi;
		if(vis[v]==cxy) continue; 
		if(calc(v)) return 1;
	}
	for(auto qwq:e[G]) 
	{
		int v=qwq.fi;
		if(vis[v]==cxy) continue;
		if(solve(v)) return 1;
	}
	return 0;
}
inline int check() {return solve(1);}
signed main()
{
	n=read(),L=read(),R=read();
	R(i,1,n-1) 
	{
		int u=read(),v=read();val[i]=read();
		e[u].pb(mkp(v,val[i])),e[v].pb(mkp(u,val[i]));
	}
	sort(val+1,val+n);
	int l=1,r=n-1;
	while(l<=r) 
	{
		M=(l+r)>>1;cxy--;
		if(check()) l=M+1;else r=M-1;
	}
	M=r;cxy--;check();
	printf("%lld %lld\n",ansu,ansv);
}
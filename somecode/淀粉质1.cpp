#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define us unsigned 
#define ll long long
#define ull unsigned long long
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=3e9+24;
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
const int M=1e7+10;
const int N=222222;
struct edge
{
	int nxt,to,val;
}e[N<<1];
int head[N],cnt;
int n,q;
int Mx_s[N],siz[N],dis[N],rev[N],vis[N],siz_tr,rt,tot_e;
int ton[M],ans[M];
int ljt[N];
int qs[22222];
inline void init(){memset(vis,0,sizeof(vis));memset(head,-1,sizeof(head));cnt=0;}
inline void add_edge(int u,int v,int d){e[++cnt]=(edge){head[u],v,d};head[u]=cnt;}
void dfs1(int u,int f)
{
	Mx_s[u]=0,siz[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f||vis[v]) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		Mx_s[u]=max(Mx_s[u],siz[v]);
	}
	Mx_s[u]=max(Mx_s[u],siz_tr-siz[u]);
	if(Mx_s[u]<Mx_s[rt]) rt=u;
}
void get_dist(int u,int f)
{
	if(dis[u]>=1e7) return;
	rev[++tot_e]=dis[u];
	for(int i=head[u];i!=-1;i=e[i].nxt) 
	{
		int v=e[i].to;
		if(v==f||vis[v]) continue;
		dis[v]=dis[u]+e[i].val;
		get_dist(v,u);
	}
}	
void calc(int u)
{
	int lenq=0;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		tot_e=0;dis[v]=e[i].val;get_dist(v,u);
		R(j,1,tot_e) R(k,1,q) if(qs[k]>=rev[j]) ans[k]|=ton[qs[k]-rev[j]];
		R(j,1,tot_e) ljt[++lenq]=rev[j],ton[rev[j]]|=1;
	}
	R(i,1,lenq) ton[ljt[i]]=0;
}
void solve(int u)
{
	vis[u]=ton[0]=1;calc(u);
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		Mx_s[rt=0]=inf,siz_tr=siz[v];
		dfs1(v,u);dfs1(rt,0);solve(rt);
	}
}
signed main()
{
	init();
	n=read(),q=read();
	R(i,2,n) 
	{
		int u=read(),v=read(),d=read();
		add_edge(u,v,d),add_edge(v,u,d);
	}
	R(i,1,q) qs[i]=read();
	Mx_s[rt]=siz_tr=n;
	dfs1(1,0);
	dfs1(rt,0);
	solve(rt);
	R(i,1,q) puts(ans[i]?"AYE":"NAY");
}
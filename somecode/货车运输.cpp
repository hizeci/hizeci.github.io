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
const int N=1e5+10;
vector<pii>g[N];
int n,m,q;
struct edge{int u,v,d;inline int operator <(const edge &a)const{return d>a.d;} }e[N];
int fa[N][22],val[N][22],Lg[N];
int dep[N],FFa[N];
inline int find_FFa(int x){return x==FFa[x]?x:find_FFa(FFa[x]);}
void dfs1(int u,int f)
{
	fa[u][0]=f;
	for(auto qwq:g[u]) 
	{
		int v=qwq.fi;
		if(v==f) continue;
		dep[v]=dep[u]+1;
		val[v][0]=qwq.se;
		dfs1(v,u);
	}
}
void init_st(){R(j,1,20)R(i,1,n)fa[i][j]=fa[fa[i][j-1]][j-1],val[i][j]=min(val[i][j-1],val[fa[i][j-1]][j-1]);}
inline int get_LCA(int x,int y)
{
	if(find_FFa(x)!=find_FFa(y)) return -1;
	int res=inf;
	if(dep[x]<dep[y]) Swap(x,y);
	int del=dep[x]-dep[y];
	L(i,0,20) if(del&(1<<i)) ckmin(res,val[x][i]),x=fa[x][i];
	if(x==y) return res;
	L(i,0,20) 
	{
		if(fa[x][i]!=fa[y][i])
		{
			ckmin(res,min(val[x][i],val[y][i]));
			x=fa[x][i];y=fa[y][i];
		}
	}
	return min(res,min(val[x][0],val[y][0]));
}
signed main()
{
	n=read(),m=read();
	int u,v,d,fu,fv;R(i,1,m) u=read(),v=read(),d=read(),e[i]=(edge){u,v,d};
	sort(e+1,e+m+1);
	R(i,1,n) FFa[i]=i;
	R(i,1,m) 
	{
		u=e[i].u,v=e[i].v,d=e[i].d,fu=find_FFa(u),fv=find_FFa(v);
		if(fu!=fv) FFa[fv]=fu,g[u].pb(mkp(v,d)),g[v].pb(mkp(u,d));
	} 
	R(i,1,n) if(!dep[i]) val[i][0]=inf,dfs1(i,-1);
	init_st();
	for(q=read();q--;) u=read(),v=read(),writeln(get_LCA(u,v));
}
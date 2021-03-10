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
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
const int inf=0x7f7f7f7f7f7f7f3f;
const int mod=1e9+7;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
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

//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int N=1e5+10;
struct edge
{
	int nxt,to,val;
}e[N<<1];
int head[N],cnt;
int n,m;
int vis[N],tot_rd;
int dis[N];

inline void init(){
	cnt=0;
	memset(head,-1,sizeof(head));
}
void add_edge(int u,int v,int d){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].val=d;
	head[u]=cnt;
}
int osu[N];
void dfs(int u,int f,int mid)
{
	for(int i=head[u];i!=-1;i=e[i].nxt) {
		int v=e[i].to;if(v==f) continue;
		dfs(v,u,mid);
	}
	int tot=0;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;if(v==f) continue;
		osu[++tot]=(dis[v]+e[i].val);
	}
	sort(osu+1,osu+tot+1);
	L(i,1,tot) {
		if(osu[i]>=mid) tot_rd++,tot--;
		else break;
	}
	R(i,1,tot) if(vis[i]!=u) 
	{
		int pos=lower_bound(osu+i+1,osu+tot+1,mid-osu[i])-osu;
		while(vis[pos]==u&&pos<=tot) pos++;
		if(pos<=tot) vis[i]=vis[pos]=u,tot_rd++;
	}
	dis[u]=0;
	L(i,1,tot) if(vis[i]!=u) {
		dis[u]=osu[i];return;
	}
}
signed main()
{
	init();
	n=read(),m=read();
	R(i,2,n){
		int u=read(),v=read(),d=read();
		add_edge(u,v,d);
		add_edge(v,u,d);
	}
	int l=0,r=(int)1e18,best=(int)1e18;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		tot_rd=0;
		memset(vis,0,sizeof(vis));
		dfs(1,0,mid);
		//printf("%lld\n",tot_rd);
		if(tot_rd>=m) best=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld\n",best);
}
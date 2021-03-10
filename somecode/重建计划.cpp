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
const int inf=0x7f7f7f7f7f7f7f3f;
//const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=3e9+24;
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
/*
考虑先二分答案，把每条边边权 –mid，判断有没有长度在 [l,r] 之间且边权和 >=0 的路径。
考虑点分治，考虑枚举路径的一端，然后在它前面的子树中寻找有没有符合条件的另一端，
这个可以直接单调队列实现。然后枚举完一个子树再把它们加入备选终点即可。
时间复杂度 O(nlog^2n)。
*/
const int N=2e5+10;
int n,L,R;
int siz_tr,rt,tot_e;
int siz[N],Mx_s[N];
int nvr[N],vis[N];
double dis[N],rev[N];
int dep[N];

int que[N],st,ed,lst,ljt[N];
struct edge
{
	int nxt,to;double val;
}e[N<<1];
int head[N],cnt;
int ok,num;
int set_G[N],tot_G;
inline void init(){memset(vis,0,sizeof(vis));memset(head,-1,sizeof(head));cnt=0;}
inline void add_edge(int u,int v,double d){e[++cnt].nxt=head[u];e[cnt].to=v;e[cnt].val=d;head[u]=cnt;}
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
void getallG(int u) {
	dfs1(u,0);
	set_G[++tot_G]=rt;vis[rt]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		Mx_s[rt=0]=inf; 
		siz_tr=siz[v];
		getallG(v);
	}
}
void bfs(int poi)
{
	que[++ed]=poi;
	nvr[poi]=1;
	for(int t=lst+1;t<=ed;t++) 
	{
		int u=que[t];
		for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].to;
			if(vis[v]||nvr[v]) continue;
			dis[v]=dis[u]+e[i].val;
			dep[v]=dep[u]+1;
			que[++ed]=v;nvr[v]=1;
		}
	}
	for(int t=lst+1;t<=ed;t++) nvr[que[t]]=0;
}
void calc()
{
	int s=1,t=0,tmp=lst+1;
	L(i,0,min(R,dep[que[ed]]))
	{
		int ql=i>=L?0:L-i,qr=R-i;
		while(s<=t&&dep[ljt[s]]<ql) s++;
		while(tmp<=ed&&dep[que[tmp]]<ql) ++tmp;
		while(tmp<=ed&&dep[que[tmp]]<=qr)
		{
			while(s<=t&&dis[ljt[t]]+eps<=dis[que[tmp]]) --t;
			ljt[++t]=que[tmp++]; 
		}
		if(s<=t&&rev[i]+dis[ljt[s]]>=-eps) {ok=1;return;}
	}
}
void solve(int u)
{
	int R=set_G[++num];
	vis[R]=1;que[0]=R;
	rev[0]=dis[R]=0.0;dep[R]=ed=0;
	for(int i=head[R];i!=-1;i=e[i].nxt) 
	{
		int v=e[i].to;
		if(vis[v]) continue;
		dis[v]=e[i].val;dep[v]=1;lst=ed;
		bfs(v);calc();
		R(k,lst+1,ed) ckmax(rev[dep[que[k]]],dis[que[k]]);
	}
	R(i,0,ed) rev[dep[que[i]]]=-inf;
	for(int i=head[R];i!=-1;i=e[i].nxt) 
	{
		int v=e[i].to;
		if(vis[v]) continue;
		solve(v);
	}
}
inline int check(double mid)
{
	memset(vis,0,sizeof(vis));
	R(u,1,n) for(int i=head[u];i!=-1;i=e[i].nxt) e[i].val-=mid;
	ok=num=0;
	solve(1);
	R(u,1,n) for(int i=head[u];i!=-1;i=e[i].nxt) e[i].val+=mid;
	return ok;
}
signed main()
{
	init();
	n=read();
	L=read(),R=read();
	R(i,2,n) 
	{
		int u=read(),v=read(),d=read();
		add_edge(u,v,(double)d);rev[i]=-inf;
	}	
	Mx_s[rt=0]=inf; 
	siz_tr=n;
	getallG(1);
	//writeln(tot_G);
	//R(i,1,tot_G) writeln(set_G[i]);
	int cxy=50;
	double l=0.00,r=1000001.00,best=r;
	while(cxy--)
	{
		double mid=(l+r)/2.0;
		if(check(mid)) best=mid,l=mid;
		else r=mid;
	}
	printf("%.3lf",best);
}
/*
4 
2 3 
1 2 1 
1 3 2 
1 4 3
*/
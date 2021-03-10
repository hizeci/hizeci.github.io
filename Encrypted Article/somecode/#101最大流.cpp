//EK
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
//const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const int mod=10007;
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
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int N=1010;
const int M=10050;
int n,m,s,t;
int maxflow;
int head[N],cnt;
int vis[N],pre[N];
int incf[N];
struct edge
{
	int nxt,to;
}e[M<<1];
int c[M];

inline void init(){
	cnt=1;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v,int d){
	e[++cnt].nxt=head[u],e[cnt].to=v,c[cnt]=d,head[u]=cnt;
}
int bfs(){
	memset(vis,0,sizeof(vis));
	deque<int>q;
	q.pb(s),vis[s]=1;
	incf[s]=inf;
	while(q.size()>0) {
		int u=q.front();q.pop_front();
		for(int i=head[u];i!=-1;i=e[i].nxt){
			if(c[i]) {
				int v=e[i].to;
				if(vis[v]) continue;
				incf[v]=min(incf[u],c[i]);
				pre[v]=i;vis[v]=1;
				q.pb(v);
				if(v==t) return 1;
			}
		}
	}
	return 0;
}
void update(){
	int u=t;
	while(u!=s) {
		int i=pre[u];
		c[i]-=incf[t];
		c[i^1]+=incf[t];
		u=e[i^1].to;
	} 
	maxflow+=incf[t];
}
signed main()
{
	init();
	n=read(),m=read(),s=read(),t=read();
	R(i,1,m) {
		int u=read(),v=read(),d=read();
		add_edge(u,v,d),add_edge(v,u,0);
	}
	while(bfs()) update();
	printf("%lld\n",maxflow);
}
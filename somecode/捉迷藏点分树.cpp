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
const int N=4e5+10;
struct inanddelheap
{
	priority_queue<int>whl,del;
	inline void ist(int x){if(x!=-inf)whl.push(x);}
	inline void era(int x){if(x!=-inf)del.push(x);}
	inline int get_Top(){
		while(1)
		{
			if(whl.empty()) return -inf;
			if(del.empty()) return whl.top();
			if(whl.top()==del.top()) whl.pop(),del.pop();
			else return whl.top();
		}
	}
	inline int get_sec() {
		int tmp=get_Top();era(tmp);
		int tmp2=get_Top();ist(tmp);
		return tmp2;
	}
}all,dis_tofa[N],mxdisofch[N];
vector<int>e[N];
int dis[N][22],dep[N],fa[N];
int n,rt,siz_tr;
int siz[N],Mx_s[N];
int vis[N];
int que[N],lst_ans[N],col[N];
/*
int head[N],cnt;
struct edge
{
	int nxt,to;
}e[N];
inline void add_edge(int u,int v){e[++cnt]=(edge){head[u],v};head[u]=cnt;}
*/
void dfs1(int u,int f)
{
	Mx_s[u]=0,siz[u]=1;
	for(int v:e[u]) 
	//for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		//int v=e[i].to;
		if(v==f||vis[v]) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		ckmax(Mx_s[u],siz[v]);
	}
	ckmax(Mx_s[u],siz_tr-siz[u]);
	rt=(Mx_s[u]<Mx_s[rt])?u:rt;
}
void bfs(int G,int dp) 
{
	siz_tr=0;
	int st=1,en=0;que[++en]=G;dis[G][dp]=1;
	for(;st<=en;st++,siz_tr++) 
	{
		int u=que[st];
		for(int v:e[u]) 
		//for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			//int v=e[i].to;
			if(vis[v]) continue;
			if(dis[v][dp]>dis[u][dp]+1) 
				dis[v][dp]=dis[u][dp]+1,que[++en]=v;
		}
	}
}
void build(int u,int f,int dp)
{
	bfs(u,dp);
	//printf("%lld\n",siz_tr);
	Mx_s[rt=0]=inf;
	dfs1(u,-1);
	//printf("rt:%lld\n",rt);
	dfs1(rt,-1);
	//printf("rt:%lld\n",rt);
	dep[rt]=dp;
	if(f) R(i,1,siz_tr) dis_tofa[rt].ist(dis[que[i]][dp]);
	fa[rt]=(f==-1)?0:f;
	vis[rt]=1;int mem=rt;
	for(int v:e[mem]) 
	//for(int i=head[mem];i!=-1;i=e[i].nxt)
	{
	//	int v=e[i].to;
		if(vis[v]) continue;
		build(v,mem,dp+1);
	}
	if(f) mxdisofch[f].ist(dis_tofa[mem].get_Top());
	mxdisofch[mem].ist(0);
	lst_ans[mem]=mxdisofch[mem].get_Top()+mxdisofch[mem].get_sec();
	all.ist(lst_ans[mem]);
}
char opt[111];
signed main()
{
	//memset(head,-1,sizeof(head));

	n=read();
	R(i,0,n+1) R(j,0,20) dis[i][j]=inf;
	int u,v;R(i,2,n) {u=read(),v=read();e[u].pb(v),e[v].pb(u);/*add_edge(u,v),add_edge(v,u);*/}
	build(1,0,0);
	//printf("lst_ans:");R(i,1,n) printf("%lld ",lst_ans[i]);puts("");
	int cntbl=n;
	for(int _=read();_--;)
	{
		scanf("%s",opt+1);
		if(opt[1]=='G') 
		{
			if(cntbl==1) puts("0");
			else if(!cntbl) puts("-1");
			else writeln(all.get_Top());
		}
		else
		{
			int x=read();
			if(col[x]) mxdisofch[x].ist(0),cntbl++;
			else mxdisofch[x].era(0),cntbl--;
			int cur=x;
			while(cur) 
			{
				int aa=mxdisofch[cur].get_Top()+mxdisofch[cur].get_sec();
				if(aa!=lst_ans[cur]) all.era(lst_ans[cur]),all.ist(aa),lst_ans[cur]=aa;
				if(!fa[cur]) break;
				aa=dis_tofa[cur].get_Top();
				if(col[x]) dis_tofa[cur].ist(dis[x][dep[cur]]);
				else dis_tofa[cur].era(dis[x][dep[cur]]);
				int bb=dis_tofa[cur].get_Top();
				if(aa!=bb) mxdisofch[fa[cur]].era(aa),mxdisofch[fa[cur]].ist(bb);
				cur=fa[cur];
			}
			col[x]^=1;
		}
	}
}
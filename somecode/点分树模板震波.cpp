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
const int M=5e6+10;
int n,m,lst_ans;
int a[N];
int dep[N],st[22][N],tim,Lg[N];
int vis[N],Mx_s[N],siz[N],dfn[N],dsiz[N],dfG[N];

struct edge{int nxt,to;}e[N<<1];
int head[N],cnt;
inline void add_edge(int u,int v){e[++cnt]=(edge){head[u],v};head[u]=cnt;}
void dfs1(int u,int f,int dp) 
{
	dep[u]=dp,st[0][++tim]=u,dfn[u]=tim;
	for(int i=head[u];i!=-1;i=e[i].nxt) 
	{
		int v=e[i].to;if(v==f) continue;
		dfs1(v,u,dp+1);st[0][++tim]=u;
	}
}
inline int get_lopoi(int x,int y){return dep[x]<dep[y]?x:y;}
void init_st() 
{
	R(i,2,tim) Lg[i]=Lg[i>>1]+1;
	for(int i=1;(1<<i)<=tim;i++)
	{
		int w=(1<<i);
		R(j,1,tim-w+1) st[i][j]=get_lopoi(st[i-1][j],st[i-1][j+(w>>1)]);
	}
}
inline int get_LCA(int x,int y)
{
	x=dfn[x],y=dfn[y];
	if(x>y) Swap(x,y);
	int i=Lg[y-x+1],w=(1<<i);
	return get_lopoi(st[i][x],st[i][y-w+1]);
}
inline int get_dis(int x,int y) {return dep[x]+dep[y]-2*dep[get_LCA(x,y)];}
int dfs2(int u,int f,int siz_tr) 
{
	int rt=0;
	Mx_s[u]=0,siz[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt) 
	{
		int v=e[i].to;
		if(v==f||vis[v]) continue;
		int rtv=dfs2(v,u,siz_tr);
		siz[u]+=siz[v];
		ckmax(Mx_s[u],siz[v]);		
		rt=(Mx_s[rt]<Mx_s[rtv]||!rt)?rt:rtv;
	}
	ckmax(Mx_s[u],siz_tr-siz[u]);
	rt=(Mx_s[u]<Mx_s[rt]||!rt)?u:rt;
	return rt;
}
void buildtr(int rt,int siz_tr) 
{
	vis[rt]=1;dsiz[rt]=siz_tr;
	for(int i=head[rt];i!=-1;i=e[i].nxt) 
	{
		int v=e[i].to;
		if(vis[v]) continue;
		int vsiz=(siz[v]<siz[rt])?siz[v]:siz_tr-siz[rt];
		int rtv=dfs2(v,-1,vsiz);rtv=dfs2(rtv,-1,vsiz);
		dfG[rtv]=rt;
		buildtr(rtv,vsiz);
	}
}
struct chairman
{
	int Rt[N],Ls[M],Rs[M],val[M],tot_seg;
	void modify(int pos,int l,int r,int &x,int k) 
	{
		if(!x) x=++tot_seg;
		if(l==r){val[x]+=k;return;}
		int mid=(l+r)>>1;
		if(pos<=mid) modify(pos,l,mid,Ls[x],k);
		else modify(pos,mid+1,r,Rs[x],k);
		val[x]=val[Ls[x]]+val[Rs[x]];
	}
	int query(int L,int R,int l,int r,int x) {
		if(!x) return 0;
		if(L<=l&&r<=R) return val[x];
		int mid=(l+r)>>1,ret=0;
		if(L<=mid) ret+=query(L,R,l,mid,Ls[x]);
		if(mid<R)  ret+=query(L,R,mid+1,r,Rs[x]);
		return ret;
	}
}T1,T2;
void mmodify(int u,int k)
{	
	int now=u;
	while(now)
	{
		T1.modify(get_dis(now,u),0,n-1,T1.Rt[now],k);
		if(dfG[now]) T2.modify(get_dis(dfG[now],u),0,n-1,T2.Rt[now],k);
		now=dfG[now];
	}
}
int qquery(int u,int k)
{
	int now=u,pre=0,ret=0;
	while(now) 
	{
		if(get_dis(now,u)>k){pre=now;now=dfG[now];continue;}
		ret+=T1.query(0,k-get_dis(now,u),0,n-1,T1.Rt[now]);
		if(pre) ret-=T2.query(0,k-get_dis(now,u),0,n-1,T2.Rt[now]);
		pre=now;now=dfG[now];
	}
	return ret;
}
inline void init_all(){dfs1(1,-1,0);init_st();Mx_s[0]=inf;int rt=dfs2(1,-1,n);rt=dfs2(rt,-1,n);buildtr(rt,n);R(i,1,n)mmodify(i,a[i]);}
signed main()
{
	memset(head,-1,sizeof(head));
	n=read(),m=read();
	R(i,1,n) a[i]=read();
	int u,v;R(i,2,n) u=read(),v=read(),add_edge(u,v),add_edge(v,u);
	init_all();
	for(;m--;)
	{
		int opt=read(),x=read()^lst_ans,y=read()^lst_ans;
		if(!opt) lst_ans=qquery(x,y),writeln(lst_ans);
		if(opt) mmodify(x,y-a[x]),a[x]=y;
	}
	return 0;
}
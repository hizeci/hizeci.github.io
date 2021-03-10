//今晚去吃烤肉喝咖啡吧！
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
//#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
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
const int N=1e6+10;
vector<int>e[N];
int dep[N],hson[N],siz[N],fa[N],htop[N];
int stt[N],tim;
int col[N],a[N];
int n,m;
struct segmentree
{
	int val[N<<2],lazy[N<<2];
	inline void push_up(int x,int mid){
		val[x]=val[x<<1]+val[x<<1|1];
		if(col[mid]==col[mid+1]) --val[x];
	}
	inline void push_down(int x,int mid){
		if(!lazy[x]) return;
		lazy[x<<1]=lazy[x<<1|1]=col[mid]=col[mid+1]=lazy[x];
		val[x<<1]=val[x<<1|1]=1;
		lazy[x]=0;
	}
	void build(int l,int r,int x){
		if(l==r) {
			val[x]=1;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		push_up(x,mid);
	}
	void modify(int L,int R,int l,int r,int x,int c)
	{
		if(L<=l&&r<=R) {
			val[x]=1;
			col[l]=col[r]=lazy[x]=c;
			return;
		}
		int mid=(l+r)>>1;
		push_down(x,mid);
		if(L<=mid) modify(L,R,l,mid,x<<1,c);
		if(mid<R)  modify(L,R,mid+1,r,x<<1|1,c);
		push_up(x,mid);
	}
	int query(int L,int R,int l,int r,int x){
		if(L<=l&&r<=R) return val[x];
		int mid=(l+r)>>1,ret=0;
		push_down(x,mid);
		if(L<=mid) ret+=query(L,R,l,mid,x<<1);
		if(mid<R)  ret+=query(L,R,mid+1,r,x<<1|1);
		if(L<=mid&&mid<R&&col[mid]==col[mid+1]) --ret;
		return ret;
	}
}st;
void dfs1(int u,int f){
	dep[u]=dep[f]+1;
	siz[u]=1;
	fa[u]=f;
	for(int v:e[u])
	{
		if(v==f) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[hson[u]]<siz[v]) hson[u]=v;
	}
}
void dfs2(int u,int topf){
	htop[u]=topf;
	stt[u]=++tim;
	col[tim]=a[u];
	if(!hson[u]) return;
	dfs2(hson[u],topf);
	for(int v:e[u])
	{
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
void modify_col(int u,int v,int c)
{
	while(htop[u]!=htop[v])
	{
		if(dep[htop[u]]<dep[htop[v]]) Swap(u,v);
		st.modify(stt[htop[u]],stt[u],1,n,1,c);
		u=fa[htop[u]];
	}
	if(stt[u]>stt[v]) Swap(u,v);
	st.modify(stt[u],stt[v],1,n,1,c);
}
int query_sum(int u,int v)
{
	int tmpu=u,tmpv=v,res=0;
	while(htop[u]!=htop[v])
	{
		if(dep[htop[u]]<dep[htop[v]]) Swap(u,v);
		res+=st.query(stt[htop[u]],stt[u],1,n,1);
		u=fa[htop[u]];
	}
	if(stt[u]>stt[v]) Swap(u,v);
	res+=st.query(stt[u],stt[v],1,n,1);
	u=tmpu,v=tmpv;
	while(htop[u]!=htop[v])
	{
		if(dep[htop[u]]<dep[htop[v]]) Swap(u,v);
		if(col[stt[htop[u]]]==col[stt[fa[htop[u]]]]) res--;
		u=fa[htop[u]];
	}
	return res;
}
signed main()
{
	n=read(),m=read();
	R(i,1,n) a[i]=read();
	R(i,2,n) {
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs1(1,0);
	dfs2(1,1);
	st.build(1,n,1);
	R(i,1,m){
		char opt[100];
		scanf("%s",opt+1);
		int u=read(),v=read();
		if(opt[1]=='C') {
			int c=read();
			modify_col(u,v,c);
		}
		else printf("%d\n",query_sum(u,v));
	}
}
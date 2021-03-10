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
//const int inf=0x7f7f7f7f7f7f7f3f;
//const int inf=0x7f7f7f7f;
const int inf=123456789123456789ll;
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

//#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
/*
ans=min{a*(dis[i]-dis[s])+b} i∈{s...t};
令x为lca(s,t);
那么s到x就可以表示为
y=-a\times dis[i]+a\times dis[s]+b;
t到x
y=a\times (dis[i]+dis[s]-2 \times dis[x])+b;
*/
const int N=1e6+10;
int n,q;
int dis[N],siz[N],hson[N],htop[N],dep[N],fa[N];
int rec[N],tim,a_n[N];
struct edge
{
	int nxt,to,val;
}e[N<<1];
int head[N],cnt_eg;
struct line
{
	int k,b;
}p[N];
int tot_seg;
int s[N];
inline void init(){
	memset(head,-1,sizeof(head));cnt_eg=0;
}
inline void add_edge(int u,int v,int d){
	e[++cnt_eg].nxt=head[u],e[cnt_eg].to=v,e[cnt_eg].val=d,head[u]=cnt_eg;
}
inline int calc(int id,int x){
	return p[id].k*dis[a_n[x]]+p[id].b;
}
inline void add_seg(int k,int b){
	++tot_seg;
	p[tot_seg].k=k,p[tot_seg].b=b;
}
void dfs1(int u,int f){
	dep[u]=dep[f]+1;
	siz[u]=1;
	fa[u]=f;
	for(int i=head[u];i!=-1;i=e[i].nxt)  {
		int v=e[i].to;
		if(v==f) continue;		
		dis[v]=dis[u]+e[i].val;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[hson[u]]) hson[u]=v;
	}
}
void dfs2(int u,int topf){
	htop[u]=topf;
	rec[u]=++tim;
	a_n[tim]=u;
	if(!hson[u]) return;
	dfs2(hson[u],topf);
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==hson[u]||v==fa[u]) continue;
		dfs2(v,v);
	}
}
void print() {
	R(i,1,10) printf("%lld\n",s[i]);
}
struct segmentree
{
	int minn[N];
	inline void push_up(int x){
		minn[x]=min(minn[x],min(minn[x<<1],minn[x<<1|1]));
	}
	void build(int l,int r,int x) {
		s[x]=1,minn[x]=inf;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	}
	void modify(int L,int R,int l,int r,int x,int u){
		int mid=(l+r)>>1,v=s[x];
		if(L<=l&&r<=R){
			if(calc(u,l)<=calc(v,l)&&calc(u,r)<=calc(v,r)) {
				s[x]=u;
				minn[x]=min(minn[x],min(calc(u,l),calc(u,r)));
				return;
			}
			if(calc(u,l)>=calc(v,l)&&calc(u,r)>=calc(v,r)) return;		
			int resu=calc(u,mid),resv=calc(v,mid);
			if(p[u].k<p[v].k) 
			{
				if(calc(u,mid)<=calc(v,mid)) {
					s[x]=u;modify(L,R,l,mid,x<<1,v);
				}
				else modify(L,R,mid+1,r,x<<1|1,u);
			}
			else if(p[u].k>p[v].k)
			{
				if(calc(u,mid)<=calc(v,mid)) {
					s[x]=u;modify(L,R,mid+1,r,x<<1|1,v);
				}
				else modify(L,R,l,mid,x<<1,u);
			}
			else {
				if(p[u].b<p[v].b) s[x]=u;
			}
			minn[x]=min(minn[x],min(calc(u,l),calc(u,r)));
			push_up(x);
			return;
		}
		if(L<=mid) modify(L,R,l,mid,x<<1,u);
		if(mid<R)  modify(L,R,mid+1,r,x<<1|1,u);
		push_up(x);
		
		/*
		int mid=(l+r)>>1,v=s[x];
		if(L<=l&&r<=R) {
			if(calc(u,l)<=calc(v,l)&&calc(u,r)<=calc(v,r)) {
				s[x]=u;
				minn[x]=min(minn[x],min(calc(u,l),calc(u,r)));
				return;
			}
			if(calc(u,l)>=calc(v,l)&&calc(u,r)>=calc(v,r)) return;
			if(p[u].k<p[v].k) 
			{
				if(calc(u,mid)<=calc(v,mid)) {
					s[x]=u;modify(L,R,l,mid,x<<1,v);
				}
				else modify(L,R,mid+1,r,x<<1|1,u);
			}
			else 
			{
				if(calc(u,mid)<=calc(v,mid)) {
					s[x]=u;modify(L,R,mid+1,r,x<<1|1,v);
				}
				else modify(L,R,l,mid,x<<1,u);
			}
			minn[x]=min(minn[x],min(calc(u,l),calc(u,r)));
			push_up(x);
			return;
		}
		if(L<=mid) modify(L,R,l,mid,x<<1,u);
		if(mid<R)  modify(L,R,mid+1,r,x<<1|1,u);
		push_up(x);
		*/
	}
	int query_min(int L,int R,int l,int r,int x){
		if(L<=l&&r<=R) return minn[x];
		int mid=(l+r)>>1,ret=inf;
		if(p[s[x]].b!=inf) ret=min(calc(s[x],max(l,L)),calc(s[x],min(r,R)));
		if(L<=mid) ret=min(ret,query_min(L,R,l,mid,x<<1));
		if(mid<R)  ret=min(ret,query_min(L,R,mid+1,r,x<<1|1));
		return ret;
	}
}st;
inline int get_lca(int x,int y){
	while(htop[x]!=htop[y]){
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		x=fa[htop[x]];
	}
	return dep[x]<dep[y]?x:y;
}
inline void mmodify(int x,int y){
	while(htop[x]!=htop[y]){
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		st.modify(rec[htop[x]],rec[x],1,n,1,tot_seg);
		x=fa[htop[x]];
	}
	if(dep[x]>dep[y]) Swap(x,y);
	st.modify(rec[x],rec[y],1,n,1,tot_seg);
}
inline int qquery_min(int x,int y){
	int ret=inf;
	while(htop[x]!=htop[y]) {
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		ret=min(ret,st.query_min(rec[htop[x]],rec[x],1,n,1));
		x=fa[htop[x]];
	}
	if(dep[x]>dep[y]) Swap(x,y);
	ret=min(ret,st.query_min(rec[x],rec[y],1,n,1));
	return ret;
}
signed main()
{
	//freopen("game.out","w",stdout);
	init();
	n=read(),q=read();
	R(i,2,n) {
		int u=read(),v=read(),d=read();
		add_edge(u,v,d),add_edge(v,u,d);
	}
	dfs1(1,0);
	dfs2(1,1);
	//printf("%lld\n",get_lca(2,3));
	add_seg(0,inf);
	st.build(1,n,1);
	R(i,1,q) {
		//for(int i=1;i<=n;i++) if(s[i]!=1) printf("%lld %lld\n",i,s[i]);
		int opt=read(),u=read(),v=read();
		if(opt==1) {
			int k=read(),b=read(),l_a=get_lca(u,v);
			add_seg(-k,k*dis[u]+b);
			mmodify(u,l_a);
			add_seg(k,k*(dis[u]-(dis[l_a]*2))+b);
			mmodify(v,l_a);
		} 
		if(opt==2) printf("%lld\n",qquery_min(u,v));
	}
}
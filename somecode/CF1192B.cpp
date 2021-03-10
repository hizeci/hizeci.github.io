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
考虑树上两个点集S,T,设d(S)表示S点集中距离最远的某两个点,S\cup T 中必然存在两个点，使得其距离最远
且两端均在d(S)\cup d(V)中。也就是说在合并两个点集并直径时,只需要讨论o(1)种可能的直径
在dfs序上建一棵线段树。线段树的每个区间[l,r],维护dfs序在[l,r]内这些点组成的点集的直径
一次修改只会修改[beg[x],en[x]]相交且不包含的区间，容易发现这样的区间只有O(log n)个,暴力更新即可.
即所经过的所有非终点节点
*/
int n,q,WWW,delt;
const int N=5e5+55;
struct egd
{
	int u,v,d;
}eg[N];
std::vector<pii>e[N];
int beg[N],en[N],dep[N],dis[N],tim;
int hson[N],siz[N],fa[N],htop[N],rbeg[N];

void dfs1(int u,int f){
	fa[u]=f;
	dep[u]=dep[f]+1;
	siz[u]=1;
	beg[u]=++tim;
	for(auto qwq:e[u]) {
		int v=qwq.fi,d=qwq.se;
		if(v==f) continue;
		dis[v]=dis[u]+d;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[hson[u]]<siz[v]) hson[u]=v;
	}
	en[u]=tim;
}
void dfs2(int u,int topf){
	htop[u]=topf;
	if(!hson[u]) return ;
	dfs2(hson[u],topf);
	for(auto qwq:e[u]) {
		int v=qwq.fi;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
inline int get_lca(int x,int y){
	while(htop[x]!=htop[y])
	{
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		x=fa[htop[x]];
	}
	return (dep[x]<dep[y])?x:y;
}
struct segmentree
{
	struct trnode
	{
		int u,v,len;
	}val[N];
	int dval[N];
	int query_dis(int pos,int l,int r,int x){
		if(l==r) return dval[x];
		int mid=(l+r)>>1,ret=0;
		if(pos<=mid) ret+=query_dis(pos,l,mid,x<<1);
		else ret+=query_dis(pos,mid+1,r,x<<1|1);
		return ret+dval[x];
	}
	int query_dist(int x,int y){
		return query_dis(beg[x],1,n,1)+query_dis(beg[y],1,n,1)-2*query_dis(beg[get_lca(x,y)],1,n,1);
	}
	inline void updt(int aa,int bb,int a,int b,int x){
		int tmp=aa+bb-query_dis(beg[get_lca(a,b)],1,n,1)*2;
		if(tmp>val[x].len) val[x].len=tmp,val[x].u=a,val[x].v=b;
	}
	inline void push_up(int x){
		val[x].len=-inf;
		int lensa=query_dis(beg[val[x<<1].u],1,n,1),lensb=query_dis(beg[val[x<<1].v],1,n,1);
		int lenta=query_dis(beg[val[x<<1|1].u],1,n,1),lentb=query_dis(beg[val[x<<1|1].v],1,n,1);
		updt(lensa,lensb,val[x<<1].u,val[x<<1].v,x);
		updt(lenta,lentb,val[x<<1|1].u,val[x<<1|1].v,x);
		updt(lensa,lenta,val[x<<1].u,val[x<<1|1].u,x);
		updt(lensb,lentb,val[x<<1].v,val[x<<1|1].v,x);
		updt(lensa,lentb,val[x<<1].u,val[x<<1|1].v,x);
		updt(lensb,lenta,val[x<<1].v,val[x<<1|1].u,x);
	}	
	void build(int l,int r,int x){
		if(l==r) {
			dval[x]=dis[rbeg[l]];
			val[x].u=val[x].v=rbeg[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		push_up(x);
	}
	void modify(int L,int R,int l,int r,int x,int k){
		if(L<=l&&r<=R) { 
			dval[x]+=k;
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid) modify(L,R,l,mid,x<<1,k);
		if(mid<R) modify(L,R,mid+1,r,x<<1|1,k);
	}
	void update(int L,int R,int l,int r,int x){
		if(L<=l&&r<=R) return;
		int mid=(l+r)>>1;
		if(L<=mid) update(L,R,l,mid,x<<1);
		if(mid<R)  update(L,R,mid+1,r,x<<1|1);
		push_up(x);
	}
	void print(){
		R(i,1,20) printf("val[%lld]:u:%lld v:%lld len:%lld dval:%lld\n",i,val[i].u,val[i].v,val[i].len,dval[i]);puts("");
	}
}st;
signed main()
{
	n=read(),q=read(),WWW=read();
	FR(i,1,n) {
		int u=read(),v=read(),d=read();
		eg[i]=(egd){u,v,d};
		e[u].pb(mkp(v,d)),e[v].pb(mkp(u,d));
	}
	dfs1(1,0);
	dfs2(1,1);
	//printf("%lld\n",get_lca(3,6));
	R(i,1,n) rbeg[beg[i]]=i;
	FR(i,1,n) if(fa[eg[i].v]==eg[i].u) Swap(eg[i].u,eg[i].v);
	st.build(1,n,1);
	//st.print();
	int lst_ans=0;
	R(i,1,q) 
	{
		int d=read(),e=read();
		d=(lst_ans+d)%(n-1)+1;
		e=(lst_ans+e)%WWW;
		//printf("e:%lld d:%lld\n",e,d);
		delt=e-eg[d].d;
		eg[d].d=e;
		st.modify(beg[eg[d].u],en[eg[d].u],1,n,1,delt);

		st.update(beg[eg[d].u],en[eg[d].u],1,n,1);
		lst_ans=st.val[1].len;
		printf("%lld\n",lst_ans);
	}
}
/*
10 10 10000
1 9 1241
5 6 1630
10 5 1630
2 6 853
10 1 511
5 3 760
8 3 1076
4 10 1483
7 10 40
8 2051
5 6294
5 4168
7 1861
0 5244
6 5156
3 3001
8 5267
5 3102
8 3623
*/
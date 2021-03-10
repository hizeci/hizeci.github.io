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
const int mod=998244353;
//const int mod=10007;
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
const int N=55555;
/*
考虑K=1的情况。由于dep[lca(x,y)]=|{z,z是x和y的祖先}|
按x从小到大离线处理询问,没当x向右一个时。
将x的祖先权值都+1。
然后询问就相当于求y的所有祖先的权值之和，树剖+线段树即可

如果k>1，那么权值不是+1，而是对于深度为i的点，权值加上i^k-(i-1)^k
*/
int n,q,k;
int dep[N],siz[N],fa[N];
int hson[N],htop[N];
int beg[N],tim;
int wei[N];
int head[N],cnt,pos[N];
std::vector<int>e[N];
std::vector<pii>qs[N];
int ans[N];

void dfs1(int u,int f){
	dep[u]=dep[f]+1;
	siz[u]=1;
	fa[u]=f;
	for(int v:e[u]) {
		if(v==f) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[hson[u]]<siz[v]) hson[u]=v;
	}
}
void dfs2(int u,int topf){
	beg[u]=++tim;
	htop[u]=topf;
	pos[u]=cnt;
	wei[beg[u]]=(fpow(dep[u],k)-fpow(dep[u]-1,k))%mod;;
	if(!hson[u]) return ;
	dfs2(hson[u],topf);
	for(int v:e[u]) {
		if(v==hson[u]||v==fa[u]) continue;
		head[++cnt]=v;
		dfs2(v,v);
	}
}
//所以现在问题变成了：给定一个序列，每一个点有两个权值(a,b)，每一个点的点权为a*b，支持a权值区间加1和区间查询
//因为b不会改变，所以我们考虑线段树
//把线段树的每一个节点新弄一个权值，为\sum_{l≤i≤r} b,每次更新区间的时候用这个权值\times sum即可
int val[N<<2],sum[N<<2],lazy[N<<2];
inline void push_up1(int x){
	sum[x]=(sum[x<<1]+sum[x<<1|1])%mod;
}
//源莱氏佐田
inline void push_up2(int x){
	val[x]=(val[x<<1]+val[x<<1|1])%mod;
}
inline void upd(int x,int k){
	val[x]=(1ll*k*sum[x]%mod+val[x])%mod;
	lazy[x]=(lazy[x]+k)%mod;
}
void push_down(int x){
	if(lazy[x]){
		upd(x<<1,lazy[x]);
		upd(x<<1|1,lazy[x]);
		lazy[x]=0;
	}
}
void build(int l,int r,int x){
	if(l==r) {
		sum[x]=wei[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	push_up1(x);
}
void modify(int L,int R,int l,int r,int x,int k){
	if(L<=l&&r<=R) {
		upd(x,k);
		return;
	}
	int mid=(l+r)>>1;
	push_down(x);
	if(L<=mid) modify(L,R,l,mid,x<<1,k);
	if(mid<R)  modify(L,R,mid+1,r,x<<1|1,k);
	push_up2(x);
}
int query(int L,int R,int l,int r,int x){
	if(L<=l&&r<=R) return val[x];
	int mid=(l+r)>>1,ret=0;
	push_down(x);
	if(L<=mid) ret=(ret+query(L,R,l,mid,x<<1))%mod;
	if(mid<R)  ret=(ret+query(L,R,mid+1,r,x<<1|1))%mod;
	return ret;
}
void mmodify(int x){
	/*
	while(x){
		int t=htop[x];
		modify(beg[t],beg[x],1,n,1,1);
		x=fa[t];
	}
	*/
	while(x){
		int t=head[pos[x]];
		modify(beg[t],beg[x],1,n,1,1);
		x=fa[t];
	}
	
}
int qquery(int x){
	/*
	
	while(x){
		int t=htop[x];
		ret=(ret+query(beg[t],beg[x],1,n,1))%mod;
		x=fa[t];
	}
	return ret;
	*/
int ret=0;
	while(x){
		int t=head[pos[x]];
		ret=(ret+query(beg[t],beg[x],1,n,1))%mod;
		x=fa[t];
	}
	return ret;
	
}
void print() {
    puts("-------------------------------------------qwq---------------------------------");
    test
    R(i,1,20) printf("pos:%d beg:%d head:%d fa:%d val:%d sum:%d lazy:%d\n",pos[i],beg[i],head[i],fa[i],val[i],sum[i],lazy[i]);
    puts("-------------------------------------------qwq----------------------------------");
    tset;
}
signed main()
{
	n=read(),q=read(),k=read();
	R(i,2,n) {
		int x=read();
		e[x].pb(i);
	}
	dfs1(1,0);
	cnt=head[1]=1;
	dfs2(1,1);
	//R(i,1,20) printf("%lld ",beg[i]);puts("");
	build(1,n,1);
	R(i,1,q) {
		int x=read(),y=read();
		qs[x].pb(mkp(y,i));
	}
	R(i,1,n) {
		//test
		//print();
		mmodify(i);
		for(auto qwq:qs[i]) {
			//printf("%lld %lld\n",qwq.fi,qwq.se);
			ans[qwq.se]=qquery(qwq.fi);
		}
	}
	R(i,1,q) printf("%lld\n",(ans[i]+mod)%mod);
}

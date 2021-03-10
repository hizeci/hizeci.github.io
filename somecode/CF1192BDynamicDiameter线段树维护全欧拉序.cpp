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
线段树维护全dfs序
全dfs序为，仍然dfs遍历一棵树，每次访问到一个节点就把它记到序列末端
(下面称这时序列的长度为该的Beg,序列称为dfn)
同时每当一个节点的子树的访问正式结束，也把它的父亲记到序列末端

考虑节点u,v不妨设beg[u]<beg[v],和它们的LCA
显然u,v必然分属lca的两个子树，于是在访问v之前,u所在子树的访问一定已经结束,所以lca必定存在于(beg[u]和beg[v])之间
显然，访问v时，对lca子树访问不可能结束，于是(beg[u],beg[v])之间不可能有比lca更浅的节点
lcalca的深度是[beg[u],beg[v]]这一段区间里所有节点的深度的下界，而且它一定存在。所以它就是这段区间里的深度最小值。
所以我们就可以用线段树在全dfs序上维护一个dep的最小值。
那么具体如何得出答案？我们需要维护：
区间深度最大值，称作W（作为dep[l]和dep[r]）
区间深度最小值，称作M（作为dep[lca]）
dep[l]-2dep[lca],称作LM。通过左右区间的LM，左区间的L和右区间的M得到。
MR，LMR类似（从名字就可以知道这两个是什么东西了）。
LMR就是我们要的答案。
*/
const int N=1e6+10;
int n,q,WWW;
int egval[N];
int dis[N],beg[N],en[N],dfn[N],tim;
int head[N],cnt_eg;
int pos[N];
struct edge
{
	int to,nxt,val;
}e[N<<1];
inline void init(){
	memset(head,-1,sizeof(head));cnt_eg=0;
}
inline add_edge(int u,int v,int d){
	e[++cnt_eg].nxt=head[u],e[cnt_eg].to=v,e[cnt_eg].val=d,head[u]=cnt_eg;
}
void dfs(int u,int f){
	dfn[++tim]=u,beg[u]=tim;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;if(v==f) continue;
		pos[(i+1)>>1]=v,dis[v]=dis[u]+e[i].val;
		dfs(v,u);
		dfn[++tim]=u;
	}
	en[u]=tim;
}
int W[N],M[N],LM[N],MR[N],LMR[N],lazy_add[N];
void push_up(int x){
	W[x]=max(W[x<<1],W[x<<1|1]);
	M[x]=max(M[x<<1],M[x<<1|1]);
	LM[x]=max(max(LM[x<<1],LM[x<<1|1]),W[x<<1]+M[x<<1|1]);
	MR[x]=max(max(MR[x<<1],MR[x<<1|1]),W[x<<1|1]+M[x<<1]);
	LMR[x]=max(max(LMR[x<<1],LMR[x<<1|1]),max(LM[x<<1]+W[x<<1|1],MR[x<<1|1]+W[x<<1]));
}
inline void updt_add(int l,int r,int x,int k){
	W[x]+=k,M[x]-=2*k,LM[x]-=k,MR[x]-=k,lazy_add[x]+=k;
}
void push_down(int l,int r,int x){
	int mid=(l+r)>>1;
	updt_add(l,mid,x<<1,lazy_add[x]),updt_add(mid+1,r,x<<1|1,lazy_add[x]);
	lazy_add[x]=0;
}
void build(int l,int r,int x){
	if(l==r) {
		W[x]=dis[dfn[l]],M[x]=-2*dis[dfn[l]];
		LM[x]=MR[x]=-dis[dfn[l]],LMR[x]=0;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	push_up(x);
}
void update(int L,int R,int l,int r,int x,int k){
	if(L<=l&&r<=R) {
		updt_add(l,r,x,k);
		return;
	}
	push_down(l,r,x);
	int mid=(l+r)>>1;
	if(L<=mid) update(L,R,l,mid,x<<1,k);
	if(mid<R) update(L,R,mid+1,r,x<<1|1,k);
	push_up(x);
}
void print(){
	R(i,1,10) printf("W:%lld M:%lld LM:%lld MR:%lld LMR:%lld lazy:%lld\n",W[i],M[i],LM[i],MR[i],LMR[i],lazy_add[i]);
}
int lst_ans;
signed main()
{
	init();
	n=read(),q=read(),WWW=read();
	FR(i,1,n) {
		int u=read(),v=read();
		egval[i]=read();
		add_edge(u,v,egval[i]),add_edge(v,u,egval[i]);
	}
	dfs(1,0);
	build(1,tim,1);
	//printf("tim:%lld\n",tim);R(i,1,20) printf("%lld ",dfn[i]);puts("");
	R(i,1,q) {
		int d=read(),e=read();
		d=(d+lst_ans%(n-1))%(n-1)+1,e=(e+lst_ans%WWW)%WWW;
		//printf("%lld %lld\n",d,e);
		//printf("pos[d]:%lld beg[pos[d]]:%lld en[pos[d]]:%lld \n",pos[d],beg[pos[d]],en[pos[d]]);
		update(beg[pos[d]],en[pos[d]],1,tim,1,e-egval[d]);
		egval[d]=e,lst_ans=LMR[1];		
		//print();

		printf("%lld\n",lst_ans);
	}
}
/*
4 3 2000
1 2 100
2 3 1000
2 4 1000
2 1030
1 1020
1 890
*/
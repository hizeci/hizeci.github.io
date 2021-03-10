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
const int inf=1023456789000000;
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
树上两点距离可以表示为dep[u]+dep[v]-2*dep[lca(u,v)]
因为已经确定u,所以只需最小化dep[v]-2*dep[lca(u,v)];
在access后,能作为lca的点一定在与u相同的splay中,于是只需维护出对于每一个splay上的节点
找到最小的dep[v]-2*dep[x],(x是splay上的节点，v是x虚儿子子树内的点)。
需要维护的dep[v]是该点虚儿子子树内的最小值,其实就是我们需要维护子树信息。直接套用维护子树信息的方法即可
具体的，每次access时，更新新的子树信息(实->虚,虚->实)
然后修改的时候将修改点splay到根，该点不会是任何点的儿子，直接修改即可
查询时将查询点splay到根，先算出所有虚儿子的答案，再找splay中的min
*/
const int N=1e6+10;
std::vector<int>e[N];
int n,q;
struct inanddelheap
{	
	priority_queue<int,vector<int>,greater<int> >whl,del;
	inline void ins(int x) {if(x!=inf) whl.push(x);}
	inline void era(int x) {if(x!=inf) del.push(x);}
	inline int query_Top() {
		while(1){
			if((int)whl.size()==0) return inf;
			if((int)del.size()==0) return whl.top();
			if(whl.top()==del.top()) whl.pop(),del.pop();
			else return whl.top();
		} 
	}
}all[N];
int son[N][2],fa[N],minn1[N],minn2[N],dep[N],tag[N],val[N];
int vrrv[N];

void get_dep(int u,int f){
	dep[u]=dep[f]+1,fa[u]=f;//???
	for(int v:e[u]) if(v!=f) {
		get_dep(v,u);
	}
}
inline void clear(int x){
	son[x][0]=son[x][1]=fa[x]=minn1[x]=minn2[x]=tag[x]=val[x]=0;
}
inline int get(int x){
	return x==son[fa[x]][1];
}
inline int isnotroot(int x){
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
inline void push_up(int x){
	//clear(0);
	if(x){
		minn1[x]=val[x],minn2[x]=all[x].query_Top();
		minn1[x]=min(minn1[x],min(minn1[son[x][0]],minn1[son[x][1]]));
		minn2[x]=min(minn2[x],min(minn2[son[x][0]],minn2[son[x][1]]));
	}
}
/*
inline void push_flp(int x){
	Swap(son[x][0],son[x][1]),tag[x]^=1;
}
inline void push_down(int x){
	if(tag[x]) {
		if(son[x][0]) push_flp(son[x][0]);
		if(son[x][1]) push_flp(son[x][1]);
		tag[x]=0;
	}
}
void update(int x){
	if(isnotroot(x)) update(fa[x]);
	push_down(x);
}
*/
void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	if(isnotroot(f)) son[gf][get(f)]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x,fa[x]=gf;
	push_up(f),push_up(x); 
}
inline void splay(int x){
	//update(x);
	for(int f;f=fa[x],isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
	//push_up(x);
}
inline int access(int x){
	int y;
	for(y=0;x;y=x,x=fa[x]) {
		splay(x);
		if(min(all[son[x][1]].query_Top(),minn2[son[x][1]])<inf/10) all[x].ins(min(all[son[x][1]].query_Top(),minn2[son[x][1]]));
		son[x][1]=y;
		if(min(all[son[x][1]].query_Top(),minn2[son[x][1]])<inf/10) all[x].era(min(all[son[x][1]].query_Top(),minn2[son[x][1]]));
		val[x]=all[x].query_Top()-2*dep[x];
		push_up(x);
	}
	return y;
}
inline void make_root(int x){
	access(x),splay(x);//,push_flp(x);
}
/*
inline int find_root(int x){
	access(x),splay(x);
	while(son[x][0]) push_down(x),x=son[x][0];
	splay(x);
	return x;
}
inline void spilt(int x,int y){
	make_root(x),access(y),splay(y);
}
*/
signed main()
{
	//cout<<inf;
	n=read();
	FR(i,1,n) {
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	R(i,0,n) minn1[i]=minn2[i]=val[i]=inf,all[i].ins(inf);
	get_dep(1,0);
	q=read();
	R(i,1,q) 
	{
		int opt=read(),u=read();
		make_root(u);
		if(!opt)
		{
			if(!vrrv[u])
				all[u].ins(dep[u]),val[u]=-dep[u],push_up(u);
			else
				all[u].era(all[u].query_Top()),val[u]=all[u].query_Top()-2*dep[u],push_up(u);
			vrrv[u]^=1;
		}
		if(opt) printf("%lld\n",minn1[u]>inf/10?-1:dep[u]+minn1[u]);
	}
}
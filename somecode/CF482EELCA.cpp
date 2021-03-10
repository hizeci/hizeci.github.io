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
const int N=1e6+10;
int n,q;
int Ffa[N],a[N],siz[N];
int res;
vector<int>e[N];
char opt[111];
/*
考虑一个点对答案的贡献为(siz_{i}^2-\sum siz_{son}^2)\times s[i];
由于每一次1操作会使一条链的子树大小增加x,一条链的子树大小减少x.
考虑维护每个点的子树大小，虚子树大小，\sum 虚子树大小\times 权值,(siz_{i}^2-\sum siz_{son}^2)
不妨只考虑一条链的子树大小增加a怎么做，考虑对于先把这条链全部转换为实边，然后对于一个点i(siz_{i}^2-\sum siz_{son}^2)
的增量大小为2*a*虚子树大小 ->(siz_i+a)^2-siz_i^2-((siz_{hson}+a)^2-siz_{hson}^2)=(2\times (siz_i-siz_{hson})\times a);
于是对答案的贡献为2*a*虚子树大小。
*/
struct LinkCutTree
{
	int son[N][2],fa[N],siz[N],sum[N],tag[N],st[N];
	//ps:p->wei,a->siz2
	int susqr[N],siz2[N],wei[N];
	inline int get(int x){
		return x==son[fa[x]][1];
	}
	inline int isnotroot(int x){
		return son[fa[x]][1]==x||son[fa[x]][0]==x;
	}
	inline void push_up(int x){
		sum[x]=sum[son[x][0]]+sum[son[x][1]]+1ll*siz2[x]*wei[x];
		siz[x]=siz[son[x][0]]+siz[son[x][1]]+siz2[x];
	}
	inline void push_add(int x,int y){
		tag[x]+=y;
		susqr[x]+=(1ll*siz2[x]*y);
	}
	inline void push_down(int x){
		if(tag[x]) {
			if(son[x][0]) push_add(son[x][0],tag[x]);
			if(son[x][1]) push_add(son[x][1],tag[x]);
			tag[x]=0;
		}
	}
	void update(int x){
		if(isnotroot(x)) update(fa[x]);
		push_down(x);
	}
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
		update(x);
		for(int f;f=fa[x],isnotroot(x);rotate(x))	
			if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
		push_up(x);
	}
	inline int access(int x){
		int y;
		for(y=0;x;y=x,x=fa[x])
			splay(x),siz2[x]+=siz[son[x][1]]-siz[y],son[x][1]=y,push_up(y);
		return y;
	}
	inline int make_root(int x){
		access(x),splay(x);//push_flp	
	}
	inline int find_root(int x){
		access(x),splay(x);
		while(son[x][0]) push_down(x),x=son[x][0];
		splay(x);
		return x;
	}
	void dosomething(int x,int y)//Ffa[x]->y;
	{
		access(x),access(Ffa[x]);
		int ss=siz[x];splay(Ffa[x]);
		siz2[Ffa[x]]-=ss;push_up(Ffa[x]);
		res-=(2ll*sum[Ffa[x]]*ss);
		push_add(Ffa[x],-2ll*ss);
		access(y),fa[x]=Ffa[x]=y;
		splay(y);
		res+=(2ll*sum[y]*ss);
		push_add(y,2ll*ss);
		siz2[y]+=ss;push_up(y);
	}
	void perform(int x,int y){
		if(x==1) dosomething(y,1);
		else
		{
			access(x),access(Ffa[x]);fa[x]=0;
			int ss=siz[x];
			splay(Ffa[x]);siz2[Ffa[x]]-=ss;push_up(Ffa[x]);				
			if(find_root(y)==x)
			{
				access(Ffa[x]);
				fa[x]=Ffa[x],splay(Ffa[x]);
				siz2[Ffa[x]]+=ss,push_up(Ffa[x]);
				dosomething(y,x);
			}
			else
			{
				access(Ffa[x]);
				fa[x]=Ffa[x],splay(Ffa[x]);
				siz2[Ffa[x]]+=ss,push_up(Ffa[x]);
				dosomething(x,y);
			}
		}
	}
	void upd(int x,int y){
		splay(x),wei[x]+=y,push_up(x),res+=(1ll*y*susqr[x]);
	}
}LCT;
void dfs(int u){
	siz[u]=1;
	for(int v:e[u]){
		dfs(v),siz[u]+=siz[v];
	}
}
inline void print(){
	double x=(double)res/(double)n/(double)n;
	printf("%.10lf\n",x);
}
signed main()
{
	n=read();
	R(i,2,n) LCT.fa[i]=Ffa[i]=read(),e[Ffa[i]].pb(i);
	R(i,1,n) a[i]=read();
	dfs(1);
	R(u,1,n) {
		res+=(1ll*siz[u]*siz[u]*a[u]);
		LCT.susqr[u]+=(1ll*siz[u]*siz[u]);
		for(int v:e[u]) {
			res-=(1ll*siz[v]*siz[v]*a[u]);
			LCT.susqr[u]-=(1ll*siz[v]*siz[v]);
		}
	}
	R(i,1,n) {
		LCT.siz2[i]=LCT.siz[i]=siz[i];
		LCT.wei[i]=a[i];
		LCT.sum[i]=siz[i]*a[i];
	}
	print();
	q=read();
	R(i,1,q) 
	{
		scanf("%s",opt+1);
		int u=read(),v=read();
		if(opt[1]=='P') LCT.perform(u,v);
		if(opt[1]=='V') LCT.upd(u,v-a[u]),a[u]=v;
		print();
	}
}
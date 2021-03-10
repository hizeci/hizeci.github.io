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
const int N=2e5+10;
int n,m,p;//    是否属于同一个点 连通性
int fa[N],siz[N],bel[N],FFa[N];
int son[N][2],tag[N],wei[N];
inline int find_Fa(int x){
	return x==FFa[x]?x:FFa[x]=find_Fa(FFa[x]);
}
inline int find_bel(int x){
	return x==bel[x]?x:bel[x]=find_bel(bel[x]);
}
inline int isnotroot(int x){
	return son[find_bel(fa[x])][0]==x||son[find_bel(fa[x])][1]==x;
}
inline int get(int x){
	return x==son[find_bel(fa[x])][1];
}
inline void push_flp(int x){
	Swap(son[x][0],son[x][1]);
	tag[x]^=1;
}
inline void push_down(int x){
	if(tag[x]){
		if(son[x][0]) push_flp(son[x][0]);
		if(son[x][1]) push_flp(son[x][1]);
		tag[x]=0;
	}
}
void rotate(int x)
{
	int f=find_bel(fa[x]),gf=find_bel(fa[f]),wh=get(x);
	if(isnotroot(f)) son[gf][get(f)]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x,fa[x]=gf;
}
void update(int x){
	if(isnotroot(x)) update(find_bel(fa[x]));
	push_down(x); 
}
inline void splay(int x){
	update(x);
	for(int f;f=find_bel(fa[x]),isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(x)==get(f)?f:x); 
}
inline int access(int x){
	int y;
	for(y=0;x;y=x,x=find_bel(fa[x]))
		splay(x),son[x][1]=y;
	return y;
}
inline void make_root(int x){
	access(x),splay(x),push_flp(x);
}
inline int find_root(int x){
	access(x),splay(x);
	while(son[x][0]) push_down(x),x=son[x][0];
	splay(x);
	return x;
}
inline void spilt(int x,int y){
	make_root(x),access(y),splay(y);
}
inline void link(int x,int y){
	make_root(x),splay(x);
	fa[x]=y,FFa[find_Fa(x)]=find_Fa(y);
}
void dfs(int u,int f){
	bel[u]=f;
	wei[f]+=wei[u];
	if(son[u][0]) dfs(son[u][0],f);
	if(son[u][1]) dfs(son[u][1],f);
}
int add(int x,int y){
	x=find_bel(x),y=find_bel(y);
	if(x==y) return wei[x];
	if(find_Fa(x)!=find_Fa(y)) {
		link(x,y);
		return 0;
	}
	spilt(x,y);
	dfs(son[y][0],y);
	return wei[y];
}
signed main()
{
	n=read(),m=read(),p=read();
	R(i,1,n) bel[i]=FFa[i]=i,wei[i]=1;
	R(i,1,m) {
		int u=read(),v=read();
		add(u,v);
	}
	R(i,1,p){
		int u=read(),v=read();
		int tmp=add(u,v);
		if(!tmp) puts("No");
		else printf("%lld\n",tmp);
	}
	return 0;
}
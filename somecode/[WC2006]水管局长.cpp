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
const int inf=0x7f7f7f7f;
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
//LCT并不能直接处理边权，此时需要对每条边建立一个对应点，方便查询链上的边信息。
//利用这一技巧可以动态维护生成树
const int N=5e5+10;
int son[N][2],fa[N],tag[N],val[N],maxx[N];
int n,m,q;
struct edge
{
	int u,v,d;
	inline bool operator <(const edge a)const{
		return d<a.d;
	}
}e[N<<1];
struct ques
{
	int opt,u,v,id;
}qs[N];
map<pii,int>mp;
int ans[N],vis[N];
inline void clear(int x){
	son[x][0]=son[x][1]=fa[x]=tag[x]=val[x]=maxx[x]=0;
}
inline int get(int x){
	return x==son[fa[x]][1];
}
inline int isnotroot(int x){
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
inline void push_up(int x){
	maxx[x]=val[x];
	if(son[x][0]&&e[maxx[son[x][0]]].d>e[maxx[x]].d) maxx[x]=maxx[son[x][0]];
	if(son[x][1]&&e[maxx[son[x][1]]].d>e[maxx[x]].d) maxx[x]=maxx[son[x][1]];
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
	int f=fa[x],gf=fa[f],wh=get(x);
	if(isnotroot(f)) son[gf][get(f)]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	push_up(f);
	push_up(x);
}
void update(int x){
	if(isnotroot(x)) update(fa[x]);
	push_down(x);
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
		splay(x),son[x][1]=y,push_up(x);
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
	make_root(x);splay(x);
	if(find_root(y)!=x) fa[x]=y;
}
inline void cut(int x,int y){
	make_root(x),access(y),splay(y);
	if(son[y][0]==x&&!son[x][1]){
		son[y][0]=fa[x]=0;
		push_up(y);
	}
}
signed main()
{
	n=read(),m=read(),q=read();
	R(i,1,m) {
		int u=read(),v=read(),d=read();
		if(u>v) Swap(u,v);
		e[i]=(edge){u,v,d};
	}
	sort(e+1,e+m+1);
    //R(i,1,m) printf("i:%lld u:%lld v:%lld d:%lld\n",i,e[i].u,e[i].v,e[i].d);
	R(i,1,m) mp[mkp(e[i].u,e[i].v)]=i;	
	R(i,1,m) val[i+n]=maxx[i+n]=i;
	//R(i,1,m) printf("%lld %lld\n",val[i+n],maxx[i+n]);
	R(i,1,q){
		int opt=read(),u=read(),v=read(),id=0;
		if(u>v) Swap(u,v);
		if(qs[i].opt==2) {
			id=mp[mkp(u,v)];
			vis[id]=1;
		}
		qs[i]=(ques){opt,u,v,id};
	}
	int cnt_e=0;
	R(i,1,m) if(!vis[i])
	{
		int u=e[i].u,v=e[i].v;
        //printf("%d %d %d %d\n",u,v,find_root(u),find_root(v));
		if(find_root(u)==find_root(v)) continue;
        printf("%d %d %d %d %d\n",i,u,v,find_root(u),find_root(v));
		link(u,i+n),link(v,i+n);
		cnt_e++;
		if(cnt_e+1==n) break;
	}
	L(i,1,q)
	{
		//printf("%lld\n",i); 
		int u=qs[i].u,v=qs[i].v;			
		spilt(u,v);
		//printf("maxx[%lld]:%lld\n",v,maxx[v]);
		if(qs[i].opt==1) ans[i]=e[maxx[v]].d;
		if(qs[i].opt==2) {
			int id=qs[i].id,mx=maxx[v];
			if(e[id].d<e[mx].d) {
				cut(e[mx].u,mx+n),cut(mx+n,e[mx].v);
				link(u,id+n),link(id+n,v);
			}
		}	
	}
	R(i,1,q) if(qs[i].opt==1) printf("%d\n",ans[i]);
}
/*
4 4 3
1 2 2
2 3 3
3 4 2
1 4 2
1 1 4
2 1 4
1 1 4
*/
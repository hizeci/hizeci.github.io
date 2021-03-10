//qiuly日报 and https://www.cnblogs.com/flashhu/p/8324551.html版本

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
const int N=3e5+10;
int fa[N],son[N][2],wei[N],sum[N],tag[N],siz[N];
inline int isnotroot(int x){
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
inline int get(int x){
	return x==son[fa[x]][1];
}
inline void push_up(int x){
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
	sum[x]=sum[son[x][0]]^sum[son[x][1]]^wei[x];
}
inline void push_flp(int x){
	Swap(son[x][0],son[x][1]),tag[x]^=1;
}
inline void push_down(int x){
	if(tag[x]){
		if(son[x][0]) push_flp(son[x][0]);
		if(son[x][1]) push_flp(son[x][1]);
		tag[x]=0;
	}
}//*
void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	if(isnotroot(f)) son[gf][son[gf][1]==f]=x;//打*，上面这句一定要写在前面(普通Splay不用)
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
void splay(int x){
	update(x);
	for(int f;f=fa[x],isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(f)==get(x)?f:x);
	push_up(x);
}
inline int access(int x){
	int y=0;
	for(;x;y=x,x=fa[x]) 
		splay(x),son[x][1]=y,push_up(x);
   return y;
}
inline void make_root(int x){
	access(x),splay(x),push_flp(x);
}
int find_root(int x){
	access(x),splay(x);
	while(son[x][0]) push_down(x),x=son[x][0];
	splay(x);
	return x;
}
inline void spilt(int x,int y){
	make_root(x),access(y),splay(y);
}
inline void link(int x,int y){
	make_root(x);
	if(find_root(y)!=x) fa[x]=y;
}
inline void cut(int x,int y){
	make_root(x);
	if(find_root(y)==x&&fa[y]==x&&!son[y][0]){
		fa[y]=son[x][1]=0;
		push_up(x);
	}
}
signed main()
{
	int n=read(),m=read();
	R(i,1,n) wei[i]=read();
	while(m--)
	{
		int opt=read(),x=read(),y=read();
		if(!opt){
			spilt(x,y);
			printf("%d\n",sum[y]);
			continue;
		}
		if(opt==1){
			link(x,y);
			continue;
		}
		if(opt==2){
			cut(x,y);
			continue;
		}
		if(opt==3){
			splay(x);wei[x]=y;
		}
	}
}
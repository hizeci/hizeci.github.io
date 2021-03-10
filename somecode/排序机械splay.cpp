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
int son[N][2],fa[N],siz[N],cnt[N],wei[N],tag[N];
int tot_nd,rt,n;
struct node
{
	int val,id;
	bool operator <(const node a)const{
		return (val^a.val)?val<a.val:id<a.id;
	}
}a[N];
inline void push_up(int x) {siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;}
inline int get(int x) {return x==son[fa[x]][1];}
inline void clear(int x) {son[x][0]=son[x][1]=fa[x]=wei[x]=siz[x]=cnt[x]=0;}
void push_down(int x)
{
	if(!tag[x]) return;
	if(son[x][0]) tag[son[x][0]]^=1;
	if(son[x][1]) tag[son[x][1]]^=1;
	Swap(son[x][0],son[x][1]);
	tag[x]=0;
}	
void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	push_down(f),push_down(x);
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	if(gf) son[gf][son[gf][1]==f]=x;
	push_up(f),push_up(x);
}
void splay(int x,int to)
{
	for(int f;(f=fa[x])!=to;rotate(x)){
		push_down(fa[f]),push_down(f),push_down(x);
		if(fa[f]!=to) rotate(get(x)==get(f)?f:x);
	}
	if(!to) rt=x;
}
void build(int l,int r,int f)
{
	if(l>r) return;
	int mid=(l+r)>>1;
	if(mid<f) son[f][0]=mid;
	else son[f][1]=mid;
	siz[mid]=1,fa[mid]=f;
	if(l==r) return ;
	build(l,mid-1,mid),build(mid+1,r,mid);
	push_up(mid);
}
int find_kth(int x)
{
	int cnr=rt;
	while(1)
	{
		push_down(cnr);
		if(x<=siz[son[cnr][0]]&&son[cnr][0]) cnr=son[cnr][0];
		else{
			x-=siz[son[cnr][0]]+1;
			if(x<=0){ splay(cnr,0);return cnr;}
			cnr=son[cnr][1];
		}
	}
}
signed main()
{
	n=read();
	R(i,2,n+1) {
		int x=read();
		a[i]=(node){x,i};
	}
	a[1]=(node){-inf,1};
	a[n+2]=(node){inf,n+2};
	sort(a+1,a+n+3);
	build(1,n+2,0);
	rt=(n+3)>>1;
	R(i,2,n)
	{
		splay(a[i].id,0);
		int res=siz[son[rt][0]]+1;
		printf("%lld ",res-1);
		int xx=find_kth(i-1),yy=find_kth(res+1);
		splay(xx,0),splay(yy,xx);
		tag[son[son[rt][1]][0]]^=1;
	}
	printf("%lld\n",n);
}
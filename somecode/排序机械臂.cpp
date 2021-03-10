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

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
inline int rand1(){
	return dist(rand_num);
}
/*printf("%lld ",dist(rand_num));*/
const int N=1e6+10;
struct pai
{
	int a,b;
	pai(int a_=0,int b_=0) {a=a_,b=b_;}
};
struct node
{
	int val,id;
	inline int operator <(const node a)const{
		return (val^a.val)?val<a.val:id<a.id;
	}
}a[N];
int b[N];
int tag[N],son[N][2];
int key[N],siz[N],wei[N],mn[N],rt,tot_nd;
int n;
inline int build(int x){
	key[++tot_nd]=x,mn[tot_nd]=x,siz[tot_nd]=1,wei[tot_nd]=rand1();
	return tot_nd;
}
void push_down(int x){
	if(!tag[x]) return;
	if(son[x][0]) tag[son[x][0]]^=1;
	if(son[x][1]) tag[son[x][1]]^=1;
	Swap(son[x][0],son[x][1]);
	tag[x]=0;
}
void push_up(int x){
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
	mn[x]=key[x];
	if(son[x][0]) mn[x]=min(mn[x],mn[son[x][0]]);
	if(son[x][1]) mn[x]=min(mn[x],mn[son[x][1]]);
}

int Mer(int u,int v)
{
	if(!u||!v) return u^v;
	if(wei[u]<wei[v]) {
		push_down(u);
		son[u][1]=Mer(son[u][1],v);
		push_up(u);
		return u;
	}
	else 
	{
		push_down(v);
		son[v][0]=Mer(u,son[v][0]);
		push_up(v);
		return v;
	}
}
pai spilt(int u,int k)
{
	if(!u) return pai(0,0);
	push_down(u);
	if(siz[son[u][0]]<k){
		pai t=spilt(son[u][1],k-siz[son[u][0]]-1);
		son[u][1]=t.a;
		push_up(u);
		return pai(u,t.b);
	}
	else
	{
		pai t=spilt(son[u][0],k);
		son[u][0]=t.b;
		push_up(u);
		return pai(t.a,u);
	}
}
int find_rk(int x)
{
	int res=1;
	while(1)
	{
		push_down(x);
		if(son[x][0]&&mn[son[x][0]]==mn[x]) x=son[x][0];
		else if(son[x][1]&&mn[son[x][1]]==mn[x]) res+=siz[son[x][0]]+1,x=son[x][1];
		else return res+siz[son[x][0]];
	}
}
signed main()
{
	n=read();
	R(i,1,n) {
		int x=read();
		a[i]=(node){x,i};
	}
	sort(a+1,a+n+1);
	R(i,1,n) b[a[i].id]=i;//不去重离散化
	R(i,1,n) rt=Mer(rt,build(b[i]));
	R(i,1,n)
	{
		int k=find_rk(rt);
		pai x=spilt(rt,k);
		pai y=spilt(x.a,k-1);
		tag[y.a]^=1;
		rt=Mer(y.a,x.b);
		printf("%lld ",k+i-1);
	}
}
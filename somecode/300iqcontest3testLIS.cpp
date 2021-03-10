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
考虑dp_i表示从前面到i最多能走多少步，转移式为dp_i=max {dp_j+1} (a_j\times x_i+b_j\geq y_i)废话(
考虑二分dp_j的值。那么相当于是否存在j使得,dp_j在[l,r]内,且a_j\times x_i+b_j\geq y_i;可以用李超树判断。
于是，直接维护一个线段树套李超树，在线段树上二分即可.
O(n log^2_n)
*/
int _;
int n;
const int N=433333;
int a[N],b[N],x[N],y[N],dp[N];
int res;
int Rs[N<<2],Ls[N<<2],Rt[N<<2],s[N<<2];
struct line 
{
	int k,b;
	int eval(int x){
		return 1ll*k*x+b;
	}
}p[N];
int tot_seg,tot_nd;
inline void add_seg(int k,int b){
	p[++tot_seg].k=k,p[tot_seg].b=b;
}
inline int calc(int id,int x){
	return p[id].k*x+p[id].b;
}

void upd(int l,int r,int &x,int u)
{
	if(!x) {
		x=++tot_nd;
		s[x]=u;
		return;
	}
	line cur=p[u];
	if(cur.eval(l)>=p[s[x]].eval(l))
	{
		cur=p[s[x]];
		Swap(s[x],u);
	}
	if(l==r) return;
	if(cur.eval(r)<=p[s[x]].eval(r)) return;
	int mid=(l+r)>>1;
	if(cur.eval(mid)>=p[s[x]].eval(mid)) {
		upd(l,mid,Ls[x],s[x]);
		s[x]=u;
	}
	else upd(mid+1,r,Rs[x],u);
}
void modify(int pos,int l,int r,int x,int u){
	upd(0,300000,Rt[x],u);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) modify(pos,l,mid,x<<1,u);
	else modify(pos,mid+1,r,x<<1|1,u);
}
int check(int X,int Y,int l,int r,int x){
	if(!x) return 0;
	if(calc(s[x],X)>=Y) return 1;
	if(l==r) return 0;
	int mid=(l+r)>>1;
	if(X<=mid) return check(X,Y,l,mid,Ls[x]);
	else return check(X,Y,mid+1,r,Rs[x]);
}
int query_MX(int X,int Y,int l,int r,int x){
	if(l==r) {
		if(!check(X,Y,0,300000,Rt[x])) return l-1;
		return l;
	}
	int mid=(l+r)>>1;
	if(!check(X,Y,0,300000,Rt[x<<1|1])) return query_MX(X,Y,l,mid,x<<1);
	else query_MX(X,Y,mid+1,r,x<<1|1);
}
signed main()
{
	for(_=read();_;_--)
	{
		res=0;
		n=read(); 
		R(i,1,n) a[i]=read(),b[i]=read(),x[i]=read(),y[i]=read();
		R(i,1,n) {
			dp[i]=query_MX(x[i],y[i],1,n,1)+1;
			add_seg(a[i],b[i]);
			modify(dp[i],1,n,1,tot_seg);
			res=max(res,dp[i]);
		}
		printf("%lld\n",res);
		R(i,1,tot_nd) Ls[i]=Rs[i]=0;
		R(i,1,n<<2) Rt[i]=0;
		tot_seg=tot_nd=0;
	}
}
/*

3 
1 4 3 8 4 
1 9 10 4 3 
0 4
*/

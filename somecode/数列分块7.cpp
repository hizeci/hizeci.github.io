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
//const int mod=1e9+7;
const int mod=10007;
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
const int N=1e5+10;
int n,a[N];
int B,b[N];
int lazy_add[N],lazy_mul[N];
inline void push_down(int x){
	R(i,(x-1)*B+1,min(n,x*B)) a[i]=(a[i]*lazy_mul[x]%mod+lazy_add[x])%mod;
	lazy_mul[x]=1,lazy_add[x]=0;
}
inline void modify_add(int l,int r,int c){
	push_down(b[l]);
	R(i,l,min(b[l]*B,r)) a[i]+=c,a[i]%=mod;
	if(b[l]!=b[r]){ 
		push_down(b[r]);
		R(i,(b[r]-1)*B+1,r) a[i]+=c,a[i]%=mod;
	}
	R(i,b[l]+1,b[r]-1) lazy_add[i]+=c,lazy_add[i]%=mod;
}
inline void modify_mul(int l,int r,int c){
	push_down(b[l]);
	R(i,l,min(b[l]*B,r)) a[i]*=c,a[i]%=mod;
	if(b[l]!=b[r]) {
		push_down(b[r]);
		R(i,(b[r]-1)*B+1,r) a[i]*=c,a[i]%=mod;
	}
	R(i,b[l]+1,b[r]-1) lazy_mul[i]*=c,lazy_add[i]*=c,lazy_mul[i]%=mod,lazy_add[i]%=mod;
}

signed main()
{
	n=read(),B=sqrt(n);
	R(i,1,n) a[i]=read()%mod;
	R(i,1,n) b[i]=(i-1)/B+1;
	R(i,1,b[n]) lazy_mul[i]=1;
	R(i,1,n) {
		int opt=read(),l=read(),r=read(),c=read();
		if(!opt) modify_add(l,r,c);
		if(opt==1) modify_mul(l,r,c);
		if(opt==2) printf("%lld\n",(a[r]*lazy_mul[b[r]]%mod+lazy_add[b[r]])%mod);
	}
}
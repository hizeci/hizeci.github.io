//本代码为封装，仅供参考
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
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define us unsigned 
#define ll long long
#define ull unsigned long long
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
const ld eps=1e-8;
inline int fpow(int a,int b=mod-2,int p=mod){int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}
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
inline void write(int x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(int x){write(x),putchar(' ');}
inline void writeln(int x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int _G=3;
const int N=2222222;
const int invG=fpow(_G);
int tr[N<<1],tf;
int n,m,F[N<<1],G[N<<1];

void tpre(int n){
	if(tf==n) return;tf=n;
	R(i,0,n-1) tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
}
void NTT(int *g,int rev,int n)
{
	tpre(n);
	static ull f[N<<1],w[N<<1];w[0]=1;
	R(i,0,n-1) f[i]=(((ll)mod<<5)+g[tr[i]])%mod;
	for(int l=1;l<n;l<<=1)
	{
		ull tG=fpow(rev?_G:invG,(mod-1)/(l+l));
		R(i,1,l-1) w[i]=w[i-1]*tG%mod;
		for(int k=0;k<n;k+=l+l)
		{
			R(p,0,l-1) 
			{
				int tt=w[p]*f[k|l|p]%mod;
				f[k|l|p]=f[k|p]+mod-tt;
				f[k|p]+=tt;
			}
		}
		if(l==(1<<10)) R(i,0,n-1) f[i]%=mod;
	}
	if(!rev) 
	{
		ull invn=fpow(n);
		R(i,0,n-1) g[i]=f[i]%mod*invn%mod;
	}
	else R(i,0,n-1) g[i]=f[i]%mod;
}
void px(int *f,int *g,int n) {R(i,0,n-1)f[i]=1ll*f[i]*g[i]%mod;}
void times(int *f,int *g,int len,int lim) 
{
	static int sav[N<<1];
	int n=1;for(;n<len+len;n<<=1);
	clr(sav,n);cpy(sav,g,n);
	NTT(f,1,n);NTT(sav,1,n);
	px(f,sav,n);NTT(f,0,n);
	clr(f+lim,n-lim);clr(sav,n);
}	//len为实际长度,lim为2^k


signed main()
{
	n=read(),m=read();
	R(i,0,n) F[i]=read();
	R(i,0,m) G[i]=read();
	for(m+=n,n=1;n<=m;n<<=1);
	times(F,G,m,n);
	R(i,0,m) printf("%lld ",F[i]);
}

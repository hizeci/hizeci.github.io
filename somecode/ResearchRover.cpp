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
const int mod=1e9+7;
const double Pi=acos(-1);
//const int mod=19940417;
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
const int qwq=222222;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}
const int N=4444;
int n,m,k,t,vl[N];
int dp[N][33],g[33];
pii pnt[N];
inline int calc(int a,int b){return F[a+b]*Finv[a]%mod*Finv[b]%mod;}
signed main()
{
	init_C();
	n=read(),m=read(),k=read(),t=read();
	R(i,0,k-1) {
		int x=read(),y=read();
		pnt[i]=mkp(x,y);
	}
	pnt[k]=mkp(1,1);
	sort(pnt,pnt+k+1);
	int tt=unique(pnt,pnt+k+1)-pnt;
	if(tt<=k) t=(t+1)>>1;	
	R(i,0,23) vl[i]=t,t=(t+1)>>1;
	dp[0][0]=1;
	R(i,1,tt-1) 
	{
		FR(j,0,i) if(pnt[i].fi>=pnt[j].fi&&pnt[i].se>=pnt[j].se) 
			R(k,0,22) dp[i][k+1]=(dp[i][k+1]+dp[j][k]*calc(pnt[i].fi-pnt[j].fi,pnt[i].se-pnt[j].se)%mod)%mod;
		R(j,1,22) dp[i][j]=(dp[i][j]-dp[i][j+1])%mod; 
	}
	R(i,0,tt-1) R(j,0,23) g[j]=(g[j]+dp[i][j]*calc(n-pnt[i].fi,m-pnt[i].se)%mod)%mod;
	R(i,0,22) g[i]=(g[i]-g[i+1])%mod;
	int ans=0;
	R(i,0,23) ans=(ans+g[i]*vl[i]%mod+mod)%mod;
	ans=ans*fpow(calc(n-1,m-1))%mod;
	printf("%lld\n",(ans+mod)%mod);
}
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
const int INF=0x7f7f7f3f;
const int mod=998244353;
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
//正反求LIS
//ans:max(加起来-1)
const int N=1e6+10; 
int n,m;
int sum[N];
int dp[N],pd[N];
inline int lowbit(int x){
	return x&(-x);
}
struct BIT
{
	int val[N];
	inline void modify_mx(int x,int k){
		for(int i=x;i<=n;i+=lowbit(i)) val[i]=max(val[i],k); 
	}	
	inline int query_mx(int x){
		int ret=-1;
		for(int i=x;i;i-=lowbit(i)) ret=max(ret,val[i]);
		return ret; 
	}
}bt1,bt2;

signed main()
{
	n=read(),m=read();
	R(i,1,n) {
		int l=read(),r=read();
		sum[l]++,sum[r+1]--;
	}
	int tmp=0,res=-inf;
	R(i,1,m) tmp+=sum[i],sum[i]=tmp+1;
	R(i,1,m) dp[i]=bt1.query_mx(sum[i])+1,bt1.modify_mx(sum[i],dp[i]);
	L(i,1,m) pd[i]=bt2.query_mx(sum[i])+1,bt2.modify_mx(sum[i],pd[i]);
	R(i,1,m) res=max(res,dp[i]+pd[i]-1);printf("%lld\n",res);
}

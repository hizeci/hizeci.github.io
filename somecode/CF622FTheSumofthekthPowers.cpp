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
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
const int mod=1e9+7;
//const int mod=998244353;
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
inline void write(int x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(int x){write(x),putchar(' ');}
inline void writeln(int x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
/*
可以发现答案是一个k+1次的多项式（具体证明我不会orz
可以代入k+2值拉格朗日插值求出,
$f(x)=\sum_{i=0}^n y_i\prod_{j!=i} \frac{x-x_j}{x_i-x_j}$
时间复杂度为O(n^2)
对于本题，将1到k+2带入，有很好的性质：对于每个i，分母是1乘到i-1再乘上-1到i-k-2，可以预处理阶乘。分子可以预处理前后缀积
*/
const int N=1e6+10;
inline int get_inv(int x){
	return fpow(x,mod-2);
}
int n,k,ans,sumy;
int pre[N],suf[N],F[N];

signed main() 
{
	n=read(),k=read();
	pre[0]=suf[k+3]=F[0]=1;
	R(i,1,k+2) pre[i]=1ll*pre[i-1]*(n-i)%mod;
	L(i,1,k+2) suf[i]=1ll*suf[i+1]*(n-i)%mod;
	R(i,1,k+2) F[i]=1ll*F[i-1]*i%mod;
	R(i,1,k+2) 
	{
		sumy=(sumy+fpow(i,k))%mod;
		int s1=1ll*pre[i-1]*suf[i+1]%mod;
		int s2=F[i-1]*((k-i)&1?-1ll:1ll)*F[k+2-i]%mod;
		ans=(ans+1ll*sumy*s1%mod*get_inv(s2)%mod+mod)%mod;
	} 
	printf("%lld\n",ans);
}
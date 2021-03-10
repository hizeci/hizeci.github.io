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
//const int mod=10007;
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
/*
为什么这个ABC这么难哇/kk，蒟蒻爬了

sol搬运:
依次考虑S和T的每一位是否相同，设我们考虑到第i位
若相同：答案贡献为0
若不同：则根据上面的贪心，第i位之前的位置已经修改完毕。所以在T中第i位之前的位置可以随意选数，对第i位的贡献不影响
对于第i位之后的位置，我们枚举有多少不相同的位置
ans: 
$$ 2^n\times (\sum_{i=1}^n 2^{i-1} \times C_i \times \sum_{j=0}^{n-i} \binom {n-i}{j}(j+1) ) $$
考虑化简后面的式子，使用乘法分配律可得
$$\sum_{j=0}^{n-i}\binom {n-i}{j}(j+1) = \sum_{j=0}^{n-i}\binom{n-i}{j}+\sum_{j=0}^{n-i}\binom{n-i}{j}j $$
$$2^{n-i}+\sum_{j=0}^{n-i}\binom{n-i}{j}j$$
考虑吸收恒等式
$$\frac{r}{k}\binom{r-1}{k-1}=\frac{r}{k}\times \frac{(r-1)^\underline {k-1} }{(k-1)!}=\binom r k$$
于是有
$$\binom r k \times k=\binom {r-1}{k-1}\times r$$
原式为:
$$2^{n-i}+\sum_{j=0}^{n-i}\binom{n-i}{j}j=2^{n-i}+\sum_{j=0}^{n-i}\binom{n-i-1}{j-1}(n-i)=2^{n-i}+(n-i)\sum{j=0}{n-i-1}\binom{n-i-1}{j}=2^{n-i}+(n-i)\times 2^{n-i-1}$$
*/
const int N=2e5+10;
int n;
int a[N];
int pw2[N],res;
signed main()
{
	n=read();
	R(i,1,n) a[i]=read();
	pw2[0]=1;
	R(i,1,n) pw2[i]=pw2[i-1]*2%mod;
	sort(a+1,a+n+1);
	R(i,1,n) res=(res+1ll*pw2[i-1]*a[i]%mod*(pw2[n-i]+1ll*(n-i)*pw2[n-i-1]%mod)%mod)%mod;
	printf("%lld\n",res*pw2[n]%mod);
}
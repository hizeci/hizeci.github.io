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
const int mod=1004535809;
const ld eps=1e-8;
inline int fpow(int a,int b,int p=mod){int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}
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
固定一个K,考虑如何求答案。
枚举至少有多少种颜色恰好出现了s次，进行容斥。
$\sum_{i=k}^m \frac{n!}{(S!)^i \times (n-iS)!}\binom m i (m-i)!^{n-iS}\times (-1)^{i-k}\binom i k$

过程：

考虑容斥，计算出恰好出现了$s$次的颜色至少有$i$种的方案数$f_i$，钦定$i$种颜色正好放$S$种

有$m$种颜色选$i$种,所以有一个$\binom m i$

然后这$n$个位置分成$i+1$个部分:被钦定的$i$中颜色，每个有$S$个；剩下的$m-i$种颜色，一共$n-i\times S$个

先看作是可重的全排列数，那么方案就有$\frac {n!}{(S!)^i\times(n-iS)!}$前面各部分都是只有一种颜色，后面部分有$m-i$种取法，所以还有一个$(m-i)^{n-iS}$.

综上$f_i=\frac{n!}{(S!)^i \times (n-iS)!}\binom m i (m-i)^{n-iS} $

$ans_k=\sum_{i=k}^{m}(-1)^{i-k}\times \binom i k\times f_i$

拆开得:

$ans_k=\sum_{i=k}^{m} (-1)^{i-k}\times \frac{i!}{k!(i-k)!}\times f_i$

$ans_k\times k!=\sum_{i=k}^{m}(-1)^{i-k}\times \frac{1}{(i-k)!}\times i!\times f_i$

设$A_i=i!\times f_i,B_i=\frac{(-1)^i}{i!}$

有$G_k=\frac{1}{k!}\sum_{i=k}^{m}A[i]\times B[i-k]$

上式只与变量i与i-k有关，显然是卷积形式。复杂度m log m
*/

const int _G=3;
const int invG=fpow(_G,mod-2);
const int N=11111111;
const int M=2e5+10;
int n,m,S;
int lim,cnt_lim;
int tr[M<<1];
int A[M<<1],B[M<<1];
int jc[N],inv[N],Finv[N];
void init_C()
{
    jc[0]=Finv[0]=inv[1]=1;
    R(i,2,10000000) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,10000000) jc[i]=1ll*(jc[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return 1ll*jc[n]%mod*1ll*Finv[m]*1ll%mod*1ll*Finv[n-m]%mod;}
inline int calcF(int i){
	//$f_i=\frac{n!}{(S!)^i \times (n-iS)!}\binom m i (m-i)^{n-iS} $
	return jc[n]*fpow(Finv[S],i)%mod*Finv[n-i*S]%mod*C(m,i)%mod*fpow(m-i,n-i*S)%mod;
}
void NTT(int *g,int rev,int n)
{
	static ull f[M<<1],w[M<<1];
	w[0]=1;
	R(i,0,n-1) f[i]=((g[tr[i]]));
	for(int p=1;p<n;p<<=1) 
	{
		ull tG=fpow(rev?_G:invG,(mod-1)/(p+p));
		R(i,1,p-1) w[i]=w[i-1]*tG%mod;
		for(int k=0;k<n;k+=p+p) 
		{
			R(l,0,p-1) 
			{
				int tt=w[l]*f[k|p|l]%mod;
				f[k|p|l]=f[k|l]+mod-tt;
				f[k|l]+=tt;
			}
		}
		if(p==(1<<10)) R(i,0,n-1) f[i]%=mod;
	}
	if(!rev) 
	{
		ull invn=fpow(n,mod-2);
		R(i,0,n-1) g[i]=f[i]%mod*invn%mod;
	}
	else R(i,0,n-1) g[i]=f[i]%mod;
}
signed main()
{	
	n=read(),m=read(),S=read(),lim=min(m,n/S);
	init_C();
	R(i,0,lim) {
		//$A_i=i!\times f_i,B_i=\frac{(-1)^i}{i!}$
		A[i]=jc[i]*calcF(i)%mod;
		B[i]=(i&1)?mod-Finv[i]:Finv[i];
		//printf("A:%lld B:%lld\n",A[i],B[i]);
	}
	reverse(A,A+lim+1);//
	for(n=1;n<lim+lim+2;n<<=1);
	R(i,0,n-1) tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	NTT(A,1,n);NTT(B,1,n);
	//R(i,0,n-1) printf("A:%lld B:%lld\n",A[i],B[i]);
	R(i,0,n-1) A[i]=1ll*A[i]*B[i]%mod;
	NTT(A,0,n);
	reverse(A,A+lim+1);
	int ans=0;
	R(i,0,lim) 
	{
		int x=read();
		ans=(ans+A[i]*Finv[i]%mod*x%mod)%mod;
	}
	printf("%lld\n",ans);
}	
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
const int mod=1e9+7;
const double Pi=acos(-1);
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
int n,_;

const int sz=5;
struct mat
{
	int a[sz][sz];
	inline mat() {memset(a,0,sizeof(a));}
	inline void build() {R(i,0,3-1)a[i][i]=1;}
	inline void clr() {memset(a,0,sizeof(a));}
	inline mat operator + (const mat &T)const{
		mat res;
		R(i,0,3) R(j,0,3) res.a[i][j]=a[i][j]+T.a[i][j],res.a[i][j]>=mod?res.a[i][j]%=mod:1;
		return res;
	}	
	inline mat operator - (const mat &T)const{
		mat res;
		R(i,0,n-1) R(j,0,n-1) res.a[i][j]=(a[i][j]+T.a[i][j])%mod;
		return res;
	}
	inline mat operator * (const mat &T)const{
		mat res;int tt;
		R(i,0,2) R(k,0,2)
		{
			tt=a[i][k];
			R(j,0,2) res.a[i][j]+=T.a[k][j]*tt,res.a[i][j]>=mod?res.a[i][j]%=mod:1;
		}
		return res;
	}
	inline mat operator ^(int x)const{
		mat res,bas;
		R(i,0,n-1) res.a[i][i]=1;
		R(i,0,n-1) R(j,0,n-1) bas.a[i][j]=a[i][j]%mod;
		while(x) {
			if(x&1)res=res*bas;
			bas=bas*bas;
			x>>=1;
		}
		return res;
	}
}ans,bas;

signed main()
{
	for(_=read();_;_--)
	{
		n=read();
		if(n<=3) {
			puts("1");
			continue;
		}
		ans.clr(),bas.clr();
		ans.build();
		n--;
		bas.a[0][0]=bas.a[0][2]=bas.a[1][0]=bas.a[2][1]=1;
		while(n)
		{
			if(n&1) ans=ans*bas;
			bas=bas*bas;
			n>>=1;
		}
		printf("%lld\n",ans.a[0][0]);
	}
}
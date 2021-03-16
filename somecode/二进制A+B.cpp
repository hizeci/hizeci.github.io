#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define int long long
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x, T y) { return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x, T y) { return x>y?x=y,true:false;}
using namespace std;
//const ll inf=0x7f7f7f7f7f7f7f3f;
const ll inf=(1ll<<60);
//const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
const double eps=1e-6;
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
inline ll read()
{
    char c=getchar();ll x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
inline int lowbit(int x){return x&(-x);}
inline int cou1(int x){int ret=0;for(int i=x;i;i-=lowbit(i),ret++);return ret;}

int a,b,c;
int cnta,cntb,cntc;
int mxL,lim;
int ans;
inline int solve()
{
	if(cnta+cntb==cntc) return (fpow(2,cntc,(1ll<<60))-1);
	int t=cnta+cntb-cntc;
	if(t<0) return -1;
	if(cnta<t&&cntb<t) {R(i,1,cntc-1)ans|=(1<<i);ans|=(1<<cntc);return ans;}
	if(cnta<t) {R(i,0,cntb-t-1)ans|=(1<<i);R(i,cntb-t+1,cntb-t+cnta-1)ans|=(1<<i);ans|=(1<<cntb);return ans;}
	R(i,0,cntb+cnta-(t<<1)-1) ans|=(1<<i);R(i,cnta+cntb-(t<<1)+1,cntc) ans|=(1<<i);
	return ans;
}
signed main()
{
	a=read(),b=read(),c=read();
	cnta=cou1(a),cntb=cou1(b),cntc=cou1(c);
	cnta>cntb?Swap(cnta,cntb):1;
	mxL=max(a,max(b,c));
	for(lim=1;(1ll<<lim)<mxL;++lim); 
	int res=solve();
	printf("%lld\n",res<(1<<lim)?res:-1);
}
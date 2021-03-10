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
const int N=55555;
int n,a[N],b[N];
int B,g[N],flag[N];
int sum[N];
inline void modify_who(int x){
	flag[x]=1;sum[x]=0;
	R(i,(x-1)*B+1,x*B) {
		a[i]=pow(a[i],1.0/2.0);
		sum[x]+=a[i];
		if(a[i]>1) flag[x]=0;
	}		
}
inline void modify_sqrt(int l,int r){
	R(i,l,min(b[l]*B,r)) {
		sum[b[l]]-=a[i];
		a[i]=pow(a[i],1.0/2.0);
		sum[b[l]]+=a[i];
	}
	if(b[l]!=b[r]) R(i,(b[r]-1)*B+1,r) {
		sum[b[r]]-=a[i];
		a[i]=pow(a[i],1.0/2.0);
		sum[b[r]]+=a[i];
	}
	R(i,b[l]+1,b[r]-1) if(!flag[i]) modify_who(i);
}
inline int query(int l,int r){
	int res=0;
	R(i,l,min(b[l]*B,r)) res+=a[i];
	if(b[l]!=b[r]) R(i,(b[r]-1)*B+1,r) res+=a[i];
	R(i,b[l]+1,b[r]-1) res+=sum[i];
	return res;
}
signed main()
{
	n=read(),B=pow(n,2.0/3.0);
	R(i,1,n) a[i]=read();
	R(i,1,n) {
		b[i]=(i-1)/B+1;
		sum[b[i]]+=a[i];
	}
	R(i,1,n) {
		int opt=read(),l=read(),r=read(),c=read();
		if(!opt) modify_sqrt(l,r);
		if(opt) printf("%lld\n",query(l,r));
	}
}
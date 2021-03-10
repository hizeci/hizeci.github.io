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
//const int mod=10007;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}

const int qwq=2000010;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}

inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return 1ll*F[n]%mod*1ll*Finv[m]*1ll%mod*1ll*Finv[n-m]%mod;}


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
题意:求\sum_{i=1}^{m} \binom {n} {i}
定义S(n,m)=\sum_{i=1}^{m} \binom {n} {i}
有S(n,m)=S(n,m-1)+\binom n m 
S(n,m)=2*S(n-1,m) - \binom {n-1} {m}	
考虑莫队，那么需要处理四种操作
m++/m-- 加/减一个组合数
n++ 由于 \sum_{i=0}^{m} \binom {n+1} {i} =\sum_{i=0}^{m} \binom {n}{i}+\binom {n}{i-1}=2\times \sum_{i=0}{m}\binom n i -\binom n m
res=res*2-C(n,m)即可
n-- res=(res+C(n-1,m))/2;
*/
const int N=1e5+10;
const int B=2020;
int ans[N];
int n;
int res=2;
struct ques
{
	int l,r,id;
	inline int operator <(const ques a)const{
		return (l/B^a.l/B)?l<a.l:((l/B)&1)?r<a.r:r>a.r;
	}
}qs[N];
inline void addN(int l,int r){
	res=(2ll*res%mod-C(l-1,r)%mod+mod)%mod;
}
inline void delN(int l,int r){
	res=(1ll*res+C(l-1,r))%mod*inv[2]%mod;
}
inline void addM(int l,int r) {
	res=(1ll*res+C(l,r))%mod;
}
inline void delM(int l,int r){
	res=(1ll*res-C(l,r)+mod)%mod;
}


signed main() {
	init_C();
	n=read();
	R(i,1,n) {
		qs[i].l=read(),qs[i].r=read(),qs[i].id=i;
	}
	sort(qs+1,qs+n+1);
	int L=1,R=1;
	R(i,1,n) {
		while(L<qs[i].l) addN(++L,R);
		while(L>qs[i].l) delN(L--,R);
		while(R<qs[i].r) addM(L,++R);
		while(R>qs[i].r) delM(L,R--);
		ans[qs[i].id]=res;
	}
	R(i,1,n) printf("%lld\n",ans[i]);
}

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
/*
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
*/
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f;
//const int mod=9223372036854775807;
const ld eps=1e-8;
//inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
/*
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
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
const int M=1e6+10;
const int N=2e5+10;
int n,m,k,B;
int L=1,R;
int a[N],ans[N],res;
int cnt[M];
struct ques
{
	int l,r,id;
	inline bool operator <(const ques a)const{
		return l/B^a.l/B?l<a.l:l/B&1?r<a.r:r>a.r;
	}
}qs[N];
inline void add(int x){
	cnt[a[x]]++,res+=(2*cnt[a[x]]-1)*a[x];
}
inline void del(int x){
	cnt[a[x]]--,res-=(2*cnt[a[x]]+1)*a[x];
}
signed main()
{
	n=read(),m=read();
	B=n/sqrt(m*2/3)+1;
	R(i,1,n) a[i]=read();
	R(i,1,m) qs[i].l=read(),qs[i].r=read(),qs[i].id=i;
	sort(qs+1,qs+m+1);
	R(i,1,m)
	{
		int ql=qs[i].l,qr=qs[i].r;
		while(L<ql) del(L++);
		while(R<qr) add(++R);
		while(L>ql) add(--L);
		while(R>qr) del(R--);
		ans[qs[i].id]=res;
	}
	R(i,1,m) printf("%lld\n",ans[i]);
}
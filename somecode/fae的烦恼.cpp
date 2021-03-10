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
const int N=2e5+10;
int n,m,q,B;
int cnt[N],tot[N];//cnt[i]表示数i出现次数,tot[i]表示出现i次的数有多少个
int a[N];
int res,ans[N];
struct ques
{
	int l,r,id;
	inline bool operator <(const ques a)const{
		return (l/B^a.l/B)?l<a.l:((l/B)&1)?r<a.r:r>a.r;
	}
}qs[N];

inline void add(int x){
	tot[cnt[x]]--;
	tot[++cnt[x]]++;
	res=max(res,cnt[x]);
}
inline void del(int x){
	tot[cnt[x]]--;
	if(cnt[x]==res&&!tot[cnt[x]]) res--;
	tot[--cnt[x]]++;
}
signed main()
{
	n=read();B=sqrt(n);
	int tmp[N];
	R(i,1,n) tmp[i]=a[i]=read();
	sort(tmp+1,tmp+n+1);
	m=unique(tmp+1,tmp+n+1)-tmp-1;
	R(i,1,n) a[i]=lower_bound(tmp+1,tmp+m+1,a[i])-tmp;
	R(i,1,n) qs[i].l=read(),qs[i].r=read(),qs[i].id=i;
	sort(qs+1,qs+n+1);
	int L=1,R=0;
	R(i,1,n)
	{
		while(L<qs[i].l) del(a[L++]);
		while(R>qs[i].r) del(a[R--]);
		while(L>qs[i].l) add(a[--L]);
		while(R<qs[i].r) add(a[++R]);
		ans[qs[i].id]=res;
	}
	R(i,1,n) printf("%lld\n",ans[i]);
}
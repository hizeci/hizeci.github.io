#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=1e9+7;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline int mul(int x) {return x % mod;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
inline void Mul(int &x, int y) {if ((x *= y) >= mod) x %= mod;}
inline int fpow(int a,int b){int res=1;while(b){if(b&1)Mul(res,a);Mul(a,a);b>>=1;}return res;}
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init()
{
	F[0]=Finv[0]=inv[1]=1;
	R(i,2,500) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	R(i,1,500) F[i]=mul(F[i-1]*i),Finv[i]=mul(Finv[i-1]*inv[i]);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	return mul(mul(F[n]*Finv[m])*Finv[n-m]);
}
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
int n,k;
int a[N];
int res1=-1,res2=-1;
inline int check(int x){
	int cnt=0,sum=0;for(int i=1;i<=n;i++) {sum+=a[i],sum=max(sum,0ll);if(sum>=x)cnt++,sum=0;} return cnt;
}
signed main()
{
	n=read(),k=read();
	R(i,1,n) a[i]=read();
	int l=1,r=(int)1e18;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		int tmp=check(mid);
		if(tmp<=k) {
			r=mid-1;
			if(tmp==k) res1=mid;
		}
		else l=mid+1;
	}
	l=1,r=(int)1e18;
	//printf("%lld\n",res1);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		//printf("%lld\n",mid);
		int tmp=check(mid);
		if(tmp>=k) {
			l=mid+1;
			if(tmp==k) res2=mid;
		}
		else r=mid-1;
	}
	if(!(~res1)) puts("-1");
	else printf("%lld %lld\n",res1,res2); 
}
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
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
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
const int mod=3e9+24;
const ld eps=1e-8;
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
const int N=111111;
struct ques
{
	int l,r,id;
}qs[N],nq[N];
int n,L,q;
int a[N],ans[N],sum[N];
int dpl[55][N],dpr[55][N];
void prel(int l,int r) {
	R(i,1,min(L,r-l+1)) {
		dpl[i][0]=0;
		R(j,1,r-l+2-i) dpl[i][j]=j>=L?max(dpl[i][j-1],dpl[i][j-L]+sum[r-i-j+1		+L]):0;
	}
}
void prer(int l,int r) {
	R(i,1,min(L,r-l+1)) {
		dpr[i][0]=0;
		R(j,1,r-l+2-i) dpr[i][j]=j>=L?max(dpr[i][j-1],dpr[i][j-L]+sum[l+i+j-2]):0;
	}
}
void solve(int l,int r,int ql,int qr) {
	if(ql>qr||r-l+1<L) return;
	int mid=(l+r)>>1;
	prel(l,mid),prer(mid+1,r);
	int totl=ql-1,totr=qr+1;
	R(i,ql,qr)
	{
		if(qs[i].r<=mid) nq[++totl]=qs[i];
		else if(qs[i].l>mid) nq[--totr]=qs[i];
		else{
			ans[qs[i].id]=dpl[1][mid-qs[i].l+1]+dpr[1][qs[i].r-mid];
			R(j,max(1ll,qs[i].l+L-1-mid),min(L,qs[i].r-mid+1)-1)
				ckmax(ans[qs[i].id],dpl[L-j+1][mid+j-L-qs[i].l+1]+dpr[j+1][qs[i].r-mid-j]+sum[mid+j]);
		} 
	}
	R(i,ql,totl) qs[i]=nq[i];
	L(i,totr,qr) qs[i]=nq[i];
	solve(l,mid,ql,totl),solve(mid+1,r,totr,qr);
}
signed main()
{
	n=read(),L=read();
	R(i,1,n) a[i]=read(),sum[i]=sum[i-1]+a[i];
	L(i,L,n) sum[i]-=sum[i-L];
	q=read();
	R(i,1,q) qs[i].l=read(),qs[i].r=read(),qs[i].id=i;
	solve(1,n,1,q);
	R(i,1,q) writeln(ans[i]);
}
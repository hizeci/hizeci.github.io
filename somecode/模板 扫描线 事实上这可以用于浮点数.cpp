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
const int N=2e6+10;
struct segmentree
{
	int l,r,sum,len;
}val[N<<2];
struct scanline
{
	int l,r,h,tag;
	inline bool operator <(const scanline a)const{
		return h==a.h?l>a.l:h<a.h;
	}
}Lin[N<<1];
int Y[N<<1];
int res;
int n;
/*
void build(int l,int r,int x)
{
	val[x].l=l,val[x].r=r;
	if(l==r-1) return;
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid,r,x<<1|1);
}
*/
void push_up(int l,int r,int x)
{
	if(val[x].sum>0) val[x].len=Y[r]-Y[l];
	else val[x].len=val[x<<1].len+val[x<<1|1].len;
}
void modify(int L,int R,int l,int r,int x,int k)
{
	if(L>=Y[r]||R<=Y[l]) return;
	if(L<=Y[l]&&Y[r]<=R) {val[x].sum+=k,push_up(l,r,x);return;}
	int mid=(l+r)>>1;
	modify(L,R,l,mid,x<<1,k),modify(L,R,mid,r,x<<1|1,k);
	push_up(l,r,x);
}
signed main()
{
	n=read();
	R(i,1,n)
	{
		int _x_=read(),_y_=read(),__x__=read(),__y__=read();
		Lin[i*2-1]=(scanline){_y_,__y__,_x_,1};
		Lin[i*2]=(scanline){_y_,__y__,__x__,-1};
		Y[i*2-1]=_y_,Y[i*2]=__y__;
	}
	n<<=1;
	sort(Y+1,Y+n+1);
	sort(Lin+1,Lin+n+1);
	int m=unique(Y+1,Y+n+1)-Y-1;
	//printf("%lld\n",m);
	FR(i,1,n)
	{
		modify(Lin[i].l,Lin[i].r,1,n,1,Lin[i].tag);
		res+=(Lin[i+1].h-Lin[i].h)*val[1].len;
	}
	printf("%lld\n",(int)res);
}
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
const int N=1e6+10;
int n;
int DX[N<<2];
//这段代码将所有右端点左移了一个
struct scanline
{
	int l,r,h,tag;
	inline bool operator <(scanline a)const{
		return h<a.h;
	}
}Lin[N<<2];
struct segmentree
{
	int l,r,sum,len;
	//SUM被完全覆盖的次数 LEN区间被截长度

}val[N<<2];
void build(int l,int r,int x)
{
	val[x]=(segmentree){l,r,0,0};
	//printf("%lld %lld %lld %lld\n",val[x].l,val[x].r,val[x].sum,val[x].len);
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
}
void push_up(int x)
{
	int l=val[x].l,r=val[x].r;
	if(val[x].sum) val[x].len=DX[r+1]-DX[l];
	else val[x].len=val[x<<1].len+val[x<<1|1].len;
}
void modify(int L,int R,int x,int k)
{
	int l=val[x].l,r=val[x].r;
	if(DX[r+1]<=L||DX[l]>=R) return;
//  这里加等号的原因：
//  假设现在考虑 [2,5], [5,8] 两条线段，要修改 [1,5] 区间的sum
//  很明显，虽然5在这个区间内，[5,8] 却并不是我们希望修改的线段
//  所以总结一下，就加上了等号
	if(L<=DX[l]&&DX[r+1]<=R) {
		val[x].sum+=k;
		push_up(x);
		return;
	}
	modify(L,R,x<<1,k);
	modify(L,R,x<<1|1,k);
	push_up(x);	
}
signed main()
{
	n=read();
	R(i,1,n) 
	{
		int _x_=read(),_y_=read(),__x__=read(),__y__=read();
		DX[2*i-1]=_x_,DX[2*i]=__x__;
		Lin[2*i-1]=(scanline){_x_,__x__,_y_,1};
		Lin[2*i]=(scanline){_x_,__x__,__y__,-1};
	}
	n<<=1;
	sort(Lin+1,Lin+n+1);
	sort(DX+1,DX+n+1);
	int m=unique(DX+1,DX+n+1)-DX-1;
	//为什么是 tot - 1 ：
//  因为右端点的对应关系已经被篡改了嘛…
//  [1, tot - 1]描述的就是[X[1], X[tot]]
	build(1,m-1,1);
	int res=0;
	FR(i,1,n)
	{
		modify(Lin[i].l,Lin[i].r,1,Lin[i].tag);
		res+=val[1].len*(Lin[i+1].h-Lin[i].h);
	}
	printf("%lld\n",res);
}

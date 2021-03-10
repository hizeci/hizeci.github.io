//Guobuliao
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
//#define int long long
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
int n,q,lst[N];
struct segmentreansBit
{
	int Rt[N],Ls[N<<5],Rs[N<<5],val[N<<5],cnt_seg;
	void _modify(int pos,int l,int r,int &x,int k)
	{
		if(!x) x=++cnt_seg;
		val[x]+=k;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(pos<=mid) _modify(pos,l,mid,Ls[x],k);
		else _modify(pos,mid+1,r,Rs[x],k);
	}
	int _query(int L,int R,int l,int r,int x)
	{
		if(L<=l&&r<=R) return val[x];
		int mid=(l+r)>>1,ret=0;
		if(L<=mid) ret+=_query(L,R,l,mid,Ls[x]);
		if(mid<R)  ret+=_query(L,R,mid+1,r,Rs[x]);
		return ret;
 	}
 	inline int lowbit(int x){
 		return x&(-x);
 	}
 	void modify(int x,int y){
 		for(int i=x;i<=n;i+=lowbit(i)) _modify(y+1,1,n+1,Rt[i],1);
 	}
 	int query(int l,int r,int x,int y)
 	{
 		int ret=0;
 		for(int i=r;i;i-=lowbit(i)) ret+=_query(x+1,y+1,1,n+1,Rt[i]);
 		//--l;
 		for(int i=l;i;i-=lowbit(i)) ret-=_query(x+1,y+1,1,n+1,Rt[i]);
 		return ret;
 	}
}stb;
signed main()
{
	stb.cnt_seg=0;
	n=read();
	R(i,1,n)
	{
		int x=read();
		stb.modify(i,lst[x]);
		lst[x]=i;
	}
	q=read();
	while(q--)
	{
		int l=read(),r=read();
		printf("%d\n",stb.query(l-1,r,0,l-1));
	}
}
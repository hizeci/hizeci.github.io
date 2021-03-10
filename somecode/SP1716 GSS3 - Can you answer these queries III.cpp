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
	const int inf=0x7f7f7f7f7f7f;
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
	/*
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 rand_num(seed);  
	uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
	printf("%lld ",dist(rand_num));
	*/
int n,q;
const int N=1e6+10;
int a[N];
int res,ans;
struct segmentree
{
	int sum[N],lmx[N],rmx[N],val[N];
	void push_up(int x)
	{
		sum[x]=sum[x<<1]+sum[x<<1|1];
		lmx[x]=max(lmx[x<<1],sum[x<<1]+lmx[x<<1|1]);
		rmx[x]=max(rmx[x<<1|1],sum[x<<1|1]+rmx[x<<1]);
		val[x]=max(max(val[x<<1],val[x<<1|1]),rmx[x<<1]+lmx[x<<1|1]);
	}
	void build(int l,int r,int x) 
	{
		if(l==r) 
		{
			sum[x]=lmx[x]=rmx[x]=val[x]=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		push_up(x);
	}
	void modify(int pos,int l,int r,int x,int k)
	{
		if(l==r) 
		{
			sum[x]=lmx[x]=rmx[x]=val[x]=k;
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid) modify(pos,l,mid,x<<1,k);
		else modify(pos,mid+1,r,x<<1|1,k);
		push_up(x);
	}
	void query(int L,int R,int l,int r,int x)
	{
		if(L<=l&&r<=R) 
		{
			res=max(max(res,val[x]),ans+lmx[x]);
			ans=max(rmx[x],ans+sum[x]);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid) query(L,R,l,mid,x<<1);
		if(mid<R)  query(L,R,mid+1,r,x<<1|1);
	}
}st;
signed main()
{
	n=read();
	R(i,1,n) a[i]=read();
	st.build(1,n,1);
	q=read();
	R(i,1,q) {
		int opt=read(),x=read(),y=read();
		if(opt==1){ st.modify(x,1,n,1,y);}
		else { if(x>y)Swap(x,y);ans=-inf,res=-inf,st.query(x,y,1,n,1);printf("%lld\n",res);}
	}
}
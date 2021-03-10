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

const int N=1e6+10;
int n,h[N],w[N];
int dp[N];
int s[N<<2];
struct line
{
	int k,b;
}p[N<<2];
int tot_seg;
inline int calc(int id,int x){
	return p[id].k*x+p[id].b;
}
inline void add_seg(int k,int b){
	p[++tot_seg].k=k,p[tot_seg].b=b;
}
void modify(int l,int r,int x,int u){
	/*
	//printf("%lld\n",u);
	int v=s[x],mid=(l+r)>>1;
	int resu=calc(u,mid),resv=calc(v,mid);
//	printf("%lld %lld\n",resu,resv);
	if(calc(u,l)<=calc(v,l)&&calc(u,r)<=calc(v,r)) {
	//	printf("l:%lld r:%lld x:%lld u:%lld v:%lld\n",l,r,x,u,v);		
		s[x]=u;		
	//	printf("s[x]:%lld c(u,l):%lld c(v,l):%lld c(u,r):%lld c(v,r):%lld\n",s[x],calc(u,l),calc(v,l),calc(u,r),calc(v,r));
		return ;
	}
	if(calc(u,l)>=calc(v,l)&&calc(u,r)>=calc(v,r)) return;
	if(p[u].k>p[v].k) {
		if(resu<resv) {
			s[x]=u;
			modify(l,mid,x<<1,v);
		}
		else modify(mid+1,r,x<<1|1,u);
	}
	else if(p[u].k<p[v].k) {
		if(resu<resv) {
			s[x]=u;
			modify(mid+1,r,x<<1|1,u);
		}
		else modify(l,mid,x<<1,v);
	}
	else  {
		if(p[u].b<p[v].b) s[x]=u;
	}
	*/	
	int mid=(l+r)>>1,v=s[x];
	int resu=calc(u,mid),resv=calc(v,mid);
	if(l==r) {
		if(resu<resv) s[x]=u;
		return;
	} 
	if(resu<resv) Swap(u,s[x]);
	if(calc(u,l)<calc(s[x],l)) modify(l,mid,x<<1,u);
	else if(calc(u,r)<calc(s[x],r)) modify(mid+1,r,x<<1|1,u);
}
inline int query_min(int pos,int l,int r,int x){
	int ret=calc(s[x],pos);
	if(l==r) return ret;
	int mid=(l+r)>>1;
	if(pos<=mid) ret=min(ret,query_min(pos,l,mid,x<<1));
	if(mid<pos)  ret=min(ret,query_min(pos,mid+1,r,x<<1|1));
	return ret;
}

signed main()
{
	n=read();
	R(i,1,n) h[i]=read();
	R(i,1,n) w[i]=read()+w[i-1];
	//R(i,1,n) printf("%lld\n",w[i]);
	//add_seg(0,inf);
	p[0]=(line){0,inf};
	//modify(0,1000000,1,tot_seg);	
	//R(i,0,1000000) if(s[i]!=0) printf("%lld %lld\n",i,s[i]);
	//puts("qwee");
	add_seg(-2*h[1],h[1]*h[1]-w[1]);
	modify(0,N,1,tot_seg);
	//R(i,0,N-10) if(s[i]) printf("%lld %lld\n",i,s[i]);
	R(i,2,n) {
		dp[i]=h[i]*h[i]+w[i-1]+query_min(h[i],0,N,1);
		//printf("%lld %lld\n",h[i]*h[i]+w[i-1],query_min(h[i],0,N,1));
		add_seg(-2*h[i],dp[i]+h[i]*h[i]-w[i]);
		modify(0,N,1,tot_seg);		
		//puts("faq");
		//R(i,0,1000000) if(s[i]!=0) printf("%lld %lld\n",i,s[i]);
		//puts("qaf");
		//printf("%lld\n",dp[i]);
	}
	printf("%lld\n",dp[n]);
}
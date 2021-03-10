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
const int N=4e6+10;
typedef pair<double,int>pdi;
struct line
{
	double k,b;
}p[N];
int n,tot_seg;
int s[N];
inline double calc(int id,int x){
	return p[id].k*(x-1)+p[id].b;
}
inline void add_beeline(double k,double b){
	++tot_seg;
	p[tot_seg].k=k,p[tot_seg].b=b;
}
void modify(int l,int r,int x,int u){
	int v=s[x],mid=(l+r)>>1;
	double resu=calc(u,mid),resv=calc(v,mid);
	if(l==r) {
		if(resu>resv) s[x]=u;
		return;
	} 
	if(p[u].k>p[v].k)
	{
		if(resu>resv) {
			s[x]=u;
			modify(l,mid,x<<1,v);
		}
		else modify(mid+1,r,x<<1|1,u);
	}
	else if(p[u].k<p[v].k){
		if(resu>resv) {
			s[x]=u;
			modify(mid+1,r,x<<1|1,v);
		}
		else modify(l,mid,x<<1,u);
	}
	else {
		if(p[u].b>p[v].b) s[x]=u;
	}
	//modify(l,mid,x<<1,u),modify(mid+1,r,x<<1|1,u);
}
inline pdi PMax(pdi x,pdi y){
	return (x.fi<y.fi)?y:(x.fi>y.fi)?x:(x.se<y.se)?x:y;
}
inline pdi query_beeline(int pos,int l,int r,int x){
	double res=calc(s[x],pos);
	//printf("%.5lf\n",res);
	pdi ret={res,s[x]};
	if(l==r) return ret;
	int mid=(l+r)>>1;
	if(pos<=mid) ret=PMax(ret,query_beeline(pos,l,mid,x<<1));
	else ret=PMax(ret,query_beeline(pos,mid+1,r,x<<1|1));
	return ret;
}
char opt[111];
signed main()
{
	n=read();
	R(i,1,n) {
		scanf("%s",opt+1);
		if(opt[1]=='P') {
			double S,P;
			scanf("%lf%lf",&S,&P);
			add_beeline(P,S);
			modify(1,50005,1,tot_seg);
		}
		if(opt[1]=='Q') {
			int x=read();
			double tmp=query_beeline(x,1,50005,1).fi;
			//printf("%.5lf\n",tmp);
			printf("%lld\n",(int)tmp/100);
		}		
		//for(int i=1;i<=10;i++) printf("%lld\n",s[i]);
	}
}	
/*
10 
Pr 1000 10
Q 3
*/
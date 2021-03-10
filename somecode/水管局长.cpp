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
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
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
const int N=3e5+10;
int n,m,q;
map<pii,int>mp;
int ans[N],vis[N];
struct edge
{
	int u,v,d;
	inline bool operator <(const edge a)const{
		return d<a.d;
	}
}qs[N<<1];
struct ques
{
	int opt,x,y,id;
}qs[N];
int tag[N],fa[N],son[N][2],val[N],maxx[N];
inline void clear(int x){
	tag[x]=fa[x]=son[x][1]=son[x][0]=val[x]=maxx[x]=0;
}
inline int get(int x){
	return x==son[fa[x]][1];
}
inline int isnotroot(int x){
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
inline void push_up(int x){
	maxx[x]=val[x];
	if(e[maxx[son[x][0]]].d>e[maxx[x]].d) maxx[x]=maxx[son[x][0]];
	
}
signed main()
{
	n=read(),m=read(),q=read();
	R(i,1,m) {
		int u=read(),v=read(),d=read();
		if(x>y) Swap(u,v);
		e[i]=(edge){u,v,d};
	}
	sort(e+1,e+m+1);
	R(i,1,m) mp[mkp(e[i].u,e[i].v)]=i;
	R(i,1,q) {
		int opt=read(),u=read(),v=read();
		if(u>v) Swap(u,v);
		if(opt==2) {
			int id=mp[mkp(u,v)];
			vis[id]=1;
			qs[i]=(que){opt,u,v,id};
		}	
		else qs[i]=(ques){opt,u,v,0};
	}
	R(i,1,m) maxx[i+n]=val[i+n]=i;
	int cnt_eg=0;
	R(i,1,m) if(!vis[i])
	{
		int u=e[i].u,v=e[i].v;
		if()
	}

}
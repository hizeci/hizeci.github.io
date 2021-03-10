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
int n,m,q;
int ans[111111],fa[111111],siz[111111],rk[111111];
struct edge
{
	int x,y;
}e[111111];
struct ques
{
	int x,y,z,id;
}qs[111111],tmp[111111];
int find_fa(int x){return (x==fa[x])?x:find_fa(fa[x]);}
inline int merge(int u,int v){
	u=find_fa(u),v=find_fa(v);
	if(u==v) return 0;
	if(rk[u]<rk[v]) Swap(u,v);
	fa[v]=u,siz[u]+=siz[v];
	if(rk[u]==rk[v]) 
	{
		rk[u]++;
		return -v;
	}else return v;
}
void solve(int L,int R,int l,int r)
{
	if(l>r) return;
	if(L==R) {R(i,l,r) ans[qs[i].id]=L;return;}
	int mid=(L+R)>>1;
	stack<int>stk;
	R(i,L,mid) stk.push(merge(e[i].x,e[i].y));
	int totl=l-1,totr=r+1;
	R(i,l,r)
	{
		int u=find_fa(qs[i].x),v=find_fa(qs[i].y);
		if(siz[u]+(u!=v)*siz[v]>=qs[i].z) tmp[++totl]=qs[i];
		else tmp[--totr]=qs[i];
	}
	R(i,l,r) qs[i]=tmp[i];
	solve(mid+1,R,totr,r);
	while((int)stk.size()>0)
	{
		int u=stk.top();stk.pop();
		if(!u) continue;
		if(u<0) rk[fa[u]]--,u=-u;
		siz[fa[u]]-=siz[u],fa[u]=u;	
	}
	solve(L,mid,l,totl);
}
signed main()
{
	n=read(),m=read();
	R(i,1,m) e[i].x=read(),e[i].y=read();
	q=read();
	R(i,1,q) qs[i].x=read(),qs[i].y=read(),qs[i].z=read(),qs[i].id=i;
	R(i,1,n) siz[i]=1,fa[i]=i;	 
	solve(1,m,1,q);
	R(i,1,q) printf("%lld\n",ans[i]);
}
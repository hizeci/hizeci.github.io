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
//const int mod=9223372036854775807;
const ld eps=1e-8;
//inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
/*
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
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

const int B=300;
const int N=1e5+10;
int n,m,q;
int a[N],in[N],is_big[N];
vector<int>e[N],cnt[N],tag[N];
vector<pii>big_neb[N];
void ins(int u,int x)
{
	ckmin(x,in[u]);
	cnt[u][x]++;
	if(cnt[u][x]==1) tag[u][x/B]++;
}
void del(int u,int x)
{
	ckmin(x,in[u]);
	cnt[u][x]--;
	if(!cnt[u][x]) tag[u][x/B]--;
}
int query_mex(int u)
{
	for(int i=0;i<=in[u];i+=B)
	{
		int j=min(i+B-1,in[u]);
		if(tag[u][i/B]<j-i+1){
			R(k,i,j) if(!cnt[u][k]) return k;
		}
	}
}
void solve()
{
	n=read(),m=read();
	R(i,1,n) {in[i]=0,is_big[i]=0;vector<int>().swap(e[i]);vector<int>().swap(cnt[i]);vector<int>().swap(tag[i]);vector<pii>().swap(big_neb[i]);}
	R(i,1,n) a[i]=read();
	R(i,1,m) 
	{
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
		in[u]++,in[v]++;
	}
	R(i,1,n)
	{
		is_big[i]=(in[i]>B);
		cnt[i].resize(in[i]+1);
		tag[i].resize(in[i]/B+1);
	}
	R(u,1,n)
	{
		FR(i,0,sz(e[u]))
		{
			int v=e[u][i];
			if(is_big[v]) big_neb[u].pb(mkp(v,a[v]));
			ins(u,a[v]);
		}
	}
	q=read();
	while(q--)
	{
		int opt=read();
		if(opt==1)
		{
			int u=read(),x=read();
			if(is_big[u]) a[u]=x;
			else
			{
				FR(i,0,sz(e[u])) {
					int v=e[u][i];
					del(v,a[u]);
					ins(v,x);
				}
				a[u]=x;
			}
		}
		else
		{
			int u=read();
			FR(i,0,sz(big_neb[u]))
			{
				int v=big_neb[u][i].fi,od_a=big_neb[u][i].se;
				if(od_a!=a[v])
				{
					del(u,od_a);
					ins(u,a[v]);
					big_neb[u][i].se=a[v];
				}
			}
			printf("%d\n",query_mex(u));
		}
	}
}
signed main()
{
	int _;
	for(_=read();_;_--) solve();
}
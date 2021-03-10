#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
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
const int mod=998244353;
const double eps=1e-6;
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
const int djq=998244353;
const int N=2e5+10;
const int M=3e7+10;
bool isnotpri[N];
int pri[N],tot_pri,min_pri[N];
void eulsh() 
{
	R(i,2,N-10) 
	{
		if(!isnotpri[i]) pri[++tot_pri]=i;
		R(j,1,tot_pri) 
		{
			int qwq=i*pri[j];
			if(qwq>=(N-10)) break;
			isnotpri[qwq]=1;
			min_pri[qwq]=pri[j];
			if(i%pri[j]==0) break;
		}
	}	
} 
int Rt[N],n,Ls[M],Rs[M],tot_seg,val[M],lst_ans;
std::vector<pii> v[N];
void build(int l,int r,int &x)
{
	x=++tot_seg;
	val[x]=1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,Ls[x]);
	build(mid+1,r,Rs[x]);
}
void modify(int L,int R,int l,int r,int lst,int &x,int k) {
	x=++tot_seg;Ls[x]=Ls[lst],Rs[x]=Rs[lst],val[x]=val[lst];
	if(L<=l&&r<=R) {val[x]=1ll*val[lst]*k%djq;return;}	
	int mid=(l+r)>>1;
	if(L<=mid) modify(L,R,l,mid,Ls[lst],Ls[x],k);
	if(mid<R)  modify(L,R,mid+1,r,Rs[lst],Rs[x],k);
}
int query(int pos,int l,int r,int x)
{
	if(l==r) return val[x];
	int mid=(l+r)>>1;
	if(pos<=mid) return 1ll*val[x]*query(pos,l,mid,Ls[x])%djq;
	else return 1ll*val[x]*query(pos,mid+1,r,Rs[x])%djq;
}

signed main()
{
	eulsh();
	n=read();
	R(i,1,tot_pri) v[pri[i]].pb(mkp(0,1<<30));
	build(1,n,Rt[0]);
	R(i,1,n) 
	{
		Rt[i]=Rt[i-1];
		int x=read();
		for(;x^1;)
		{
			int p=min_pri[x],q=1; 
			if(!p)p=x;
			for(;x%p==0;x/=p,q*=p);
			for(;v[p].back().se<=q;)
			{
				int key=v[p].back().se,r=v[p].back().fi;v[p].pop_back();
				modify(v[p].back().fi+1,r,1,n,Rt[i],Rt[i],fpow(key));
			}
			modify(v[p].back().fi+1,i,1,n,Rt[i],Rt[i],q);
			v[p].pb(mkp(i,q));
		}
	}
	for(int q=read();q--;)
	{
		int l=read(),r=read();
		l=(l+lst_ans)%n+1,r=(r+lst_ans)%n+1;l>r?Swap(l,r):1;
		lst_ans=query(l,1,n,Rt[r]);
		printf("%lld\n",lst_ans);
	}
}
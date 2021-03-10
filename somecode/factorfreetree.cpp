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
const int N=1111111;
int n,mxrange;
int pri[N],tot_pri;
bool isnotpri[N*10];
int a[N],rec_L[N],rec_R[N];
int lst[N*10],min_pri[N*10];
int fa[N];

void euler_shai() {
	R(i,2,mxrange) {
		if(!isnotpri[i]) pri[++tot_pri]=i,min_pri[i]=tot_pri;
		R(j,1,tot_pri) 
		{
			int qwq=i*pri[j];
			if(qwq>mxrange) break;
			isnotpri[qwq]=1;
			min_pri[qwq]=j;
			if(i%pri[j]==0) break;
		}
	}
}
int solve(int l,int r,int f)
{
	if(l>r) return 1;
	int L=l,R=r;
	while(L<=R)
	{
		if(rec_L[L]<l&&rec_R[L]>r){fa[L]=f;return solve(l,L-1,L)&&solve(L+1,r,L);}
		if(rec_L[R]<l&&rec_R[R]>r){fa[R]=f;return solve(l,R-1,R)&&solve(R+1,r,R);}
		L++;R--;
	}
	return 0;
}
signed main()
{
	n=read();
	R(i,1,n) a[i]=read(),mxrange=max(a[i],mxrange);
	mxrange+=5;
	euler_shai();
	R(i,1,n)
	{
		int cur=a[i],tmp=0;
		while(cur^1)
		{
			int qwq=pri[min_pri[cur]];
			ckmax(tmp,lst[qwq]);
			lst[qwq]=i;
			while(cur%qwq==0) cur/=qwq;
		}
		rec_L[i]=tmp;
	}
	fill(lst,lst+mxrange+5,n+1);
	L(i,1,n)
	{
		int cur=a[i],tmp=n+1;
		while(cur^1)
		{
			int qwq=pri[min_pri[cur]];
			ckmin(tmp,lst[qwq]);
			lst[qwq]=i;
			while(cur%qwq==0) cur/=qwq;
		}
		rec_R[i]=tmp;
	}
	if(solve(1,n,0)) R(i,1,n) writesp(fa[i]);
	else puts("impossible");
}
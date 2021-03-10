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
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const int mod=10007;
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
    if(f)x=-x;
	return x;
}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
typedef vector<int> vi;
int n,m,q;
string s,t;
vi a,b,c[4];
inline int solve(int x,int y,int X,int Y,int fx=1,int fy=1){
	int I=a[x],J=b[y],dx=0,dy=0;
	if((I==1&&Y<=y)||(I==3&&y<=Y)) dx=1;
	if((!J&&X<=x)||(J==2&&x<=X)) dy=1;
	if(dx&&dy) {
		if(I==a[x]||J==b[y]) return (abs(x-X)+abs(y-Y));
		auto ix=lob(c[I].bg,c[I].ed,X),iy=lob(c[J].bg,c[J].ed,Y);
		if(!J) ix--; if(I==1) iy--;
		int tx=(0<=*ix&&*ix<n?abs(*ix-x)+abs(*ix-X)+abs(y-Y):inf);
		int ty=(0<=*iy&&*iy<m?abs(*iy-y)+abs(*iy-Y)+abs(x-X):inf);
		return min(tx,ty);
	} 
	auto ix=lob(c[(I+2)%4].bg,c[(I+2)%4].ed,x),iy=lob(c[(J+2)%4].bg,c[(J+2)%4].ed,y);
	if(!J) ix--; if(I==1) iy--;
	int tx=(fx&&0<=*ix&&*ix<n?solve(*ix,y,X,Y,0,1)+abs(*ix-x):inf);
	int ty=(fy&&0<=*iy&&*iy<m?solve(x,*iy,X,Y,1,0)+abs(*iy-y):inf);
	return min(tx,ty);
}
signed main(){
	n=read(),m=read(),q=read();
	cin>>s>>t;
	a=vi(n,1),b=vi(m);
	FR(i,0,4) c[i].pb(-1);
	FR(i,0,n) {
		if(s[i]=='E') a[i]=3;
		c[a[i]].pb(i);
	}
	FR(i,0,m) {
		if(t[i]=='S') b[i]=2;
		c[b[i]].pb(i);
	}
	FR(i,0,4) c[i].pb(inf);
	FR(i,0,q) {
		int x=read()-1,y=read()-1,X=read()-1,Y=read()-1;
		int res=solve(x,y,X,Y);
		printf("%lld\n",(res>=inf)?-1:res);
	}
}	
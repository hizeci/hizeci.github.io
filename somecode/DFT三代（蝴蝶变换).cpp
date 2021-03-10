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
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
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
inline void write(int x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(int x){write(x),putchar(' ');}
inline void writeln(int x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int N=1351111;
int n,m;
struct CP
{
	double x,y;
	CP (double xx=0,double yy=0) {x=xx,y=yy;}
	CP operator + (CP const &A)const{return CP(x+A.x,y+A.y);} 
	CP operator - (CP const &A)const{return CP(x-A.x,y-A.y);}
	CP operator * (CP const &A)const{return CP(x*A.x-y*A.y,x*A.y+y*A.x);}
	CP operator / (CP const &A)const{double tt=A.x*A.x-A.y*A.y;return CP((x*A.x+y*A.y)/tt,(y*A.x-x*A.y)/tt);}
}f[N<<1],p[N<<1];
//rev=1->DFT,rev=0->IDFT
void fft(CP *f,int len,int rev) 
{
	if(len==1) return;
	fft(f,len/2,rev);fft(f+len/2,len/2,rev);
	CP tG(cos(2*Pi/len),sin(2*Pi/len)),buf(1,0);
	if(!rev) tG.y*=-1;
	R(k,0,len/2-1){
		//注意到指针fl[k] <--> f[k] . . . fr[k] <--> f[k+len/2]
		CP tt=buf*f[k+len/2];
		f[k+len/2]=f[k]-tt;
		f[k]=f[k]+tt;
		buf=buf*tG;
	}
}
int tr[N<<1];

signed main()
{
	n=read(),m=read();
	R(i,0,n) scanf("%lf",&f[i].x);
	R(i,0,m) scanf("%lf",&p[i].x);
	for(m+=n,n=1;n<=m;n<<=1);
	R(i,0,n-1) tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	R(i,0,n-1) if(i<tr[i]) swap(f[i],f[tr[i]]),swap(p[i],p[tr[i]]);
	fft(f,n,1);fft(p,n,1);//DFT
	R(i,0,n-1) f[i]=f[i]*p[i];
	R(i,0,n-1) if(i<tr[i]) swap(f[i],f[tr[i]]);
	fft(f,n,0);
	R(i,0,m) printf("%lld ",(int)(f[i].x/n+0.499999));
}
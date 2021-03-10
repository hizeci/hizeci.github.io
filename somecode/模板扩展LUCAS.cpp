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
const ld eps=1e-8;
inline int fpow(int a,int b,int p=mod){int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}
/*
const int qwq=1e7+10;
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
inline void write(int x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(int x){write(x),putchar(' ');}
inline void writeln(int x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int N=1e6+10;
//excrt:
int a[N],b[N];
int pri[N],cnt_pri[N],tot_pri;
int n,m,p;
inline int QuickMul(int a,int b,int mod)
{
    int c=a*b-(int)((ld)a*b/mod+0.5)*mod;
    return c<0?c+mod:c;
}
int exgcd(int a,int b,int &x,int &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);y-=x*(a/b);
	return d;
}
inline int get_inv(int a,int mod){
	int x,y;
	exgcd(a,mod,x,y);
	return (x%mod+mod)%mod;
}

int excrt(){
	int M=b[1],ans=a[1];
	int x,y,k;
	R(i,2,tot_pri) {
		int A=M,B=b[i],C=(a[i]-ans%B+B)%B;//ax \equiv c(\bmod b)
		int D=exgcd(A,B,x,y),BG=B/D;
		if(C%D) return -1;
		x=QuickMul(x,C/D,BG);
		ans+=x*M;
		M*=BG;
		ans=(ans%M+M)%M;
	}
	return ans;
}
int calc(int n,int p,int pk)
{
	if(!n) return 1;
	int ans=1;
	R(i,1,pk) if(i%p) ans=ans*i%pk;
	ans=fpow(ans,n/pk,pk);
	R(i,1,n%pk) if(i%p) ans=ans*i%pk;
	return ans*calc(n/p,p,pk)%pk;
}
int solve(int n,int m,int p,int pk)
{
	if(n==0||m==0||n==m) return 1;
	if(n<m) return 0;
	int cnt=0,k=n-m;
	int nn=calc(n,p,pk),mm=calc(m,p,pk),nm=calc(k,p,pk);
	while(n) n/=p,cnt+=n;
	while(m) m/=p,cnt-=m;
	while(k) k/=p,cnt-=k;
	return nn*get_inv(mm,pk)*get_inv(nm,pk)%pk*fpow(p,cnt,pk)%pk;
} 
signed main()
{	
	n=read(),m=read(),p=read();
	int tmp=p;
	for(int i=2;i*i<=p;i++) {
		if(tmp%i==0)
		{c
			pri[++tot_pri]=i;
			while(tmp%i==0) tmp/=i,cnt_pri[tot_pri]++;
		}
	}
	if(tmp!=1) pri[++tot_pri]=tmp,cnt_pri[tot_pri]++;
	R(i,1,tot_pri) b[i]=fpow(pri[i],cnt_pri[i]),a[i]=solve(n,m,pri[i],b[i]);
	printf("%lld\n",excrt());
}
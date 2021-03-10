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
const int inf=0x7f7f7f7f7f7f;
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
const int N=2e5+10;

struct node
{
	int x,y;
	inline bool operator <(const node a)const{
		return (x^a.x)?x<a.x:y<a.y;
	}
}a[N],tmp[N];
int n,b[N];
inline int pin(int a){
	return a*a;
}
inline int dis(int x,int y){
	return pin(a[x].x-a[y].x)+pin(a[x].y-a[y].y);
}
inline int solve(int l,int r)
{
	if(l>=r) return inf;
	if(l+1==r) {if(a[l].y>a[r].y)swap(a[l],a[r]);return dis(l,r);}
	int mid=(l+r)>>1,t=a[mid].x,tot=0,d=min(solve(l,mid),solve(mid+1,r));
	int i=l,j=mid+1;
	R(k,l,r) if(i<=mid&&(j>r||a[i].y<a[j].y)) tmp[k]=a[i++];else tmp[k]=a[j++];
	R(k,l,r) a[k]=tmp[k];
	R(k,l,r) if(pin(a[k].x-t)<d) b[++tot]=k;
	R(i,1,tot) for(int j=i+1;j<=tot&&pin(a[b[j]].y-a[b[i]].y)<d;j++) d=min(d,dis(b[i],b[j]));
	return d;
}

signed main()
{
	n=read();
	R(i,1,n) a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1);
	printf("%.4f\n",(double)sqrt(solve(1,n)));
}
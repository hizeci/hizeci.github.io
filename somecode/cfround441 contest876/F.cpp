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
int n;
int a[N];
int L[N],R[N];	
int stk[N],top;
int posL[N],posR[N];
int tmp[N];
signed main()
{
	//printf("%lld\n",(1ll<<32));
	n=read();
	R(i,1,n) a[i]=read();
	a[n+1]=inf;
	R(i,1,n+1) {
		while(top&&a[stk[top]]<a[i]) R[stk[top--]]=i-1;
		L[i]=stk[top]+1;stk[++top]=i;
	}
	//R(i,1,n) printf("L[%lld]:%lld R[%lld]:%lld \n",i,L[i],i,R[i]);
	R(i,1,n) R(j,0,30) if(a[i]&(1ll<<j)) tmp[j]=i;else posL[i]=max(posL[i],tmp[j]);
	R(i,0,32) tmp[i]=n+1; R(i,1,n)  posR[i]=n+1;
	L(i,1,n) R(j,0,30) if(a[i]&(1ll<<j)) tmp[j]=i;else posR[i]=min(posR[i],tmp[j]);
	//R(i,1,n) printf("posL[%lld]:%lld posR[%lld]:%lld \n",i,posL[i],i,posR[i]);
	int res=0;
	R(i,1,n){
		int ok1=0,ok2=0;
		if(L[i]<=posL[i]) res+=1ll*(R[i]-i+1)*(posL[i]-L[i]+1),ok1=1;
		if(posR[i]<=R[i]) res+=1ll*(i-L[i]+1)*(R[i]-posR[i]+1),ok2=1;
		if(ok1&&ok2) res-=1ll*(posL[i]-L[i]+1)*(R[i]-posR[i]+1);
	}
	printf("%lld\n",res);
}
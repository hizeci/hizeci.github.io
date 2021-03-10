#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=1e9+7;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline int mul(int x) {return x % mod;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
inline void Mul(int &x, int y) {if ((x *= y) >= mod) x %= mod;}
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}int n,m,l;
const int N=550;
int dp[N][N][2];
/*
dp[i][j]表示选了i个点有j条边的总方案数，第三维记录这个状态是否选过大小为l的块
1. 加入一个单独的点，这个点形成一个新的联通块 Add(dp[i][j],dp[i-1][j-1]);
2. 加入一条长度为k的链（2<=k<=l)。注意到链上的点可以随意排列，但是在图的意义下把一个排列翻转和原排列是等价的，所以是除2。
因为强制选编号最小的没选的点，于是组合数减1 Add(dp[i][j],dp[i-k][j-k+1]*C(k-1,n-(i-k)-1)*((k!)/2))
3.加入一个大小为2的环 Add(dp[i][j],dp[i-2][j-2]*C(2-1,n-(i-2)-1))
4.加入一个大小为K的环(k>2)Add(dp[i][j],dp[i-k][j-k]*C(k-1,n-(i-k)-1)*((K-1)!)/2);
*/
int F[N],inv[N],Finv[N];

void init()
{
	F[0]=Finv[0]=inv[1]=1;
	R(i,2,500) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	R(i,1,500) F[i]=mul(F[i-1]*i),Finv[i]=mul(Finv[i-1]*inv[i]);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	return mul(mul(F[n]*Finv[m])*Finv[n-m]);
}

signed main()
{	
	init();
	n=read(),m=read(),l=read();
	dp[0][0][0]=1;
	R(i,1,n)
	{
		R(j,0,i)
		{
			Add(dp[i][j][0],dp[i-1][j][0]);
			R(k,2,min(i,l))
			{
				if(j>=(k-1)) Add(dp[i][j][0],mul(mul(mul(dp[i-k][j-(k-1)][0]*C(i-1,k-1))*F[k])*Finv[2]));
				if(j>=k)     Add(dp[i][j][0],mul(mul(mul(dp[i-k][j-k][0]*C(i-1,k-1))*F[max(2ll,k-1)])*Finv[2]));
			}
			if(l==1) Add(dp[i][j][1],dp[i-1][j][0]);
			else Add(dp[i][j][1],dp[i-1][j][1]);
			FR(k,2,min(i,l))
			{
				if(j>=(k-1)) Add(dp[i][j][1],mul(mul(mul(dp[i-k][j-(k-1)][1]*C(i-1,k-1))*F[k])*Finv[2]));
				if(j>=k)     Add(dp[i][j][1],mul(mul(mul(dp[i-k][j-k][1]*C(i-1,k-1))*F[max(2ll,k-1)])*Finv[2]));
			}
			if(l>1&&i>=l) {
				if(j>=(l-1)) Add(dp[i][j][1],mul(mul(mul(dp[i-l][j-(l-1)][0]*C(i-1,l-1))*F[l])*Finv[2]));
				if(j>=l)     Add(dp[i][j][1],mul(mul(mul(dp[i-l][j-l][0]*C(i-1,l-1))*F[max(2ll,l-1)])*Finv[2]));
			}
		}
	}
	printf("%lld\n",dp[n][m][1]);
}
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
//const int inf=0x7f7f7f7f;
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
/*
考虑从一个点开始有多少个不同的字符串 有:dp[i]=\sum dp[j]+s[i]
对于每一个点，设hson[i]表示i的所有出边中dp值最大的那个。设所有形如i->hson[i]的边为重边
其他的边为轻边。可以发现，每次询问最多只会跳log次轻边。
对于轻边直接二分即可。考虑重边，由于重边是一个树形结构，直接树上倍增即可。
复杂度o(nlognlogw)
还有一个暴力的可持久化平衡树做法，可惜我不会，时间复杂度o(能过)
*/
const int MX=1e8;
const int N=1e5+10;
int _;
int n,m,q;
int s[N],vis[N],hson[N],dp[N],f[N];//f[u]从u到hson[u]需要跳过多少字符串
int bz[22][N],bzf[22][N];
std::vector<pii>e[N];
std::vector<int>val[N];//从u到e[u][i]需要跳过多少字符串
inline int cmp(pii a,pii b){
	return (a.se^b.se)?a.se<b.se:a.fi<b.fi;
}
int dfs(int u) {
	if(vis[u]) return dp[u];
	vis[u]=1;f[u]=dp[u]=s[u];
	for(auto qwq:e[u]){
		int v=qwq.se;
		dfs(v);
		if(dp[hson[u]]<dp[v]&&dp[u]<=MX) hson[u]=v,f[u]=dp[u];
		dp[u]+=dp[v];
		ckmin(dp[u],2*MX);
		val[u].pb(dp[u]); 
	}
	bz[0][u]=hson[u],bzf[0][u]=f[u];
	R(i,1,20) {
		bz[i][u]=bz[i-1][bz[i-1][u]];
		bzf[i][u]=bzf[i-1][bz[i-1][u]]+bzf[i-1][u];
		//printf("i:%lld u:%lld bzf:%lld %lld %lld\n",i,u,bzf[i][u],bzf[i-1][u],bzf[i-1][bz[i-1][u]]);
		ckmin(bzf[i][u],2*MX);
	}
	return dp[u];
}
inline int swim(int rk){
	int u=1,ret=0;
	while(1919810) {
		L(i,0,20) {
			if(bz[i][u]&&rk>bzf[i][u]) {
				int v=bz[i][u];
				if(rk>bzf[i][u]+dp[v]) continue;
				rk-=bzf[i][u];
				u=v,ret+=(1ll<<i);
			}
		}
		if(rk==1&&s[u]) return ret;
        int tmp=(int)(lob(val[u].begin(),val[u].end(),rk)-val[u].begin());
		if(tmp) rk-=val[u][tmp-1];
		else rk-=s[u];
		u=e[u][tmp].se,ret++;
	}
}
signed main()
{
	_=read();
	R(t,1,_) {
		printf("Case #%lld:\n",t);
		n=read(),m=read(),q=read();
		R(i,1,n) {
			vis[i]=0;
			dp[i]=-1;
			hson[i]=f[i]=0;e[i].clear(),val[i].clear();
			R(j,0,20) bz[j][i]=bzf[j][i]=0;
		}
		R(i,2,n) s[i]=read();
		R(i,1,m) {
			int u=read(),v=read(),d=read();
			e[u].pb(mkp(d,v));
		}
        
		R(i,1,n) sort(e[i].bg,e[i].ed);
		dfs(1);
		//R(i,1,20) {printf("dp:%lld f:%lld\n",dp[i],f[i]);}
		//R(i,0,5) R(j,1,10) printf("bz:%lld bzf:%lld\n",bz[i][j],bzf[i][j]);
		R(i,1,q) {
			int rk=read();
			//printf("duck:");
			if(rk>dp[1]) puts("-1");
			else printf("%lld\n",swim(rk));
		}


	}
}
/*
1
3 3 4
1 1
1 2 1
1 3 12
2 3 3
1
2
3
4
*/
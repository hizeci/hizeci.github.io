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
const int inf=0x7f7f7f3f;
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
const int N=2e3+10;
int n,m,faq;
struct node
{
	int dist,x,y;
	inline bool operator <(const node a)const{
		return dist>a.dist;
	}
};
priority_queue<node>q;
int dis[N][N],vis[N][N];
int r[N][N],c[N][N];
inline void dij(int sx,int sy,int tx,int ty)
{
	memset(vis,0,sizeof(vis));
	R(i,1,n) R(j,1,m) dis[i][j]=inf;
	dis[sx][sy]=0;
	q.push((node){dis[sx][sy],sx,sy});
	while(q.size()>0)
	{
		int ux=q.top().x,uy=q.top().y;q.pop();		
		if(vis[ux][uy]) continue;
		vis[ux][uy]=1;
		int vx=ux+1,vy=uy;
		if(dis[vx][vy]>dis[ux][uy]+c[ux][uy]) {
			dis[vx][vy]=dis[ux][uy]+c[ux][uy];
			q.push((node){dis[vx][vy],vx,vy});
		}
		vx=ux-1,vy=uy;
		if(dis[vx][vy]>dis[ux][uy]+c[vx][vy]) {
			dis[vx][vy]=dis[ux][uy]+c[vx][vy];
			q.push((node){dis[vx][vy],vx,vy});
		}
		vx=ux,vy=uy+1;
		if(dis[vx][vy]>dis[ux][uy]+r[ux][uy]) {
			dis[vx][vy]=dis[ux][uy]+r[ux][uy];
			q.push((node){dis[vx][vy],vx,vy});
		}
		vx=ux,vy=uy-1;
		if(dis[vx][vy]>dis[ux][uy]+r[vx][vy]) {
			dis[vx][vy]=dis[ux][uy]+r[vx][vy];
			q.push((node){dis[vx][vy],vx,vy});
		}
	}	
}
signed main()
{
	freopen("diss.in","r",stdin);
	freopen("diss.out","w",stdout);
	n=read(),m=read();
	R(i,1,n) FR(j,1,m) r[i][j]=read();
	FR(i,1,n) R(j,1,m) c[i][j]=read();
	faq=read();
	while(faq--)
	{
		int sx=read(),sy=read(),tx=read(),ty=read();
		dij(sx,sy,tx,ty);
		printf("%lld\n",dis[tx][ty]);
	}
}
/*
2 2
2
3
6 4
2
1 1 2 2
1 2 2 1

2 3
558 163
102 2000
461 1732 561
2
2 1 2 3
1 2 2 2
*/

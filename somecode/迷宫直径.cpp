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
const int mod=1e9+7;
//const int mod=10007;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}

const int qwq=2000010;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}

inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return 1ll*F[n]%mod*1ll*Finv[m]*1ll%mod*1ll*Finv[n-m]%mod;}


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

const int N=26;
int n,m;
int vis[N][N],dis[N][N];
char s[N][N];
int res;
signed main(){
	n=read(),m=read();
	R(i,1,n) scanf("%s",s[i]+1);
	R(i,1,n) {
		R(j,1,m) {
			if(s[i][j]=='#') continue;
			memset(vis,0,sizeof(vis));
			memset(dis,0,sizeof(dis));
			deque<pii>q;
			q.pb(mkp(i,j));
			vis[i][j]=1;
			while(q.size()>0){
				int x=q.front().fi,y=q.front().se;q.pop_front();
				int xx=x+1,yy=y;
				if(xx>0&&yy>0&&xx<=n&&yy<=m&&s[xx][yy]=='.'&&!vis[xx][yy]) {
					vis[xx][yy]=1;
					dis[xx][yy]=dis[x][y]+1;
					res=max(dis[xx][yy],res);
					q.pb(mkp(xx,yy));
				}
				xx=x-1,yy=y;
				if(xx>0&&yy>0&&xx<=n&&yy<=m&&s[xx][yy]=='.'&&!vis[xx][yy]) {
										vis[xx][yy]=1;

					dis[xx][yy]=dis[x][y]+1;
					res=max(dis[xx][yy],res);
					q.pb(mkp(xx,yy));
				}
				xx=x,yy=y+1;
				if(xx>0&&yy>0&&xx<=n&&yy<=m&&s[xx][yy]=='.'&&!vis[xx][yy]) {
										vis[xx][yy]=1;

					dis[xx][yy]=dis[x][y]+1;
					res=max(dis[xx][yy],res);
					q.pb(mkp(xx,yy));
				}
				xx=x,yy=y-1;
				if(xx>0&&yy>0&&xx<=n&&yy<=m&&s[xx][yy]=='.'&&!vis[xx][yy]) {					vis[xx][yy]=1;

					dis[xx][yy]=dis[x][y]+1;
					res=max(dis[xx][yy],res);
					q.pb(mkp(xx,yy));
				}

			}
		}
	}
	printf("%lld\n",res);
}

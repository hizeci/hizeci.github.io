#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define us unsigned 
#define ll long long
#define ull unsigned long long
//#define int long long
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x,T y){return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x,T y){return x>y?x=y,true:false;}
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
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
const int N=1010;
const int dx[]={1,-1,-1,1};
const int dy[]={1,1,-1,-1};
const int ex[]={0,-1,-1,0};
const int ey[]={0,0,-1,-1};
const char fuck[]="\\/\\/";
deque<pii>q;
int n,m;
char a[N][N];
int dis[N][N];
int bfs() 
{
	R(i,0,n+1)R(j,0,m+1) dis[i][j]=inf;
	dis[0][0]=0;
	q.pb(mkp(0,0));
	while((int)q.size()>0) 
	{
		int x=q.front().fi,y=q.front().se;q.pop_front();
		R(i,0,3)
		{
			int xx=x+dx[i],yy=y+dy[i],wx=x+ex[i],wy=y+ey[i];
			if(0<=xx&&xx<=n&&0<=yy&&yy<=m) 
			{				
				int dist=(fuck[i]!=a[wx][wy])+dis[x][y];
				if(fuck[i]!=a[wx][wy]) 
				{
					if(dis[xx][yy]>dist){
						q.pb(mkp(xx,yy));
						dis[xx][yy]=dist;
					}
				}
				else 
				{
					if(dis[xx][yy]>dist){
						q.push_front(mkp(xx,yy));
						dis[xx][yy]=dist;
					}
				}
				//printf("%d\n",dist);		
			}
		}
	}
	return dis[n][m];
}
signed main()
{
	n=read(),m=read();
	if((n+m)%2) return puts("NO SOLUTION")&0;
	R(i,0,n-1) scanf("%s",a[i]);
	printf("%d\n",bfs());
}
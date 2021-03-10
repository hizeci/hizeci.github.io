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
/*
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
*/
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f;
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
const int N=1e3+10;
int n;
int sx,sy,tx,ty,cx,cy;
int dx[10]={0,1,-1,0,0,1,-1,1,-1};
int dy[10]={0,0,0,1,-1,1,-1,-1,1};
int can[N][N];
int vis[N][N];
inline int check(int x,int y)
{
	if(x<1||y<1||x>n||y>n) return 0;
	return 1;
}
inline void print_mat()
{
	R(i,1,n){ R(j,1,n) printf("%lld ",can[i][j]);puts("");}
}

void dfs(int x,int y)
{
	if(x==tx&&y==ty)
	{
		puts("YES");
		exit(0);
	}
	for(int i=1;i<=8;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(check(xx,yy)&&!can[xx][yy]&&!vis[xx][yy]){
			vis[xx][yy]=1;
			dfs(xx,yy);
			vis[xx][yy]=0;
		}
	}
}


signed main()
{
	freopen("king.in","r",stdin);
	freopen("king.out","w",stdout);
	n=read();
	cx=read(),cy=read();
	sx=read(),sy=read();
	tx=read(),ty=read();
	if(n<=20)
	{
		R(i,1,n) 
		{
			can[cx][i]=can[i][cy]=1;
			if(check(cx+i,cy+i)) can[cx+i][cy+i]=1;
			if(check(cx+i,cy-i)) can[cx+i][cy-i]=1;
			if(check(cx-i,cy+i)) can[cx-i][cy+i]=1;
			if(check(cx-i,cy-i)) can[cx-i][cy-i]=1;
		}
		//print_mat();
		dfs(sx,sy);
		puts("NO");
		return 0;
	}
	if(sx==tx&&sy==ty) {
		puts("YES");
		return 0;
	}
	if(sx>tx) Swap(sx,tx);
	if(sy<ty) Swap(sy,ty);
	if((sx<=cx&&cx<=tx)||(sy<=cy&&cy<=ty))
	{
		puts("NO");
		return 0;
	}
	/*
	R(i,1,n)
	{
		if(check(cx+i,cy+i)) 
		{
			int xx=cx+i,yy=cy+i;
			if((sx<=xx&&xx<=tx)||(sy<=yy&&yy<=ty))
			{
				puts("NO");
				return 0;
			}
		}
		if(check(cx+i,cy-i)) 
		{
			int xx=cx+i,yy=cy-i;
			if((sx<=xx&&xx<=tx)||(sy<=yy&&yy<=ty))
			{
				puts("NO");
				return 0;
			}
		}
		if(check(cx-i,cy+i)) 
		{
			int xx=cx-i,yy=cy+i;
			if((sx<=xx&&xx<=tx)||(sy<=yy&&yy<=ty))
			{
				puts("NO");
				return 0;
			}
		}
		if(check(cx-i,cy-i))
		{
			int xx=cx-i,yy=cy-i;
			if((sx<=xx&&xx<=tx)||(sy<=yy&&yy<=ty))
			{
				puts("NO");
				return 0;
			}
		}
	}
	*/
	puts("YES");
	return 0;
}
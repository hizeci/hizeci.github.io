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
//const int mod=1e9+7;
const int mod=9223372036854775807;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline int mul(int x) {return x % mod;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
inline void Mul(int &x, int y) {if ((x *= y) >= mod) x %= mod;}
inline int fpow(int a,int b){int res=1;while(b){if(b&1)Mul(res,a);Mul(a,a);b>>=1;}return res;}
const int ovo=5050;
int F[ovo],inv[ovo],Finv[ovo];
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
const int N=55;
const int M=110;
const int L=2050;
int n,m;
char s[N],t[N];
int dp[N][M][L];
int vis[N][M][L],qwq[N][M][L];
int ooo,res;
struct AC_automaton
{
	struct tri
	{
		int ch[30],fil,end;
	}AC_A[M];
	int tot;
	AC_automaton() {tot=0;}
	void ins(char *s,int num)
	{
		int now=0;
		for(int j=1;s[j];j++)
		{
			int x=s[j]-'a';
			if(!AC_A[now].ch[x]) AC_A[now].ch[x]=++tot;
			now=AC_A[now].ch[x];
		}
		AC_A[now].end|=(1<<num);
	}
	void get_fail()
	{
		deque<int>q;
		FR(i,0,26)
			if(AC_A[0].ch[i])
			{
				AC_A[AC_A[0].ch[i]].fil=0;
				q.pb(AC_A[0].ch[i]);
			}
		while(q.size()>0)
		{
			int u=q.front();
			q.pop_front();
			AC_A[u].end|=AC_A[AC_A[u].fil].end;
			FR(i,0,26) if(AC_A[u].ch[i]) 
			{
				int v=AC_A[u].ch[i];
				AC_A[v].fil=AC_A[AC_A[u].fil].ch[i];
				q.pb(v);
			}
			else AC_A[u].ch[i]=AC_A[AC_A[u].fil].ch[i];
		}
	}
}AC;
int Sear(int x,int y,int z)
{
	if(x==n) {
		vis[x][y][z]=1;
		return qwq[x][y][z]=(z==((1<<m)-1));
	}
	if(vis[x][y][z]) return qwq[x][y][z];
	vis[x][y][z]=1;
	int ok=0;
	FR(i,0,26) ok|=Sear(x+1,AC.AC_A[y].ch[i],z|AC.AC_A[AC.AC_A[y].ch[i]].end);
	return qwq[x][y][z]=ok; 
}
void Print(int x,int y,int z)
{
	if(!qwq[x][y][z]) return;
	if(x==n) {
		R(i,1,n) printf("%c",t[i]);//putchar(t[i]);
		puts("");
		return;
	}
	FR(i,0,26) t[x+1]=i+'a',Print(x+1,AC.AC_A[y].ch[i],z|AC.AC_A[AC.AC_A[y].ch[i]].end);
}
signed main()
{
	n=read(),m=read();
	ooo=(1<<m)-1;
	R(i,1,m)
	{
		scanf("%s",s+1);
		AC.ins(s,i-1);
	}
	AC.get_fail();
	dp[0][0][0]=1;
	FR(i,0,n) R(j,0,AC.tot) R(mask,0,ooo) 
	if(dp[i][j][mask]) FR(l,0,26) 
		Add(dp[i+1][AC.AC_A[j].ch[l]][mask|AC.AC_A[AC.AC_A[j].ch[l]].end],dp[i][j][mask]);
	for(int i=0;i<=AC.tot;i++) Add(res,dp[n][i][ooo]);
	printf("%lld\n",res);
	if(res<=42) Sear(0,0,0),Print(0,0,0);
}
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
const int mod=1e4+7;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline int mul(int x) {return x % mod;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
inline void Mul(int &x, int y) {if ((x *= y) >= mod) x %= mod;}
inline int fpow(int a,int b){int res=1;while(b){if(b&1)Mul(res,a);Mul(a,a);b>>=1;}return res;}
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
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

const int N=1e4+10;
char s[N];
int n,m;
int res;
int dp[110][N];
deque<int>q;
struct AC_automaton
{
	struct tri
	{
		int fil,end,ch[30];
	}AC_A[N];
	int tot;
	AC_automaton() {tot=0;}
	void ins(char *s)
	{
		int now=0;
		for(;*s;s++) {
			int x=*s-'A';
			if(!AC_A[now].ch[x]) AC_A[now].ch[x]=++tot;
			now=AC_A[now].ch[x];
		}
		AC_A[now].end=1;
	}
	/*
	考虑使用AC自动机，则原问题转化为：求使这m个字符串都匹配不上的字符串的个数。
	所以，匹配过程中经过的点，其fail链上的节点（包括本身）都不能有结束节点。
	*/
	void get_fail()
	{
		deque<int>q;
		FR(i,0,26) if(AC_A[0].ch[i])
		{ 
			AC_A[AC_A[0].ch[i]].fil=0;
			q.pb(AC_A[0].ch[i]);
		}
		while(q.size()>0)
		{
			int u=q.front();q.pop_front();
			FR(i,0,26)
			{
				int v=AC_A[u].ch[i];
				if(v) 
				{
					AC_A[v].fil=AC_A[AC_A[u].fil].ch[i];
					AC_A[v].end|=AC_A[AC_A[v].fil].end;
					q.pb(v);
				}
				else AC_A[u].ch[i]=AC_A[AC_A[u].fil].ch[i];
			}
		}
	}
	//dp[i][j]表示从根节点开始走i步到j节点的方案数
	//(当前准备匹配第i个字符，且当前在AC自动机上的j节点时，不合法的方案总数)长度为 i 且后缀字符为AC自动机上节点 j 的文本串数量
	void DP()
	{
		dp[0][0]=1;
		R(i,1,m)
			R(j,0,tot) if(!AC_A[j].end) //全部点沿着子节点生成文本串下一个字母且不经过模式串
			{
				FR(k,0,26) Add(dp[i][AC_A[j].ch[k]],dp[i-1][j]);
			}
		R(i,0,tot) if(!AC_A[i].end) Add(res,dp[m][i]);
	}
}AC;

signed main()
{
	n=read(),m=read();
	R(i,1,n)
	{
		scanf("%s",s);
		AC.ins(s);
	}
	AC.get_fail();
	AC.DP();
	printf("%lld\n",(fpow(26,m)-res+mod)%mod);
}
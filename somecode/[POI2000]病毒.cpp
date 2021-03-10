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
inline int fpow(int a,int b){int res=1;while(b){if(b&1)Mul(res,a);Mul(a,a);b>>=1;}return res;}
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
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
const int N=3e5+10;
struct AC_automaton
{
	struct tri
	{
		int ch[10],fil,end;
	}AC_A[N];
	int tot=0;
	AC_automaton() {tot=0;}
	void ins(char *s)
	{
		int now=0;
		for(int j=1;s[j];j++)
		{
			int x=s[j]-'0';
			if(!AC_A[now].ch[x]) AC_A[now].ch[x]=++tot;
			now=AC_A[now].ch[x];
		}
		AC_A[now].end=1;
	//	printf("%lld\n",now);
	}
	void get_fail()	
	{
		deque<int>q;
		R(i,0,1) if(AC_A[0].ch[i])
		{
			AC_A[AC_A[0].ch[i]].fil=0;
			q.pb(AC_A[0].ch[i]);
		}
		while(q.size()>0)
		{
			int u=q.front();
			q.pop_front();
			R(i,0,1) if(AC_A[u].ch[i])
			{
				q.pb(AC_A[u].ch[i]);
				int v=AC_A[u].fil;
				while(v&&!AC_A[v].ch[i]) v=AC_A[v].fil;// 要不到根节点，要不找到最长匹配后缀段
				if(!AC_A[v].ch[i]) AC_A[AC_A[u].ch[i]].fil=0; // 失配指针转移到根节点 
				else 
				{
					AC_A[AC_A[u].ch[i]].fil=AC_A[v].ch[i];
					AC_A[AC_A[u].ch[i]].end|=AC_A[AC_A[v].ch[i]].end;
				}
			}
			else AC_A[u].ch[i]=AC_A[AC_A[u].fil].ch[i];
		}
	}
}AC;
int isl[N],vis[N];
char s[N];
int n;
void dfs(int u)
{
	isl[u]=1;
	R(i,0,1) 
	{
		int v=AC.AC_A[u].ch[i];
		if(isl[v]) {
			puts("TAK");
			exit(0);
		}
		else if(!AC.AC_A[v].end&&!vis[v])
		{
			vis[v]=1;
			dfs(v);
		}
	}
	isl[u]=0;
}
signed main()
{
	n=read();
	R(i,1,n)
	{
		scanf("%s",s+1);	
		AC.ins(s);
	}
	AC.get_fail();
	//for(int i=0;i<=10;i++) printf("%lld %lld\n",AC.AC_A[i].fil,AC.AC_A[i].end);
	dfs(0);
	puts("NIE");
}
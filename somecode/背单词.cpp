#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define int long long
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x, T y) { return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x, T y) { return x>y?x=y,true:false;}
using namespace std;
//const ll inf=0x7f7f7f7f7f7f7f3f;
const ll inf=(1ll<<60);
//const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
const double eps=1e-6;
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
inline ll read()
{
    char c=getchar();ll x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
char s[511111];
int son[511111][27],val[511111];
int tot_nd=1;
int n,ans;
int fff[511111],siz[511111];
vector<int>e[511111];
int st[511111],tim;
void ins(char *s,int id)
{
	int p=1;
	for(;*s;s++)
	{
		//printf("p:%lld\n",p);
		int i=*s-'a';
		p=(!son[p][i])?son[p][i]=++tot_nd:son[p][i];
	}
	val[p]=id;
}
inline int find_fff(int x){return (fff[x]==x)?x:fff[x]=find_fff(fff[x]);}
void dfs1(int u)
{	
	R(i,0,25)
	{
		int v=son[u][i];
		if(!v) continue;
		//printf("u:%lld v:%lld\n",u,v);
		if(!val[v]) fff[v]=find_fff(u);
		else e[val[find_fff(u)]].pb(val[v])/*,printf("fa of u:%lld val[fu]:%lld v:%lld val[v]:%lld\n",find_fff(u),val[find_fff(u)],v,val[v])*/;
		dfs1(v);
	}
}
void dfs2(int u)
{
	siz[u]=1;
	for(int v:e[u])
	{
		//printf("u:%lld v:%lld\n",u,v);
		dfs2(v);
		siz[u]+=siz[v];
	}
	sort(e[u].begin(),e[u].end(),[&](int x,int y){return siz[x]<siz[y];});
	//for(int v:e[u]) printf("u:%lld v:%lld\n",u,v);
}
void dfs3(int u)
{
	st[u]=++tim;
	for(int v:e[u])
	{	
		ans+=tim-st[u]+1;
		dfs3(v);
	}
}
signed main()
{
	n=read();
	R(i,1,n) {scanf("%s",s);reverse(s,s+strlen(s));ins(s,i);}
	R(i,1,tot_nd) fff[i]=i;
	dfs1(1);dfs2(0);dfs3(0);
	writeln(ans);
}
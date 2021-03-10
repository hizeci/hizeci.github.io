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
int mod;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
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
const int N=1e5+10;
int n,m,q;
int fa[N];
int bz[18][N];
int dep[N],s[N],a[N];
std::vector<int>e[N];
inline int find_r(int x){
	return x==fa[x]?x:fa[x]=find_r(fa[x]);
}
void dfs1(int u)
{
	dep[u]=dep[bz[0][u]]+1;
	for(int v:e[u])
	{
		if(!dep[v])
		{
			bz[0][v]=u;
			dfs1(v);
			if(find_r(u)==find_r(v)) a[u]|=a[v];
		}
		else if(dep[v]<dep[u]-1)
		{
			if((dep[u]+dep[v]+1)&1) a[u]=1;
			for(int x=find_r(u);dep[x]>dep[v]+1;x=find_r(x)) fa[x]=bz[0][x];
		}
	}
}
void dfs2(int u)
{
	s[u]+=a[u];
	for(int v:e[u])
	{
		if(dep[v]==dep[u]+1)
		{
			if(find_r(u)==find_r(v)) a[v]|=a[u];
			s[v]=s[u];
			dfs2(v);
		}
	}
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	L(i,0,16) if(dep[bz[i][x]]>=dep[y]) x=bz[i][x];
	if(x==y) return x;
	L(i,0,16) if(bz[i][x]!=bz[i][y]) x=bz[i][x],y=bz[i][y];
	return bz[0][x];
}
signed main()
{
	n=read(),m=read();
	R(i,1,m)
	{
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	R(i,1,n) fa[i]=i;
	R(i,1,n) if(!dep[i]) dfs1(i),dfs2(i);
	R(j,1,16)
		R(i,1,n) bz[j][i]=bz[j-1][bz[j-1][i]];
	q=read();
	while(q--)
	{
		int u=read(),v=read();
		int l_a=LCA(u,v);
		//if(q==2) printf("%lld\n",l_a);
		if(!l_a) puts("No");
		else if(((dep[u]+dep[v])&1)||s[u]+s[v]-2*s[l_a]) puts("Yes");
		else puts("No");
	}
}
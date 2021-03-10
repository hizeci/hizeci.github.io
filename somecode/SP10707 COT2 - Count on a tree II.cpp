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
const int B=2000;
const int N=2e5+10;
struct ques
{
	int l,r,l_a,id;
	inline bool operator <(const ques a)const{
		return (l/B^a.l/B)?l<a.l:((l/B)&1)?r<a.r:r>a.r;
	}
}qs[N];
std::vector<int>e[N];
int n,q;
int vis[N],cnt[N];

int col[N],tmp[N];
int st[N],en[N],tim;
int arr[N];

int Sz[N],dep[N],fa[N],htop[N],hson[N];

int res,ans[N];
/*
void dfs1(int u,int f)
{
	dep[u]=dep[f]+1,fa[u]=f,Sz[u]=1;
	st[u]=++tim;
	//arr[tim]=u;
	for(int v:e[u])
	{
		if(v==f) continue;
		dfs1(v,u);
		Sz[u]+=Sz[v];
		if(Sz[hson[u]]>Sz[v]) hson[u]=v;
	}
	en[u]=++tim;
	//arr[tim]=u;
}
void dfs2(int u,int topf)
{
	htop[u]=topf;
	if(!hson[u]) return;
	dfs2(hson[u],topf);
	for(int v:e[u])
	{
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
*/
void dfs1(int u,int f)
{
	Sz[u]=1,dep[u]=dep[f]+1,fa[u]=f;
	st[u]=++tim;
	for(int v:e[u])
	{
		if(v==f) continue;
		dfs1(v,u);
		Sz[u]+=Sz[v];
		if(Sz[hson[u]]<Sz[v]) hson[u]=v;
	}
	en[u]=++tim;
}
void dfs2(int u,int topf)
{
	htop[u]=topf;
	if(!hson[u]) return;
	dfs2(hson[u],topf);
	for(int v:e[u])
	{
		if(v==hson[u]||v==fa[u]) continue;
		dfs2(v,v);
	}
}
/*
int get_LCA(int x,int y)
{
	while(htop[x]!=htop[y])
	{
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		x=fa[htop[x]];
	}
	return (dep[x]<dep[y])?x:y;
}
*/

inline int get_LCA(int x,int y){
	while(htop[x]!=htop[y]) {if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);x=fa[htop[x]];} return (dep[x]<dep[y])?x:y;
}

void add(int x)
{
	vis[x]^=1;
	if(vis[x]) res+=!cnt[col[x]],cnt[col[x]]++;
	else cnt[col[x]]--,res-=!cnt[col[x]];	
}
signed main()
{
	n=read(),q=read();
	R(i,1,n) tmp[i]=col[i]=read();
	sort(tmp+1,tmp+n+1);
	int m=unique(tmp+1,tmp+n+1)-tmp-1;
	R(i,1,n) col[i]=lower_bound(tmp+1,tmp+m+1,col[i])-tmp;
	FR(i,1,n) {
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs1(1,0);
	dfs2(1,1);
	R(i,1,n) arr[st[i]]=arr[en[i]]=i;
	R(i,1,q) 
	{
		int x=read(),y=read();
		if(st[x]>st[y]) Swap(x,y);
		int L_A=get_LCA(x,y);
        printf("%lld\n",L_A);
		if(en[x]>=en[y]) qs[i]=(ques){st[x]+1,st[y],L_A,i};
		else qs[i]=(ques){en[x],st[y],L_A,i};
	}
	sort(qs+1,qs+q+1);
	int L=1,R=0;
	R(i,1,q)
	{
		while(L>qs[i].l) add(arr[--L]);
		while(R>qs[i].r) add(arr[R--]);
		while(L<qs[i].l) add(arr[L++]);
		while(R<qs[i].r) add(arr[++R]);
		//add(qs[i].l_a);
		ans[qs[i].id]=res+(cnt[col[qs[i].l_a]]==0);
	}
	R(i,1,q) printf("%lld\n",ans[i]);
}
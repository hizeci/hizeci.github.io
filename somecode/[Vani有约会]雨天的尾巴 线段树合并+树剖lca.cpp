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
//#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
//const int inf=0x7f7f7f7f7f7f;
//const int mod=9223372036854775807;
const ld eps=1e-8;
//inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
/*
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
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
const int N=1e5+10;
const int M=80*N;
int n,m;
struct edge
{
	int nxt,to;
}e[N<<1];
int head[N],cnt_e;
int dep[N],hson[N],htop[N],fa[N];
int sz[N];
int Rt[N],Ls[M],Rs[M];
int val[M],id[M],tot_seg;
int res[N];
inline void init_e() {
	cnt_e=0;memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v) {
	e[++cnt_e].nxt=head[u],e[cnt_e].to=v,head[u]=cnt_e;
}
void dfs1(int u,int f)
{
	dep[u]=dep[f]+1;
	fa[u]=f;
	sz[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[hson[u]]<sz[v]) hson[u]=v;
	}
}
void dfs2(int u,int topf)
{
	htop[u]=topf;
	if(!hson[u]) return ;
	dfs2(hson[u],topf);
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
int Lca(int x,int y)
{
	while(htop[x]!=htop[y])
	{
		if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
		x=fa[htop[x]];
	}
	return (dep[x]<dep[y])?x:y;
}
void push_up(int x)
{
	if(!Ls[x])
	{
		val[x]=val[Rs[x]];
		id[x]=id[Rs[x]];
		return ;
	}
	if(!Rs[x])
	{
		val[x]=val[Ls[x]];
		id[x]=id[Ls[x]];
		return;
	}
	if(val[Ls[x]]>=val[Rs[x]])
	{
		val[x]=val[Ls[x]];
		id[x]=id[Ls[x]];
	}
	else {
		val[x]=val[Rs[x]];
		id[x]=id[Rs[x]];
	}
}
void modify(int pos,int l,int r,int &x,int k)
{
	if(!x) x=++tot_seg;
	if(l==r) 
	{
		val[x]+=k;
		id[x]=pos;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) modify(pos,l,mid,Ls[x],k);
	else modify(pos,mid+1,r,Rs[x],k);
	push_up(x);
}
int Mer(int l,int r,int a,int b)
{
	if(!a||!b) return a+b;
	if(l==r){
		val[a]+=val[b];
		return a;
	}
	int mid=(l+r)>>1;
	Ls[a]=Mer(l,mid,Ls[a],Ls[b]);
	Rs[a]=Mer(mid+1,r,Rs[a],Rs[b]);
	push_up(a);
	return a;
}
void calc(int u,int f)
{
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		calc(v,u);
		Rt[u]=Mer(1,100000,Rt[u],Rt[v]);
	}
	res[u]=id[Rt[u]];
	if(!val[Rt[u]]) res[u]=0;
}
signed main()
{
	init_e();
	n=read(),m=read();
	FR(i,1,n) {
		int u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	while(m--)
	{
		int u=read(),v=read(),z=read();
		int l_a=Lca(u,v);
		//printf("%d\n",l_a);
		modify(z,1,100000,Rt[u],1);
		modify(z,1,100000,Rt[v],1);
		modify(z,1,100000,Rt[l_a],-1);
		modify(z,1,100000,Rt[fa[l_a]],-1);
	}
	calc(1,0);
	R(i,1,n) printf("%d\n",res[i]);
}
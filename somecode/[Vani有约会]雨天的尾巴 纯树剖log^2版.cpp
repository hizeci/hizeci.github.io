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
struct edge
{
	int nxt,to;
}e[N<<1];
int head[N],cnt_e;
int seg[N],dfn[N],tim;
int fa[N],dep[N],sz[N];
int htop[N],hson[N];
int n,m;

inline void init_e(){
	cnt_e=0;memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v){
	e[++cnt_e].nxt=head[u],e[cnt_e].to=v,head[u]=cnt_e;
}
void dfs1(int u,int f)
{
	dep[u]=dep[f]+1;
	sz[u]=1;
	fa[u]=f;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int topf)
{
	seg[u]=++tim;
	dfn[tim]=u;
	htop[u]=topf;
	if(!hson[u]) return;
	dfs2(hson[u],topf);
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
//使用类似前向星的方式存储修改
int Lnk[N],cnt_v;
int Nxt[N<<5],Val[N<<5];
inline void add_v(int u,int v){
	Nxt[++cnt_v]=Lnk[u],Val[cnt_v]=v,Lnk[u]=cnt_v;
}
void save_modify(int u,int v,int k)
{
	while(htop[u]!=htop[v])
	{
		if(dep[htop[u]]<dep[htop[v]]) swap(u,v);
		add_v(seg[htop[u]],k),add_v(seg[htop[v]]+1,-k);//表示减少k位置救济粮
		u=fa[htop[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	add_v(seg[htop[u]],k),add_v(seg[htop[v]]+1,-k);
}
int Mxcnt[N<<2],Mxpos[N<<2];
void push_up(int x){ 
	if(Mxcnt[x<<1]>=Mxcnt[x<<1|1]) Mxcnt[x]=Mxcnt[x<<1],Mxpos[x]=Mxpos[x<<1];
	else Mxcnt[x]=Mxcnt[x<<1|1],Mxpos[x]=Mxpos[x<<1|1];
}
void build(int l,int r,int x)
{
	if(l==r) {Mxcnt[x]=0,Mxpos[x]=l;return;}
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	push_up(x);
}
void modify(int pos,int l,int r,int x,int k)
{
	if(l==r) {Mxcnt[x]+=k;return;}
	int mid=(l+r)>>1;
	if(pos<=mid) modify(pos,l,mid,x<<1,k);
	else modify(pos,mid+1,r,x<<1|1,k);
	push_up(x);
}
int res[N];
signed main()
{
	init_e();
	n=read(),m=read();
	FR(i,1,n) {
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	while(m--)
	{
		int u=read(),v=read(),d=read();
		save_modify(u,v,d);
	}
	build(1,100000,1);
	R(i,1,n)
	{
		for(int e=Lnk[i];e;e=Nxt[i])
		{
			if(Val[e]>0) modify(Val[e],1,100000,1,1);
			else modify(-Val[e],1,100000,1,1);
		}
		res[dfn[i]]=Mxcnt[1]?Mxpos[1]:0;
	}
	R(i,1,n) printf("%d\n",res[i]);

}
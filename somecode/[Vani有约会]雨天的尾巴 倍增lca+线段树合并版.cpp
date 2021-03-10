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
int head[N],cnt_e;
struct edge
{
	int nxt,to;
}e[N<<1];	
int n,m;
int fa[19][N],dep[N];
int Rt[N],res[N];
int Ls[M],Rs[M],val[M],id[M],tot_seg;
	
inline void init_e(){
	cnt_e=0;memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v){
	e[++cnt_e].nxt=head[u];e[cnt_e].to=v;head[u]=cnt_e;
}
/*
val[]统计值，id[]统计编号
使用线段树合并，每个点维护一棵权值线段树，下标为救济粮种类
区间维护数量最多的救济粮编号(下标)。每个节点答案为id[Rt[x]];
树上差分对于分发路径u,v在u,v,上+1,在lca(u,v)-1,fa[lca(u,v)]-1（因为lca(u,v)上也被加了一次):
最后统计时自底向上做树上前缀和，线段树合并得到当前节点信息
tips：在合并时会出现id[Rt[x]]!=0但是val[Rt[x]]为0的情况，这时候表示编号为tre[rot[x]]的救济粮数量为0，
所以此时应该将res[x]更新为0（根据题意）
*/
void push_up(int x)
{
	if(!Ls[x])
	{
		val[x]=val[Rs[x]];
		id[x]=id[Rs[x]];
		return;
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
	else 
	{
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

void dfs(int u,int f)
{
	fa[0][u]=f;
	dep[u]=dep[f]+1;
	R(i,1,18) fa[i][u]=fa[i-1][fa[i-1][u]];
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs(v,u);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	L(i,0,18) if(dep[fa[i][x]]>=dep[y]) x=fa[i][x];
	if(x==y) return x;
	L(i,0,18) if(fa[i][x]!=fa[i][y]) x=fa[i][x],y=fa[i][y];
	return fa[0][x];
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
	FR(i,1,n)
	{
		int u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	while(m--)
	{
		int u=read(),v=read(),z=read(),l_a=lca(u,v);
		//printf("%d\n",l_a);
		modify(z,1,100000,Rt[u],1);
		modify(z,1,100000,Rt[v],1);
		modify(z,1,100000,Rt[l_a],-1);
		modify(z,1,100000,Rt[fa[0][l_a]],-1);
	}
	calc(1,0);
	R(i,1,n) printf("%d\n",res[i]);
}
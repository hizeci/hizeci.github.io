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
const int N=1e6+161;
const int B=2000;
std::vector<int> e[N];
int htop[N],hson[N],dep[N],fa[N],Sz[N];
int n,m,q;
int v[N],w[N];
int st[N],en[N];
int col[N];
int tim;
int cnt_m;
struct mify
{
	int pos,cly,clz;//位置，原颜色，后颜色
}mf[N];
int cnt_q;
struct ques
{
 	int l,r,t,l_a,id;
 	inline bool operator <(const ques a)const{
 		return (l/B!=a.l/B)?l<a.l:(r/B!=a.r/B)?r<a.r:t<a.t;
 	}
}qs[N];
int arr[N<<1];
int ans[N],val[N],cnt[N];
int res;
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
int get_lca(int x,int y)
{
	while(htop[x]!=htop[y])
	{
		if(dep[htop[x]]<dep[htop[y]]) Swap(x,y);
		x=fa[htop[x]];
	}
	return (dep[x]<dep[y])?x:y;
}
void add(int x)
{
	x=arr[x];
	val[x]^=1;
	if(val[x])	
	{
		cnt[col[x]]++;
		res+=v[col[x]]*w[cnt[col[x]]];
	}
	else
	{
		res-=v[col[x]]*w[cnt[col[x]]];
		cnt[col[x]]--;
	}
}
void modify(int x)
{
	int post=mf[x].pos;
	if(col[post]==mf[x].clz)
	{
		if(val[post])
		{
			cnt[mf[x].cly]++;
			res+=(v[mf[x].cly]*w[cnt[mf[x].cly]]-v[col[post]]*w[cnt[col[post]]]);
			cnt[col[post]]--;
		}
		col[post]=mf[x].cly;
	}
	else
	{
		if(val[post])
		{
			cnt[mf[x].clz]++;
			res+=(v[mf[x].clz]*w[cnt[mf[x].clz]]-v[col[post]]*w[cnt[col[post]]]);
			cnt[col[post]]--;
		}
		col[post]=mf[x].clz;
	}
}
signed main()
{
	n=read(),m=read(),q=read();
	R(i,1,m) v[i]=read();
	R(i,1,n) w[i]=read();
	FR(i,1,n) {
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs1(1,0);
	dfs2(1,1);
	R(i,1,n) col[i]=read();
	R(i,1,q)
	{
		int opt=read(),x=read(),y=read();
		if(!opt){
			mf[++cnt_m]=(mify){x,col[x],y};
			col[x]=y;
		}
		else 
		{
			if(st[x]>st[y]) Swap(x,y);
			int L_A=get_lca(x,y);
			if(en[x]>=en[y]) qs[++cnt_q]=(ques){st[x]+1,st[y],cnt_m,L_A,cnt_q};
			else qs[++cnt_q]=(ques){en[x],st[y],cnt_m,L_A,cnt_q};
		}
	}
	
	R(i,1,n) arr[st[i]]=arr[en[i]]=i;
	sort(qs+1,qs+cnt_q+1);
	int L=1,R=0,T=cnt_m;
	R(i,1,cnt_q)
	{
		while(L>qs[i].l) add(--L);
		while(R>qs[i].r) add(R--);
		while(L<qs[i].l) add(L++);
		while(R<qs[i].r) add(++R);
		while(T<qs[i].t) modify(++T);
		while(T>qs[i].t) modify(T--);
		ans[qs[i].id]=res+v[col[qs[i].l_a]]*w[cnt[col[qs[i].l_a]]+1];
	}
	R(i,1,cnt_q) printf("%lld\n",ans[i]);
	
}
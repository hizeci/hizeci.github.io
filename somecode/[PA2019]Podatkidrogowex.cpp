#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define us unsigned 
#define ll long long
#define ull unsigned long long
#define int long long
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
const ld eps=1e-8;
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
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
inline void write(int x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(int x){write(x),putchar(' ');}
inline void writeln(int x){write(x);putchar('\n');}

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<ull> dist(0, 1000000);  // ¸ø¶¨·¶Î§
mt19937 rad(1234);
/*
printf("%lld ",dist(rand_num));
*/
/*
考虑二分答案，然后点分治，用主席树维护路径，相当于现在有 O(n) 个组，每个组有一个系数 1 或 -1，每个组有一些路径，路径总数是 O(nlogn) 级别的，现在我们可以把同一组内的两个路径拼到一起，贡献是改组的系数，求有多少 <=x 的贡献。这个直接把边权排序一下然后 two pointers 即可。
最后的问题就是如何二分，由于答案过大不能二分答案，但是路径只有 O(n^2) 条，直接二分路径即可。具体方法是：考虑当前有左路径 pl，右路径 pr，随机一个路径 pmid 使得 pl<pmid<pr，然后算 < pmid 的路径有多少即可。 
*/
const int djq=1e9+7;
int n,k;
std::vector<pii>e[25555];
int st[50050],en[50050],tim;
int tot_seq,seq[10000015],cfi[50050];
int tot_road,road[10000015];
/*
struct edge
{
	int nxt,to,val;
}e[50050];
int head[50050],cnt;
inline void add_edge(int u,int v,int d){e[++cnt]=(edge){head[u],v,d};head[u]=cnt;}
*/
namespace chairman
{
	int tot_seg;
	ull sum[10000015],hsh[50050];
	int pw[50050],val[10000015],Ls[10000015],Rs[10000015];
	inline void init(){pw[0]=1;R(i,1,n)hsh[i]=((ull)rad()<<32)+rad(),pw[i]=1ll*pw[i-1]*n%djq;}
	int modify(int pos,int l,int r,int id)
	{
		int rt=++tot_seg;
		sum[rt]=sum[id]+hsh[pos],val[rt]=val[id]+1,Ls[rt]=Ls[id],Rs[rt]=Rs[id];
		if(l==r) return rt;
		int mid=(l+r)>>1;
		if(pos<=mid) Ls[rt]=modify(pos,l,mid,Ls[id]);
		else Rs[rt]=modify(pos,mid+1,r,Rs[id]);
		return rt;
	}
	/*
	考虑由于不会产生进位，所以比较两个路径的大小只需要从高位向低位比较即可。
	如果用线段树维护哈希值可以使两个路径的比较的复杂度降到 O(logn)。
	*/
	int cmp_o(int rt11,int rt12,int rt21,int rt22,int l=1,int r=n)
	{
		if(l==r){int tmp=val[rt11]+val[rt12]-val[rt21]-val[rt22];return tmp<0?1:tmp==0?0:-1;}
		int mid=(l+r)>>1;
		//先比较右区间，若相同则递归左区间，否继续递归右区间
		if(sum[Rs[rt11]]+sum[Rs[rt12]]==sum[Rs[rt21]]+sum[Rs[rt22]]) 
		return cmp_o(Ls[rt11],Ls[rt12],Ls[rt21],Ls[rt22],l,mid);
		return cmp_o(Rs[rt11],Rs[rt12],Rs[rt21],Rs[rt22],mid+1,r);
	} 
	ll query(int l,int r,int x,int y)
	{
		if(l==r) return 1ll*(val[x]+val[y])*pw[l]%djq;
		int mid=(l+r)>>1;
		return (query(l,mid,Ls[x],Ls[y])+query(mid+1,r,Rs[x],Rs[y]))%djq;
	}
}

namespace starchy
{
	int rt,siz_tr;
	int Mx_s[25555],siz[25555];
	int Rt[25555];
	bool vis[25555];
	
	void dfs1(int u,int f) //find_G
	{
		//printf("%d %d\n",u,f);
		siz[u]=1;Mx_s[u]=0;
		for(auto qwq:e[u]) 
		{
			int v=qwq.fi;
			if(v==f||vis[v]) continue;
			dfs1(v,u);
			siz[u]+=siz[v];
			ckmax(Mx_s[u],siz[v]);
		}
		ckmax(Mx_s[u],siz_tr-siz[u]);
		rt=(Mx_s[u]<Mx_s[rt])?u:rt;
	}
	/*
	void dfs1(int u,int f) //find_G
	{
		//printf("%d %d\n",u,f);
		siz[u]=1;
		for(auto qwq:e[u]) 
		//for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=qwq.fi;
			//int v=e[i].to;
			if(v==f||vis[v]) continue;
			dfs1(v,u);
			siz[u]+=siz[v];
		}
	}
	void dfs2(int u,int f) 
	{
		//printf("%d %d\n",u,f);
		Mx_s[u]=0;
		for(auto qwq:e[u]) 
		//for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=qwq.fi;
			//int v=e[i].to;
			if(v==f||vis[v]) continue;
			dfs2(v,u);
			ckmax(Mx_s[u],siz[v]);
		}
		ckmax(Mx_s[u],siz_tr-siz[u]);
		rt=(Mx_s[u]<Mx_s[rt])?u:rt;
	}
	*/
	void init(int u,int f) 
	{
		for(auto qwq:e[u]) 
		//for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=qwq.fi;
			//int v=e[i].to;
			if(v==f||vis[v]) continue;
			Rt[v]=chairman::modify(qwq.se,1,n,Rt[u]);
			//Rt[v]=chairman::modify(e[i].val,1,n,Rt[u]);
			init(v,u);
		}
	}
	void calc(int u,int f) 
	{
		seq[++tot_seq]=Rt[u];
		for(auto qwq:e[u])
		//for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=qwq.fi;
			//int v=e[i].to;
			if(v==f||vis[v]) continue;
			calc(v,u);
		}
	}
	void solve(int u) 
	{
		//printf("1:%d %d\n",u,rt);
		dfs1(u,-1);
		dfs1(rt,-1);
		//printf("2:%d %d\n",u,rt);
		Rt[u]=0;
		init(u,-1);
		st[++tim]=tot_seq+1,cfi[tim]=1;
		calc(u,-1);
		en[tim]=tot_seq,vis[u]=1;
		for(auto qwq:e[u]) 
		//for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=qwq.fi;
			//int v=e[i].to;
			if(vis[v]) continue;
			st[++tim]=tot_seq+1,cfi[tim]=-1;
			calc(v,-1);
			en[tim]=tot_seq;
			//dfs1(v,-1);
			Mx_s[rt=0]=inf,siz_tr=siz[v];
			dfs1(v,-1);
			dfs1(rt,-1);
			//printf("rt:%d u:%d v:%d\n",rt,u,v);
			solve(rt);
		}
	}
	void mian()
	{
		chairman::init();
		//dfs1(1,-1);
		Mx_s[rt=0]=inf;siz_tr=n;
		dfs1(1,-1);
		dfs1(rt,-1);
		//printf("rt:%d\n",rt);
		solve(rt); 
		//cpy(road+1,seq+1,tot_seq);
		for(int i=1;i<=tot_seq;i++) road[i]=seq[i];
		//printf("tot_seq:%d\n",tot_seq); for(int i=1;i<=tot_seq;i++) printf("seq:%d\n",road[i]);
		sort(road+1,road+tot_seq+1,[&](int x,int y){return chairman::cmp_o(x,0,y,0)>0;});
		//printf("tot_seq:%d\n",tot_seq); for(int i=1;i<=tot_seq;i++) printf("road:%d\n",road[i]);
		R(i,1,tot_seq) if(i==1||chairman::cmp_o(road[i],0,road[tot_road],0)<0) road[++tot_road]=road[i];
		//printf("tot_seq:%d\n",tot_seq); for(int i=1;i<=tot_seq;i++) printf("road:%d\n",road[i]);
		R(i,1,tim) sort(seq+st[i],seq+en[i]+1,[&](int x,int y){return chairman::cmp_o(x,0,y,0)>0;}); 
		//printf("tot_seq:%d\n",tot_seq); for(int i=1;i<=tot_seq;i++) printf("road:%d\n",road[i]);
		//R(i,1,tim) printf("st:%d en:%d\n",st[i],en[i]);
	}
}
namespace Div2
{
	int tot_proad;
	pii proad[1000015];
	int pl[1000015],pr[1000015];
	mt19937 radd(time(0)^(ull)(new char));
	int check(int m1,int m2) 
	{
		int res=0;
		R(i,1,tim) 
		{
			int now=en[i];
			R(j,st[i],en[i]) 
			{
				while(now>j&&chairman::cmp_o(seq[j],seq[now],m1,m2)<0) now--;
				//res+=cfi[i]*max(0,now-j);
				res+=cfi[i]*max(0ll,now-j);
			}
		}
		return res;
	}
	void mian()
	{
		int l1=road[1],l2=road[1],r1=road[tot_road],r2=road[tot_road];
		while(233)
		{
			pl[0]=tot_road+1,pr[0]=tot_road;
			ll alls=0;
			R(i,1,tot_road) 
			{
				pl[i]=pl[i-1],pr[i]=pr[i-1];
				while(pl[i]>i+1&&chairman::cmp_o(l1,l2,road[i],road[pl[i]-1])>=0) pl[i]--;
				while(pr[i]>i&&chairman::cmp_o(r1,r2,road[i],road[pr[i]])>0) pr[i]--;
				ckmax(pl[i],i+1);alls+=max(0ll,pr[i]-pl[i]+1);
			}
			//printf("all:%lld\n",alls);
			if(alls<=(int)2e5) 
			{
				//for(int i=1;i<=tot_road;i++) printf("pl:%d pr:%d\n",pl[i],pr[i]);
				R(i,1,tot_road) R(j,pl[i],pr[i]) proad[++tot_proad]=mkp(road[i],road[j]);
				//printf("tpr:%d\n",tot_proad);
				sort(proad+1,proad+tot_proad+1,[&](pii x,pii y){return chairman::cmp_o(x.fi,x.se,y.fi,y.se)>0;});
				//R(i,1,tot_proad) printf("fi:%d se:%d\n",proad[i].fi,proad[i].se);
				tot_proad=0;
				R(i,1,alls) if(i==1||chairman::cmp_o(proad[i].fi,proad[i].se,proad[tot_proad].fi,proad[tot_proad].se)<0)proad[++tot_proad]=proad[i];
				//printf("tot_proad:%d\n",tot_proad);
				//R(i,1,tot_proad) printf("fi:%d se:%d\n",proad[i].fi,proad[i].se);
				break;
			} 
			int mid=(((ull)radd()<<32)+radd())%alls+1,m1=0,m2=0;
			R(i,1,tot_road) 
			{
				if(mid<=pr[i]-pl[i]+1) {m1=road[i],m2=road[pl[i]+mid-1];break;}
 				mid-=max(0ll,pr[i]-pl[i]+1);
 			}
 			if(check(m1,m2)>=k) r1=m1,r2=m2;else l1=m1,l2=m2;
		}
		int l=1,r=tot_proad,best=0;
		while(l<=r) 
		{
			int mid=(l+r)>>1;
			if(check(proad[mid].fi,proad[mid].se)>=k) best=mid,r=mid-1;else l=mid+1;
		}
		//printf("best:%d\n",best);
		//printf("%d %d\n",proad[best].fi,proad[best].se);
		printf("%lld\n",chairman::query(1,n,proad[best].fi,proad[best].se));
	}
}
signed main()
{
	//freopen("pod4c.in","r",stdin);
	//memset(head,-1,sizeof(head));

	n=read(),k=read();
	int u,v,d;
	R(i,2,n) {u=read(),v=read(),d=read();/*add_edge(u,v,d),add_edge(v,u,d);*/e[u].pb(mkp(v,d)),e[v].pb(mkp(u,d));}
	//puts("output:--------------------");
	starchy::mian();
	//printf("%d\n", tot_road);
	Div2::mian();
}
/*
16 38
1 10 3
6 8 1
8 10 1
1 4 12
16 14 8
9 3 6
12 7 7
11 2 14
13 14 7
16 8 13
2 15 9
7 16 4
5 15 15
16 15 7
3 10 13
*/
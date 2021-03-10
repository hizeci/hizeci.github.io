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
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
const int mod=1e9+7;
//const int mod=10007;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}

const int qwq=2000010;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}

inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return 1ll*F[n]%mod*1ll*Finv[m]*1ll%mod*1ll*Finv[n-m]%mod;}


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
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
/*
题意:
1.子树+ 
2.到根的路径和
sol:
考虑使用ETT维护,考虑val[i]表示i号点的权值,对于欧拉序上的一个位置id
如果其是第一次出现,则a[i]=val[id];
else a[i]=-val[id];
则从根到x的权值和就是a到第一次出现id位置的前缀和。这样就解决了1操作的问题

时间复杂度O(mlogn)

*/
const int N=2e5+10;
int a[N];
int n,m;
struct edge
{
	int nxt,to;
}e[N<<1];
int head[N],cnt_eg;
inline void init(){
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v){
	e[++cnt_eg].nxt=head[u],e[cnt_eg].to=v,head[u]=cnt_eg;
}
struct eulertree
{
	int siz[N],son[N][2],val[N],fa[N],cnt[N],lazy_add[N],sum[N];
	int rt;
	int sta[N],stak;
	inline int get(int x) {
		return x==son[fa[x]][1];
	}
	inline void push_up(int x){
		siz[x]=siz[son[x][0]]+siz[son[x][1]]+cnt[x];
		sum[x]=sum[son[x][0]]+sum[son[x][1]]+1ll*cnt[x]*val[x];
	}
	inline void upd(int x,int k) {
		val[x]+=k,lazy_add[x]+=k,sum[x]+=1ll*siz[x]*k;
	}
	inline void push_down(int x) {
		if(lazy_add[x]) {
			if(son[x][0]) upd(son[x][0],lazy_add[x]);
			if(son[x][1]) upd(son[x][1],lazy_add[x]);
			lazy_add[x]=0;
		}
	}
	
	void rotate(int x,int &k)
	{
		int f=fa[x],gf=fa[f],wh=get(x);
		if(k==f) k=x;
		//push_down(f),push_down(x);		///???????
		else son[gf][get(f)]=x;//??????
		fa[f]=x,fa[x]=gf;fa[son[x][wh^1]]=f;
		son[f][wh]=son[x][wh^1];
		son[x][wh^1]=f;
		push_up(f);push_up(x);
	}
	void update(int x){
		if(x!=rt) update(fa[x]);
		//printf("%lld\n",x);
		push_down(x);
	}
	inline void splay(int x,int &k){
		update(x);
		for(int f;f=fa[x],x!=k;rotate(x,k))
			if(f!=k) rotate(get(x)==get(f)?f:x,k);
		push_up(x);//????
	}
	/*
	void splay(int x,int &k){
            //printf("%d %d\n",x,k);
            sta[++stak]=x;for(int i=x;i^rt;i=fa[i])sta[++stak]=fa[i];
            for(int i=stak;i;i--) {printf("%lld\n",sta[i]);push_down(sta[i]);}stak=0;
            while(x!=k){
            	//printf("x:%lld k:%lld\n",x,k);
                int y=fa[x],z=fa[y];
                if(y!=k){
                    int d1=(son[z][0]==y),d2=(son[y][0]==x);
                    if(d1^d2)rotate(x,k);else rotate(y,k);
                }
                rotate(x,k);
            }
        } 
        */
	inline int find_MIN(int x) {
		while(son[x][0]) x=son[x][0];return x;
	}
	inline int find_MAX(int x){
		while(son[x][1]) x=son[x][1];return x;
	}

	void ins(int x,int d,int opt) {
		if(!rt) rt=x;
		else fa[x]=rt,son[rt][1]=x;
		val[x]=d,cnt[x]=opt;
		push_up(x);splay(x,rt);
	}
	inline int query(int x) {
		splay(x,rt);
		return sum[son[x][0]]+1ll*cnt[x]*val[x];
	}
	void build(int u,int f){
		ins(u+1,a[u],1);
		for(int i=head[u];i!=-1;i=e[i].nxt){
			int v=e[i].to;if(v==f) continue;
			build(v,u);
		} 
		ins(u+n+2,a[u],-1);
	}
	void link(int x,int y) {
		splay(x,rt);int t1=find_MAX(son[rt][0]);
		splay(x+n+1,rt);int t2=find_MIN(son[rt][1]);
		splay(t1,rt);splay(t2,son[t1][1]);
		int z=son[t2][0];fa[z]=son[t2][0]=0;
		splay(y,rt);int t3=find_MIN(son[y][1]);
		splay(t3,son[y][1]);fa[z]=t3;son[t3][0]=z;
	}
	void modify(int x,int k) {
		splay(x,rt);int t1=find_MAX(son[rt][0]);
		splay(x+n+1,rt);int t2=find_MIN(son[rt][1]);
		splay(t1,rt);splay(t2,son[t1][1]);upd(son[t2][0],k);
	}
	void print() {
		R(i,0,10) printf("fa:%lld son0:%lld son1:%lld val:%lld cnt:%lld sum:%lld siz:%lld lazy_add:%lld\n",fa[i],son[i][0],son[i][1],val[i],cnt[i],sum[i],siz[i],lazy_add[i]);
	}
}ETT;
char opt[22];
signed main()
{
	init();
	n=read();
	R(i,2,n) {
		int f=read();
		add_edge(f,i);
		add_edge(i,f);
	}
	R(i,1,n) a[i]=read();
	ETT.ins(1,0,0);
	ETT.build(1,0);
	ETT.ins(2*n+3,0,0);
	//ETT.print();
	//R(i,0,10) printf("%lld\n",ETT.fa[i]);
	m=read();
	R(i,1,m) {
		//ETT.print();
		scanf("%s",opt+1);
		if(opt[1]=='Q') {
			int x=read();
			printf("%lld\n",ETT.query(x+1));
		}
		if(opt[1]=='C') {
			int x=read(),y=read();
			ETT.link(x+1,y+1);
		}
		if(opt[1]=='F') {
			int x=read(),y=read();
			ETT.modify(x+1,y);
		}
	}
}
/*
3
1
1
4 5 7
5
Q 2
F 1 3
Q 2
C 2 3
Q 2
*/
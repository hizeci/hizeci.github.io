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
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const int mod=10007;
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
暴力:kruskal

引理:对于一条边权为x的边(x\leq r_i)，存在一个阙值y，使得当l_i\leq y时,该边
不会被记到答案中，当y<l_i\leq x时，该边会记到答案中

证明:考虑反证,若上述引理不成立,则必然存在两个数a,b(a<b\leq x),使得l_i=a时，
该边会记录到答案中,当l_i=b时,该边不会记到答案中。设该边的两个端点分别为x_i和y_i,
由于当l_i=b时该边不会记到答案中,所以对边权在[b,x)中的所有边做上述算法后,x_i和y_i必然连通。
由于a<b,故对边权在[a,x)中的所有边做上述算法后,x_i和y_i必然连通。
由此推出l_i=a时，该边不会记录到答案中,与假设矛盾,故假设不成立。从而引理得证.

考虑对所有的边按权值从小到大排序，下文所说的跟边的顺序相关的内容都是按权值从小到大排序后的

考虑引理1中的y怎么求:从该边开始从后往前扫，不断在图中加入被扫过的边，
扫到第一个使图出现环的边的边权即为引理1的阙值y.如果没有这样的边,y=-oo

如果对于每条边都这样找的话还是不行,考虑如何快速维护。考虑一条连接了x_i和y_i的边x,
对于所有x之前的边,求出其最大生成树,那么阙值y就是x_i到y_i的路径中边权最小的边的权值。
如果x_i和y_i不连通，那么y=-oo,考虑怎么维护最大生成树,如果x_i和y_i连通，
我们需要将x_i到y_i的路径中边权最小的边删掉，
并加入当前这条边，如果x_i和y_i本来就不连通,直接加入这条边即可。
于是，我们需要维护加边和删去一条路径上最小的边,和求出一条路径上最小的边权，这些都可以用LCT实现
这部分的时间复杂度为O(mlogn)

考虑求出阙值之后如何求出答案，设p_i表示第i条边的阙值,那么对于第j个询问,
第i条边被算进了答案当且仅当p_i<l_j\leq w_i且r_j\geq w_i。这就是一个经典的二维数点问题,
由于询问强制在线，我们可以用主席树维护，这个部分时间复杂度为O(qlogn).
*/
const int N=111111;
int n,m,q;
int alle[N];
int arr[N*10];
int id,lst_ans;

struct edge
{
	int u,v,d;
	inline int operator <(const edge a)const{
		return d<a.d;
	}
}e[N];
struct canlongsegmentree
{
	int val[N*20],Ls[N*20],Rs[N*20],Rt[N*2],tot_seg;
	void clr() {
		R(i,1,tot_seg) val[i]=Ls[i]=Rs[i]=0;
		R(i,1,m) Rt[i]=0;
		tot_seg=0;
	}
	void modify(int pos,int l,int r,int &x,int lst,int k){
		x=++tot_seg;
		val[x]=val[lst]+k;
		Ls[x]=Ls[lst],Rs[x]=Rs[lst];
		if(l==r) return;
		int mid=(l+r)>>1;
		if(pos<=mid) modify(pos,l,mid,Ls[x],Ls[lst],k);
		else modify(pos,mid+1,r,Rs[x],Rs[lst],k);
	}
	int query(int L,int R,int l,int r,int x){
		if(!x) return 0;
		if(L<=l&&r<=R) return val[x];
		int mid=(l+r)>>1,ret=0;
		if(L<=mid) ret+=query(L,R,l,mid,Ls[x]);
		if(mid<R)  ret+=query(L,R,mid+1,r,Rs[x]);
		return ret;
	}
}clst;	
struct linkcutree
{
	int son[N<<2][2],fa[N<<2],tag[N<<2],minn[N<<2],val[N<<2],siz[N<<2];
	void init() {
		R(i,1,n+m) son[i][0]=son[i][1]=fa[i]=tag[i]=0;
		R(i,1,n) minn[i]=val[i]=inf;
		R(i,1,m) minn[i+n]=val[i+n]=i;
	}
	inline int get(int x){
		return x==son[fa[x]][1];
	}
	inline int isnotroot(int x){
		return x==son[fa[x]][0]||x==son[fa[x]][1];
	}
	inline void push_up(int x){
		siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
		minn[x]=val[x];
		if(son[x][0]) ckmin(minn[x],minn[son[x][0]]);
		if(son[x][1]) ckmin(minn[x],minn[son[x][1]]);
	}
	inline void push_flp(int x){
		Swap(son[x][0],son[x][1]);
		tag[x]^=1;
	}
	inline void push_down(int x){
		if(tag[x]) {
			if(son[x][0]) push_flp(son[x][0]);
			if(son[x][1]) push_flp(son[x][1]);
			tag[x]=0;
		}
	}
	void rotate(int x){
		int f=fa[x],gf=fa[f],wh=get(x);
		if(isnotroot(f)) son[gf][get(f)]=x;
		son[f][wh]=son[x][wh^1];
		fa[son[x][wh^1]]=f;
		son[x][wh^1]=f;
		fa[f]=x,fa[x]=gf;
		push_up(f),push_up(x);
	}
	void update(int x){
		if(isnotroot(x)) update(fa[x]);
		push_down(x);
	}
	inline void splay(int x){
		update(x);
		for(int f;f=fa[x],isnotroot(x);rotate(x)) 
			if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
		push_up(x);
	}
	inline int access(int x){
		int y;for(y=0;x;y=x,x=fa[x]) splay(x),son[x][1]=y,push_up(x);return y;
	}
	inline void make_root(int x){
		x=access(x),splay(x),push_flp(x);
	}
	inline int find_root(int x){
		access(x),splay(x);
		while(son[x][0]) push_down(x),x=son[x][0];
		splay(x);
		return x;
	}
	inline void spilt(int x,int y){
		make_root(x),access(y),splay(y);
	}
	inline void link(int x,int y){
		make_root(x),splay(x);
		if(find_root(y)!=x) fa[x]=y;
	}
	inline void cut(int x,int y){
		spilt(x,y);
		if(son[y][0]==x&&!son[x][1]) 
			son[y][0]=fa[x]=0;push_up(y);
	}
}lct;
int _;
signed main()
{
	for(_=read();_;_--) {
		n=read(),m=read();
		R(i,1,m) {
			int u=read(),v=read(),d=read();
			e[i]=(edge){u,v,d};
		}
		sort(e+1,e+m+1);
		R(i,1,m) alle[i]=e[i].d;
		lct.init();
		R(i,1,m) {
			if(lct.find_root(e[i].u)!=lct.find_root(e[i].v)) {
				lct.link(e[i].u,n+i),lct.link(n+i,e[i].v);arr[i]=0;
			}
			else {
				lct.spilt(e[i].u,e[i].v);
				id=lct.minn[e[i].v];
				arr[i]=id;
				lct.cut(e[id].u,id+n),lct.cut(id+n,e[i].v);
				lct.link(e[i].u,i+n),lct.link(i+n,e[i].v);
			}
		}
		clst.clr();
		R(i,1,m) {
			clst.modify(arr[i],0,m,clst.Rt[i],clst.Rt[i-1],e[i].d);
		}
		q=read();
		lst_ans=0;
		R(i,1,q) {
			int l=read(),r=read();
			l-=lst_ans,r-=lst_ans;
			l=lob(alle+1,alle+m+1,l)-alle-1;
			r=lob(alle+1,alle+m+1,r+1)-alle-1;
			lst_ans=clst.query(0,l,0,m,clst.Rt[r])-clst.query(0,l,0,m,clst.Rt[l]);
			printf("%d\n",lst_ans);
		}
	}
}
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
const int inf=0x7f7f7f7f7f7f7f3f;
//const int inf=0x7f7f7f7f;
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
sto 鏡音リン orz
全局平衡二叉树：一种可以处理树上链修改/查询的数据结构，可以做到
一条链整体修改:(log n)
一天链整体查询:(log n)
还可以求LCA，子树修改，子树查询，这些复杂度与轻重链剖分一样
主要性质:
1.它由很多棵二叉树通过轻边连起来，每一棵二叉树维护原树的一条重链，
其中序遍历的顺序就是这条重链单调递增的顺序，每个节点都仅出现在一棵二叉树中
2.边分为重边和轻边，重边是包含在二叉树的边，维护的时候就想正常维护二叉树一样，记录左右儿子和父节点。
轻边从一棵二叉树的根节点指向它所对于的重链顶端的根节点。轻边维护的时候"认父不认子"，即只能从子节点访问父节点
注意：全局平衡二叉树中的边和原树中的边没有对应关系
3.算上轻边和重边，这棵树的高度是(log n)级别的。这是保证复杂度的性质
建树:
按照性质里所说来就可以了。首先是像普通重链剖分一样，一次dfs求出每个节点的重儿子。然后从根开始，找到根节点所在的重链，
对于这些点的轻儿子开始递归建树，并连上轻边。然后我们需要给重链上的点建一棵二叉树，我们先把重链上点存到数组里，求出
每个点轻儿子的siz+1。然后我们按照这个求出这条重链的加权中点，把它作为二叉树的根两边递归建树，并连上重边
std::vector<int> G[N];
int n, fa[N], son[N], sz[N];
void dfsS(int u) {
	sz[u] = 1;
	for (int v : G[u]) {
		dfsS(v);
		sz[u] += sz[v];
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
}
int b[N], bs[N], l[N], r[N], f[N], ss[N];
// 给b中[bl,br)内的点建二叉树，返回二叉树的根
int cbuild(int bl, int br) {
	int x = bl, y = br;
	while (y-x > 1) {
		int mid = (x+y) >> 1;
		if (2*(bs[mid]-bs[bl]) <= bs[br]-bs[bl]) x = mid;
		else y = mid;
	}
	// 二分求出按bs加权的中点
	y = b[x];
	ss[y] = br-bl; // ss：二叉树中重子树的大小
	if (bl < x) {l[y] = cbuild(bl, x); f[l[y]] = y; }
	if (x+1 < br) {r[y] = cbuild(x+1, br); f[r[y]] = y; }
	return y;
}
int build(int x) {
	int y = x;
	do for (int v : G[y])
		if (v != son[y])
			f[build(v)] = y; // 递归建树并连轻边，注意要从二叉树的根连边，不是从儿子连边
	while (y = son[y]);
	y = 0;
	do {
		b[y++] = x; // 存放重链中的点
		bs[y] = bs[y-1] + sz[x] - sz[son[x]]; // bs：轻儿子size和+1，求前缀和
	} while (x = son[x]);
	return cbuild(0, y);
}
由代码可以看出建树的时间复杂度是O(n log n)的.
关于树高是(log n)的证明:
考虑从任意一个点跳父节点到根.跳轻边就相当于在原树中跳到另一条重链,由重链剖分的性质可得跳轻边最多log n条
因为建二叉树的时候根节点找的是轻儿子的加权中点，那么跳一次重边算上轻儿子的size至少翻倍，所以跳重边最多也是log n条整体树高log n

实际上关于全局平衡二叉树的部分就已经讲完了，
剩下的链修改、链查询只需要从要操作的点往根跳，
要操作某个点重链上比它深度小的所有点，
就相当于在这条重链的二叉树里操作这个点左侧的所有点，
可以拆成一系列子树操作，像维护普通二叉树一样维护子树和，
打子树加标记就行。我使用的是标记永久化，
其实也是可以标记用 pushdown，子树和用 pushup 的，
不过可能不太好写（因为平时处理二叉树都是自上而下，这里是自下而上，
可能需要先处理出跳的路径然后从上往下 pushdown 一遍，常数大大大）。

// a：子树加标记
// s：子树和（不算加标记的）
int a[N], s[N];
void add(int x) {
	bool t = true; int z = 0;
	while (x) {
		s[x] += z;
		if (t) {
			a[x]++; if (r[x]) a[r[x]]--;
			z += 1 + ss[l[x]];
			s[x] -= ss[r[x]];
		}
		t = (x != l[f[x]]);
		if (t && x != r[f[x]]) z = 0; // 跳过轻边要清空
		x = f[x];
	}
}
int query(int x) {
	int ret = 0;
	bool t = true; int z = 0;
	while (x) {
		if (t) {
			ret += s[x] - s[r[x]];
			ret -= 1ll * ss[r[x]] * a[r[x]];
			z += 1 + ss[l[x]];
		}
		ret += 1ll * z * a[x];
		t = (x != l[f[x]]);
		if (t && x != r[f[x]]) z = 0; // 跳过轻边要清空
		x = f[x];
	}
	return ret;
}
对于子树操作，就是要考虑轻儿子的，需要再维护一个包括轻儿子的子树和、子树标记
*/
const int N=55555;
int n,q,fa[N],siz[N],hson[N];
std::vector<int>e[N];
void dfs1(int u){
	siz[u]=1;
	for(int v:e[u]) {
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[hson[u]]<siz[v]) hson[u]=v;
	}
}
int ffa[N];
int siz_hson[N];
int Ls[N],Rs[N];
int hchain[N],siz_softchain[N];
int rebuild(int L,int R){
	int x=L,y=R;
	while(y-x>1) {
		int mid=(x+y)>>1;
		if(((siz_softchain[mid]-siz_softchain[L])<<1)<=siz_softchain[R]-siz_softchain[L]) x=mid;
		else y=mid;
	}
	y=hchain[x];
	siz_hson[y]=R-L;
	if(L<x) {
		Ls[y]=rebuild(L,x);
		ffa[Ls[y]]=y;
	}
	if(x+1<R) {
		Rs[y]=rebuild(x+1,R);
		ffa[Rs[y]]=y;
	}
	return y;
}
int build(int x){
	int y=x;
	do
	{
		for(int v:e[y]) {
			if(v==hson[y]) continue;
			ffa[build(v)]=y;
		}
	}while(y=hson[y]);
	
	do
	{
		hchain[y++]=x;
		siz_softchain[y]=siz_softchain[y-1]+siz[x]-siz[hson[x]];
	}while(x=hson[x]);
	return rebuild(0,y);
}
int lazy[N],val[N];
void modify_add(int x){
	int t=1,sum=0;
	while(x){
		val[x]+=sum;
		if(t) {
			lazy[x]++;
			if(Rs[x]) lazy[Rs[x]]--;
			sum+=1+siz_hson[Ls[x]];
			val[x]-=siz_hson[Rs[x]];
		}
		t=(x!=Ls[ffa[x]]);
		if(t&&x!=Rs[ffa[x]]) sum=0;
		x=ffa[x];
	}
}
int query(int x){
	int ret=0,t=1,sum=0;
	while(x){
		if(t) {
			ret+=val[x]-val[Rs[x]];
			ret-=1ll*siz_hson[Rs[x]]*lazy[Rs[x]];
			sum+=siz_hson[Ls[x]]+1;
		}
		ret+=1ll*sum+lazy[x];
		t=(x!=Ls[ffa[x]]);
		if(t&&x!=Rs[ffa[x]]) sum=0;
		x=ffa[x];
	}
	return ret;
}
std::vector<pii>qs1[N],qs2[N];
int ans[N];

signed main()
{	
	n=read(),q=read();
	R(i,2,n) {
		fa[i]=read()+1;
		e[fa[i]].pb(i);	
	}
	dfs1(1);
	build(1);
	FR(i,0,q) {
		int x=read(),y=read()+1,d=read()+1;
		if(x) qs1[x].pb(mkp(x,d));
		qs2[y].pb(mkp(y,d));
	}
	R(i,1,n) {
		modify_add(1);
		for(auto qwq:qs1[i]) 
			ans[qwq.se]-=query(qwq.fi);
		for(auto qwq:qs2[i]) 
			ans[qwq.se]+=query(qwq.fi);
	}
	R(i,0,q) {
		printf("%lld\n",ans[i]%201314);
	}
}

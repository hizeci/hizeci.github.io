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
    if(f)x=-x;return x;
}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
/*
维护子树信息
LCT 不擅长维护子树信息。统计一个结点所有虚子树的信息，就可以求得整棵树的信息。
例题「BJOI2014」大融合:
给定n个结点和q次操作,每个操作为如下形式:
1.A x y 在结点x和y之间连接一条边。
2.Q x y 给定一条已经存在的边(x,y),求有多少条简单路径,其中包含边(x,y).
保证在任意时刻，图的形态都是一棵森林。
1e5

为询问 Q 考虑另一种表述，我们发现答案等于边(x,y)在x侧的结点数与y侧的结点数的乘积,
即将边(x,y)断开后分别包含x和y的树的结点数。
为了消除断边的影响，在询问后我们再次连接边(x,y)。
但是这题中 LCT 维护的是子树的大小，不像我们印象中的维护一条链的信息，而 LCT 的构造 认父不认子 ，
不方便我们直接进行子树的统计
方法是统计一个结点x所有虚儿子（即父亲为x，但x在 Splay中的左右儿子并不包含它)所代表的子树的贡献。

定义siz2[x]为结点x的所有虚儿子代表的子树的结点数,siz[x]为结点x子树中的结点数。
不同于以往我们维护 Splay 中子树结点个数的方法，我们在计算结点x子树中的结点数时，还要加上siz2[x] ，
void maintain(int x){
	clear(0);
	if(x) siz[x]=siz[son[x][0]]+siz[son[x][1]]+1+siz2[x];
}

而且在我们 改变 Splay 的形态 （即改变一个结点在 Splay 上的左右儿子指向时），需要及时修改 siz2[x] 的值。
在 Rotate(),Splay() 操作中，我们都只是改变了 Splay 中结点的相对位置，
没有改变任意一条边的虚实情况，所以不对 siz2[x] 进行任何修改。

在 access 操作中，在每次 splay 完后，都会改变刚刚 splay 完的结点的右儿子，
即该结点与其原右儿子的连边和该节点和新右儿子的连边的虚实情况发生了变化，我们需要加上新变成虚边所连的子树的贡献，减去刚刚变成实边所连的子树的贡献。
int access(int x){
	int y;
	for(y=0;x;y=x,x=fa[x]) 
		splay(x),siz2[x]+=siz[son[x][1]]-siz[y],son[x][1]=y,maintain(x);
	return y;
}

在 MakeRoot(),Find() 操作中，我们都只是调用了之前的函数或者在 Splay 上条边，并不用做任何修改。
在连接两点时，我们修改了一个结点的父亲。我们需要在父亲结点的 siz2 值中加上新子结点的子树大小贡献。
makeroot(x);
makeroot(y);
fa[x] = y;
siz2[y] += st.siz[x];

在断开一条边时，我们只是删除了 Splay 上的一条实边， Maintain 操作会维护这些信息，不需要做任何修改。

代码修改的细节讲完了，总结一下 LCT 维护子树信息的要求与方法：
1.维护的信息要有 可减性 ，如子树结点数，子树权值和，
但不能直接维护子树最大最小值，因为在将一条虚边变成实边时要排除原先虚边的贡献。
2.新建一个附加值存储虚子树的贡献，在统计时将其加入本结点答案，在改变边的虚实时及时维护。
3.其余部分同普通 LCT，在统计子树信息时一定将其作为根节点。
4.如果维护的信息没有可减性，如维护区间最值，可以对每个结点开一个平衡树维护结点的虚子树中的最值。
*/
const int N=2e6+10;
int son[N][2],fa[N],siz[N],siz2[N],tag[N];
int n,q;

inline void clear(int x){
	son[x][0]=son[x][1]=fa[x]=siz[x]=siz2[x]=tag[x]=0;
}
inline int get(int x){
	return x==son[fa[x]][1];
}
inline int isnotroot(int x){
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
inline void push_up(int x){
	clear(0);if(x) siz[x]=siz[son[x][1]]+siz[son[x][0]]+1+siz2[x]; 
}
inline void push_flp(int x){
	Swap(son[x][0],son[x][1]);tag[x]^=1;
}
inline void push_down(int x){
	if(tag[x]) {
		if(son[x][0]) push_flp(son[x][0]);
		if(son[x][1]) push_flp(son[x][1]);
		tag[x]=0;
	}
}
void update(int x){
	if(isnotroot(x)) update(fa[x]);
	push_down(x);
}
void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	if(isnotroot(f)) son[gf][get(f)]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x,fa[x]=gf;
	push_up(f),push_up(x); 
}
inline void splay(int x){
	update(x);
	for(int f;f=fa[x],isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
	push_up(x);//???
}
inline int access(int x){
	int y;
	for(y=0;x;y=x,x=fa[x])
		splay(x),siz2[x]+=siz[son[x][1]]-siz[y],son[x][1]=y,push_up(x);
	return y;
}
inline void make_root(int x){
	access(x),splay(x),push_flp(x);
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
	//make_root(x),splay(x);
	//if(find_root(y)!=x) splay(y),fa[x]=y,siz2[y]+=siz[x];
	make_root(x),make_root(y);
	fa[x]=y,siz2[y]+=siz[x];
}
inline void cut(int x,int y){
	spilt(x,y);
	if(son[y][0]==x&&!son[x][1]){
		son[y][0]=fa[x]=0;
		push_up(y);
	}
}
char opt[111];
signed main()
{
	n=read(),q=read();
	R(i,1,q) {
		scanf("%s",opt+1);
		int u=read(),v=read();
		if(opt[1]=='A') link(u,v);
		if(opt[1]=='Q') {
			cut(u,v);
			make_root(u),make_root(v);
			printf("%lld\n",1ll*siz[u]*siz[v]);
			link(u,v);
		}
	}
}
/*
8 6
A 2 3
A 3 4
A 3 8
A 8 7
A 6 5
Q 3 8
*/
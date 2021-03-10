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
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int N=1511111;
struct edge
{
    int nxt,to;
}e[N<<1];
int head[N],cnt;
int n;
int fa[N],son[N][2],tag[N],siz[N],sum[N],col[N],id[N][4];
//首先，每一次修改权值改变的点的集合一定是某一条自上而下的链，并且不一定是从根开始的，但是一定以被修改点结尾的。
//所以就可以通过维护或者计算的方式通过LCT搞出这个链的起点（也就是最上面的点），然后通过splay区间修改的方式进行链修改。
//我们定义sum_i 表示第i个点的儿子当中，颜色为1的点的个数。
//1、若被修改点是从1修改成0，那么从被修改点开始向上，只有sum=2的点的颜色改变（从1变成0）
//2、若被修改点是从0修改成1，那么从被修改点开始向上，只有sum=1的点的颜色改变（从0变成1）
//所以我们可以求出这个sum全部为2或者全部为1的从上到下的链的起点，然后在splay里面修改就行了
//直接维护最深的不为1/2点的编号
//需要注意特判：如果整条从根到叶子的链没有一个不为1/2的点，直接做区间修改。
//最后对于主函数里面的修改，分两种情况：
//1、如果路径上存在id_1或者id_2,我们可以把被修改的链上的点的sum-1/+1（因为只有这些点的sum会变),然后再pushup.
//2、如果没有id_1或者id_2 ,说明这次修改会影响到从该节点到根的所有点，那么就直接整条链修改就行了，同时把1节点的颜色取反。

//设当前被修改点为x。
//1、在修改的时候，不能将被修改的叶子节点也放到splay当中（即access的时候一定要从fa[x]开始access），
//因为叶子节点的sum为0，那么这个splay里面的id_1,id_2 都是这个叶子节点，那么我们维护的id_1,id_2  就没有意义了。
//2.在把fa[x]旋根之后，一定是修改右子树，而不是修改整个子树，因为左子树的信息并不会改变。
//3.在修改了右子树之后，不要忘记对fa[x]进行单点修改。
inline void init(){
    memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
inline int get(int x){
	return x==son[fa[x]][1];
}	
inline int isnotroot(int x){
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
inline void push_up(int x){
	id[x][1]=id[son[x][1]][1];
	id[x][2]=id[son[x][1]][2];
	if(!id[x][1]) {
		if(sum[x]!=1) id[x][1]=x;
		else id[x][1]=id[son[x][0]][1];
	}
	if(!id[x][2]){
		if(sum[x]!=2) id[x][2]=x;
		else id[x][2]=id[son[x][0]][2];
	}
}
inline void modify_add(int x,int k){
	sum[x]+=k,col[x]=sum[x]>1;
	Swap(id[x][1],id[x][2]);
	/*这里直接swap就行了，因为进行加标记的子树一定是全部sum为1或者2的子树，这种子树修改之后id[1]和id[2]值会交换。 
	以将整个子树的点sum全部减一为例。
	首先，修改之后的id[2]为肯定就是这个子树里面最深的点了（因为原来他的sum是2，现在他的sum变成1了，所以现在的id[2]就是他了），然后这个最深的点肯定是原来的id[1]（因为他原来是sum=2的点，又是最深的点），所以id[2]=id[1]；
	其次，原来的id[2]在减一之后一定sum不等于1（因为如果减一之后他的sum变成1的话，他原来的sum就一定为2了，那么他就不是id[2]了），又因为这个id[2]下面的点在减一之后全部变成1了，所以他就变成id[1]了。
	综上，修改后的id[2]=原来的id[1]，修改后的id[1]=原来的id[2]，swap就行了。
	*/
	tag[x]+=k;
} 
inline void push_down(int x){
	if(tag[x]){
		if(son[x][0]) modify_add(son[x][0],tag[x]);
		if(son[x][1]) modify_add(son[x][1],tag[x]);
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
	fa[f]=x;
	fa[x]=gf;
	push_up(f);
	push_up(x);
}
inline void splay(int x){
	update(x);
	for(int f;f=fa[x],isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
	push_up(x);
} 
inline int access(int x){
	int y;
	for(y=0;x;y=x,x=fa[x]) 
		splay(x),son[x][1]=y,push_up(x);
	return y;
}
void dfs(int u,int f)
{
	sum[u]=0;
	for(int i=head[u];i!=-1;i=e[i].nxt)
	{
        int v=e[i].to;
		if(v==f) continue;
		dfs(v,u);
		sum[u]+=col[v];
	}
	if(u<=n) col[u]=sum[u]>1;
}
signed main()
{
    init();
	n=read();
	R(i,1,n){
		R(j,1,3){
			int x=read();
			fa[x]=i;
            add_edge(i,x),add_edge(x,i);
		}
	}
	R(i,n+1,3*n+1) col[i]=read();
	dfs(1,0);
	int q=read();
	int lst,qwq,res=col[1],x,lazy;
	while(q--)
	{
		lst=read();x=fa[lst];
		lazy=col[lst]?-1:1;
		access(x),splay(x);
		qwq=id[x][col[lst]?2:1];
		if(qwq){
			splay(qwq);
			modify_add(son[qwq][1],lazy);
			push_up(son[qwq][1]);
			sum[qwq]+=lazy;
			col[qwq]=sum[qwq]>1;
			push_up(qwq);
		} 
		else res^=1,modify_add(x,lazy),push_up(x);
		col[lst]^=1;
		printf("%d\n",res);
	}
}
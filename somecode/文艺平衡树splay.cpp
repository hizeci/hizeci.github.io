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
const int inf=0x7f7f7f7f7f7f;
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
/*
那么对于区间反转这种操作，我们由于原数列的顺序已经给定，所以不能按照权值排序，所以选择按照点的编号建立一棵二叉搜索树。
诶，所以啊，不用一个个insert编号，我们只需要进行一下递归建树即可qwq—建树可以仿照线段树的建树qwq
那么我们现在已经有一棵编号树了(并且由于递归建树，一开始是平衡的)，我们要对它进行区间翻转操作。那么实际上我们可以发现，在反转区间[l~r]的时候，
我们可以考虑利用Splay性质，将l-1翻转至根节点，再将r+1翻转至根节点的右儿子

但在这里还是需要注意，我们为了方便，在1号节点之前和n号节点之后又加了两个节点并赋值为-INF和INF
作为虚点，既满足二叉搜索树的性质，又可以让我们在翻转1~n时不会GG
那么实际上，在我们把当前区间确定下来之后，我们就要开始进行反转操作。而对于反转操作，我们可以不断替换子节点的左右子树达到此目的。
比如对于1~5这个序列，我们反转2 4这个区间，过程就是这样：
那么实际上我们如果反转2 4那么我们需要先将1和5旋转上去，类似这样：
那么实际上我们翻转两个子树就相当于反转2 4
但在这个地方我们可以考虑打个标记，标记的存在就只在于记录现在对于当前节点应不应该翻转两个子树。
*/
const int N=1111111;
int rt,tot_nd,fa[N],son[N][2],wei[N],cnt[N],siz[N],tag[N];
inline void maintain(int x) {siz[x]=siz[son[x][0]]+siz[son[x][1]]+cnt[x];}
inline int get(int x) {return x==son[fa[x]][1];}
inline void clear(int x) {son[x][0]=son[x][1]=fa[x]=wei[x]=cnt[x]=siz[x]=0;}
/*
struct Splay_Tr
{
	int fa,siz,cnt,tag,wei,son[2];
}s[N];
*/
int a[N];
/*
inline int get(int x) {return x==s[s[x].fa].son[1];}
inline void maintain(int x) {s[x].siz=s[x].cnt+s[s[x].son[0]].siz+s[s[x].son[1]].siz;}
*/
void push_down(int x)
{
	if(x&&tag[x]) 
	{
		tag[son[x][0]]^=1,tag[son[x][1]]^=1;
		Swap(son[x][0],son[x][1]);
		tag[x]=0;
		/*
		s[s[x].son[0]].tag^=1,s[s[x].son[1]].tag^=1;
		Swap(s[x].son[0],s[x].son[1]);
		s[x].tag=0;
		*/
	}
}
void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	push_down(x),push_down(f);
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	if(gf) son[gf][son[gf][1]==f]=x;
	maintain(f);
	maintain(x);
}
/*
void splay(int x,int &to)
{
	int f=fa[to];
	while(fa[x]!=f) 
	{
		if(fa[fa[x]]!=f) rotate(get(x)==get(fa[x])?fa[x]:x);
		rotate(x);
	}
	to=x;
}
*/
void splay(int x,int to)
{
	for(int qwq;(qwq=fa[x])!=to;rotate(x))
		if(fa[qwq]!=to) rotate(get(x)==get(qwq)?qwq:x);
	if(!to) rt=x;
}
int build(int l,int r,int f)
{
	if(l>r) return 0;
	int mid=(l+r)>>1;
	int cnr=++tot_nd;
	fa[cnr]=f;
	son[cnr][0]=son[cnr][1]=0;
	cnt[cnr]++;
	wei[cnr]=a[mid];
	siz[cnr]++;
	son[cnr][0]=build(l,mid-1,cnr);
	son[cnr][1]=build(mid+1,r,cnr);
	maintain(cnr);
	return cnr;
}
int find(int x)
{
	int cnr=rt;
	while(1)
	{
		push_down(cnr);
		if(x<=siz[son[cnr][0]]) cnr=son[cnr][0];
		else
		{
			x-=siz[son[cnr][0]]+1;
			if(!x) return cnr;
			cnr=son[cnr][1];
		}
	}
}
void rever(int x,int y)
{
	int l=x-1,r=y+1;
	l=find(l),r=find(r);
	splay(l,0),splay(r,l);
	int cnr=son[rt][1];
	cnr=son[cnr][0];
	tag[cnr]^=1;
}
void print(int cnr)
{
	push_down(cnr);
	if(son[cnr][0]) print(son[cnr][0]);
	if(wei[cnr]!=-inf&&wei[cnr]!=inf) {printf("%lld ",wei[cnr]);}
	if(son[cnr][1]) print(son[cnr][1]);
}

signed main()
{
	int n=read(),m=read();
	a[1]=-inf,a[n+2]=inf;
	R(i,1,n) a[i+1]=i;
	rt=build(1,n+2,0);
	while(m--) {
		int x=read(),y=read();
		rever(x+1,y+1);
	}
	print(rt);puts("");
}
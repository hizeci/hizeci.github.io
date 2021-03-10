//splay
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
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/

const int N=1111111;  //wei[]节点权值 cnt_wei权值出现次数,siz[]子树大小
int rt,fa[N],son[N][2],wei[N],cnt_wei[N],siz[N];
int tot_nd;//节点个数
inline void maintain(int x) {siz[x]=siz[son[x][0]]+siz[son[x][1]]+cnt_wei[x];} //在改变节点位置后，将节点 x 的 siz 更新。
inline int get(int x) {return x==son[fa[x]][1];}//判断节点 x 是父亲节点的左儿子还是右儿子
inline void clear(int x) {son[x][0]=son[x][1]=fa[x]=wei[x]=siz[x]=cnt_wei[x]=0;}
inline int find(int x) {int cnr=rt;while(wei[cnr]!=x)cnr=son[cnr][x>wei[cnr]];return cnr;}
/*
我们定义一个结点与他父亲的关系是 x,那么在旋转时,他的父亲成为了他的 !x儿子,并且那个上文中所说的“多余结点”，
同时也是当前节点的 !x儿子，但在旋转之后需要成为当前节点的“前”父节点的 x儿子。
by hua
*/
/*
为了使 Splay 保持平衡而进行旋转操作，旋转的本质是将某个节点上移一个位置。

旋转需要保证 ：

整棵 Splay 的中序遍历不变（不能破坏二叉查找树的性质）。
受影响的节点维护的信息依然正确有效。
root 必须指向旋转后的根节点。
在 Splay 中旋转分为两种：左旋和右旋。

具体分析旋转步骤 （假设需要旋转的节点为 x，其父亲为 y，以右旋为例）

将 y的左儿子指向 x 的右儿子，且 x 的右儿子的父亲(为)指向 y ； ch[y][0]=ch[x][1]; fa[ch[x][1]]=y;
将  x的右儿子指向 y ，且 y 的父亲(为)指向 x ； ch[x][chk^1]=y; fa[y]=x;
如果原来的 y还有父亲 z ，那么把 z 的某个儿子（原来 y 所在的儿子位置）指向 x ，且 x 的父亲(为)指向 z。 fa[x]=z; if(z) ch[z][y==ch[z][1]]=x;
*/
void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	//push_down(f),pushdown(x);
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
Splay 规定：每访问一个节点后都要强制将其旋转到根节点。此时旋转操作具体分为 6 种情况讨论（其中 x 为需要旋转到根的节点）
如果 x 的父亲是根节点，直接将 x 左旋或右旋
如果 x 的父亲不是根节点，且 x 和父亲的儿子类型相同，首先将其父亲左旋或右旋，然后将 x 右旋或左旋
如果 x 的父亲不是根节点，且 x 和父亲的儿子类型不同，将 x 左旋再右旋、或者右旋再左旋
*/
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
/*
插入
插入操作是一个比较复杂的过程，具体步骤如下（假设插入的值为 k
如果树空了，则直接插入根并退出。
如果当前节点的权值等于 k 则增加当前节点的大小并更新节点和父亲的信息，将当前节点进行 Splay 操作
否则按照二叉查找树的性质向下找，找到空节点就插入即可（请不要忘记 Splay 操作）。
*/
void ins(int k)
{
	if(!rt)
	{
		wei[++tot_nd]=k;
		cnt_wei[tot_nd]++;
		rt=tot_nd;
		maintain(rt);
		return;
	}
	int cnr=rt,f=0;
	while(1)
	{
		if(wei[cnr]==k)
		{
			cnt_wei[cnr]++;
			maintain(cnr);
			maintain(f);
			splay(cnr,rt);
			break;
		}
		f=cnr;
		cnr=son[cnr][wei[cnr]<k];
		if(!cnr)
		{
			wei[++tot_nd]=k;
			cnt_wei[tot_nd]++;
			fa[tot_nd]=f;
			son[f][wei[f]<k]=tot_nd;
			maintain(tot_nd);
			maintain(f);
			splay(tot_nd,rt);
			break;
		}
	}
}
/*
查询 x 的排名
根据二叉查找树的定义和性质，显然可以按照以下步骤查询 x 的排名：
如果 x 比当前节点的权值小，向其左子树查找。
如果 x 比当前节点的权值大，将答案加上左子树 siz 和当前节点 cnt 的大小，向其右子树查找。
如果 x 与当前节点的权值相同，将答案加 1 并返回。

注意最后需要进行 Splay 操作。
*/
/*
int find_rk(int k)
{
	int cnr=find(k);
	splay(cnr,rt);
	return siz[son[rt][0]]+1;
}
*/
int find_rk(int k)
{
	int res=0,cnr=rt;
	while(1)
	{
		if(k<wei[cnr]) cnr=son[cnr][0];
		else
		{
			res+=siz[son[cnr][0]];
			if(k==wei[cnr]) 
			{
				splay(cnr,rt);
				return res+1;
			}
			res+=cnt_wei[cnr];
			cnr=son[cnr][1];
		}
	}
}
/*
查询排名 x 的数
设 k 为剩余排名，具体步骤如下：
如果左子树非空且剩余排名 k 不大于左子树的大小 siz ，那么向左子树查找。
否则将 k 减去左子树的和根的大小。如果此时 k 的值小于等于 0 ，则返回根节点的权值，否则继续向右子树查找。
*/
int find_kth(int k)
{
	int cnr=rt;
	while(1)
	{
		if(son[cnr][0]&&k<=siz[son[cnr][0]]) cnr=son[cnr][0];
		else
		{
			k-=cnt_wei[cnr]+siz[son[cnr][0]];
			if(k<=0) {
				splay(cnr,rt);
				return wei[cnr];
			}
			cnr=son[cnr][1];
		}
	}
}
/*
查询前驱
前驱定义为小于 x 的最大的数，那么查询前驱可以转化为：将 x 插入（此时 x 已经在根的位置了），
前驱即为 x 的左子树中最右边的节点，最后将 x 删除即可。
*/
int find_lst()
{
	int cnr=son[rt][0];
	while(son[cnr][1]) cnr=son[cnr][1];
	splay(cnr,rt);
	return cnr;
}
/*
查询后继
后继定义为大于 x 的最小的数，查询方法和前驱类似： x 的右子树中最左边的节点。
*/
int find_nxt()
{
	int cnr=son[rt][1];
	while(son[cnr][0]) cnr=son[cnr][0];
	splay(cnr,rt);
	return cnr;
}
/*
合并两棵树
合并两棵 Splay 树，设两棵树的根节点分别为 x 和 y ，那么我们要求 x 树中的最大值小于 y 树中的最小值。删除操作如下：
如果 x 和 y 其中之一或两者都为空树，直接返回不为空的那一棵树的根节点或空树。
否则将 x 树中的最大值 Splay 到根，然后把它的右子树设置为 y 并更新节点的信息，然后返回这个节点。
*/
/*
删除操作
先将x旋转到根的位置
如果cnt_wei[x]>1(有不止一个x),那么将cnt_wei[x]减1并退出
否则合并它的两棵子树即可
*/
void del(int k)
{
	find_rk(k);
	if(cnt_wei[rt]>1)
	{
		cnt_wei[rt]--;
		maintain(rt);
		return;
	}
	if(!son[rt][0]&&!son[rt][1])
	{
		clear(rt);
		rt=0;
		return;
	}
	if(!son[rt][0])
	{
		int cnr=rt;
		rt=son[rt][1];
		fa[rt]=0;
		clear(cnr);
		return;
	}
	if(!son[rt][1])
	{
		int cnr=rt;
		rt=son[rt][0];
		fa[rt]=0;
		clear(cnr);
		return;
	}
	int cnr=rt,x=find_lst();
	fa[son[cnr][1]]=x;
	son[x][1]=son[cnr][1];
	clear(cnr);
	maintain(rt);
}
signed main()
{
	//int n=read(),m=read();
	//R(i,1,n) a[i]=read();
	int n=read();
	R(i,1,n)
	{
		int opt=read(),x=read();
		if(opt==1) ins(x);
		if(opt==2) del(x);
		if(opt==3) printf("%lld\n",find_rk(x));
		if(opt==4) printf("%lld\n",find_kth(x));
		if(opt==5) ins(x),printf("%lld\n",wei[find_lst()]),del(x);
		if(opt==6) ins(x),printf("%lld\n",wei[find_nxt()]),del(x);
	}
}
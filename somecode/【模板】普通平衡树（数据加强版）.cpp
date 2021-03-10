//fhq treap
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

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
/*
printf("%lld ",dist(rand_num));
*/
const int N=1111111;
struct pai
{
	int a,b;
	pai(int a_=0,int b_=0){a=a_,b=b_;}
};
int key[N],wei[N],siz[N],son[N][2];
int n,m,tot_key,res,rt,lst_res;
inline int rand1(){
	return dist(rand_num);
}
inline void push_up(int x)
{
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
}
/*如果当前子树的根的值大于等于 k，
就继续分裂左子树，并将分出来的右边的子树作为根节点的左子树；
否则分裂右子树，并将分出来的左边的子树作为根节点的右子树。
函数 split 接受一个根和一个 k，返回分裂后的两棵子树的根。
*/

/*
upd on 2021/2/7 key和wei换下位置
*/
pai spilt(int u,int k)
{
	if(!u) return pai(0,0);
	if(key[u]<k)//如果值小于k
	{
		pai t=spilt(son[u][1],k);//分裂右子树
		son[u][1]=t.a;//将左边的子树作为根的右子树
		push_up(u);
		return pai(u,t.b);
	}
	else
	{
		pai t=spilt(son[u][0],k);
		son[u][0]=t.b;
		push_up(u);
		return pai(t.a,u);
	}
};
/*
合并是将 x,y 两个 Treap 合并为一个 Treap（x 中的每一个结点的值都小于等于 y 中每一个结点的值）

比较两个树根的权，权大的作为权小的子结点，继续合并子树。

merge 函数接受两个参数，为两棵树的根；返回合并后的根。
*/
int mer(int u,int v)
{
	if(!u||!v) return u^v;
	if(wei[u]<wei[v])
	{
		son[u][1]=mer(son[u][1],v); //将右子树和另一棵树合并，作为右子树
		push_up(u);
		return u;
	}
	else 
	{
		son[v][0]=mer(u,son[v][0]);
		push_up(v);
		return v;
	}
}
/*
插入一个值为 k 的结点:
先申请一个新的结点，作为一棵树 y；并将原来的树分裂成 x,z 两棵树。
然后依次合并 x,y,z，就完成了。
*/
void ins(int k)
{
	key[++tot_key]=k,wei[tot_key]=rand1(),siz[tot_key]=1;
	pai t=spilt(rt,k);//以K为关键值分裂
	rt=mer(mer(t.a,tot_key),t.b);//依次合并
}
/*
删除比较巧妙，先将树分裂成 x,y,z 三棵树；其中 x 的每个结点的值均小于 k，y 的每个结点的值均为 k，z 的每个结点的值均大于 k。
然后目标就是要在 y 中删除仅一个结点
做法是，直接合并 y 的左右两棵子树，根节点就被删除掉了。
接下来的事情都知道了，依次合并 x,y,z。
*/
void era(int k)
{
	pai x,y;
	x=spilt(rt,k);//将整棵树分为小于 k 的和大于等于 k 的
	y=spilt(x.b,k+1);//将大于等于 k 的分为等于 k 的和大于 k 的
	y.a=mer(son[y.a][0],son[y.a][1]);//直接合并 y.a 的两棵子树
	rt=mer(x.a,mer(y.a,y.b));//依次合并起来，更新根
}
/*
查询排名
直接分裂，并将值小于 k 的树的大小加一，返回。
*/
int find1(int k)
{
	pai t=spilt(rt,k);
	int re=siz[t.a]+1;
	rt=mer(t.a,t.b);
	return re;
}
/*
根据排名找树
这次结点上的数就是结点编号了，因为结点的值和权没有用。
比如要找第 3 个数，让我们从根节点开始。
首先，1 号结点的左子树有 4 个结点，那第 3 个结点肯定在左子树了，于是去找左子树的第 3 个结点；
然后，发现 2 号结点的左子树只有 1 个结点，那第 3 个结点肯定在右子树了，于是去找 2 号结点的右子树的第 1 个结点；
接着，发现 5 号结点的左子树有 1 个结点，那第 1 个结点肯定在左子树了，于是去找 5 号结点的左子树的第 1 个结点；
最后，发现 8 号结点的左子树只有 0 个结点，那 8 号结点自己肯定就是答案了，于是返回自己的值。

有循环和递归两种实现方式。
*/
/*
int find2(int k)
{
	int pos=rt;//当前结点初始为根
	while(pos)
	{
		if(k==siz[son[pos][0]]+1) return key[pos]; //如果要找的正是当前结点，直接返回
		if(k<=siz[son[pos][0]]) pos=son[pos][0]; //如果要找的在左子树，当前节点转为左子节点
		else k-=siz[son[pos][0]]+1,pos=son[pos][1];//否则不仅当前结点转为右子节点，还要将 k 减去左子树大小+1
	}
}
*/
int find2(int u,int k)
{
	if(k==siz[son[u][0]]+1) return key[u];
	if(k<=siz[son[u][0]]) return find2(son[u][0],k);
	else return find2(son[u][1],k-siz[son[u][0]]-1);
}
/*
求前驱
什么叫“小于 k，且最大的数”？不就是前面的那个数吗，所以直接查找排名比 k 的排名少一的数。
*/
inline int lst(int k){
	return find2(rt,find1(k)-1);
}
/*
求后继
值相同的结点可能不止一个，所以不能找后面的那个数了，但是可以将值加一，查询它的排名，并找到对应的值。
*/
inline int nxt(int k){
	return find2(rt,find1(k+1));
}
/*
对于一个数集，排序后就是 Treap 的中序遍历；而根肯定是随机权最小的结点
因此期望位置在正中间；所以这棵树期望平衡；所以复杂度为 O(logn)。
*/
signed main()
{
	n=read(),m=read();
	R(i,1,n) {
		int x=read();
		ins(x);
	}
	R(i,1,m)
	{
		int opt=read(),x=read();
		if(opt==1) ins(x^lst_res);
		if(opt==2) era(x^lst_res);
		if(opt==3) {
			lst_res=find1(x^lst_res);
			res^=lst_res;
		}
		if(opt==4){
			lst_res=find2(rt,x^lst_res);
			res^=lst_res;
		}
		if(opt==5){
			lst_res=lst(x^lst_res);
			res^=lst_res;
		}
		if(opt==6){
			lst_res=nxt(x^lst_res);
			res^=lst_res;
		}
	}
	printf("%lld\n",res);

	return 0;
}
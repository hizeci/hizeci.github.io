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
/*
const int N=1e6+10;
int son[N][2],fa[N],  sum[N]  ,wei[N],   tag[N] , laz[N],  siz[N];//and other...
//  左右儿子  父亲为..路径权值和 点权      翻转标记  权值标记  子树大小
// splay 系函数 get(x) 获取x是父亲的哪个儿子 splay(x)通过和rotate操作联动把x旋转到当前Splay Tree的根 rotate(x)将x上旋一层的操作
//access(x) 把根到x的所有点放在一条实链里，使根到x成为一条实路径，并且在同一棵Splay中
//isroot(x) 判断x是否是所在树的根
//update(x) 使access操作后，递归地从上到下pushdown更新信息
//makeroot(x) 使x成为其所在树的根
//link(x,y)在x,y两点之间连一条边
//cut(x,y)把x,y两点之间的边删掉
//find(x)找到x所在树的根节点的编号
//fix(x,v)修改x的点权为v
//spilt(x,y)提取出(x,y)区间的路径，方便区间操作
inline void push_up(int x){
	//maintain other variables
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
}
inline void push_down(int x){
	if(tag[x]!=std_tag)	{
		//pushdown the tag
		tag[x]=std_tag;
	}
}
inline int get(int x) {return x==fa[ch[x][1]];}
inline int isroot(int x) {return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;}
void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	if(!isroot(f)) son[gf][son[gf][1]==f]=x;//打*，上面这句一定要写在前面(普通Splay不用)
	son[f][wh]=son[x][wh^1];		
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	push_up(f);
	push_up(x);		
}
void update(int x){
	if(!isroot(x)) update(fa[x]);
	push_down(x);
}
void splay(int x){
	update(x);
	for(int f;f=fa[x],!isroot(x);rotate(x))
		if(!isroot(f)) rotate(get(f)==get(x)?f:x);
}
//access是LCT的核心操作，求解一条路径，而这条路径恰好是我们当前的一棵Splay,直接调用其信息即可
inline int access(int x){
	int p;
	for(p=0;x;p=x,x=fa[x]){
		splay(x),son[x][1]=p,push_up(x);
	}
	return p;
}
//void access(int x){for(int y=0;x;y=x,x=fa[x]){splay(x);son[x][1]=y;push_up(x);}}	
//我们发现 Access() 其实很容易，只有如下四步操作：
//1.把当前节点转到根。
//2.把儿子换成之前的节点。
//3.更新当前点的信息。
//4.把当前点换成当前点的父亲，继续操作。
//这里提供的 Access 还有一个返回值。这个返回值相当于最后一次虚实链变换时虚边父亲节点的编号。该值有两个含义：
//连续两次 Access 操作时，第二次 Access 操作的返回值等于这两个节点的 LCA.
//表示x到根的链所在的 Splay 树的根。这个节点一定已经被旋转到了根节点，且父亲一定为空。
inline void makeroot(int x){
	x=access(x);
	Swap(son[x][0],son[x][1]);
	tag[x]^=1;
}
//Make_Root() 的重要性丝毫不亚于 Access() 。我们在需要维护路径信息的时候，
//一定会出现路径深度无法严格递增的情况，根据 AuxTree 的性质，这种路径是不能出现在一棵 Splay 中的。
//这时候我们需要用到 Make_Root() 。
//Make_Root() 的作用是使指定的点成为原树的根，考虑如何实现这种操作。
//设 Access(x) 的返回值为 y ，则此时 x 到当前根的路径恰好构成一个 Splay，且该 Splay 的根为 y .
//考虑将树用有向图表示出来，给每条边定一个方向，表示从儿子到父亲的方向。容易发现换根相当于将 x 到根的路径的所有边反向（请仔细思考）。
//因此将 x 到当前根的路径翻转即可。
//由于 y 是 x 到当前根的路径所代表的 Splay 的根，因此将以 y 为根的 Splay 树进行区间翻转即可。
//总结:access(x)+reverse即可
inline void link(int x,int y){
	makeroot(x);
	splay(x);
	fa[x]=y;
}
//Link 两个点其实很简单，先 Make_Root(x) , 然后把 x 的父亲指向 y 即可。如果连边不一定合法的话只需要判断 findroot(x) 是否等于 findroot(y) 即可

//Split 操作意义很简单，就是拿出一棵 Splay , 维护的是 x 到 y 的路径。
//先 MakeRoot(x) ，然后 Access(y) 。如果要 y 做根，再 Splay(y) 。
//另外 Split 这三个操作直接可以把需要的路径拿出到 y 的子树上
//总结:makeroot(x)+access(y)

//cut:如果保证合法，直接 Split(x, y) ，这时候 y 是根， x 一定是它的儿子，双向断开即可。就像这样：
inline void cut(int x,int y){
	makeroot(x),access(y),splay(y),son[x][0]=fa[x]=0;
}
//如果是不保证合法，我们需要判断一下是否有，我选择使用 map 存一下，但是这里有一个利用性质的方法：
//想要删边，必须要满足如下三个条件：
//x,y连通
//x,y的路径上没有其他链
//x没有右儿子
//总结一下，上面三句话的意思就一个,x,y之间有边

//如果割边不一定合法的话，需要：
//1.判一下 x,y 是否连通
//2.split 后判一下该链的大小是否为 2 即可。

//inline void anothercut(int x,int y){//并未知道是否正确
//	spilt(x,y),splay(x),son[x][1]=fa[y]=0,push_up(x);
//}

inline int find(int x){
	access(x),splay(x);
	while(son[x][0]) push_down(x),x=son[x][0];
	splay(x);
	return x;
}
//Find() 其实就是找到当前辅助树的根。在 Access(p) 后，再 Splay(p) 。这样根就是树里最小的那个，一直往 ls 走，沿途 PushDown 即可。
//一直走到没有 ls, 非常简单。
//注意，每次查询之后需要把查询到的答案对应的结点 Splay 上去以保证复杂度。
//总结：access(x) 后跳一跳左子树即可。

//一些提醒
//干点啥前一定要想一想需不需要 PushUp 或者 PushDown , LCT 由于特别灵活的原因，少 Pushdown 或者 Pushup 一次就可能把修改改到不该改的点上！
//LCT 的 Rotate 和 Splay 的不太一样， if (z) 一定要放在前面。
//LCT 的 Splay 操作就是旋转到根，没有旋转到谁儿子的操作，因为不需要。
*/
const int N=1e6+10;
int n,m;
int rt,tot_nd,tag[N],son[N][2],fa[N],siz[N],sum[N],wei[N];
inline int get(int x) {return x==son[fa[x]][1];}
inline int isroot(int x){
	return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;
}
inline void push_up(int x){
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
	sum[x]=sum[son[x][0]]^sum[son[x][1]]^wei[x];
}
void push_down(int x)
{
	if(tag[x])
	{
		tag[son[x][0]]^=1;
		tag[son[x][1]]^=1;
		Swap(son[x][0],son[x][1]);
		tag[x]=0;
	}
}
void update(int x){
	if(!isroot(x)) update(fa[x]);
	push_down(x);
}
void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	if(!isroot(f)) son[gf][f==son[gf][1]]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x,fa[x]=gf;
	push_up(f),push_up(x);
}
int stk[N];
void splay(int x){
	int top=0;
	stk[++top]=x;
	for(int i=x;!isroot(i);i=fa[i]) stk[++top]=fa[i];
		//printf("%d\n",top);
	while(top) {push_down(stk[top--]);}
	//stack<int>stk;
	//while(stk.size()>0) stk.pop();
	//stk.push(x);
	//for(int i=x;!isroot(i);i=fa[i]) stk.push(fa[i]);
	//printf("%d\n",(int)stk.size());
	//while(stk.size()>0) push_down(stk.top()),stk.pop();
	
	//update(x);
	for(int f=fa[x];!isroot(x);rotate(x),f=fa[x])
		if(!isroot(f)) rotate(get(x)==get(f)?f:x);
	push_up(x);
}
/*
void splay(int x)
{
	update(x);
	for(int f;f=fa[x],!isRoot(x);rotate(x))
		if(!isRoot(f)) rotate(get(x)==get(f)?f:x);
	//push_up(x);QAQ??
}
*/
int access(int x){
	int y=0;
	//for(;x;x=fa[y=x])????
	for(;x;y=x,x=fa[x]) 
		splay(x),son[x][1]=y,push_up(x);
	return y;
}
void make_root(int x)
{
	access(x);
	splay(x);
	tag[x]^=1;
}	
/*
void makeroot(int x)
{
	x=access(x);
	Swap(son[x][0],son[x][1]);
	tag[x]^=1;
}
*/
int find_root(int x){//Find()	
	access(x),splay(x);
	while(son[x][0]) push_down(x),x=son[x][0];
	//splay(x);
	return x;
}
/*
void link(int x,int y)
{
	make_root(x);
	if(find_root(y)==x) return;
	//splay(x);????
	fa[x]=y;
	return ;
}
*/
void link(int x,int y){
	make_root(x);
	fa[x]=y;
}
void spilt(int x,int y)
{
	make_root(x);
	access(y);
	splay(y);
}

void cut(int x,int y)
{
	spilt(x,y);
	if(son[y][get(x)^1]||fa[x]!=y||son[x][1]) return;
	// if(son[y][get(x)^1]||fa[x]!=y||son[x][1]) return;
	fa[x]=son[y][0]=0;
	push_up(y);
}

//A big problem ----- why the below is wrong
/*
void cut(int x,int y)
{
	make_root(x);
	//if(find_root(y)!=x||fa[y]!=x||son[y][0]) return;
	if(find_root(y)!=x||siz[x]>2) return;
	access(y),splay(y);
	fa[y]=son[x][1]=0;push_up(x);
}	
*/
signed main()
{
	n=read(),m=read();
	R(i,1,n) sum[i]=wei[i]=read();
	R(i,1,m)
	{		
		//printf("%d\n",find_root(1));
		int opt=read(),x=read(),y=read();
		if(!opt){
			spilt(x,y);
			printf("%d\n",sum[y]);
			continue;
		}
		if(opt==1){
			if(find_root(x)!=find_root(y)) link(x,y);
			continue;
		}
		if(opt==2){
			if(find_root(x)==find_root(y)) cut(x,y);
			continue;
		}
		if(opt==3){
			wei[x]=y;
			access(x);
			splay(x);
			push_up(x);
			continue;
		}
	}
}
//some can guo https://www.cnblogs.com/yzhang-rp-inf/p/10201857.html
//
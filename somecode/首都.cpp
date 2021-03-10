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
const int N=2e6+10;
int son[N][2],fa[N],siz[N],siz2[N],tag[N];
int FFa[N];
int n,q,res;
int find_FFa(int x){
	return FFa[x]==x?x:FFa[x]=find_FFa(FFa[x]);
}
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
	clear(0);if(x) siz[x]=siz[son[x][0]]+siz[son[x][1]]+1+siz2[x];
}
inline void push_flp(int x){
	Swap(son[x][0],son[x][1]),tag[x]^=1;
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
void rotate(int x){
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
		if(isnotroot(f)) rotate(get(f)==get(x)?f:x);
	push_up(x);
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
	make_root(x),splay(x);
	if(find_root(y)!=x) splay(y),fa[x]=y,siz2[y]+=siz[x];
}
inline void cut(int x,int y){
	spilt(x,y);
	if(son[y][0]&&!son[x][1]) {
		son[y][0]=fa[x]=0;
		push_up(y);
	}
}
/*
考虑直接连接两颗树对重心的影响
要用到一个性质——连接两颗树后，新的重心一定在原来的两个重心的路径上。
那就可以直接link然后把链提出来去找了。我们当然不能把整条链全找遍了，毕竟重心的性质那么多，也要好好利用嘛。

具体:
具体找法：类似树上二分，我们需要不断逼近树的重心的位置。
记下lsum表示当前链中搜索区间左端点以左的子树大小，rsum表示右端点以右的。
x的整个子树就表示了当前搜索区间，在中序遍历中x把搜索区间分成了左右两块（在Splay中对应x的左子树和右子树）。
如果x左子树的siz加上lsum和x右子树的siz加上rsum都不超过新树总大小的一半，那么x当然就是重心啦！
当然，如果总大小是奇数，重心只会有一个，那就找到了。否则，因为必须编号最小，所以还要继续找下去。
当我们没有确定答案时，还要继续找下去，那么就要跳儿子了。
x把整个链分成了左右两个部分，而重心显然会在大小更大的一部分中，这个也应该好证明。
如果x左子树的siz加上lsum小于x右子树的siz加上rsum，那就跳右儿子继续找。
这时候当前搜索区间减小了，搜索区间以外的部分增大了，lsum应该加上si[x]+1。反之亦然。
如果跳进了空儿子，那肯定所有情况都考虑完了，直接结束查找。
当然，重心找到了就还是要伸展一下，保证复杂度。当然，重心找到了就还是要伸展一下，保证复杂度。
*/

int find_Center_of_gravity(int x){
	int l,r;
	int opt=siz[x]&1,sum=siz[x]/2,lsum=0,rsum=0,the_Center_of_gravity=inf,nowl,nowr;
	while(x)
	{
		push_down(x);
		l=son[x][0],r=son[x][1],nowl=siz[l]+lsum,nowr=siz[r]+rsum;
		if(nowl<=sum&&nowr<=sum) {
			if(opt) {the_Center_of_gravity=x;break;}
			else if(the_Center_of_gravity>x) the_Center_of_gravity=x;
		}
		if(nowl<nowr) lsum+=siz[l]+siz2[x]+1,x=r;
		else rsum+=siz[r]+siz2[x]+1,x=l;
	}
	splay(the_Center_of_gravity);
	return the_Center_of_gravity;
}
char opt[111];
signed main()
{
	n=read(),q=read();
	R(i,1,n) siz[i]=1,FFa[i]=i,res^=i;
	R(i,1,q) {
		scanf("%s",opt+1);
		if(opt[1]=='A') 
		{
			int u=read(),v=read();
			int fu=find_FFa(u),fv=find_FFa(v);
			//printf("fu:%lld fv:%lld\n",fu,fv);
			link(u,v);
			spilt(fu,fv);
			int tmp=find_Center_of_gravity(fv);
			res^=fu^fv^tmp;
			FFa[fu]=FFa[fv]=FFa[tmp]=tmp;
		}
		if(opt[1]=='Q'){
			int u=read();
			printf("%lld\n",find_FFa(u));
		}
		if(opt[1]=='X') {
			printf("%lld\n",res);
		}
	}
}
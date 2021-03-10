//LCT维护边双:
//如果要求将边双缩成点，每次添加一条边，所连接的树上的两点如果互相连通那么这条路径上的所有点都会被缩成一个点

//「AHOI2005」航线规划:LCT+并查集(缩点)
//给出N个点,初始时有M条无向边,Q次操作,每次操作为以下之一：
//1:0 u v ：删除u,v之间的连边，保证此时存在这样的一条边。
//2:1 u v ：查询此时u,v两点之间可能的所有路径必须经过的边的数量。
//保证图在任意时刻都连通。
//可以发现,u,v两点之间的所有可能路径必须经过的边的数量为将所有边双连通分量缩成点之后u所在点和v所在点之间的路径上的结点数-1。
//由于题目中的删边操作不好进行，我们考虑离线逆向进行操作，改删边为加边。
//加入一条边时，如果两点原来不连通，则在 LCT 上连接两点；
//否则提取出加这条边之前 LCT 上这两点之间的路径，遍历辅助树上的这个子树，相当于遍历了这条路径，将这些点合并，利用并查集维护合并的信息。
//用合并后并查集的代表元素代替原来树上的路径。注意之后的每次操作都要找到操作点在并查集上的代表元素进行操作。
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
const int N=200020;
int bel[N];
int n,m,q;
map<pii,int>mp;//graph
struct ques
{
	int opt,u,v;
}qs[N];
int ans[N],tot_ans;
inline int find_ps(int x){
	return bel[x]?bel[x]=find_ps(bel[x]):x;
}
void mergr_bl(int x,int y){
	x=find_ps(x),y=find_ps(y);
	if(x!=y) bel[x]=y;
}
int son[N][2],fa[N],tag[N],siz[N];
inline void clear(int x){
	son[x][0]=son[x][1]=fa[x]=tag[x]=siz[x]=0;
}
inline int get(int x){
	return x==son[find_ps(fa[x])][1];
}
inline int isnotroot(int x){
	return son[find_ps(fa[x])][0]==x||son[find_ps(fa[x])][1]==x;
}
inline void push_up(int x){
	if(x) siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
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
inline void rotate(int x){
	x=find_ps(x);
	int f=find_ps(fa[x]),gf=find_ps(fa[f]),wh=get(x);
	if(isnotroot(f)) son[gf][get(f)]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	push_up(f);
	push_up(x);
	//push_up(gf);
}
void update(int x){
	if(isnotroot(x)) update(find_ps(fa[x]));
	push_down(x);
}
inline void splay(int x){
	update(x);
	for(int f;f=find_ps(fa[x]),isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(f)==get(x)?f:x);
	push_up(x);
}
inline int access(int x){
	int y;
	for(y=0;x;y=x,x=find_ps(fa[x]))
		splay(x),son[x][1]=y,push_up(x);
	return y;
}
inline void make_root(int x){
	x=find_ps(x),access(x),splay(x),push_flp(x);
}
inline int find_root(int x){
	x=find_ps(x),access(x),splay(x);
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
void dfs(int u){
	push_down(u);
	if(son[u][0]) dfs(son[u][0]),mergr_bl(son[u][0],u);
	if(son[u][1]) dfs(son[u][1]),mergr_bl(son[u][1],u);
}

signed main()
{
	n=read(),m=read();
	R(i,1,n) push_up(i);
	R(i,1,m) {
		int u=read(),v=read();
		mp[mkp(u,v)]=mp[mkp(v,u)]=1;
	}
	while(scanf("%d",&qs[++q].opt)==1)
	{
		if(qs[q].opt==-1) {
			--q;break;
		}
		qs[q].u=read(),qs[q].v=read();
		if(qs[q].opt==0) mp[mkp(qs[q].u,qs[q].v)]=mp[mkp(qs[q].v,qs[q].u)]=0;
	}
	reverse(qs+1,qs+q+1);
	map<pii,int>::iterator it;
	for(it=mp.begin();it!=mp.end();it++)
	{
		if(it->se){
			mp[mkp(it->fi.se,it->fi.fi)]=0;
			int x=find_ps(it->fi.fi),y=find_ps(it->fi.se);
			if(find_root(x)!=find_root(y)) link(x,y);
			else
			{
				if(x==y) continue;
				spilt(x,y);
				dfs(y);
				int tmp=find_ps(y);
				fa[tmp]=find_ps(fa[y]);
				son[tmp][0]=son[tmp][1]=0;
				push_up(tmp);
			} 
		}
		
	}
	R(i,1,q)
	{
		int x=find_ps(qs[i].u),y=find_ps(qs[i].v);
		spilt(x,y);
		if(qs[i].opt==0)
		{
			dfs(y);
			int tmp=find_ps(y);
			fa[tmp]=fa[y];
			son[tmp][0]=son[tmp][1]=0;
			push_up(tmp);
		}
		if(qs[i].opt==1)
			ans[++tot_ans]=siz[y]-1;
	}
	L(i,1,tot_ans) printf("%d\n",ans[i]);
}
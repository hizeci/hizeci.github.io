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
首先，找一个节点所在堆的堆顶要用并查集，而不能暴力向上跳。
再考虑单点查询，若用普通的方法打标记，就得查询点到根路径上的标记之和，最坏情况下可以达到O(n)的复杂度。
如果只有堆顶有标记，就可以只有路径压缩的并查集复杂度查询了

可以用类似启发式合并的方式,每次合并的时候把较小的那个堆标记暴力下传到每个节点，然后把较大的堆的标记作为合并后的堆的标记
由于合并后有另一个堆的标记，所以较小的堆下传标记时要下传标记时要下传其标记减去另一个堆的标记。
由于每个节点被合并一次所在堆的大小至少乘2，所以每个节点最多被push_down(log n)次
暴力下放总复杂度O(nlogn)

再考虑单点加，先删除，再更新，最后插入即可

然后是全局MAX,可以用左偏树/平衡树 来维护每个堆的堆顶

所以每个操作分别如下

1:暴力下传点数较小的堆的标记,合并两个堆,更新siz,tag,在multiset中删去合并后不在堆顶的那个原堆顶

2.删除节点,更新值,插入回来,更新multiset。需要分删除节点是否为根来讨论一下

3.堆顶打标记,更新multiset

4.打全局标记

5.查询值+堆顶标记+全局标记

6.查询根的值+堆顶标记+全局标记

7.查询multiset最大值+全局标记

*/
const int N=333333;
int SEKAI,n,m;
int ffa[N];

int fa[N],val[N],son[N][2],siz[N],tag[N];
int dist[N];

char opt[111];

multiset<int>s;

inline int find_ffa(int x){
	return ffa[x]==x?x:ffa[x]=find_ffa(ffa[x]);
}
inline int& rs(int x){
    return son[x][dist[son[x][1]]<dist[son[x][0]]];
}
void update(int x,int k) {
	if(!x) return;
	val[x]+=k;
	if(son[x][0]) update(son[x][0],k);
	if(son[x][1]) update(son[x][1],k);
}
void push_up(int x) {
	if(!x) return;
	if(dist[x]!=dist[rs(x)]+1) {
		dist[x]=dist[rs(x)]+1;
		if(fa[x]) push_up(fa[x]);
	}
}
inline int mer(int u,int v) {
	if(!u||!v) return u^v;
	if(val[u]<val[v]) Swap(u,v);
	fa[rs(u)=mer(rs(u),v)]=u;
	push_up(u);
	return u;
}
signed main()
{
	n=read();
	R(i,1,n) {
		ffa[i]=i,siz[i]=1,val[i]=read();
		s.insert(val[i]);
	}
	m=read();
	R(i,1,m) {
		int x,y;
		scanf("%s",opt+1);
		if(opt[1]=='U') {
			int u=read(),v=read();
			x=find_ffa(u),y=find_ffa(v);
			if(x!=y) {
				if(siz[x]>siz[y]) Swap(x,y);
				update(x,tag[x]-tag[y]);
				ffa[x]=ffa[y]=mer(x,y);
				if(ffa[x]==x) {
					s.erase(s.find(val[y]+tag[y]));
					tag[x]=tag[y];
					siz[x]+=siz[y];
					tag[y]=siz[y]=0;
				}
				else {
					s.erase(s.find(val[x]+tag[y]));
					siz[y]+=siz[x];
					siz[x]=tag[x]=0;
				}
			}
		}
		if(opt[1]=='A') {
			//A1 90 43
			if(opt[2]=='1') {
				x=read();
				int v=read();					
				//if(x==90&&v==43) printf("%lld %lld %lld %lld %lld\n",find_ffa(x),son[x][0],son[x][1],fa[son[x][0]],fa[son[x][1]]); //printf("ffa:%lld szS:%lld\n",x,(int)s.size());
				if(x==find_ffa(x)) {				
					fa[son[x][0]]=fa[son[x][1]]=0;
					y=mer(son[x][0],son[x][1]);
					s.erase(s.find(val[x]+tag[x]));
					val[x]+=v;
					fa[x]=son[x][0]=son[x][1]=0;
					dist[x]=1;
					ffa[x]=ffa[y]=mer(x,y);
					s.insert(val[ffa[x]]+tag[x]);
					if(ffa[x]==y) tag[y]=tag[x],siz[y]=siz[x],tag[x]=siz[x]=0;
				}
				else {
					fa[son[x][0]]=fa[son[x][1]]=fa[x];
					son[fa[x]][x==son[fa[x]][1]]=mer(son[x][0],son[x][1]);
					val[x]+=v;
					fa[x]=son[x][0]=son[x][1]=0;
					dist[x]=1;
					y=find_ffa(x);
					ffa[x]=ffa[y]=mer(x,y);
					if(ffa[x]==x) {
						s.erase(s.find(val[y]+tag[y]));
						s.insert(val[x]+tag[y]);
						tag[x]=tag[y],siz[x]=siz[y],siz[y]=tag[y]=0;
					}
				}
			}
			if(opt[2]=='2') {
				x=find_ffa(read());
				s.erase(s.find(val[x]+tag[x]));
				tag[x]+=read();
				s.insert(val[x]+tag[x]);
			}
			if(opt[2]=='3') {
				SEKAI+=read();
			}
		}
		if(opt[1]=='F') {
			if(opt[2]=='1') {
				x=read();
				printf("%d\n",val[x]+tag[find_ffa(x)]+SEKAI);
			}
			if(opt[2]=='2') {
				x=find_ffa(read());
				printf("%d\n",val[x]+tag[x]+SEKAI);
			}
			if(opt[2]=='3') {
				printf("%d\n",*s.rbegin()+SEKAI);
			}
		}
	}
} 
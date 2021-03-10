#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
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

#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
/*
printf("%lld ",dist(rand_num));
*/
/*
插入:
在堆里删除元素abs(head[id+1]-tail[id])
然后插入两个新元素abs(head[id+1]-new),abs(new-til[id]).然后在新的til[id]中再附上new
每次询问min_GAP就是询问堆中最小值

支持删除，插入，查询权值最小，显然可以用平衡树去搞。

对于第二种询问，
单独插入一个元素，我们需要在集合中查找它的前驱和后驱，便可以计算最小的差值，显然这个答案是单调的，直接记录即可

支持插入，查前驱，查后继，显然可以又用平衡树去搞。
*/

const int N=1111111;
int res_of_MIN_SORT_GAP=inf;
int n,m;
int a[N],b[N];

struct pai
{
	int a,b;
	pai(int a_=0,int b_=0) {a=a_,b=b_;}
};
inline int rand1() {
	return dist(rand_num);
}
struct fhqtreap
{
	int wei[N],siz[N],key[N],son[N][2];
	int tot_key,rt;
	inline void init(){
		memset(wei,0,sizeof(wei)),memset(siz,0,sizeof(siz));
		memset(key,0,sizeof(key)),memset(son,0,sizeof(son));
		tot_key=rt=0;
	}
	inline void push_up(int x){
		siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
	}
	int mer(int u,int v){
		if(!u||!v) return u^v;
		if(wei[u]<wei[v]) {
			son[u][1]=mer(son[u][1],v);
			push_up(u);
			return u;
		}
		else {
			son[v][0]=mer(u,son[v][0]);
			push_up(v);
			return v;
		}
	}
	pai spilt(int u,int k) {
		if(!u) return pai(0,0);
		if(key[u]<k) {
			pai t=spilt(son[u][1],k);
			son[u][1]=t.a;
			push_up(u);
			return pai(u,t.b);
		}
		else {
			pai t=spilt(son[u][0],k);
			son[u][0]=t.b;
			push_up(u);
			return pai(t.a,u);
		}
	}
	inline int find_MAX(int u){
		while(son[u][1]) u=son[u][1];return key[u];
	}
	inline int find_MIN(int u) {
		while(son[u][0]) u=son[u][0];return key[u];
	}
	inline void ins1(int k) {	
		key[++tot_key]=k,wei[tot_key]=rand1(),siz[tot_key]=1;
		son[tot_key][0]=son[tot_key][1]=0;
		pai t=spilt(rt,k);		
		rt=mer(mer(t.a,tot_key),t.b);
	}
	inline void ins2(int k) {
		key[++tot_key]=k,wei[tot_key]=rand1(),siz[tot_key]=1;
		son[tot_key][0]=son[tot_key][1]=0;
		pai t=spilt(rt,k);
		if(siz[t.a]) res_of_MIN_SORT_GAP=min(res_of_MIN_SORT_GAP,abs(k-find_MAX(t.a)));
		if(siz[t.b]) res_of_MIN_SORT_GAP=min(res_of_MIN_SORT_GAP,abs(find_MIN(t.b)-k));
		rt=mer(mer(t.a,tot_key),t.b);
	}
	void era(int k) {
		pai x,y;
		x=spilt(rt,k);
		y=spilt(x.b,k+1);
		y.a=mer(son[y.a][0],son[y.a][1]);
		rt=mer(x.a,mer(y.a,y.b));
	}
}Trp1,Trp2; 
char opt[111];

signed main()
{
	Trp1.init(),Trp2.init();
	n=read(),m=read();
	R(i,1,n) a[i]=b[i]=read();
	FR(i,1,n) Trp1.ins1(abs(a[i]-a[i+1]));
	R(i,1,n) Trp2.ins2(a[i]);
	R(i,1,m) {
		scanf("%s",opt+1);
		if(opt[1]=='I') {
			int id=read(),k=read();
			Trp2.ins2(k);
			if(id!=n) {
				Trp1.era(abs(a[id+1]-b[id]));
				Trp1.ins1(abs(a[id+1]-k));
			}
			Trp1.ins1(abs(b[id]-k));
			b[id]=k;
		}
		if(opt[5]=='G') {
			printf("%d\n",Trp1.find_MIN(Trp1.rt));
		}
		if(opt[5]=='S') {
			printf("%d\n",res_of_MIN_SORT_GAP);
		}
	} 
}
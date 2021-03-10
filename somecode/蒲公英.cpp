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
//const int mod=1e9+7;
const int mod=10007;
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
    if(f)x=-x;
	return x;
}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
/*
一个集合a的众数为mode(a)

定理1:考虑集合a,b,那么mode(a并b)包含于mode(a)并b

证明:这个几乎是显然的(原话).因为t既不是mode(a)也不属于b,那么它在a并b中的出现次数就是在a的出现次数就是在a的出现次数,而这不会比mode(a)出现地更多

考虑询问[l,r],如果区间[l,r]在某一个块内部，那么我们暴力得出答案，复杂度为(sqrt(n))
不然令l在第a块,r在第b块，那么[l,r]就由
1.l到a块的最后一个
2.从a+1块到b-1块
3.b块第一个到r
这3部分组成，注意到第二部分的答案我们已经处理出来了，那么根据定理1,[l,r]的众数要么是第二部分的众数，要么是第1部分或者第3部分中的数,
由于第1,3部分的大小最大是2sqrt(n),我们只需要枚举这些数
我们只需要对每种不同的数,对他们的位置进行二分查找，就能回答[l,r]中有几个x这样的问题
那么一次询问复杂度为O(sqrt(n)log_n)
考虑去掉log_n这个系数
不妨令f(i,x)表示[0,i]区间有几个x
[l,r]区间数量为f(r,x)-f(l-1,x)
不妨将n个数分成sqrt(n)块，每块大小预处理出C[i][x]表示第0块到第i块中,x出现了多少次，这个的时间需要nsqrt(n)
同时对于每个块b预处理A[b][i][x]出它的前i个中x出现了多少次，注意到这里x最多sqrt(n)那么每个预处理每个块需要\sqrt(n)^2=n的时间和空间
我们需要得到值x在第i个块内部的id，可以对每一个块开一个表来实现
*/
const int B=222;
const int N=155555;
int n,id;
int a[N],b[N];
int f[5555][5555];
map<int,int>mp;
int val[N],tot[N];
std::vector<int> v[N];
void init(int x){
	memset(tot,0,sizeof(tot));
	int mx=0,ans=0;
	R(i,(x-1)*B+1,n) {
		tot[a[i]]++;
		if(tot[a[i]]>mx||(tot[a[i]]==mx&&val[a[i]]<val[ans])) 
			ans=a[i],mx=tot[a[i]];
		f[x][b[i]]=ans;
	}
}
inline int check(int l,int r,int x){
	int t=upb(v[x].begin(),v[x].end(),r)-lob(v[x].begin(),v[x].end(),l);
	return t;
}
inline int query(int l,int r){
	int ans=0,mx=0;
	ans=max(ans,f[b[l]+1][b[r]-1]);
	mx=max(mx,check(l,r,ans));
	R(i,l,min(b[l]*B,r)) {
		int t=check(l,r,a[i]);
		if(t>mx||(t==mx&&val[a[i]]<val[ans])) ans=a[i],mx=t; 
	}
	if(b[l]!=b[r]){
		R(i,(b[r]-1)*B+1,r){
			int t=check(l,r,a[i]);
			if(t>mx||(t==mx&&val[a[i]]<val[ans])) ans=a[i],mx=t; 
		}
	}
	return ans;
}
int q,lst_ans;
signed main()
{
	n=read(),q=read();
	R(i,1,n){
		a[i]=read();
		if(!mp[a[i]]) {
			mp[a[i]]=++id;
			val[id]=a[i];
		}
		a[i]=mp[a[i]];
		v[a[i]].pb(i);
	}
	R(i,1,n) b[i]=(i-1)/B+1;
	R(i,1,b[n]) init(i);
	R(i,1,q) {
		int l=read(),r=read();
		l=(l+lst_ans-1)%n+1,r=(r+lst_ans-1)%n+1;
		if(l>r) Swap(l,r);
		lst_ans=val[query(l,r)];
		printf("%lld\n",lst_ans);
	}
}
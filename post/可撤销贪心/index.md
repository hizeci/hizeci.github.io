
一个挺有趣的东西

<!--more-->

贪心本身是没有反悔操作的，求的就是当前的最优解。但当前的最优解有可能是局部最优解，而不是全局最优解，这时候就可以使用反悔操作。

反悔操作指的是这一步的贪心不是全局最优解，我们就退回去一步(人工$_{???}$或自动判断),换一种贪心策略。按照判断方式的不同可以分为反悔自动机和反悔堆两种方法。



### 例题

一个种树问题

洛谷[P1792 国家集训队 种树](https://www.luogu.com.cn/problem/P1792)

给出一个环，这个环被划分为$n$个位置，在第$i$个位置种树可以获得$a_i$的收益，要求相邻的两个位置都不能种树，求种正好是$m$棵树的最大收益

$m\leq n\leq 2\times 10^6$





题解:

考虑直接贪心，从大到小能选就选

这显然是不对的。

考虑添加一个反悔机制：设当前最优的位置为$i$，在选了$i$后在候选方案添加一个$a_{l}+a_{r}-a_i$表示不选当前这个，而选相邻两个数。具体做法是将点$i$的权值从$a_i$替换为$a_l+a_r-a_i$,再将$l,r$两点位置打上标记表示不能选这两个位置。然后进行下一轮贪心。每次贪心找到最大的权值最大且可以选中的点。

用堆维护所有可选的位置，双向链表维护每个位置左右最近的未选位置，然后取每次取最大的加入答案，做$m$次即为最优解。

证明:咕咕咕

其实这就像就二分图匹配的增广路算法(

代码:

```c++
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
//#define int long long
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x, T y) { return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x, T y) { return x>y?x=y,true:false;}
using namespace std;
//const ll inf=0x7f7f7f7f7f7f7f3f;
const ll inf=(1ll<<60);
//const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=998244353;
const double eps=1e-6;
inline int fpow(int a,int b=mod-2,int p=mod){int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}
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
inline ll read()
{
    char c=getchar();ll x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int N=222222;
struct node{int val,pos;inline bool operator <(const node &A)const{return val<A.val;}};
int n,m,ans;
priority_queue<node>q;
int nxt[N],lst[N];
int a[N];
int vis[N];
inline void modify(int x){vis[x]=1;nxt[lst[x]]=nxt[x];lst[nxt[x]]=lst[x];nxt[x]=lst[x]=0;}
signed main()
{
	n=read(),m=read();
	if((n/2)<m) return puts("Error!")&0;
	R(i,1,n) a[i]=read();
	R(i,1,n-1) nxt[i]=i+1;nxt[n]=1;
	R(i,2,n) lst[i]=i-1;lst[1]=n;
	R(i,1,n) q.push((node){a[i],i});
	int l,r,pos,val;
	R(i,1,m) 
	{
		while(vis[q.top().pos]) q.pop();
		pos=q.top().pos,val=q.top().val;q.pop();
		ans+=val;
		l=lst[pos],r=nxt[pos];
		a[pos]=a[l]+a[r]-a[pos];
		modify(l),modify(r);	
		q.push((node){a[pos],pos});
	}
	writeln(ans);
}
```


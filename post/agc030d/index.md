
<!--more-->

令$dp[T][i][j]$表示在$T$次运算之后$a_i\ge a_j$的概率。我们可以从初始数组信息获得$dp[0][i][j]$的值。

然后考虑每次运算之后的转移，虽然这看上去每次是$O(N^2)$的，但由于每次只会更改两个位置，所以可以在$O(N)$时间复杂度内完成转移。

由于期望的线性性，因此最后数组期望逆序对个数为$\sum dp[Q][i][j](i<j)$再乘上$2^Q$

时间复杂度$O(N^2+NQ)$

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
#define int long long
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
template <typename T> bool ckmax(T &x, T y) { return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x, T y) { return x>y?x=y,true:false;}
using namespace std;
//const ll inf=0x7f7f7f7f7f7f7f3f;
//const ll inf=(1ll<<60);

const int inf=0x7f7f7f7f;
const int mod=1e9+7;
const double Pi=acos(-1);
//const int mod=998244353;
const double eps=1e-6;
inline int fpow(int a,int b=mod-2,int p=mod){a%=p;int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}
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
int a[3333];
double dp[3333][3333];
int n,q;

signed main()
{
	n=read(),q=read();
	R(i,1,n) a[i]=read();
	R(i,1,n) R(j,1,n) dp[i][j]=a[i]>a[j];
	int x,y;
	R(k,1,q) 
	{
		x=read(),y=read();
		if(x>y) swap(x,y);
		R(i,1,n) if(i^x&&i^y) 
		{
			dp[x][i]=dp[y][i]=(dp[x][i]+dp[y][i])/2.0;
			dp[i][x]=dp[i][y]=(dp[i][x]+dp[i][y])/2.0;
		}
		dp[x][x]=dp[y][y]=0;
		dp[x][y]=dp[y][x]=(dp[x][y]+dp[y][x])/2.0;
	}
	double ans=0;
	R(i,1,n) R(j,i+1,n) ans=(ans+dp[i][j]);
	printf("%.18lf\n",ans);
}
```


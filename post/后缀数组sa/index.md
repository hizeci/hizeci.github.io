
## 后缀数组(SA)

[oi-wiki](https://oi-wiki.org/string/sa/)

[自为风月马前卒](https://www.cnblogs.com/zwfymqz/)

[鏡音リン](https://www.luogu.com.cn/blog/nederland/solution-p3809)

[诱导排序与 SA-IS 算法](https://riteme.site/blog/2016-6-19/sais.html)

[[2009\]后缀数组——处理字符串的有力工具 by. 罗穗骞](https://wenku.baidu.com/view/5b886b1ea76e58fafab00374.html)

[Flying2018字符串算法学习笔记](https://www.cnblogs.com/Flying2018/p/13741568.html)

[Flying2018-SA-IS学习笔记](https://www.cnblogs.com/Flying2018/p/13848482.html)

[blackfrog](https://www.luogu.com.cn/blog/blackfrog/sa-algorithm)

[ctz's blog](https://ctz45562.github.io/2019/04/14/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/)

<!--more-->

倍增+$sort$,$O(n\log ^2n)$做法

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
const int N=1e6+10;
char s[N];
int n,lim;
int sa[N],rk[N<<1],ork[N<<1];

signed main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	R(i,1,n) sa[i]=i,rk[i]=s[i];
	for(lim=1;lim<n;lim<<=1)
	{
		sort(sa+1,sa+n+1,[&](int x,int y){return rk[x]==rk[y]?rk[x+lim]<rk[y+lim]:rk[x]<rk[y];});
		cpy(ork,rk,n<<1);
		//memcpy(ork,rk,sizeof(rk));
		int cnt=0;
		R(i,1,n)
		{
			if(ork[sa[i]]==ork[sa[i-1]]&&ork[sa[i]+lim]==ork[sa[i-1]+lim]) rk[sa[i]]=cnt;
			else rk[sa[i]]=++cnt;
		}
	}
	R(i,1,n) writesp(sa[i]);
}
```

倍增+基数排序$O(n\log n)$求法

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
const int N=1e6+10;
#define cmp(x,y,w) (ornk[x]==ornk[y]&&ornk[x+w]==ornk[y+w])
void get_SA(char *s,int *sa,int *rnk,int n)
{
	static int m,cnt[N],osa[N],ornk[N<<1],px[N];m=0;
	R(i,1,n) ++cnt[(int)s[i]],ckmax(m,(int)s[i]);
	R(i,2,m) cnt[i]+=cnt[i-1];
	L(i,1,n) sa[cnt[(int)s[i]]--]=i;
	m=0;R(i,1,n) rnk[sa[i]]=s[sa[i]]==s[sa[i-1]]?m:++m;
	for(int lim=1;m<n;lim<<=1)
	{
		clr(cnt,m+5),cpy(ornk+1,rnk+1,n+1);
		R(i,n-lim+1,n) osa[++cnt[0]]=i;
		//L(i,n-lim+1,n) osa[++cnt[0]]=i; 
		R(i,1,n) if(sa[i]>lim) osa[++cnt[0]]=sa[i]-lim;
		//R(i,1,n) ++cnt[rnk[i]];
		R(i,1,n) ++cnt[px[i]=rnk[osa[i]]];
		R(i,2,m) cnt[i]+=cnt[i-1];
		//L(i,1,n) sa[cnt[rnk[osa[i]]]--]=osa[i];
		L(i,1,n) sa[cnt[px[i]]--]=osa[i];
		m=0;R(i,1,n) rnk[sa[i]]=cmp(sa[i],sa[i-1],lim)?m:++m;
		if(m==n) {R(i,1,n)sa[rnk[i]]=i;break;}
	}
}
int n,sa[N],rnk[N];
char s[N];
signed main()
{	
	scanf("%s",s+1);
	n=strlen(s+1);
	get_SA(s,sa,rnk,n);
	R(i,1,n) writesp(sa[i]);
}
```

下面为两个$O(n)$做法

诱导排序与 SA-IS 算法:



DC3 :

不会



题目:



以下为加密部分

{{% hugo-encryptor "E3EIgy$qN#vy0hMM3#!S" %}}

{{% /hugo-encryptor %}}
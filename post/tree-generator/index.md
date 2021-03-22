
<!--more-->

题意:略

考虑一个点经过一个括号序列后到的点距离它的距离，其实就是将这个括号序列匹配的括号消掉，剩下来的括号的个数。

所以答案就是求出最大的子段，使得剩下的括号数量最多。

考虑线段树维护，主要难点是在合并两个区间上。

合并两个区间时，假设左边的右括号数为 $a$，左括号数为 $b$。右边的右括号数为 $c$，左括号数为 $d$。那么对答案的贡献是 $a+abs(b-c)+d$。即 $max(a+b-c+d,a-b+c+d)$。由于答案是求最大值，所以可以把 $\max$ 拆开来求。由上式可以看出，对于每一个点只需要维护 后缀左括号+后缀右括号,后缀左括号-后缀右括号,前缀右括号+前缀左括号,前缀右括号-前缀左括号的最大值即可。时间复杂度 $O(q\log n)$。

```c++
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
/*
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
*/
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
/*
a+b      a-b    c+d    -c+d
设四个值分别为x,y,z,k;
考虑如何维护x
对于区间i,记其左右儿子分别为Ls,Rs，如果这个最优划分点在右边，那么直接用Rs的x对答案取MAX。
如果最优划分点在左边，说明右边已经全部入选，那么将右边匹配完后剩下的左右括号分别记作l,r，我们现在所知的就是右边形如)))(((
我们要在左边的哪里选择划分能让x最大，考虑在选择的划分点之后有a的右括号和b的左括号，那么x可以表示为
x=a+abs(b-r)+l 展开 x=max(a+b-r+l,a-b+r+l)，同时，有x_ls=a+b,y_ls=a-b
因为是上传，所以ls和rs所有信息已知，
x_i=max(x_rs,x_ls-r_rs+l_rs,y_ls+l_rs+r_rs);
由维护过程可知，我们还要区间的l,r即这个区间全部进行匹配后，剩下的左括号和右括号
y,z,k同理

*/
const int N=2e5+10;
int n,q;
char s[N];
int cnt;
struct segmentree
{
	
	int sufral[N<<2],sufrcl[N<<2],preral[N<<2],prercl[N<<2],secl[N<<2],secr[N<<2],val[N<<2];
	/*
	#define x sufral 
	#define y sufrcl
	#define z prercl
	#define k preral
	#define l secl
	#define r secr
	*/
	
	void print()
	{
    	printf("\n-----------cnt:%lld\n", ++cnt);
		puts("-----------------------------12-----------------");
		puts("");
		R(i,1,10) printf("%lld %lld %lld %lld %lld %lld %lld\n",sufral[i],sufrcl[i],prercl[i],preral[i],secl[i],secr[i],val[i]); 
		puts("-----------------------------23------------------");
		puts("");
	}
	void push_up(int x)	
	{	
		/*
	#define x sufral 
	#define y sufrcl
	#define z prercl
	#define k preral
	#define l secl
	#define r secr
	*/
		//print();
		#define ls x<<1
		#define rs x<<1|1
		if(secl[ls]>secr[rs]) 
			secl[x]=secl[ls]-secr[rs]+secl[rs],secr[x]=secr[ls];
		else 
			secr[x]=secr[rs]-secl[ls]+secr[ls],secl[x]=secl[rs];
		sufral[x]=max(sufral[rs],max(sufral[ls]+secl[rs]-secr[rs],sufrcl[ls]+secr[rs]+secl[rs]));
		sufrcl[x]=max(sufrcl[rs],sufrcl[ls]+secr[rs]-secl[rs]);
		prercl[x]=max(prercl[ls],secl[ls]-secr[ls]+prercl[rs])	;
		preral[x]=max(preral[ls],max(secl[ls]+secr[ls]+prercl[rs],secr[ls]-secl[ls]+preral[rs]));
		val[x]=max(max(sufral[ls]+prercl[rs],sufrcl[ls]+preral[rs]),max(val[ls],val[rs]));
		//print();
	#undef ls
	#undef rs
	}
	void build(int l,int r,int x)
	{
		/*
		#define x sufral 
		#define y sufrcl
		#define z prercl
		#define k preral
		#define l secl
		#define r secr
		*/
		if(l==r)
		{
			int k=(s[l]=='(')?1:-1;
			sufral[x]=preral[x]=1;
			sufrcl[x]=max(-k,0ll);
			prercl[x]=max(k,0ll);
			secl[x]=(k==1),secr[x]=(k==-1);
			val[x]=1;
			//printf("l:%lld k:%lld\n",l,k);
			//print();
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		push_up(x);
	}
	void modify(int pos,int l,int r,int x,int k)
	{
		/*
		#define x sufral 
		#define y sufrcl
		#define z prercl
		#define k preral
		#define l secl
		#define r secr
		*/
		if(l==r)
		{
			//printf("X:%lld L:%lld K:%lld x:%lld y:%lld z:%lld k:%lld l:%lld r:%lld ans:%lld\n",x,l,k,sufral[x],sufrcl[x],prercl[x],preral[x],secl[x],secr[x],val[x]);
			sufral[x]=preral[x]=1;
			sufrcl[x]=max(-k,0ll);
			prercl[x]=max(k,0ll);
			secl[x]=(k==1),secr[x]=(k==-1);
			val[x]=1;
			//printf("X:%lld L:%lld K:%lld x:%lld y:%lld z:%lld k:%lld l:%lld r:%lld ans:%lld\n",x,l,k,sufral[x],sufrcl[x],prercl[x],preral[x],secl[x],secr[x],val[x]);
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid) modify(pos,l,mid,x<<1,k);
		else modify(pos,mid+1,r,x<<1|1,k);
		push_up(x);
	}	
	
}st;

signed main()
{
	//freopen("tmp1.out","w",stdout);
	n=read(),q=read();
	scanf("%s",s+1);
	n=strlen(s+1);
	st.build(1,n,1);
	//st.print();
	printf("%lld\n",st.val[1]);
	while(q--)
	{
		//st.print();
		int x=read(),y=read();
		st.modify(x,1,n,1,s[y]=='('?1:-1);
		st.modify(y,1,n,1,s[x]=='('?1:-1);
		swap(s[x],s[y]);
		printf("%lld\n",st.val[1]);
	}
}
```


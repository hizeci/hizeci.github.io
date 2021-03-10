
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=998244353;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
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
const int N=4e4+10;
int n;
int a[N],res;
int now=1;

signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(;now+1<n;)
	{
		int i;
		for(i=now;i+1<n;i++) if(a[i]<=a[i+2])
		{
			a[i+1]+=a[i];
			res+=a[i+1];
			for(int j=i;j>now;j--) a[j]=a[j-1];
			now++;
			int j=i+1;
			for(;a[j]>a[j-1]&&j>now;j--) Swap(a[j],a[j-1]);
			break;
		}
		if(i==n-1)
		{
			a[n-1]+=a[n];
			res+=a[--n];
		}
	}
	if(now==n-1) res+=a[n-1]+a[n];
	printf("%lld\n",res);
	return 0;
}

	//#pragma GCC optimize(2)
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
#define int long long
using namespace std;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int N=5e3+10;
const int inf=0x7f7f7f7f7f7f;
int n,m,k;
int a[N];
int dp[N];
int g[N];
deque<int>q;
void dqpop(int x)
{
	if(x==q.front()) q.pop_front();
}
void dqpush(int x)
{
	while(q.size()>0&&q.back()<x) q.pop_back();
	q.push_back(x);
}
signed main()
{	
	n=read(),m=read(),k=read();	if(n/m>k){puts("-1");return 0;}
	for(int i=1;i<=n;i++){ a[i]=read();dp[i]=g[i]=-inf;}
	for(int i=1;i<=k;i++)
	{
		q.clear();
		for(int j=0;j<=n;j++)
		{
			if(j>m){dqpop(g[j-m-1]);}
			if(j>=i){dp[j]=max(dp[j],q.front()+a[j]);}
			dqpush(g[j]);
		}
		for(int j=0;j<=n;j++)
		{
			g[j]=dp[j];
			dp[j]=-inf;
		}
	}
	int res=-inf;
	for(int i=n-m+1;i<=n;i++)
	{
		res=max(res,g[i]);
	}
	printf("%lld\n",res);
}
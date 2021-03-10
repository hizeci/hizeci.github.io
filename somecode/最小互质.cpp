#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb push_back
#define pii pair<int,int> 
#define mkp make_pair
#define us unsigned 
#define int long long
using namespace std;
const int inf=1e18;
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
const int N=110;
int a[N],vis[N];
int n,res; 
inline int gcd(int a,int b){
	return (b==0)?a:gcd(b,a%b);
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(vis[i]==0)
		{
			res++;
			for(int j=n;j>=1;j--) if(!vis[j]&&gcd(a[i],a[j])==1) 
			{
				vis[j]=1;
				a[i]*=a[j];
			}
		}
	}
	printf("%lld\n",res);
}

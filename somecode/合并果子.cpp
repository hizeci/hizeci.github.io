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
const int inf=1e18+100;
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
const int N=100010;
deque<int>a,b;
map<int,int>mp;
int n,res;
signed main()
{
	freopen("fruit.in","r",stdin);
	freopen("fruit.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) ++mp[read()];
	for(int i=1;i<N;i++) while(mp[i]--) a.pb(i);
		/*
	for(int i=1;i<=n;i++) {
		printf("%lld\n",a.front());
		a.pop_front();
	}
	*/
	for(int i=1;i<n;i++)
	{
		int x=0,y=0;
		if(a.size()>0&&b.size()>0)
		{
			if(a.front()>b.front()) 
				x=b.front(),b.pop_front();
			else x=a.front(),a.pop_front();
		}
		else if(a.size()>0) x=a.front(),a.pop_front();
		else if(b.size()>0) x=b.front(),b.pop_front();
		if(a.size()>0&&b.size()>0)
		{
			if(a.front()>b.front()) 
				y=b.front(),b.pop_front();
			else y=a.front(),a.pop_front();
		}
		else if(a.size()>0) y=a.front(),a.pop_front();
		else if(b.size()>0) y=b.front(),b.pop_front();
		res+=(x+y);
		b.pb(x+y);
	}
	printf("%lld\n",res);
}
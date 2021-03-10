#include<bits/stdc++.h>
using namespace std;
const int long long inf=0x3f3f3f3f3f;
inline long long read()
{
	long long x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
struct node
{
	int dis,w;
}a[500100];

deque<int>q;
long long sum,dp[500100],ans;
int l,r,n,d,k;
inline long long check(int l,int r)
{
	q.clear();
	//memset(dp,-inf,sizeof(dp));
	dp[0]=0;
	int j=0;
	for(int i=1;i<=n;i++)
	{
		while(a[i].dis-a[j].dis>=l&&j<i)
		{
			if(q.size()==0) q.push_back(j); 
			else
			{
				while(q.size()>0&&dp[q.back()]<=dp[j])
				{
					q.pop_back();
				}
				q.push_back(j);
			}
				
			j+=1;
		}
		while(q.size()>0&&a[i].dis-a[q.front()].dis>r)
		{
			q.pop_front();
		}
		if(q.size()>0) dp[i]=dp[q.front()]+a[i].w;
		else dp[i]=-inf;
	}
	long long maxx=-inf;
	for(int i=1;i<=n;i++)
	{
		maxx=max(maxx,dp[i]);
	}
	return maxx;
}

inline void binary()
{
	while(l!=r)
	{
				
		int mid=(l+r)/2+1;
		int ll=max(1,d-mid),rr=d+mid;
		if(check(ll,rr)<k)
		{
			l=mid;
		} 
		else
		{
			r=mid-1;
			ans=mid;
		} 
	}
}

int main()
{
	freopen("jump.in","r",stdin);
	freopen("jump.our","w",stdout);
	n=read();
	d=read();
	k=read();
	for(int i=1;i<=n;i++)
	{
		a[i].dis=read();
		a[i].w=read();
		if(a[i].w>0)
		{
			sum+=a[i].w;
			r=max(r,a[i].dis);
		}
	}
	if(sum<k)
	{
		puts("-1");
		return 0;	
	}
	binary();
	cout<<ans;
} 
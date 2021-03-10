#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x,y;	
}a[1000100];
int n,R[1000100],maxx,len;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
bool cmp(node x,node y)
{
	return x.x<y.x;
}
inline int check(int x)
{
	 int l=0,r=maxx,mid;
	 while(l!=r)
	 {
	 	mid=(l+r)/2+1;
		if(R[mid]<=x) l=mid;
		else r=mid-1;
	 }	
	 return l;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i].x=read();
		a[i].y=read();
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		len=check(a[i].y)+1;
		maxx=max(maxx,len); 
		if(R[len]==0) R[len]=a[i].y;
		else R[len]=min(R[len],a[i].y);
	}
	cout<<maxx;
} 
//IEE
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
const int N=1e5+10;
int n,a[N];

struct segmentree
{
	struct node
	{
		int sum,maxx;
	}tr[N<<2];
	inline void clr(){
		//for(int i=0;i<(N<<2);i++) tr[i].maxx=tr[i].sum=0;
		memset(tr,0,sizeof(tr));
	}
	inline void push_up(int x){
		tr[x].sum=tr[x<<1].sum+tr[x<<1|1].sum;
		tr[x].maxx=max(tr[x<<1].maxx,tr[x<<1|1].maxx);
	}	 
	void build(int l,int r,int x)
	{
		if(l==r){
			tr[x].sum=tr[x].maxx=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,x<<1);
		build(mid+1,r,x<<1|1);
		push_up(x);
	}
	void modify(int L,int R,int l,int r,int x)
	{
		if(l==r)
		{
			tr[x].maxx=tr[x].sum=sqrt(tr[x].sum);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid&&tr[x<<1].maxx>1) modify(L,R,l,mid,x<<1);
		if(mid<R&&tr[x<<1|1].maxx>1) modify(L,R,mid+1,r,x<<1|1);
		push_up(x); 
	}
	int query(int L,int R,int l,int r,int x)
	{
		if(L<=l&&r<=R) return tr[x].sum;
		int mid=(l+r)>>1,ret=0;
		if(L<=mid) ret+=query(L,R,l,mid,x<<1);
		if(mid<R)  ret+=query(L,R,mid+1,r,x<<1|1);
		return ret;
	}
}st;
signed main()
{
	freopen("sqrt.in","r",stdin);
	freopen("sqrt.out","w",stdout);
	int t=0;
	//for(int t=1;t<=_;t++)
	while(scanf("%lld",&n)==1)
	{
		for(int i=1;i<=n;i++) a[i]=read();
		st.clr();
		st.build(1,n,1);
		int m=read();		
		printf("Case #%lld:\n",++t);
		while(m--)
		{
			int opt=read(),x=read(),y=read();
			if(opt==0) st.modify(x,y,1,n,1);
			else printf("%lld\n",st.query(x,y,1,n,1));
		}
	}
}

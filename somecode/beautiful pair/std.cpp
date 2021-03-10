#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int n,num,tot;
int a[maxn],b[maxn],lg[maxn],root[maxn];
int st[maxn][20];
ll ans;
struct Seg
{
	#define lc(p) (seg[p].lc)
	#define rc(p) (seg[p].rc)
	#define sum(p) (seg[p].sum)
	int lc,rc,sum;
}seg[maxn*30];
void insert(int pre,int &p,int l,int r,int pos)
{
	p=++tot;
	seg[p]=seg[pre];sum(p)++;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)insert(lc(pre),lc(p),l,mid,pos);
	else insert(rc(pre),rc(p),mid+1,r,pos);
}
int query(int pre,int p,int l,int r,int ql,int qr)
{
	if(ql>r||qr<l)return 0;
	if(l>=ql&&r<=qr)return sum(p)-sum(pre);
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(lc(pre),lc(p),l,mid,ql,qr);
	if(qr>mid)res+=query(rc(pre),rc(p),mid+1,r,ql,qr);
	return res;
}
inline void ST()
{
	lg[0]=-1;
	for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++)st[i][0]=i;
	for(int j=1;j<=17;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=a[st[i][j-1]]>=a[st[i+(1<<(j-1))][j-1]]?st[i][j-1]:st[i+(1<<(j-1))][j-1];
}
inline int st_query(int l,int r)
{
	int t=lg[r-l+1];
	return a[st[l][t]]>=a[st[r-(1<<t)+1][t]]?st[l][t]:st[r-(1<<t)+1][t];
}
void solve(int ql,int qr)
{
	if(ql>qr)return;
	if(ql==qr){ans+=(b[a[ql]]==1);return;}
	int mid=st_query(ql,qr);
	if(mid-ql+1<=qr-mid)
		for(int i=ql;i<=mid;i++)
		{
			int k=upper_bound(b+1,b+num+1,b[a[mid]]/b[a[i]])-b-1;
			ans+=query(root[mid-1],root[qr],1,num,1,k);
		}
	else
		for(int i=mid;i<=qr;i++)
		{
			int k=upper_bound(b+1,b+num+1,b[a[mid]]/b[a[i]])-b-1;
			ans+=query(root[ql-1],root[mid],1,num,1,k);			
		}
	solve(ql,mid-1);solve(mid+1,qr);
}
int main()
{
	¡¢¡¢freopen("try.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);num=unique(b+1,b+n+1)-(b+1);
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+num+1,a[i])-b;
	for(int i=1;i<=n;i++)insert(root[i-1],root[i],1,num,a[i]);
	ST();
	solve(1,n);
	printf("%lld",ans);
	return 0;
}

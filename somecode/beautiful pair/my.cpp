#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<unordered_map>
using namespace std;

inline int read()
{
  int x=0,f=1;char ch=getchar();
  while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
  while (isdigit(ch)) {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
  return x*f;
}

const int maxn =  1e5+1e2;

int c[maxn];
int a[maxn];
int b[maxn];
int n,m;
int dp[maxn][23];
int p[maxn];
int tmp = 0;
unordered_map<int,int> mp;

struct Node{
    int id,val;
};

Node g[maxn];

int lowbit(int x)
{
    return (-x) & x;
}

void update(int x,int p)
{
    for (int i=x;i<=n;i+=lowbit(i)) c[i]+=p;
}

long long query(int x)
{
    long long ans=0;
    for (int i=x;i;i-=lowbit(i)) ans+=(long long)c[i];
    return ans;
}

int find(int x)
{
    if (x>p[n]) return tmp;
    return g[upper_bound(p+1,p+1+n,x)-p-1].id;
}

bool cmp(Node a,Node b)
{
    return a.val<b.val;
}

int countmax(int x,int y)
{
    int k = log2(y-x+1);
    return max(dp[x][k],dp[y-(1 <<k)+1][k]);
}

void init()
{
    for (int j=1;j<=21;j++)
      for (int i=1;i<=n;i++)
      {
      	 if (i+(1 << j)-1<=n)
      	 {
      	 	dp[i][j]=max(dp[i][j-1],dp[i+(1 << (j-1))][j-1]);
           }
      }	
}

long long solve(int l,int r)
{
    if (l>r) return 0;
    if (l==r)  {
      if (a[l]==1)return 1;
      else return 0;
    }
    long long cnt=0;
    int mid = (l+r) >> 1;
    int mx = countmax(l,r),pos=0;
    for (int i=l;i<=r;i++)
    {
        if (a[i]==mx) {
           if (!pos || abs(mid-i)<abs(mid-pos)) pos=i;
        }
    }
    cnt+=solve(l,pos-1);
    cnt+=solve(pos+1,r);
    for (int i=pos+1;i<=r;i++) update(b[i],1);
    for (int i=l;i<=pos;i++) cnt=cnt+(query(find(mx/a[i])));
    for (int i=pos+1;i<=r;i++) update(b[i],-1);
    //cout<<l<<" "<<r<<" "<<cnt<<endl;
    for (int i=l;i<=pos-1;i++) update(b[i],1);
     cnt=cnt+(query(find(mx/a[pos])));
    for (int i=l;i<=pos-1;i++) update(b[i],-1);	
    //out<<l<<" "<<r<<" "<<cnt<<endl;
    if (a[pos]==1) cnt++;
    return cnt;
}

int main()
{
	freopen("try.in","r",stdin);
  n=read();
  for (int i=1;i<=n;i++) a[i]=read(),g[i].id=i,g[i].val=a[i],dp[i][0]=a[i];
  init();
  sort(g+1,g+1+n,cmp);
  for (int i=1;i<=n;i++)
  {
  	 if (g[i].val!=g[i-1].val) tmp++;
  	 b[g[i].id]=tmp;
  	 mp[a[g[i].id]]=tmp;
  }
  //for (int i=1;i<=n;i++) cout<<b[i]<<" "; 
  memset(g,0,sizeof(g));
  for (int i=1;i<=n;i++) p[i]=a[i],g[i].val=a[i],g[i].id=b[i];
  sort(g+1,g+1+n,cmp);
  sort(p+1,p+1+n);
  //cout<<endl;
  long long ans=solve(1,n);
  cout<<ans;
  return 0;
}

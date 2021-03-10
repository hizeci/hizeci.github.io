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
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
int mod;
const ld eps=1e-8;
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
const int N=1e6+10;
int a[N],b[N];
int nxt[N];
int res;
int n,m,p,_;
signed main()
{
	_=read();
	for(int t=1;t<=_;t++)
	{
		res=0;
		n=read(),m=read(),p=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=m;i++) b[i]=read();
		memset(nxt,0,sizeof(nxt));
		//nxt[0]=0;
		for(int i=2,j=0;i<=m;i++)	
		{
			while(j&&b[i]!=b[j+1]) j=nxt[j];
			if(b[i]==b[j+1]) j++;
			nxt[i]=j;
		}
		for(int k=0;k<p;k++)
		{
			for(int i=k+1,j=0;i<=n;i+=p)
			{
				while(j&&a[i]!=b[j+1]) j=nxt[j];
				if(a[i]==b[j+1]) j++;
				if(j==m-1) res++,j=nxt[j];
			}
		}
		printf("Case #%lld: %lld\n",t,res);
	}
}
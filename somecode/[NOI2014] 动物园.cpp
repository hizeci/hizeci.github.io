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
const int mod=1e9+7;
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
/*
const int N=1.5e6+15;
int n;
char s[N];
int nxt[N],bz[21][N];
int _;
signed main()
{
	for(_=read();_;_--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		nxt[1]=0;
		for(int i=2;i<=n;i++) 
		{
			int j=nxt[i-1];
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) nxt[i]=j+1;
			else nxt[i]=0;
			bz[0][i]=nxt[i]; 
			//printf("%lld\n",nxt[i]);
		} 
		for(int j=1;j<20;j++)
			for(int i=1;i<=n;i++) bz[j][i]=bz[j-1][bz[j-1][i]];
		int res=1;
		for(int i=2;i<=n;i++)
		{
			int tt=i;
			for(int j=19;j>=0;j--) 
				if((bz[j][tt]<<1)>i) tt=bz[j][tt];
			int gg=0;
			for(int j=19;j>=0;j--)
				if(bz[j][tt]) gg+=(1<<j),tt=bz[j][tt];
			res=1ll*res*(gg+1)%mod;
		}
		printf("%lld\n",res	);
	}
}
*/
const int N=1.5e6+15;
char s[N];
int n;
int nxt[N],ans[N];
int _;

signed main()
{
	for(_=read();_;_--)
	{
		int res=1;
		scanf("%s",s+1);
		n=strlen(s+1);
		ans[1]=1;
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;
			nxt[i]=j;
			ans[i]=ans[j]+1;
		}
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;
			while((j<<1)>i) j=nxt[j];
			res=1ll*res*(ans[j]+1)%mod;
		}
		printf("%lld\n",res);
	}
}
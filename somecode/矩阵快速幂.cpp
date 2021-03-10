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
const int mod=1e9+7;
inline void add(int &x,int y)
{
	x+=y;
	x%=mod;
}
struct matrix
{
	int x,y,mat[4][4];
	matrix() {memset(mat,0,sizeof(mat));}
	matrix operator *(const matrix T)
	{
		matrix res;
		for(int i=0;i<3;i++)
		{
			for(int k=0;k<3;k++)
			{
				int r=mat[i][k];
				for(int j=0;j<3;j++)
				{
					add(res.mat[i][j],T.mat[k][j]*r%mod);
				}
			}
		}
		return res;
	}
};
int _,n;
void solve()
{
	matrix ans,base;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) base.mat[i][j]=ans.mat[i][j]=0;
	for(int i=0;i<3;i++) ans.mat[i][i]=1;
	base.mat[0][0]=base.mat[0][2]=base.mat[1][0]=base.mat[2][1]=1;
	while(n)
	{
		if(n&1) ans=ans*base;
		base=base*base;
		n>>=1;
	}
	printf("%lld\n",ans.mat[0][1]);
}
signed main()
{
	for(_=read();_;_--)
	{
		n=read();
		if(n<=3) 
		{
			puts("1");
			continue;
		}
		n++;
		solve();
	}
}

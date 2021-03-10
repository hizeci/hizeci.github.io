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
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=998244353;
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
const int N=1e4+10;
int _;
int n,W;
struct node
{
	int v,w;
	ld tmp;
	inline bool operator <(const node a)const{
		return tmp>a.tmp;
	}
}a[N];
signed main()
{
	for(_=read();_;_--)
	{
		W=read(),n=read();
		for(int i=1;i<=n;i++)
		{
			int v=read(),w=read();
			ld tmp=(ld)1.0*w/v;
			a[i].v=v,a[i].w=w,a[i].tmp=tmp;
		}
		ld res=0.0;
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
		{
			if(W>=a[i].v) 
			{
				W-=a[i].v;
				res+=a[i].w;
			}
			else
			{
				res+=W*(a[i].tmp);
				break;
			}
		}
		printf("%.2Lf\n",res);
	}
}
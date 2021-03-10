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
const int mod=19930726;
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
const int N=1e5+10;
int a[N],b[N],c[N];
int n;
int res;
int posi,posk;
inline int fpow(int a,int b){
	int res=1;while(b){if(b&1)res=res*a;a=a*a;b>>=1;}return res;
}
signed main()
{
	n=read();
	R(i,1,n) a[i]=read();
	R(i,1,n) b[i]=read();
	R(i,1,n) c[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+n+1),sort(c+1,c+n+1);
	R(i,1,n)
	{
		for(;a[posi+1]<b[i]&&posi+1<=n;) posi++;
		for(;c[posk+1]<=b[i]&&posk+1<=n;) posk++;
		res+=posi*(n-posk);
	}
	printf("%lld\n",res);
}
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
const int mod=998244353;
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
double A,B,C,D;
inline double f(double x){
	return A*x*x*x+B*x*x+C*x+D;
}
inline double ff(double x){
	return 3.0*A*x*x+2.0*B*x+C;
}
double newton(double x)
{
	double a=f(x);
	while(a>eps||a<-eps)
	{
		x-=a/ff(x);
		a=f(x);
	}
	return x;
}

signed main()
{
	scanf("%lf%lf%lf%lf",&A,&B,&C,&D);
	double delta_X=4.0*B*B-12.0*A*C;
	double x1=(-delta_X-2*B)/(6*A),x2=(delta_X-2*B)/(6*A);
	printf("%.2f %.2f %.2f\n",newton(x1-eps),newton((x1+x2)/2.0),newton(x2+eps));
}
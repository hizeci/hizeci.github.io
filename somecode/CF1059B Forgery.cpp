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
const int mod=9223372036854775807;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
	F[0]=Finv[0]=inv[1]=1;
	R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
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
const int N=1010;
char a[N][N],s[N][N];
int dx[10]={0,1,-1,0,0,1,-1,1,-1};
int dy[10]={0,0,0,1,-1,1,-1,-1,1};
int n,m;
inline int check(int i,int j){
	R(k,1,8) 
	{
		int xx=dx[k]+i,yy=dy[k]+j;
		if(a[xx][yy]=='.') return 0;
	}
	return 1;
}
signed main()
{
	n=read(),m=read();
	R(i,1,n) scanf("%s",a[i]+1);
	FR(i,2,n) FR(j,2,m) 
	{
		if(check(i,j)) {
			R(k,1,8) 
			{
				int xx=dx[k]+i,yy=dy[k]+j;
				s[xx][yy]='#';
			}
		}
	}
	R(i,1,n) R(j,1,m) if(s[i][j]!=a[i][j]&&a[i][j]=='#') {puts("NO");return 0;}
	puts("YES");

}
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
const int N=5e4+10;
int pri[N],unpri[N],mu[N];
int sumu[N];
void init_mu()
{
	int tot=0;mu[1]=1;
	for(int i=2;i<=(int)5e4;i++)
	{
		if(!unpri[i]) pri[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&pri[j]*i<=(int)5e4;j++) 
		{
			unpri[pri[j]*i]=1;
			if(i%pri[j]==0) {
				mu[i*pri[j]]=0;
				break;
			}			
			mu[pri[j]*i]=-mu[i];
		}
	}
	for(int i=1;i<=(int)5e4;i++) sumu[i]=sumu[i-1]+mu[i];
}
int solve(int n,int m)
{
	int res=0;
	for(int L=1,R,E=min(n,m);L<=E;L=R+1)
		R=min(n/(n/L),m/(m/L)),
		res+=(sumu[R]-sumu[L-1])*(n/L)*(m/L);
	return res;
}
int _,a,b,c,d,k;
signed main()
{
	init_mu();
	for(_=read();_;_--)
	{
		a=read(),b=read(),c=read(),d=read(),k=read();
		printf("%lld\n",solve(b/k,d/k)-solve(b/k,(c-1)/k)-solve((a-1)/k,d/k)+solve((a-1)/k,(c-1)/k));
	}
}
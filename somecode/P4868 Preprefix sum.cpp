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
const int N=100100;
int a[N],sum[N];
int n,m;
struct segmentree
{
	int val[N<<2],lazy1[N<<2];
	void push_down(int len,int x)
	{
		if(!lazy1[x]) return;
		lazy1[x<<1]+=lazy1[x];
		lazy1[x<<1|1]+=lazy1[x];
		val[x<<1]+=lazy1[x]*(len-(len>>1));
		val[x<<1|1]+=lazy1[x]*(len>>1);
		lazy1[x]=0;
	}
	void push_up(int x){
		val[x]=val[x<<1]+val[x<<1|1];
	}
	void modify_add(int L,int R,int l,int r,int x,int k)
	{
		if(L<=l&&r<=R) {
			lazy1[x]+=k;
			val[x]+=k*(r-l+1);
			return;
		}
		push_down(r-l+1,x);
		int mid=(l+r)>>1;
		if(L<=mid) modify_add(L,R,l,mid,x<<1,k);
		if(mid<R)  modify_add(L,R,mid+1,r,x<<1|1,k);
		push_up(x);
	}
	int query_sum(int L,int R,int l,int r,int x)
	{
		if(L<=l&&r<=R) return val[x];
		push_down(r-l+1,x);
		int mid=(l+r)>>1,ret=0;
		if(L<=mid) ret+=query_sum(L,R,l,mid,x<<1);
		if(mid<R ) ret+=query_sum(L,R,mid+1,r,x<<1|1);
		return ret; 
	}
}st;
signed main()
{
	n=read(),m=read();
	R(i,1,n) a[i]=read(),sum[i]=a[i]+sum[i-1];
	R(i,1,n) sum[i]+=sum[i-1];
	while(m--)
	{
		char opt[20];
		scanf("%s",opt);
		if(opt[0]=='Q') 
		{
			int x=read();
			printf("%lld\n",1ll*sum[x]+st.query_sum(1,x,1,n,1));
		}
		else
		{
			int x=read(),y=read();
			st.modify_add(x,n,1,n,1,y-a[x]);
			a[x]=y;
		}
	}

}
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
/*
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
*/
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
const int N=2e5+10;
int n,m,q;
int tot_seg;
int a[N],b[N],T[N];
int val[N<<5],L[N<<5],R[N<<5];
int build(int l,int r)
{
	int rt=++tot_seg;
	val[tot_seg]=0;
	if(l<r) 
	{
		int mid=(l+r)>>1;
		L[rt]=build(l,mid);
		R[rt]=build(mid+1,r);
	}
	return rt;
}
int modify(int pos,int l,int r,int x)
{
	int rt=++tot_seg;
	L[rt]=L[pos],R[rt]=R[pos],val[rt]=val[pos]+1;
	if(l<r) 
	{
		int mid=(l+r)>>1;
		if(x<=mid) L[rt]=modify(L[pos],l,mid,x);
		else R[rt]=modify(R[pos],mid+1,r,x);
	}
	return rt;
}
int query(int u,int v,int l,int r,int k)
{
	if(l>=r) return l;
	int x=val[L[v]]-val[L[u]];
	int mid=(l+r)>>1;
	if(x>=k) return query(L[u],L[v],l,mid,k);
	else return query(R[u],R[v],mid+1,r,k-x);
}
signed main()
{
	n=read(),q=read();
	R(i,1,n) a[i]=b[i]=read();
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	T[0]=build(1,m);
	R(i,1,n)
	{
		int t=lower_bound(b+1,b+m+1,a[i])-b;
		T[i]=modify(T[i-1],1,m,t);
	}
	while(q--)
	{
		int l=read(),r=read(),k=read();
		int t=query(T[l-1],T[r],1,m,k);
		printf("%lld\n",b[t]);
	}
}
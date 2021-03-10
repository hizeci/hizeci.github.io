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
const int N=1e5+10;
std::vector<int>e[N];
int Ls[N<<6],Rs[N<<6],Rt[N],tot_seg;
int val[N<<6],res[N<<6];
int c[N];
int n;
void push_up(int x)
{
	if(val[Ls[x]]==val[Rs[x]]) {
		val[x]=val[Ls[x]];
		res[x]=res[Ls[x]]+res[Rs[x]];
		return;
	}
	if(val[Ls[x]]>val[Rs[x]]){
		val[x]=val[Ls[x]];
		res[x]=res[Ls[x]];
		return;
	}
	else {
		val[x]=val[Rs[x]];
		res[x]=res[Rs[x]];
		return;
	}
}
void modify(int pos,int l,int r,int &x,int k)
{
	if(!x) x=++tot_seg;
	if(l==r){
		val[x]+=k;
		res[x]=l;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) modify(pos,l,mid,Ls[x],k);
	else modify(pos,mid+1,r,Rs[x],k);
	push_up(x);
}
int Mer(int l,int r,int a,int b)
{
	if(!a||!b) return a+b;
	if(l==r)
	{
		val[a]+=val[b];
		res[a]=l;
		return a;
	}
	int mid=(l+r)>>1;
	Ls[a]=Mer(l,mid,Ls[a],Ls[b]);
	Rs[a]=Mer(mid+1,r,Rs[a],Rs[b]);
    push_up(a);
	return a;
}
void dfs(int u,int f)
{
	for(int v:e[u])
	{
		if(v==f) continue;
		dfs(v,u);
		Rt[u]=Mer(1,1000000,Rt[u],Rt[v]);
	}
	modify(c[u],1,1000000,Rt[u],1);
	res[u]=res[Rt[u]];
}
signed main()
{
	n=read();
	R(i,1,n) c[i]=read();
	FR(i,1,n){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	R(i,1,n) printf("%lld\n",res[i]);
}
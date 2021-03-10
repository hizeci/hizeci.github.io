#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=1e9+7;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
/*
const int qwq=2000010;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}

inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return 1ll*F[n]%mod*1ll*Finv[m]*1ll%mod*1ll*Finv[n-m]%mod;}
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

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
/*
printf("%lld ",dist(rand_num));
*/
const int N=1111111;
struct pai
{
	int a,b;
	pai(int a_=0,int b_=0) {a=a_,b=b_;}
};
int key[N],wei[N],siz[N],son[N][2];
int n,tot_nd,res,rt;
inline int rand1() {return dist(rand_num);}
inline void maintain(int x) {siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;}
pai spilt_(int u,int k)
{
	if(!u) return pai(0,0);
	if(key[u]<=k)//qwq
	{
		pai t=spilt_(son[u][1],k);//qwq
		son[u][1]=t.a;
		maintain(u);
		return pai(u,t.b);
	}
	else
	{
		pai t=spilt_(son[u][0],k);
		son[u][0]=t.b;
		maintain(u);
		return pai(t.a,u);
	}
}
pai spilt(int u,int k)
{
	if(!u) return pai(0,0);
	if(siz[son[u][0]]+1<=k)//qwq
	{
		pai t=spilt(son[u][1],k-siz[son[u][0]]-1);//qwq
		son[u][1]=t.a;
		maintain(u);
		return pai(u,t.b);
	}
	else
	{
		pai t=spilt(son[u][0],k);
		son[u][0]=t.b;
		maintain(u);
		return pai(t.a,u);
	}
}
int Mer(int u,int v)
{
	if(!u||!v) return u^v;
	if(wei[u]<wei[v]) 
	{
		son[u][1]=Mer(son[u][1],v);
		maintain(u);
		return u;
	}
	else 
	{
		son[v][0]=Mer(u,son[v][0]);
		maintain(v);
		return v;
	}
}
void ins(int k)
{
	key[++tot_nd]=k,wei[tot_nd]=rand1(),siz[tot_nd]=1;
	pai t=spilt_(rt,k);
	rt=Mer(Mer(t.a,tot_nd),t.b);
}
/*
void del(int k)
{
	pai x,y;
	x=spilt(rt,k);
	y=spilt(x.b,k+1);
	y.a=Mer(son[y.a][0],son[y.a][1]);
	rt=Mer(x.a,Mer(y.a,y.b));
}
int find_rk(int k)
{
	pai t=spilt(rt,k);
	int tmp=siz[t.a]+1;
	rt=Mer(t.a,t.b);
	return tmp;
}
int find_kth(int k)
{
	int cnr=rt;
	while(cnr)
	{
		if(k==siz[son[cnr][0]]+1) return key[cnr];
		if(k<=siz[son[cnr][0]]) cnr=son[cnr][0];
		else k-=siz[son[cnr][0]]+1,cnr=son[cnr][1];
	}
}
*/
/*
int find_kth(int cnr,int k)
{
	if(k==siz[son[cnr][0]]+1) return key[u];
	if(k<=siz[son[cnr][0]]) return find_kth(son[cnr][0],k);
	else return find_kth(son[cnr][1],k-siz[son[cnr][0]]-1);
}
*/
/*
inline int find_lst(int k){
	return find_kth(find_rk(k));
}
inline int find_nxt(int k){
	return find_kth(find_rk(k+1));
}
*/
inline int pre(int k){
	pai x,y;
	x=spilt_(rt,k);
	y=spilt(x.a,siz[x.a]-1);
	int ret=key[y.b];
	rt=Mer(Mer(y.a,y.b),x.b);
	return ret;
}
inline int suf(int k)
{
	pai x,y;
	x=spilt_(rt,k-1);
	y=spilt(x.b,1);
	int ret=key[y.a];
	rt=Mer(x.a,Mer(y.a,y.b));
	return ret;
}
signed main()
{
	n=read();
	int x=read();
	res+=x;
	//ins(-inf),ins(inf);
	ins(x);
	int ok=0;
	R(i,2,n) 
	{		
		int x=read();
		int _pre=pre(x),_suf=suf(x);
		if(!_pre&&(!ok||x<0)) _pre=inf;
		if(!_suf&&(!ok||x<0)) _suf=inf;
		if(!x) ok=1;
		res+=min(abs(_pre-x),abs(_suf-x));
        ins(x);
	}
	printf("%lld\n",res);
}
//delete numbers			
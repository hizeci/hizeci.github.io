//fhq treap
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
//const int inf=0x7f7f7f7f7f7f;
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
int rand1(){
	return dist(rand_num);
}
struct pai
{
	int a,b;
	pai(int a_=0,int b_=0) {a=a_,b=b_;}
};
int key[N],siz[N],son[N][2],wei[N];
int tot_key,rt;
inline void maintain(int x){
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;
}

pai spilt(int u,int k)
{
	if(!u) return pai(0,0);
	if(key[u]<k)
	{
		pai t=spilt(son[u][1],k);
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

int mer(int u,int v)
{
	if(!u||!v) return u^v;
	if(wei[u]<wei[v])
	{
		son[u][1]=mer(son[u][1],v); 
		maintain(u);
		return u;
	}
	else
	{
		son[v][0]=mer(u,son[v][0]);
		maintain(v);
		return v;
	}
}

void ins(int k)
{
	key[++tot_key]=k,wei[tot_key]=rand1(),siz[tot_key]=1;
	pai t=spilt(rt,k);
	rt=mer(mer(t.a,tot_key),t.b);
}

void del(int k)
{
	pai x,y;
	x=spilt(rt,k);
	y=spilt(x.b,k+1);
	y.a=mer(son[y.a][0],son[y.a][1]);
	rt=mer(x.a,mer(y.a,y.b));
}

int find_rk(int k)
{
	pai t=spilt(rt,k);	
	int tmp=siz[t.a]+1;
	rt=mer(t.a,t.b);
	return tmp;	
}

int find_kth(int k)
{
	int pos=rt;
	while(pos)
	{
		if(k==siz[son[pos][0]]+1) return key[pos];
		if(k<=siz[son[pos][0]]) pos=son[pos][0];
		else k-=siz[son[pos][0]]+1,pos=son[pos][1];
	}
}

inline int find_lst(int k){
	return find_kth(find_rk(k)-1);
}

inline int find_nxt(int k){
	return find_kth(find_rk(k+1));
}
signed main()
{
	int n=read();
	R(i,1,n)
	{
		int opt=read(),x=read();
		if(opt==1) ins(x);
		if(opt==2) del(x);
		if(opt==3) printf("%lld\n",find_rk(x));
		if(opt==4) printf("%lld\n",find_kth(x));
		if(opt==5) printf("%lld\n",find_lst(x));
		if(opt==6) printf("%lld\n",find_nxt(x));
	}
}
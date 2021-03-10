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
/*
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
*/
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
const int N=2e5+10;
int n,res;
struct scanline
{
	int l,r,h;
	inline bool operator <(const scanline a)const{
		return h<a.h;
	}
}In[N],Dl[N];
struct segmentree
{
	#define ls val[x].l
	#define rs val[x].r
	struct node
	{
		int l,r,len,tag;
	}val[N<<6];
	int tot_seg;
	inline void push_up(int l,int r,int x){
		if(val[x].tag) val[x].len=r-l+1;// 如果这个点上有标记， 那么就说明被线段覆盖了， 长度就是 r-l+1
		else val[x].len=val[ls].len+val[rs].len;
	}
	//动态开点让树上很多线段不存在，所以不需要离散化
	void modify(int L,int R,int l,int r,int &x,int k){
		if(!x) x=++tot_seg;
		if(L<=l&&r<=R){
			val[x].tag+=k;
			push_up(l,r,x);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid) modify(L,R,l,mid,ls,k);
		if(mid<R) modify(L,R,mid+1,r,rs,k);
		push_up(l,r,x);
	}
	#undef ls
	#undef rs
}st;
signed main()
{
	n=read();
	int mi=(int)1e9,mx=0;
	R(i,1,n)
	{
		int _x_=read(),_y_=read(),__x__=read(),__y__=read();
		In[i]=(scanline){_y_,__y__,_x_};
		Dl[i]=(scanline){_y_,__y__,__x__};
		mi=min(mi,_y_),mx=max(mx,__y__);
	}
	int rt=0;
	sort(In+1,In+n+1),sort(Dl+1,Dl+n+1);
	In[n+1]=(scanline){0,0,(int)1e9+7},Dl[n+1]=(scanline){0,0,(int)1e9+7};
	int a=1,b=1,lst=0;
	R(i,1,n<<1)
	{
		int x=min(In[a].h,Dl[b].h);
		res+=(x-lst)*st.val[1].len;
		lst=x;
		if(In[a].h==x)st.modify(In[a].l,In[a].r-1,mi,mx,rt,1),++a;
		else st.modify(Dl[b].l,Dl[b].r-1,mi,mx,rt,-1),++b;
	}
	printf("%lld\n",res);
}
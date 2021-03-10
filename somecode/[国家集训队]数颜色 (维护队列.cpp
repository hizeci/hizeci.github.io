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
//#define int long long
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
//const int mod=9223372036854775807;
const ld eps=1e-8;
//inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
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
const int N=2335033;
int n,m,tot_B,B;
int bel[N];
int cnt[N],a[N],ans[N];
int tot_q,tot_m;

struct ques
{
	int l,r,ti,id;
	inline bool operator <(const ques a)const{
		return (bel[l]^bel[a.l])?bel[l]<bel[a.l]:((bel[r]^bel[a.r])?bel[r]<bel[a.r]:ti<a.ti);
	}
}qs[N];
struct mify
{
	int pos,col;
}mf[N];

signed main()
{
	n=read(),m=read();
	B=pow(n,2.0/3.0);
	tot_B=ceil((double)n/(1.0*B));
	R(i,1,tot_B) R(j,(i-1)*B+1,i*B) bel[j]=i;
	R(i,1,n) a[i]=read();
	while(m--)
	{
		char opt[100];
		scanf("%s",opt);
		if(opt[0]=='Q')
			qs[++tot_q].l=read(),qs[tot_q].r=read(),qs[tot_q].ti=tot_m,qs[tot_q].id=tot_q;
		else mf[++tot_m].pos=read(),mf[tot_m].col=read();
	}
	sort(qs+1,qs+tot_q+1);
	int L=1,R=0,tim=0,res=0;
	for(int i=1;i<=tot_q;i++)
	{
		int ql=qs[i].l,qr=qs[i].r,qt=qs[i].ti;
		while(L<ql) res-=!--cnt[a[L++]];
		while(L>ql) res+=!cnt[a[--L]]++;
		while(R<qr) res+=!cnt[a[++R]]++;
		while(R>qr) res-=!--cnt[a[R--]];
		while(tim<qt) {
			++tim;
			if(ql<=mf[tim].pos&&mf[tim].pos<=qr) 
				res-=!--cnt[a[mf[tim].pos]]-!cnt[mf[tim].col]++;
			Swap(a[mf[tim].pos],mf[tim].col);
		}
		while(tim>qt)
		{
			if(ql<=mf[tim].pos&&mf[tim].pos<=qr)
				res-=!--cnt[a[mf[tim].pos]]-!cnt[mf[tim].col]++;
			Swap(a[mf[tim].pos],mf[tim].col); 
			--tim;
		}
		ans[qs[i].id]=res;
	}
	R(i,1,tot_q) printf("%d\n",ans[i]);
}
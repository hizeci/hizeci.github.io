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
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/

const int N=1111111;  //wei[]节点权值 cnt_wei权值出现次数,siz[]子树大小
int rt,tot_nd,fa[N],son[N][2],wei[N],cnt[N],siz[N];
inline void maintain(int x) {siz[x]=siz[son[x][0]]+siz[son[x][1]]+cnt[x];}
inline int get(int x) {return x==son[fa[x]][1];} 
inline void clear(int x) {son[x][0]=son[x][1]=fa[x]=wei[x]=siz[x]=cnt[x]=0;}

void rotate(int x)
{
	int f=fa[x],gf=fa[f],wh=get(x);
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	if(gf) son[gf][son[gf][1]==f]=x;
	maintain(f);
	maintain(x);
}
void splay(int x)
{
	for(int f=fa[x];f=fa[x],f;rotate(x)) 
		if(fa[f]) rotate(get(x)==get(f)?f:x);
	rt=x;
}
void ins(int k)
{
	if(!rt)
	{
		wei[++tot_nd]=k;
		cnt[tot_nd]++;
		rt=tot_nd;
		maintain(rt);
		return;
	}
	int cnr=rt,f=0;
	while(1)
	{
		if(wei[cnr]==k)
		{
			cnt[cnr]++;
			maintain(cnr);
			maintain(f);
			splay(cnr);
			return;
		}
		f=cnr;
		cnr=son[cnr][wei[cnr]<k];
		if(!cnr)
		{
			wei[++tot_nd]=k;
			cnt[tot_nd]++;
			fa[tot_nd]=f;
			son[f][wei[f]<k]=tot_nd;
			maintain(tot_nd);
			maintain(f);
			splay(tot_nd);
			return;
		}
	}
}
int find_rk(int k)
{
	int res=0,cnr=rt;
	while(cnr)
	{
		if(k<wei[cnr]) cnr=son[cnr][0];
		else
		{
			res+=siz[son[cnr][0]];
			if(k==wei[cnr]) {
				splay(cnr);
				return res+1;
			}
			res+=cnt[cnr];
			cnr=son[cnr][1];
		}
	}
	return res+1;
}
int find_kth(int k)
{
	int cnr=rt;
	while(1)
	{
		if(son[cnr][0]&&k<=siz[son[cnr][0]]) cnr=son[cnr][0];
		else 
		{
			k-=siz[son[cnr][0]]+cnt[cnr];
			if(k<=0) {
				splay(cnr);
				return wei[cnr];
			}
			cnr=son[cnr][1];
		}
	}
}
int find_lst()
{
	int cnr=son[rt][0];
	while(son[cnr][1]) cnr=son[cnr][1];
	splay(cnr);
	return cnr;
}
int find_nxt()
{
	int cnr=son[rt][1];
	while(son[cnr][0]) cnr=son[cnr][0];
	splay(cnr);
	return cnr;
}
void del(int k)
{
	find_rk(k);
	if(cnt[rt]>1)
	{
		cnt[rt]--;
		maintain(rt);
		return;
	}
	if(!son[rt][0]&&!son[rt][1])
	{
		clear(rt);
		rt=0;
		return;
	}
	if(!son[rt][0])
	{
		int cnr=rt;
		rt=son[rt][1];
		fa[rt]=0;
		clear(cnr);
		return;
	}
	if(!son[rt][1])
	{
		int cnr=rt;
		rt=son[rt][0];
		fa[rt]=0;
		clear(cnr);
		return;
	}
	int cnr=rt,x=find_lst();
	fa[son[cnr][1]]=x;
	son[x][1]=son[cnr][1];
	clear(cnr);
	maintain(rt);
}
signed main()
{
	int n=read(),m=read(),lst_res=0,res=0;
	R(i,1,n) {
		int x=read();
		ins(x);
	}
	R(i,1,m)
	{
		int opt=read(),x=read()^lst_res;
		if(opt==1) ins(x);
		if(opt==2) del(x);
		if(opt==3) lst_res=find_rk(x);
		if(opt==4) lst_res=find_kth(x);
		if(opt==5) ins(x),lst_res=wei[find_lst()],del(x);
		if(opt==6) ins(x),lst_res=wei[find_nxt()],del(x);
		if(opt>=3) res^=lst_res;
	}
	printf("%lld\n",res);

}
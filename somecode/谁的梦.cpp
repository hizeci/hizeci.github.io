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
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
const int mod=19260817;
//const int mod=10007;
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


//#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;
    return x;
}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int N=2e5+10;
int n,m,inv2=9630409;
int len[N];
int F[N],inv[N];
struct pai
{
	int x,y,val;
	pai(int x_=0,int y_=0,int val_=0) {x=x_,y=y_,val=val_;}
}a[N];
int tot;

int s=1,cntcol;
set<int>S[N];
map<int,int>pos,census[N];
int ans,ret[N];
map<pii,int>vec;
set<int>::iterator it,l,r;
int cnt[N];

inline int calc(int x) {
	return x*(x+1)/2%mod;
}
inline void add(int &x,int y) {
	x+=y;
	x>=mod?x-=mod:1;
}
void init()
{
	F[0]=inv[0]=1;
	R(i,1,n) {
		F[i]=calc(len[i])*F[i-1]%mod;
		inv[i]=fpow(F[i],mod-2);
		R(j,1,len[i]) {
			a[++tot]=pai(i,j,read());
			if(!pos[a[tot].val]) pos[a[tot].val]=++cntcol;
			a[tot].val=pos[a[tot].val];
			S[a[tot].val].insert(tot);
			vec[mkp(i,j)]=tot;
		}
	}
	R(i,1,cntcol) {
		int x=0,y=0;
		ret[i]=1;
		for(it=S[i].bg;it!=S[i].ed;it++) {
			int p=*it;
			if(!x) ret[i]=ret[i]*F[a[p].x-1]%mod,add(census[i][a[p].x],calc(a[p].y-1));
			else if(x==a[p].x) add(census[i][a[p].x],calc(a[p].y-y-1));
			else {
				add(census[i][x],calc(len[x]-y));
				if(census[i][x]) ret[i]=ret[i]*census[i][x]%mod;
				else cnt[i]++;
				ret[i]=ret[i]*F[a[p].x-1]%mod*inv[x]%mod;
				add(census[i][a[p].x],calc(a[p].y-1));
			}
			x=a[p].x,y=a[p].y;
		}
		add(census[i][x],calc(len[x]-y));
		if(census[i][x]) ret[i]=ret[i]*census[i][x]%mod;
		else cnt[i]++;
		ret[i]=ret[i]*F[n]%mod*inv[x]%mod;
		add(ans,s-(cnt[i]?0:1)*ret[i]);
	}
	ans=(ans%mod+mod)%mod;
	printf("%lld\n",ans);
}
void modify(int c,int x,int y,int p,int opt){
	int L,R;
	l=S[c].lob(p),r=l;
	if(l==S[c].bg) L=0;
	else {
		l--,L=*l;
		if(a[L].x!=x) L=0;
		else L=a[L].y;
	}
	r++;
	if(r==S[c].ed) R=len[x];
	else {
		R=*r;
		if(a[R].x!=x) R=len[x];
		else R=a[R].y-1;
	}	
	if(opt&&R==len[x]&&!L) census[c][x]=calc(len[x]);
	ans-=s-(cnt[c]?0:1)*ret[c];
	if(census[c][x]) ret[c]=ret[c]*fpow(census[c][x],mod-2)%mod;
	else cnt[c]--;
	census[c][x]+=(opt?-1:1)*(calc(R-L)-calc(R-y)-calc(y-L-1));
	if(census[c][x]) ret[c]=ret[c]*census[c][x]%mod;
	else cnt[c]++;
	ans+=s-(cnt[c]?0:1)*ret[c];
}
void solve() {
	int x=read(),y=read(),d=read(),p=vec[mkp(x,y)],c=a[p].val;
	modify(c,x,y,p,0);
	S[c].erase(p);
	if(!pos[d]) pos[d]=++cntcol,ret[cntcol]=F[n];
	d=pos[d];
	a[p].val=d;
	S[d].insert(p);
	modify(d,x,y,p,1);
	ans=(ans%mod+mod)%mod;
	printf("%lld\n",ans);
}
signed main()
{
	n=read(),m=read();
	R(i,1,n) len[i]=read(),s=s*len[i]%mod*(len[i]+1)%mod*inv2%mod;
	init();
	while(m--)solve();

}
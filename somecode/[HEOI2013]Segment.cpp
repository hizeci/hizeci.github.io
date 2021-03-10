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
const int inf=0x7f7f7f7f7f7f7f3f;
//const int inf=0x7f7f7f7f;
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

//#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int mod1=39989;
const int mod2=1e9;
const int N=1e6+10;
typedef pair<double,int> pdi;
struct line
{
	double k,b;
}p[N];//1e5;
int n,lst_ans;
int tot_seg;
int s[N];//40000<<2
inline double calc(int id,int x){
	return p[id].k*x+p[id].b;
}
inline void add_seg(int sx,int sy,int tx,int ty){
	++tot_seg;
	if(sx==tx) p[tot_seg].k=0,p[tot_seg].b=max(sy,ty);//判断直线斜率为0的情况
	else p[tot_seg].k=1.0*(ty-sy)/(tx-sx),p[tot_seg].b=sy-p[tot_seg].k*sx;
}
void modify(int L,int R,int l,int r,int x,int u)
{
	int v=s[x],mid=(l+r)>>1;
	double resu=calc(u,mid),resv=calc(v,mid);
	if(L<=l&&r<=R){
		if(l==r) {
			if(resu>resv) s[x]=u;
			return;
		}
		if(p[u].k>p[v].k) 
		{
			if(resu>resv) {
				s[x]=u;
				modify(L,R,l,mid,x<<1,v);
			}
			else modify(L,R,mid+1,r,x<<1|1,u);
		}
		else if(p[u].k<p[v].k) {
			if(resu>resv) {
				s[x]=u;
				modify(L,R,mid+1,r,x<<1|1,v);
			}
			else modify(L,R,l,mid,x<<1,u);
		}
		else  {
			if(p[u].b>p[v].b) s[x]=u;
		}
		return;
	}
	if(L<=mid) modify(L,R,l,mid,x<<1,u);
	if(mid<R)  modify(L,R,mid+1,r,x<<1|1,u);
}
inline pdi PMax(pdi x,pdi y){
	return (x.fi<y.fi)?y:(x.fi>y.fi)?x:(x.se<y.se)?x:y;
}

inline pdi query_seg(int pos,int l,int r,int x){

	double res=calc(s[x],pos);	
	pdi ret={res,s[x]};
	if(l==r) return ret;
	int mid=(l+r)>>1;
//	printf("%d\n",mid);
	if(pos<=mid) ret=PMax(ret,query_seg(pos,l,mid,x<<1));
	if(mid<pos)  ret=PMax(ret,query_seg(pos,mid+1,r,x<<1|1));
	return ret;
/*
	if(r<pos||pos<l) return {0,0};
	int mid=(l+r)>>1;
	double res=calc(s[x],pos);
	if(l==r) return {res,s[x]};
	return PMax({res,s[x]},PMax(query_seg(pos,l,mid,x<<1),query_seg(pos,mid+1,r,x<<1|1)));
	*/
}	
signed main()
{
	n=read();
	R(i,1,n) {
		//R(i,1,10) printf("%.5lf %.5lf %lld\n",p[i].k,p[i].b,s[i]);
		int opt=read();
		if(!opt) {
			int x=read();
			x=(x+lst_ans-1+mod1)%mod1+1;
			lst_ans=query_seg(x,1,mod1,1).se;
			printf("qwq:%lld\n",x);
			printf("%lld\n",lst_ans);
		}
		if(opt){
			int sx=read(),sy=read(),tx=read(),ty=read();
			sx=(sx+lst_ans-1+mod1)%mod1+1;			
			tx=(tx+lst_ans-1+mod1)%mod1+1;
			sy=(sy+lst_ans-1+mod2)%mod2+1;
			ty=(ty+lst_ans-1+mod2)%mod2+1;
			if(sx>tx) Swap(sx,tx),Swap(sy,ty);
			printf("qwq:%lld %lld %lld %lld\n",sx,tx,sy,ty);
			add_seg(sx,sy,tx,ty);
			modify(sx,tx,1,mod1,1,tot_seg);
		}
	}
}
/*
3 
1 4 8 3 4
1 4 9 3 10
0 4
*/
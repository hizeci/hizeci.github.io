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
const int N=3e5+10;
struct insanderaset
{
	priority_queue<int>whl,del;
	int SEKAI;
	inline void ins(int x) {whl.push(x);}
	inline void era(int x) {del.push(x);}
	inline int one() {
		while((int)del.size()>0&&whl.top()==del.top()) del.pop(),whl.pop();
		return whl.top()+SEKAI;
	}
	inline void clr() {
		priority_queue<int>emp1,emp2;
		swap(whl,emp1),swap(del,emp2);
	}
}num[N],all;
std::vector<int>pos[N];
int n,m;
int a[N],fa[N];
inline int find_fa(int x){
	return x==fa[x]?x:fa[x]=find_fa(fa[x]);
}
void mer(int x,int y){
	x=find_fa(x),y=find_fa(y);
	if(x==y) return;
	if((int)pos[x].size()<(int)pos[y].size()) Swap(x,y);
	all.era(num[x].one()),all.era(num[y].one());
	for(int i:pos[y]) {
		fa[i]=x;a[i]+=num[y].SEKAI-num[x].SEKAI;
		num[x].ins(a[i]);pos[x].pb(i);
	}
	pos[y].clear();
	all.ins(num[x].one());
	num[y].clr();
}
char opt[111];
signed main()
{
	n=read();
	R(i,1,n) {
		a[i]=read();
		num[i].ins(a[i]);
		all.ins(a[i]);
		pos[i].pb(i);
		fa[i]=i;
	}
	m=read();
	R(i,1,m) {
		scanf("%s",opt+1);
		int x,y;
		if(opt[1]=='U') {
			x=read(),y=read();
			mer(x,y);
		}
		if(opt[1]=='A'){
			if(opt[2]=='1'){
				x=read(),y=read();
				int tmp=a[x];
				a[x]+=y;
				x=find_fa(x);
				all.era(num[x].one());
				num[x].era(tmp);
				num[x].ins(tmp+y);
				all.ins(num[x].one());
			}
			if(opt[2]=='2'){
				x=read(),y=read();
				x=find_fa(x);
				all.era(num[x].one());
				num[x].SEKAI+=y;
				all.ins(num[x].one());
			}
			if(opt[2]=='3') {
				x=read();
				all.SEKAI+=x;
			}
		}
		if(opt[1]=='F') {
			if(opt[2]=='1')
			{
				x=read();
				int tmp=a[x];
				x=find_fa(x);
				tmp+=num[x].SEKAI;
				tmp+=all.SEKAI;
				printf("%lld\n",tmp);
			}
			if(opt[2]=='2') {
				x=read();
				x=find_fa(x);
				printf("%lld\n",num[x].one()+all.SEKAI);
			}
			if(opt[2]=='3') {
				printf("%lld\n",all.one());
			}
		}

	}	
}
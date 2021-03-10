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
//const int mod=10007;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}

const int qwq=2000010;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=1ll*(F[i-1]*i)%mod,Finv[i]=1ll*(Finv[i-1]*inv[i])%mod;
}

inline int C(int n,int m){ if(m<0||m>n||n<0) return 0;return 1ll*F[n]%mod*1ll*Finv[m]*1ll%mod*1ll*Finv[n-m]%mod;}


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
/*
考虑整数唯一分解定理
N=A1^P1*A2^P2*A3*P3*...*Aqwq^Pqwq
且由于互质所以每个S中的数均为A_m^P_m*A_q^P_q次 
且质因数数量不会超过18 (不然大概炸long long)(2*3*5*7*..*)<LONG_LONG_MAX
那么考虑直接装压dp
*/
const int N=550;

int n,m;
int a[N];
int dp[262150];
int p[N][20],q[N][20];
int div_pri[262150];
int cnt_div_pri[262150];
int zhi_div_pri[262150];
int tot_pri=0,uiqtot;
map<int,int>mp;

inline int check_div_pri(int i,int x){
	for(int num=2;num*num<=x;num++) {
		if(x%num==0) {
			p[i][++cnt_div_pri[i]]=num;
			div_pri[++tot_pri]=num;
			while(x%num==0) x/=num,q[i][cnt_div_pri[i]]++;
		}
	}
	if(x>1) p[i][++cnt_div_pri[i]]=x,q[i][cnt_div_pri[i]]=1,div_pri[++tot_pri]=x;
}
/*
42 8
1 2 3 6 7 14 21 42
*/

signed main() {
	//freopen("division.in","r",stdin);
	//freopen("division.out","w",stdout);
	cout<<(1ll<<20);
	n=read(),m=read(); 
	R(i,1,m) {
		int x=read();
		check_div_pri(i,x);
	}

	R(i,1,tot_pri) {//去重
		if(n%div_pri[i]==0&&mp[div_pri[i]]==0) {
			div_pri[++uiqtot]=div_pri[i],mp[div_pri[i]]=uiqtot;
			while(n%div_pri[uiqtot]==0) n/=div_pri[uiqtot],zhi_div_pri[uiqtot]++;
		}
	}
	//printf("uni:%lld\n",uiqtot); R(i,1,10) printf("pri:%lld cnt:%lld zhi:%lld\n",div_pri[i],cnt_div_pri[i],zhi_div_pri[i]);
	//R(i,1,10) R(j,1,10) if(p[i][j]||q[i][j]) printf("p:%lld q:%lld\n",p[i][j],q[i][j]);
	if((n^1)) return puts("0")&0;
	dp[0]=1;
	R(i,1,m) {
		int mask=0,ok=1;
		R(j,1,cnt_div_pri[i]){
			int num=mp[p[i][j]];
			if(num&&zhi_div_pri[num]==q[i][j]) mask|=(1ll<<(num-1));
			else {
				//printf("%lld %lld\n",i,j);
				ok=0;
				break;
			}
		} 
		if(ok) {
			L(ano,0,(1<<uiqtot)-1) {//避免重复计算
				//printf("%lld %lld\n",mask,ano);
				if(!(mask&ano)) dp[ano|mask]+=dp[ano];
			}
		}
	}
	printf("%lld\n",dp[(1ll<<uiqtot)-1]);
}
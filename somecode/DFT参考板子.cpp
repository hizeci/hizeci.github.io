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
//const int mod=1e9+7;
const int mod=998244353;
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
inline void write(int x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(int x){write(x),putchar(' ');}
inline void writeln(int x){write(x);putchar('\n');}
/*
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0, 10000000);  // ¸ø¶¨·¶Î§
printf("%lld ",dist(rand_num));
*/
const int N=1351111;
const double Pi=acos(-1);
int n,m;
struct CP
{
	double x,y;
	CP(double xx=0,double yy=0){x=xx,y=yy;}
	CP operator + (CP const &a)const {
		return CP(x+a.x,y+a.y);
	}
	CP operator - (CP const &a)const{
		return CP(x-a.x,y-a.y);
	}
	CP operator * (CP const &a)const{
		return CP(x*a.x-y*a.y,x*a.y+y*a.x);
	}
	CP operator / (CP const &a)const{
		double t=a.x*a.x-a.y*a.y;
		return CP((x*a.x+y*a.y)/t,(y*a.x-x*a.y)/t);
	}
}f[N<<1],sav[N<<1];
void dft(CP *f,int len) 
{
	if(len==1) return;
	CP *fl=f,*fr=f+len/2;
	R(k,0,len-1) sav[k]=f[k];
	R(k,0,len/2-1) fl[k]=sav[k<<1],fr[k]=sav[k<<1|1];
	dft(fl,len/2);dft(fr,len/2);
	//由于每次使用的单位根次数不同(len次单位根),所以要重新求。
	CP tG(cos(2*Pi/len),sin(2*Pi/len)),buf(1,0);
	R(k,0,len/2-1) 
	{
		//这里buf = (len次单位根的第k个)
		sav[k]=fl[k]+buf*fr[k];//(1)
		sav[k+len/2]=fl[k]-buf*fr[k];//(2)
		//这两条语句具体见Tips的式子
		buf=buf*tG;
	}
	R(k,0,len-1) f[k]=sav[k];
}
signed main() 
{
	n=read();
	R(i,0,n-1) scanf("%lf",&f[i].x);
	for(m=1;m<n;m<<=1);
	dft(f,m);
	R(i,0,m-1) printf("(%.4f,%.4f)\n",f[i].x,f[i].y);
}
//tips:
//(1)F(\omega_n^{k+n/2})=FL(\omega_{n/2}^k)-\omega_n^kFR(\omega_{n/2}^k)
//(2)F(\omega_n^k)=FL(\omega_{n/2}^k)+\omega_n^kFR(\omega_{n/2}^k)
//现在问题来了,DFT输出的都是些杂乱的点值表达,所以解决不了问题。
//上文说过,IDFT是DFT的逆(CP),她可以把点值还原成多项式,最终完成乘法。
/*
求omega
struct CP
{
  CP (double xx=0,double yy=0){x=xx,y=yy;}
  double x,y;
  CP operator + (CP const &B) const
  {return CP(x+B.x,y+B.y);}
  CP operator - (CP const &B) const
  {return CP(x-B.x,y-B.y);}
  CP operator * (CP const &B) const
  {return CP(x*B.x-y*B.y,x*B.y+y*B.x);}
  //除法没用
}w[Maxn];
//w长得是不是很像ω?
int n;
int main()
{
  scanf("%d",&n);
  CP sav(cos(2*Pi/n),sin(2*Pi/n)),buf(1,0);
  for (int i=0;i<n;i++){
    w[i]=buf;
      buf=buf*sav;
  }
  for (int i=0;i<n;i++)
      printf("w[%d][n]=(%.4lf,%.4lf)\n",i,w[i].x,w[i].y);
  //由于精度问题会出现-0.0000的情况,将就看吧
  return 0;
}
*/
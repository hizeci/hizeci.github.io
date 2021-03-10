#include<bits/stdc++.h>
#define lb long double
#define db double
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
const db eps=1e-8;
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
namespace task1//BC
{
	int mon[20],g[5050];
	inline void init() {
		R(i,1,4713) g[i]=365+(i%4==1);
		R(i,1,4713) g[i]+=g[i-1];
	}
	void solve(int x)
	{
		int pos=lob(g+1,g+4713+1,x)-g;
		int yea=4714-pos,mth,dy;
		x-=g[pos-1];
		mon[1]=31,mon[2]=28+(yea%4==1),mon[3]=31,mon[4]=30,mon[5]=31,mon[6]=30,mon[7]=31,mon[8]=31,mon[9]=30,mon[10]=31,mon[11]=30,mon[12]=31;
		R(i,1,12) mon[i]+=mon[i-1];
		R(i,1,12) if(mon[i]>=x) {mth=i;dy=x-mon[i-1];break;}
		printf("%lld %lld %lld BC\n",dy,mth,yea);
	}	
}
namespace task2//before 1582.10.4
{
	int g[2020],mon[20];
	inline void init() {
		R(i,1,1582) g[i]=365+(i%4==0);
		R(i,1,1582) g[i]+=g[i-1];
	}
	void solve(int x)
	{
		int yea=lob(g+1,g+1582+1,x)-g,mth,dy;
		x-=g[yea-1];
		mon[1]=31,mon[2]=28+(yea%4==0),mon[3]=31,mon[4]=30,mon[5]=31,mon[6]=30,mon[7]=31,mon[8]=31,mon[9]=30,mon[10]=31,mon[11]=30,mon[12]=31;
		R(i,1,12) mon[i]+=mon[i-1];
		R(i,1,12) if(mon[i]>=x) {mth=i,dy=x-mon[i-1];break;}
		printf("%lld %lld %lld\n",dy,mth,yea);
	}
}
namespace task3
{
	int mon[20];
	inline int get_sum(int yea){
		return 365*yea+(yea/4)-(yea/100)+(yea/400)+12;
	}
	inline int check_yea(int yea){
		return (yea%400==0)||(yea%4==0&&yea%100!=0);
	}
	void solve(int x)
	{			
		int yea,mth,dy;
		if(x<=577825)//1582
		{	
			yea=1582;
			x-=577460;		
			mon[1]=31,mon[2]=28+(yea%4==0),mon[3]=31,mon[4]=30,mon[5]=31,mon[6]=30,mon[7]=31,mon[8]=31,mon[9]=30,mon[10]=31,mon[11]=30,mon[12]=31;
		}
		else
		{
			int l=1583,r=(int)1e9;
			while(r-l>=44) 
			{
				int mid=(l+r)>>1;
				if(get_sum(mid)>=x) r=mid-1;
				else l=mid+1,yea=mid+1;
			}
			L(i,l-10,r+10) if(get_sum(i)<x) {yea=i+1;break;}
			x-=get_sum(yea-1);
			mon[1]=31,mon[2]=28+check_yea(yea),mon[3]=31,mon[4]=30,mon[5]=31,mon[6]=30,mon[7]=31,mon[8]=31,mon[9]=30,mon[10]=31,mon[11]=30,mon[12]=31;	
		}
		R(i,1,12) mon[i]+=mon[i-1];
		R(i,1,12) if(mon[i]>=x) {mth=i,dy=x-mon[i-1];break;}
		printf("%lld %lld %lld\n",dy,mth,yea);
	}
}
signed main()
{
	task1::init(),task2::init();
	int q=read();
	R(i,1,q) {
		int n=read()+1;
		if(n<=1721424) task1::solve(n);
		//2000000
		else
		{
			n-=1721424;
			if(n<=577737) task2::solve(n);
			else n+=10,task3::solve(n);
		}
	}
}
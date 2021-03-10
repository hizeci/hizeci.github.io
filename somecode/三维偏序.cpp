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
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define us unsigned 
#define ll long long
#define ull unsigned long long
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }
using namespace std;
//const int inf=0x7f7f7f7f7f7f7f3f;
const int inf=0x7f7f7f7f;
//const int mod=1e9+7;
const double Pi=acos(-1);
const int mod=3e9+24;
const ld eps=1e-8;
inline int fpow(int a,int b=mod-2,int p=mod){int res=1;while(b){if(b&1)res=res*a%p;a=a*a%p;b>>=1;}return res;}
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
int n,k,sz;
int a[111111],b[111111],c[111111];
int ans[111111],cnt[111111],len,ln[22],nl;
int BiT[444444];
struct ques
{
	int x,y,id;
	inline int operator < (const ques &A)const{return x<A.x;}
}cur[111111],arr[22][111111],nwt[111111];
std::vector<ques>v[222222];
inline void upd(int x,int y){for(int i=x;i<=sz;BiT[i]+=y,i+=i&(-i));}
inline int qry(int x){int ret=0;for(int i=x;i>=1;ret+=BiT[i],i-=i&(-i));return ret;}
void calc(vector<ques> &v)
{
	if((int)v.size()==0) return;
	sort(v.begin(),v.end());
	int pos=0;
	R(i,0,(int)v.size()-1)
	{
		for(;pos<(int)v.size()&&v[pos].x<=v[i].x;upd(v[pos].y,1),pos++); 
		ans[v[i].id]=qry(v[i].y);
	}
	R(i,0,(int)v.size()-1) upd(v[i].y,-1); 
}
void solve(int l,int r,int dep)
{
	if(l==r) 
	{
		len=v[l].size();
		R(i,0,len-1) cur[i+1]=v[l][i];
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid,dep+1);
	R(i,1,len) arr[dep][i]=cur[i];
	ln[dep]=len;
	solve(mid+1,r,dep+1);
	int la=1,lb=1;nl=0;
	while(la<=ln[dep]&&lb<=len) 
	{
		if(arr[dep][la].x<=cur[lb].x) 
		{
			nwt[++nl]=arr[dep][la];
			upd(arr[dep][la].y,1);
			la++;
		}
		else
		{
			nwt[++nl]=cur[lb];
			ans[cur[lb].id]+=qry(cur[lb].y);
			lb++;
		}
	} 
	while(la<=ln[dep]) 
	{
		upd(arr[dep][la].y,1);
		nwt[++nl]=arr[dep][la];
		la++;
	}
	while(lb<=len)
	{		
		nwt[++nl]=cur[lb];
		ans[cur[lb].id]+=qry(cur[lb].y);
		lb++;
	}
	R(i,1,la-1) upd(arr[dep][i].y,-1);
	len=nl;
	R(i,1,len) cur[i]=nwt[i];
}
signed main()
{
	n=read(),k=read();
	for(sz=1;sz<k;sz<<=1);
	R(i,1,n) {a[i]=read(),b[i]=read(),c[i]=read(),v[a[i]].push_back((ques){b[i],c[i],i});}
	R(i,1,k) calc(v[i]);
	solve(1,k,0);
	R(i,1,n) cnt[ans[i]]++;
	R(i,1,n) printf("%lld\n",cnt[i]);
}
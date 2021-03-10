#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=1e8-3;
const ld eps=1e-8;
inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
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
const int N=1e6+10;
struct node
{
	int id,hg;
	inline bool operator <(const node a)const{
		return hg<a.hg;
	}
}a[N],b[N];
int n;
int res;
int tmp[N];
int mp[N];
void gbst(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	gbst(l,mid),gbst(mid+1,r);
	int i=l,cnt=l-1,j=mid+1;
	while(i<=mid&&j<=r) if(mp[i]<=mp[j]) tmp[++cnt]=mp[i++];else tmp[++cnt]=mp[j++],res+=(mid-i+1),res%=mod;
	while(i<=mid) tmp[++cnt]=mp[i++];
	while(j<=r)   tmp[++cnt]=mp[j++];
	for(i=l;i<=r;i++) mp[i]=tmp[i]; 
}
signed main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	n=read();
	R(i,1,n) a[i].hg=read(),a[i].id=i;
	R(i,1,n) b[i].hg=read(),b[i].id=i;
	sort(a+1,a+n+1),sort(b+1,b+n+1);
	R(i,1,n) mp[b[i].id]=a[i].id;
	gbst(1,n);
	printf("%lld\n",res);
}
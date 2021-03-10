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
const int mod=19930726;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
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
const int N=2e6+10;
char a[N],s[N];
int n,k,len;
int hw[N];
int res=1,sum;
map<int,int>mp;
inline int fpow(int a,int b){
	int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;
}
signed main()
{
	len=n=read(),k=read();
	scanf("%s",a+1);
	s[0]='$';
	for(int i=1;i<=len;i++) s[i*2-1]='#',s[i*2]=a[i];
	s[len=len*2+1]='#';
	int mid,mxright=0;
	for(int i=1;i<=len;i++) 
	{
		if(i<mxright) hw[i]=min(hw[(mid<<1)-i],hw[mid]+mid-i);
		else hw[i]=1;
		while(s[i+hw[i]]==s[i-hw[i]]) hw[i]++;
		if(hw[i]+i>mxright) mxright=hw[i]+i,mid=i;
		if(hw[i]%2==0) ++mp[hw[i]-1];
	}
	if(n%2==0) n--;
	for(int i=n;i>=1&&k>0;i-=2) 
	{
		sum+=mp[i];
		res*=fpow(i,min(k,sum)),res%=mod,k-=sum;
	}
	if(k>0) res=-1;
	printf("%lld\n",res);
}

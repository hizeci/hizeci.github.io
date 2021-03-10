#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb push_back
#define pii pair<int,int> 
#define mkp make_pair
#define us unsigned 
#define int long long
using namespace std;
const int inf=1e18+100;
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
const int N=1010;
struct bignum
{
	int num[N],len;
}a,b,c;
char s[N];
void add(bignum a,bignum b,bignum &c)
{
	c.len=max(a.len,b.len)+100;
	for(int i=1;i<=c.len;i++)
	{
		c.num[i]+=a.num[i]+b.num[i];
		c.num[i+1]+=c.num[i]/10;
		c.num[i]%=10;
	}
}
void jian(bignum a,bignum b,bignum &c)
{
	c.len=max(a.len,b.len)+100;
	for(int i=1;i<=c.len;i++)
	{
		if(a.num[i]<b.num[i]) a.num[i]+=10,a.num[i+1]-=1;
		c.num[i]+=a.num[i]-b.num[i];
	}	
} 
void times(bignum a,bignum b,bignum &c)
{
	
}
signed main()
{
	scanf("%s",s+1);
	a.len=strlen(s+1);
	for(int i=1;i<=a.len;i++) a.num[i]=s[a.len-i+1]-'0';
	scanf("%s",s+1);
	b.len=strlen(s+1);
	for(int i=1;i<=b.len;i++) b.num[i]=s[b.len-i+1]-'0';
	//add(a,b,c);
	jian(a,b,c);
	while(c.len>1&&c.num[c.len]==0) c.len--;
	for(int i=c.len;i;i--) printf("%lld",c.num[i]);
}
	 

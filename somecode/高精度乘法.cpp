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
const int N=2021;
char s[N];
int a[N],b[N],c[N];

signed main()
{
	scanf("%s",s+1);
	int lena=strlen(s+1);
	for(int i=1;i<=lena;i++) a[i]=s[lena-i+1]-'0';
	scanf("%s",s+1);
	int lenb=strlen(s+1);
	for(int i=1;i<=lenb;i++) b[i]=s[lenb-i+1]-'0';
	for(int i=1;i<=lena;i++)
	{
		int x=0;
		for(int j=1;j<=lenb;j++)
		{
			c[i+j-1]+=a[i]*b[j]+x;
			x=c[i+j-1]/10;
			c[i+j-1]%=10; 
		}
		c[i+lenb]=x;
	}	
	int lenc=lena+lenb;
	while(lenc&&c[lenc]) lenc--;
	for(int i=lenc;i>=1;i--) printf("%lld",c[i]); 
}

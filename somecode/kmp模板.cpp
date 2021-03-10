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
const int N=1e6+10;
int nxt[N];
char a[N],b[N];
int lena,lenb;

signed main()
{
	scanf("%s%s",a+1,b+1);
	int lena=strlen(a+1),lenb=strlen(b+1);
	for(int i=2,j=0;i<=lenb;i++)
	{
		while(j&&b[i]!=b[j+1]) j=nxt[j];
		if(b[i]==b[j+1]) j++;
		nxt[i]=j;
	}		
	for(int i=1,j=0;i<=lena;i++)
	{
		while(j&&a[i]!=b[j+1]) j=nxt[j];
		if(a[i]==b[j+1]) j++;
		if(j==lenb) {printf("%lld\n",i-lenb+1);j=nxt[j];}
	}
	for(int i=1;i<=lenb;i++) printf("%lld ",nxt[i]);
} 

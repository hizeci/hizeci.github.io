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
char s[N]; 
int nxt[N];
int n;
int _;

signed main()
{
	while(scanf("%lld",&n)==1)
	{
		if(!n) break;
		scanf("%s",s+1);		
		printf("Test case #%lld\n",++_);
		for(int i=2,j=0;i<=n;i++)	
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;
			nxt[i]=j;
			//printf("%lld %lld\n",i,j);
		}
		for(int i=1;i<=n;i++)
		{
			if((i%(i-nxt[i])==0)&&nxt[i])
				printf("%lld %lld\n",i,i/(i-nxt[i]));
		}
		puts("");
	}	
}

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
const int N=4e5+10;
char a[N],s[N<<1];
int n,hw[N],res=1;

inline void init_mana(int &n){
	s[0]='~';s[1]='#';int cnt=1;
	for(int i=1;i<=n;i++) s[++cnt]=a[i],s[++cnt]='#';
	n=(n<<1)+2;s[n]=0;
}
void mana()
{
	int mxright=0,mid;//目前所触及最右边，当前包含mxright的对称轴 
	for(int i=1;i<=n;i++)
	{
		        		              //j 
		if(i<mxright) hw[i]=min(hw[(mid<<1)-i],hw[mid]+mid-i);else hw[i]=1;
		while(s[i+hw[i]]==s[i-hw[i]]) hw[i]++;
		if(hw[i]+i>mxright) mxright=hw[i]+i,mid=i; 
	} 
}

signed main()
{
	scanf("%s",a+1);
	n=strlen(a+1);
	init_mana(n);
	mana();
	//for(int i=1;i<=n;i++) res=max(res,hw[i]);printf("%lld\n",res-1);
	for(int i=1;i<=n;i++) res+=hw[i]/2;
	printf("%lld\n",res-1);
}

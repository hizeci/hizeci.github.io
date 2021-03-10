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
//#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
//const int inf=0x7f7f7f7f7f7f;
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
const int N=2e5+10;
char s[N][120];
int n;
struct Trie
{
	int tot,tr[N*110][30],val[N*110];
	void ins(char *s)
	{
		int now=1;
		for(;*s;s++){
			int tmp=*s-'a';
			if(!tr[now][tmp]) tr[now][tmp]=++tot;
			now=tr[now][tmp];
		}
		val[now]++;
	}
	int query(char *s)
	{
		int now=1;
		for(;*s;s++)
		{
			int tmp=*s-'a';
			if(!tr[now][tmp]) return 0;
			now=tr[now][tmp];
		}
		if(val[now]) return 1;
		return 0;
	}
	int find_word(char *s)
	{
		int now=1;
		for(int i=0;s[i];i++)
		{
			int tmp=s[i]-'a';
			if(!tr[now][tmp]) break;
			now=tr[now][tmp];
			if(val[now]&&s[i+1])
			{
				char qwq[110];
				for(int j=0;j<=105;j++) qwq[j]=0;
				for(int j=i+1;s[j];j++) qwq[j-(i+1)]=s[j];
				if(query(qwq)) return 1;
			}
		}
		return 0;
	}
}t;
signed main()
{
	while(scanf("%s",s[++n])) {t.ins(s[n]);}
	for(int i=1;i<=n;i++) if(t.find_word(s[i])) printf("%s\n",s[i]);
}
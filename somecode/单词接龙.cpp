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
const int N=22;
string s[N];
int vis[N];
int n,mxlen;
int get_len(string s,string t)
{
	int milen=max(s.size(),t.size());
	int ok;
	for(int i=1;i<milen;i++) 
	{
		ok=1;
		for(int j=0;j<i;j++) if(s[s.size()-i+j]!=t[j]) ok=0;
		if(ok) return i;
	}
	return 0;
}
void dfs(int num,int len,int cnt)
{
	if(cnt==2*n) {mxlen=max(mxlen,len);return;} 
	int ok=0;
	for(int i=0;i<n;i++)
	{
		if(vis[i]!=2) 
		{		
			int tmp=get_len(s[num],s[i]);
			if(tmp)
			{
				ok=1;
				vis[i]++;
				dfs(i,len+s[i].size()-tmp,cnt+1);
				vis[i]--;
			} 
		}
	}
	if(!ok) mxlen=max(len,mxlen);
}
signed main()
{
	n=read();
	for(int i=0;i<=n;i++) cin>>s[i];
	//printf("%lld\n",get_len(s[1],s[2]));
	dfs(n,0,0);
	printf("%lld\n",mxlen+1);
} 
/*
5
at
touch
cheat
choose
tact
a
*/


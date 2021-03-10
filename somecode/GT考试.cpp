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
int mod;
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
const int N=30;
int n,m;
char s[N];
int nxt[N];
//dp[i][j]=\sum dp[i-1][k]*g[k][j]
//g[k][j]表示为从K转移到J的方案数
//将dp数组的每一行抽象为一个矩阵F[i],有F[i]=F[i-1]*G;
//F[N]=F[0]*G^n
struct Matrix
{
	int mat[N][N];
	Matrix(){memset(mat,0,sizeof(mat));}
}G,F;
Matrix operator * (Matrix a,Matrix b){
	/*
	Matrix res;
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<m;k++)
				Add(res.mat[i][j],a.mat[i][k]*b.mat[k][j]);
	*/
	Matrix res;
	int r;
	FR(i,0,m)
		FR(k,0,m)
		{
			int r=a.mat[i][k];
			FR(j,0,m)
				res.mat[i][j]+=r*b.mat[k][j],res.mat[i][j]%=mod;
		}
	return res;
		
}
Matrix fpow(Matrix a,int b)
{
	Matrix res;
	R(i,0,m) res.mat[i][i]=1;
	//
	while(b)
	{	
		//R(i,1,m) R(j,1,m) printf("%lld",a.mat[i][j]);puts("");	
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
signed main()
{
	n=read(),m=read(),mod=read();
	scanf("%s",s+1);
	int j=0;
	R(i,2,m)
	{
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
//		printf("%lld\n",nxt[i]);
	}
	FR(i,0,m)
	{
		R(ch,'0','9')
		{
			int j=i;
			while(j&&s[j+1]!=ch) j=nxt[j];
			if(ch==s[j+1]) j++;
			Add(G.mat[i][j],1);
			//G.mat[i][j]++,G.mat[i][j]%=mod;
		}	
	}
	G=fpow(G,n);	
	//for(int i=0;i<m;i++) {for(int j=0;j<m;j++) printf("%lld ",G.mat[i][j]);puts("");};
	F.mat[0][0]=1;
	F=F*G;
	int sum=0;
	FR(i,0,m) sum+=F.mat[0][i],sum%=mod;//Add(sum,F.mat[0][i]);
	printf("%lld\n",sum);
}
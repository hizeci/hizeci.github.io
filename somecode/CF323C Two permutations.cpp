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
//const int mod=9223372036854775807;
const ld eps=1e-8;
//inline int fpow(int a,int b){int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
/*
const int qwq=5050;
int F[qwq],inv[qwq],Finv[qwq];
void init_C()
{
    F[0]=Finv[0]=inv[1]=1;
    R(i,2,qwq-10) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    R(i,1,qwq-10) F[i]=(F[i-1]*i)%mod,Finv[i]=(Finv[i-1]*inv[i])%mod;
}
inline int C(int n,int m){ if(m<0||m>n) return 0;return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;}
*/
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
/*
二维数点问题
考虑在第i时刻维护前i行有哪些列有点
每次单点修改 ，用主席树
答案就是r1时刻的线段树[l2,r2]的和-(l1-1)时刻[l2,r2]的和
*/
const int N=1e6+10;
int a[N],b[N];
int val[N<<5],Ls[N<<5],Rs[N<<5],Rt[N];
int tot_seg;
int n,m;
int lst_ans;
inline int get_tr(int x){
	return ((x-1+lst_ans)%n)+1;
}
int build(int l,int r)
{
	//printf("%lld %lld\n",l,r);
	int rt=++tot_seg;
	val[rt]=0;
	if(l==r) return rt;
	int mid=(l+r)>>1;
	Ls[rt]=build(l,mid);
	Rs[rt]=build(mid+1,r);
	return rt;
}
int modify(int pos,int l,int r,int x)
{
	int rt=++tot_seg;
	Ls[rt]=Ls[pos],Rs[rt]=Rs[pos],val[rt]=val[pos]+1;
	//printf("%lld\n",rt);
	if(l==r) return rt;
	int mid=(l+r)>>1;
	if(x<=mid) Ls[rt]=modify(Ls[pos],l,mid,x);
	else Rs[rt]=modify(Rs[pos],mid+1,r,x);
	return rt;
}
int query(int L,int R,int l,int r,int x)
{
	if(L<=l&&r<=R) return val[x];
	int mid=(l+r)>>1,ret=0;
	if(L<=mid) ret+=query(L,R,l,mid,Ls[x]);
	if(mid<R)  ret+=query(L,R,mid+1,r,Rs[x]);
	return ret;
}
signed main()
{
	n=read();
	R(i,1,n) b[read()]=i;
	R(i,1,n) a[i]=b[read()];
	Rt[0]=build(1,n);
	R(i,1,n) Rt[i]=modify(Rt[i-1],1,n,a[i]);
	m=read();
	//R(i,0,n) printf("%d\n",Rt[i]);
	while(m--)
	{
		/*
		int l1=read(),r1=read(),l2=read(),r2=read();
		printf("lastans:%d\n%d %d %d %d\n",lst_ans,l1,r1,l2,r2);
		l1=f(l1),r1=f(r1),l2=f(l2),r2=f(r2);
		printf("lastans:%d\n%d %d %d %d\n",lst_ans,l1,r1,l2,r2);
		if(l1>r1) swap(l1,r1); if(l2>r2) swap(l2,r2);
		//l1=2,r1=3,l2=1,r2=4;
		printf("lastans:%d\n%d %d %d %d\n",lst_ans,l1,r1,l2,r2);
		*/
		int a=read(),b=read(),c=read(),d=read();
		int e=min(get_tr(a),get_tr(b)),f=max(get_tr(a),get_tr(b)),g=min(get_tr(c),get_tr(d)),h=max(get_tr(c),get_tr(d));
		printf("%d\n",lst_ans=query(e,f,1,n,Rt[h])-query(e,f,1,n,Rt[g-1]));
		lst_ans++;
	}
	return 0;
}
